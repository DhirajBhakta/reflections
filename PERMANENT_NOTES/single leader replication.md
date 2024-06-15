AKA ... *active/active* ... *master/slave*
![[ddia-67.png]]
All writes are accepted ONLY on the leader
- leader sends "data change" as part of _replication log_ or _change stream_.
- ... writes applied on the replicas in the **same order** as they were processed on the leader

replicas(and leader) can accept reads.

##### Cons (Single point of failure)
If leader fails, you cant write to the DB (until _failover_ completes successfully)

Solution:
- **Partitioning**: Each partition will have a single leader.
- OR use multi-leader or leaderless replication.


#### Adding new follower (replica)
_Setting up new followers ... without downtime_

You could lock the DB, stop accepting writes, and copy over the data to replica... but this requires downtime.
1. Take a DB snapshot(consistent snapshot)
2. Copy the snapshot to the new node
3. The new follower connects to the leader
	1. requests all "data changes" that happened since the snapshot was taken. (from the "offset" in the replication log)
	2. follower processes the backlog of all data changes since snapshot
4. Follower is "caught up"

There's a "log sequence number" for every log in the _replication log_. The time at which the snapshot is taken is associated to a particular "log sequence number". all logs AFTER this ..correspond to "data changes" that happened after the snapshot was taken.
... from the "offset" in the replication log.


#### Node Outages — Follower Crash
Replica(Follower) crash is easy to handle. Each follower maintains the _replication log_ of "data changes".
- connect to the leader
- request all data changes that happened during the time when it was disconnected.
- apply the changes
- follower is "caught up".

#### Node Outages — Leader Crash (Failover)
Leader crash is harder. **Handling leader crash is called "failover"** . One of the followers needs to be _promoted_. A lot of things can go wrong with automatic failure, so its almost always **done manually**

Automatic failover steps.
- Detection of leader failure
	- _using a timeout._ Leader didn't respond in 30s? its dead. 
	- Finding the right timeout is challenging. 30s? 10s? large timeout = long time to detect failure. Short timeout = too many unnecessary failovers.
- New leader election
	- ... consensus problem. Every other node must "agree".
	- Will the new leader have all the writes that was processed by old leader? If asynchronous replication was used... you may not get all writes. You'll lose writes, and you essentially "discard" such writes. Bad durability. 
	- can cause "split brain problem"
- Reconfiguring the system to use the new leader
	- old leader must recognise the new leader upon rejoining.
		- can cause "split brain problem". Both leaders believe they're the leader. old and new.



#### Replication — Synchronous and Asynchronous
Synchronous: The **leader waits until the follower has confirmed** that it received the write before reporting "success" to the user. 

**advantages**
- up-to-date data on all replicas (strong consistency)
- normally, replication is fast.

**disadvantages**
- SINGLE replica outage can cause the whole system to go down. 

>**Note** 
>_In practise, "sync replication" = "one of the followers is sync, rest are async".

Asynchronous: The leader sends the message, but **doesn't wait for a response from follower**. 
- This is better, and often the default.
- Leader can continue processing writes, even if all followers have fallen behind.
- Replication is quite fast, but there is no guarantee of how long it might take. (eventual consistency)

#### Replication — Replication Lag and the problems it causes, guarantees to mitigate
Replication Lag : The delay between write happening on the leader ... ... ...  and being reflected on a follower. 
- its usually a fraction of a second
- but if operating at near capacity, lag can go upto many seconds/minutes.
	- Always ask this question: _"is it okay for my system if replication lag increases by minutes??"_
- You can **monitor** ReplicationLag as a metric in seconds... by subtracting the follower's current position from leader's current position. 

Read-scaling-architecture: simply adding more read replicas for a system which has far more reads than writes. It removes the load from the leader.

Replication lag (eventual consistency) has problems when asynchronous replication is used. So the system must give the following guarantees. System will be unreliable(bad user experience, stale data, out of order data, time moving backwards, causal relationships not honoured) due to replication lag, such a system is useless without the following guarantees. 
1. _Read-After-Write Consistency_ / (Read your writes consistency)
	- Scenario:  _user makes a write...then makes a read from a stale replica._
	- This guarantee says that if the user reloads the page, they will see all their writes. (no guarantees about other users' writes though)
	- Assures users that their writes have been saved correctly.
	- How to implement?
		- **Selective reading from the leader**
			- read your writes directly from the leader
			- you need to decide what needs to be read from the leader, else read replicas don't have any point to exist.
		- **Timestamp tracking** 
			- for 1min after last update, read from the leader
			- The client notes the timestamp(logical) of last update, and reads from a given replica ONLY if it contains that logical timestamp
	- _Cross-device Read-After-Write Consistency_ 
		- requests from web browser and mobile app.. 
		- write from one device, read from another. 
		- pitfalls
			- timestamp based approaches will not work. Clients on diff devices don't know what's the  timestamp of latest update. "Who did the latest update? mobile or web app?"
2. _Monotonic Reads_
	- To avoid "moving back in time"
	- Scenario : _user first reads from a fresh replica, then reads from a stale replica_ 
	- On first load you see 10 comments, you reload and see just 9 comments.
		- you read from replica A: you see A, B, C, D
		- you read from replica B: you see A, B, C
		- you read from replica C: you see A
		- ... this happens because replication takes time
		- _feels like you're going back in time_
	- This guarantee ensures that user will not read older data after just having read newer data.
	- Strong consistency >> monotonic reads consistency >> eventual consistency
	- How to implement?
		- A given user always reads from the same replica (userID hash)
		- A user is "assigned" to a given replica
3.  _Consistent Prefix Reads_
	- This guarantee ensures that if a sequence of writes happen in a certain order, anyone reading those writes will see them appear in the same order. **Preserving causal relationships** . 
	- Reading "out of order". violating causality, causing confusion.
		- you read from replica A: you see A, B, C, D
		- you read from replica B: you see A, B, D, C
		- ... this happens because replication takes time, and D might've reached replicaB earlier. (Network Race Condition)
	- Its a problem in sharded(partitioned) DBs (which lack global ordering)
		- required data(from query) is spread across different shards.
		- Every partition may not process the writes in the order they come. Partitions operate independently.
	- how to implement?
		- related writes should be written to same partition; 
		- related writes are "assigned" to a partition(replica). 
		- eg: temporal writes data related to same workflow to same partition (workflowID hash)
		- OR if its not possible to write causally related data to same partition...then, store the causal dependencies, i.e store that "X is dependant on Y".
		- OR use version vectors.

> **Note** The above reasons are why "Transactions" exist to give strong consistency. 
> Devs dont worry about subtle issues in replication., trust the DB to just work.


#### Replication Logs — Implementation
_Logical(Row based) replication is mostly preferred, .. and can also be applied for CDC_

- **Statement-based replication**
	- every statement like INSERT, UPDATE, DELETE are sent to every replica
	- every replica executes such statements. _as if it received them directly from the client._
	- cons
		- non-deterministic functions like `RAND()` , `NOW()` will generate different value on different replicas
		- auto-incrementing columns will get messed up.
- **WAL shipping**
	- WAL = **storage engines's log**
	- WAL = _append only sequence of **bytes** containing all writes to the DB._
	- WAL = log of SSTables, LSMTrees...log based index DBs "log structured storage engines". compacted, garbage collected, merged..
	- WAL = log written by BTrees prior to writing to index, for crash recovery.
	- This sequence of bytes (logs) can be sent to the replica to build up a copy.
	- cons
		- too low level logs... bytes! on disk blocks! ..._coupled to the storage engine_. 
		- what if leader has a different version of the storage engine compared to a replica?
- **Row based log replication (Logical)**
	- "logical" = decoupled from storage engine internals.
	- "logical log" != storage engine's log
	- logical log contains the following for inserts, updates, deletes
		- Inserts: new values for all columns.
		- Deletes: unique row identification.
		- Updates: new values of changed columns.
	- **useful for CDC (change data capture)** ...
		- build data warehouse
		- build custom indexes
		- build custom caches
- **Trigger based replication**
	- More flexibility via "code"/triggers+storedProcedures
	- implement conflict resolution logic
	- trigger = custom code automatically executed when data changes
		- you could write to another table via a trigger. Some other app logic might pick up values from this new table and do the replication maybe.
	- cons
		- more overheads, more bugs