## What is ScyllaDB
- Real time big-data DB
- Drop in replacement for Cassandra and Dynamodb
- 10X performance. Low tail latency
    - Closer to the hardware. Built on C++.
    - Completely asynchronous, avoid contention.
    - Low node count. But...Uses bigger and better nodes
    - eg: 900+ Cassandra nodes --> 70 Scylla Nodes
    - No JVM, no garbage collector, no stop-the-world, no latency spikes
    - Less complexity. Best performance out of the box. Not much tuning required. Smaller footprint, self-optimizing.
    - Throughput 10X higher than Cassandra
    - Linear scalability to many-core machinesj
    - Focussed on modern fast SSDs

## ScyllaDB Architecture
- distributed concepts derived from cassandra
- cassandra in-turn derived distributed concepts from DynamoDB... and data modelling concepts from BigTable.

#### Node

#### Shard 

#### Partition
A Partition is a subset of Data .
Partition Key is the unique identifier for a partition. Hash of partitionKey = Token. 


#### Ring
Scylla cluster = nodes visualised as a RING. 

#### Token/Token-Range
Token = hashed primary key. 
A Token identifies both node and the partition. 


#### Shared-Nothing Architecture

#### Keyspaces
Keyspaces are collection of tables. You define `replicationFactor` at the Keyspace level. "Keyspace" is analogous to "Database" in RDBMS.

#### Partition Key & Clustering Key 
Partition Key uniquely identifies a partition. 

#### Joins are impossible 
TODO




## Tasks


### Uninstalling Temporal
Comment out `- ./helm-release.yaml` in temporal/kustomization.yaml

### Uninstalling Scylladb
Comment out `- ./scylla-helm-release.yaml` in temporal/kustomization.yaml
Delete the PVs and PVCs manually for the scylla pods to terminate.

### Find the data volume( & available free space) size of each scylladb node
SSH into one of the scylladb pod
run `df -h` and find the entry associated with `/var/lib/scylla`. 

### Increasing the replicationFactor of a scylladb keyspace
Read this for overview on replicationFactor https://www.scylladb.com/2018/08/28/scylla-fault-tolerance/.

If there is just one scylladb node, replicationFactor has to be 1
If there are just two scylladb nodes, replicationFactor has to be <=2
If there are 3 or more scylladb nodes, replicationFactor can be 3 (ideal)

SSH into a scylladb pod.
Find the existing replicationFactor
```cql
cqlsh -e "DESCRIBE KEYSPACE temporal" | grep replication_factor
cqlsh -e "DESCRIBE KEYSPACE temporal_visibility" | grep replication_factor
```

Say you want to update replicationFactor from 2->3. run `cqlsh`
```cql
ALTER KEYSPACE temporal WITH REPLICATION={'class': 'SimpleStrategy', 'replication_factor': '3'} ;
ALTER KEYSPACE temporal_visibility WITH REPLICATION={'class': 'SimpleStrategy', 'replication_factor': '3'} ;
```
Run repair on relevant keyspaces.
```sh
nodetool repair --full temporal_visibility
nodetool repair --full temporal
```

### Wiping out Scylladb without deleting scylladb nodes
How to wipe out all data and delete all schemas without getting rid of scylladb pods and associated volumes.

Make sure all temporal workflows are "Completed", nothing is in "Running" state. You can either wait for them to end or terminate them all.

Run the following after SSH'ing into `temporal-admin-tools` pod in `temporal` K8s namespace.
```sh
# Check how many workflows are currently Running
tctl --ns test workflow count --query 'ExecutionStatus="Running"'
tctl --ns test workflow list --query 'ExecutionStatus="Running"'

# Terminate all the "Running" workflows
tctl --ns test batch start --query 'ExecutionStatus="Running"' --batch_type terminate --reason "Terminate all workflows for total cleanup

# verify that all workflows have terminated
tctl --ns test workflow count --query 'ExecutionStatus="Running"'
```
Make sure to check that no workflow is "Running" on the temporal web-UI.

Next, drop the temporal keyspaces on scylladb. Run `cqlsh` after SSH'ing into one of the scylladb pods in `scylla` K8s namespace
```sh
describe keyspaces
drop keyspace temporal_visibility
drop keyspace temporal
```
Delete snapshots if any. Exit cqlsh
```sh
nodetool listsnapshots
nodetool clearsnapshot
```
Monitor the `nodetool status` output to check that the size is gradually decreasing. Keyspace deletion is an asychronous job.


### Bootstrapping Temporal from scratch on K8s
Temporal requires
- scylladb
- elasticsearch (AWS Opensearch)

If you are re-installing Temporal, you can use the existing elasticsearch index created during previous Temporal bootstrap.
Hence you need to **delete the job** called `es-index-setup` and bypass the step of creating elasticsearch index. Only after deleting this job, you will see the next jobs called `schema-setup` and `schema-update`. These will install the required NoSQL schemas on scyllaDB as required by Temporal. 

Make sure you have wiped out scylladb (data + schema) before doing this. You dont have to worry if the scylladb nodes are brand new.

Post this, make sure to add required namespaces via admin tools. See the section "Adding a new namespace on Temporal"

### Adding a new namespace on Temporal
SSH into `temporal-admin-tools` pod

List existing namespaces
```sh
tctl namespace list
```

Add a new namespace
```sh
tctl --ns <namespace_name> namespace register --gd false --history_archival_state enabled
```

### Draining Temporal of all running workflows
List all running workflows
```
tctl --namespace <namespace_name> workflow list
```





### Adding new Scylladb node
On dev cluster, Karpenter will provision a new node automatically. On Prod cluster, add a new node to "scylla" nodepool on AWS EKS console and wait for it to be provisioned. The DaemonSet should spawn a pod called `local-volume-provisioner` on this new node.

- SSH into an exiting scylla pod. watch `nodetool status`. Any new joining node will eventuall appear here as 'UJ' ("Up Joining"). Note that you cannot add a new node if any existing node is "Down". Try restarting it or removing it from the cluster.
- increment `members` attr in the yaml, commit, push < fluxcd >
- wait for PVC and PV to be automatically created and linked to the pod. ~7mins
- `nodetool status` should say 'UJ' ("Up Joining") for the new node. Other nodes are now streaming data to this new node.
- wait until `nodetool status` says 'UN' ("Up Normal") for new node also.
- run `nodetool cleanup` on ALL(except new) nodes. Cleanup removes data from a node that was already transferred to the new node. Cleanup should be done one by one. It consumes a lot of resources.
- update temporal yaml (`config.cassandra.hosts` array) to point to new scylla pod's headless service, commit , push < flucd >

Note: adding the new scylla node via `members` yaml attr and pointing the temporal deployment to the new scylla node's headless service should be done in **separate commits** as described above.


### Adding new Scylladb node (1->2 nodes)
WARNING!: avoid this scenario as much as possible. There IS a way to update replicationFactor for a keyspace with ALTER KEYSPACE command. But this hasnt been experimented with properly. For now, prefer a full temporal cluster reinstall.

Adding a node to an existing cluster of 1 node is not trivial

Any schemas(keyspace schemas) created on ScyllaDB requires the following 
- replicationFactor (1,2)
- consistency level (none, `local_quorum`)
- serialConsistency level (none, `local_serial`)

Currently Temporal is the only application creating schemas on ScyllaDB during Temporal cluster bootstrap. If there is just one ScyllaDB node, the replicationFactor HAS to be 1 and light weight transactions cannot be enforced since it requires atleast 2 ScyllaDB nodes. This implies that when you move from 1->2 ScyllaDB nodes, you have to **wipe out the existing DB/terminate scylla nodes and recreate the schemas with replicationFactor=2 and LWT related consistency levels.**

Follow the steps above for "Wiping out Scylladb without deleting scylladb nodes"
Follow the steps for "Uninstalling Temporal"
Add a new node by incrementing `members` attr in the yaml.
Commit and push < fluxcd >.

Make changes on Temporal HelmRelease as described above < TODO INSERT BEFORE/AFTER IMAGES HERE >
Commit and push < fluxcd >
Delete the job called "es-index-setup" (See "Bootstrapping Temporal from scratch on K8s" for details)
Make sure to add required temporal namespaces (See "Adding a new namespace on Temporal" for details)
Run some test workflows to check temporal works fine.
`nodetool status temporal` should show that each node has 100% ownership since there are now 2 nodes and replicationFactor=2.

### Adding new Scylladb node (2->3 nodes)

### Scylla cluster repair on all nodes
A "cluster repair" on all nodes ensures consistency across all replicas and fixes any inconsistency if found. It is recommended to run cluster repairs regularly, atleast once a week.
Scylla manager by default runs cluster repairs once a week (TODO: i havent found a way to verify this)

Its also important to run "cluster repair" 
- prior to removing a node
- after changing replicationFactor for one or more keyspaces
- regularly, say every week ..as a cronjob (managed by scylla-manager)

To manually trigger a "cluster repair", SSH into `scylla-manager` pod in `scylla-manager` K8s namespace. `sctool` is scylla-manager's command line tool.
```sh
sctool cluster list
```

sctool progress --cluster scylla/scylla repair/a77ea838-7fe9-4bb9-b154-bdbdc3b37838


### Removing a Scylladb node
- Run full cluster repair before removing the node
- update temporal HelmRelease yaml to stop pointing to the headless service of the node to be removed. Edit the `cassandra.hosts` attribute. Remove the final element from the array, commit, push < fluxcd >
- Run `nodetool status`
- objective is to remove a node which is 'UN' ("Up Normal")
- run `nodetool decommission` on the last scylla node. If there are 5 nodes, run this on the 5th node. Decommission is the recommended method to scale down the cluster and prevent data loss by ensuring that this node will stream its data to remaining nodes in the cluster. (Note: other nodes should have enough disk space to take on this extra data of node to be removed). This will take quite a while. DONT ABORT!
- wait until `nodetool status` says there are now N-1 nodes.
- Update scylla HelmRelease yaml to update `members` and decrement it. Commit, push < fluxcd > 

Note: stopping pointing the temporal deployment away from scylla node's headless service, and updating scylla deployment `members` should be done in **separate commits** as described above.


### Monitoring temporal with sample workload
It is helpful to check if any maintenance activity causes downtime on temporal by triggering workflows constantly.
Here's a sample repo which does the same :< TODO INSERT GITLAB REPO LINK >
```sh
source venv/bin/activate
# start worker in one shell
python main.py worker
# start apiserver in another shell
python main.py
# trigger the apis
./monitor.sh
```
Keep this running during any upgrades/maintenance to observe if anything goes wrong with temporal.

Note that you do need to whitelist your IP address on AWS WAF. ( add IP to the IPSet named "temporal" )

## Misc
### `nodetool status`
Shows scylla node status. Watch this command when a new node is joining or leaving. Or to check total number of running nodes in the scylla cluster.
To see the effective percentage ownership of data for each nodes, you need to provide the keyspace name . eg: `nodetool status temporal` or `nodetool status temporal_visibility` . ("temporal" and "temporal_visibility" are keyspace names)

Read https://www.scylladb.com/2018/08/28/scylla-fault-tolerance/ for info on replicationFactor.

### `nodetool repair`
NOTE: avoid this and prefer scylla-manager's `sctool repair` command
Being distributed in nature, data in scylladb can be inconsistent across nodes and data among replicas get out of sync. To identify such inconsistencies across nodes and repair them for a given keyspace, we run `nodetool repair <keyspace_name>`. You need to run this especially when you change the replicationFactor for a given keyspace.

When you run `nodetool repair` on a node. That particular node acts as the "repair master" and **ONLY the data contained in that node and its replications on other nodes will be repaired**. Hence you need to run `nodetool repair` on every scylladb node.

I repeat, You need to run `nodetool repair` on every scylladb node. Hence, avoid this altogether and use `sctool repair` command of scylla-manager for convenience.

### `sctool cluster list`
Lists existing scylla clusters. You will see 2 clusters in this output. One is the main scylladb cluster which is backing temporal. The other is the one used by scylla-manager itself.(scylla-manager runs on top of its own cluster of scylladb)

Sample output for reference
+--------------------------------------+-------------------------------+---------+
| ID                                   | Name                          | Port    |
+--------------------------------------+-------------------------------+---------+
| b59bdb78-063b-4b8f-82ab-88aa8bbd34db | scylla-manager/scylla-manager | default |
| bac59e99-56fc-4db2-b15d-5f814968d7b2 | scylla/scylla                 | default |
+--------------------------------------+-------------------------------+---------+

### `sctool repair`
Run a full cluster repair.
```sh
sctool repair --cluster scylla/scylla
```
Make a note of the returned taskID (which looks like "repair/a77ea838-7fe9-4bb9-b154-bdbdc3b37838"). You need to provide this to check the progress of the task, or stop the task in case scylla manager itself goes down and comes back up in the middle of a frikkin repair.


### `sctool progress`
Check the progress of a given repair task
```sh
sctool progress --cluster scylla/scylla <taskID>
```

for example..
```sh
sctool progress --cluster scylla/scylla repair/a77ea838-7fe9-4bb9-b154-bdbdc3b37838
```

### `sctool stop`
Stop a given repair task ( say if scylla-manager went down during a repair operation, you need to abort the repair task after scylla manager comes back up )
```sh
sctool stop --cluster scylla/scylla <taskID>
```

for example..
```sh
sctool stop --cluster scylla/scylla repair/f13c1ee0-fbdc-4359-967c-5c388c2d3582
```
You can then create a new repair task with `sctool repair`.


### `nodetool cleanup`
- cleanup unneeded data (tombstones & old checkpoints)
- free up disk space . Improve performance.

### `nodetool decommission`
Gracefully removes the node from the cluster. Transfers its data to other nodes in the cluster, updates cluster metadata and indicates its intention to leave the cluster. Decommission ensures that data remains available and properly replicated after the node's removal.
Please run full cluster repair prior to running this.

### `nodetool removenode`
TODO.
DONT use this



# Whatis?
- Why cert-manager for k8s deployment of scylla?
- replicationFactor
- scylla-operator
- HostID
- seeds
- endpoint_snitch
- Tokens
- tombstones
- checkpoints
- /proc/sys/fs/aio-max-nr and /proc/sys/fs/aio-nr
- Why run `nodetool cleanup` before removing a node?  What does `nodetool cleanup` even do?
- Why package update succeeds when i do `sudo pacman -Syy` and then `sudo pacman -S helm`?

### TODO
- tags for pricing
- upgrade?repair?deprecate?
    - "node-setup" [DaemonSet]. Scylla-operator is deprecating this. Move to the new approach.
    - "node-provisioner"  [HelmRelease from a GitRepository]. Possibly deprecated?
    - "scylla-operator" [HelmRelease from HelmRepository]. <1.9>
    - "scylla-manager" [HelmRelease from HelmRepository]. <1.9>
    - "scylla" [HelmRelease from HelmRepository]. <5.0.5>



