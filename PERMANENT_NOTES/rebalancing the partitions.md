Data storage or retrieval is then a two-step process.
1. First, you find the partition for the given data item.
2. Then you find the cluster node where the partition is stored.

To balance data across the cluster nodes when new ones are added, some of the partitions can be moved to the new nodes.

#### Partitioning — Rebalancing
When you add new nodes / remove nodes ... you need to rebalance , i.e  move data around to maintain fair distribution.

Goals of Rebalancing
- **Balanced/even distribution** after rebalancing.
- **Minimal Disruption** during rebalancing. Rebalancing should not take up lots of resources (CPU, mem). Should continue accepting reads/writes.
- **Efficiency** ... make rebalancing fast and minimise network or disk I/O load. Don't move around data more than necessary.

How to rebalance? But first.. How NOT to rebalance? [Fixed Partitions (martinfowler.com)](https://martinfowler.com/articles/patterns-of-distributed-systems/fixed-partitions.html)
- DONT use `hash(key) % N`  . Modulo N is not good because N=number of nodes, number of nodes keep growing and shrinking and this will force records to keep moving everytime number of nodes change.
- Such frequent rebalancing is excessively expensive.

How to rebalance?
- **Fixed number of partitions**
	- [Fixed Partitions (martinfowler.com)](https://martinfowler.com/articles/patterns-of-distributed-systems/fixed-partitions.html)
	- _Number of partitions is FIXED when DB is first setup,  and never changed afterwards._ (eg:Temporal)
		- Although it IS possible to split and merge partitions(see **dynamic partitioning** next), a fixed number of partitions is **operationally simpler**.
	- create FAR MORE partitions, say 1000 partitions for 10 initial nodes. [[#Partitioning — How many partitions should I have?]]
	- When new node is added it can "steal" few partitions from existing nodes.
		- ... until partitions are fairly distributed again.
		- number of partitions does not change
		- assignment of keys to partitions does not change
		- assignment of partitions to nodes changes!
	- Cons
		- Choosing the right number of partitions is difficult. [[#Partitioning — How many partitions should I have?]]
		- If you choose to have too many partitions, its resource expensive. Each partition has resource overhead (incl metadata tracking)
		- if you have too less partitions, a single partition can grow very large, and gets expensive to move it around to a bigger machine (why move the whole thing? because you can move the entire partition as a unit. You cannot split a partition in Fixed partitions mode since number of partitions is fixed forever.)
- **Dynamic number of partitions**
	- When a partition grows to exceed a threshold size(10GB)
		- one partition can **split** into two partitions.. or two can **merge** into one... to keep number of partitions dynamic/flexible.
		- Similar to BTree. 
	- Why is it needed?
		- in key-range partitioning, you can end up with all data in one partition if you have the boundaries wrong while partitioning .
	- _adapts to data volume._ Overheads of having too many partitions isn't there.
	- since rebalancing/merging/splitting is done automatically, might lead to over-rebalancing/over-merging/over-splitting if signals are not configured correctly (need admin intervention) and might bring the system to a halt due to high resource usage.
- **Partitions proportional to number of nodes**
	- fixed number of partitions per node.
		- just add nodes if you want to increase partitions. 
		- Existing partitions are randomly split to distribute load
	- vNodes in cassandra. Consistent Hashing

> **Note** : fully automated rebalancing is risky, might lead to excessively expensive rebalancing operations. Can overload the network and even cause DB's denial of service.
> Say one node is overloaded, slow to respond. Other nodes conclude its dead, **and trigger automatic rebalancing** to move load away from it. This puts additional load on the overloaded node, other nodes, and the n/w .. make the situation worse.. **cascading failure**. 


#### Partitioning — How many partitions should I have?
_(assume fixed number of partitions, decided in advance_) 

Goals:
- make the data spread evenly across the cluster (large number of partitions is better)
- minimize the number of cross partition reads (small number of partitions is better)
- ...
- (as per Cassandra)
	- a partition should have <100k rows.
	- a partition's size should be <100MB
![[ddia-68.png]]

Consider the assignment of 
- data rows to partitions
- partitions to nodes

Consider the total number of partitions
- can stay fixed for lifetime (eg: ElasticSearch , cassandra, with vNodes consistent hashing)
- can increase or decrease dynamically

> Assume fixed number of partitions for this discussion.

**Large number of Partitions**
Read [[how is data read in Cassandra]], and consider what would happen if every row had a _unique PK_ (unique partition Key).
For every key, the [[how is data read in Cassandra|partition index]] (on disk) is consulted. And Disk access is worse!
Pros:
- More partitions => more parallelism
Cons:
- Increased metadata overhead (additional storage and resources)
- Use the Kafka topic analogy:
	- if the kafka topic has N partitions, then you need N consumers to consume the topic, since a single consumer can read from just one partitions.
	- overall resource usage is high since you have more consumers now.
- May need to contact multiple partitions, and cross partitions reads/writes has bad performance. Range query performance is also bad in cross partitions, collect from multiple partitions and combine.
- Data will now be spread across too many SSTables
- Limited Batching opportunities. (You can batch reads/writes to a given partition)

**Small number of Partitions**
Read [[how is data read in Cassandra]], and consider what would happen if every row had the _same PK_ (same partition Key).
a LOT of linear scans on the on-disk SSTable would have to be done.
Pros:
- less overhead to maintain the partitions (metadata), less resources.
Cons:
- assume no replication. then only one node will hold the given partition (PK=given value, constant for all rows). that node will now be overloaded. Other nodes are just sitting IDLE.
- even with replication, only the same set of nodes which contain the replicas of the given shard will be overloaded with quorum writes.

