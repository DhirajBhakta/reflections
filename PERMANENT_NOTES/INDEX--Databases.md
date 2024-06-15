The easiest way to improve DB performance(latency,throughput) is to scale up/scale out the DB and tune . But that isn't enough after a point. 
[[always use the official drivers]]
[[clientside driver timeouts should be twice that of server timeouts]]
[[have observability in place]]
[[backups or maintenance tasks should not coincide with high user load times]]
[[concurrency-latency-throughput , little's law]]
[[ACID properties bring a severe performance hit]]
[[aim for sequential operations on hard drive]]

[[designing a DB from first principles]]
### Storage Engines & Indexes
[[designing a DB from first principles#Indexes (on disk)|Comparing Indexes, how to choose the best one?]]
- [[hash indexes]]
- [[LSM Trees + SSTables]]
- [[B Trees & B+Trees]]

### Replication
[[why do you need Replication?]]
If data never changes, it would be so simple to copy paste data across replicas. All difficulty in replication lies in **handling changes to replicated data**. Which is why you need the following algorithms...
- [[single leader replication]]
- [[multi leader replication]]
- [[leaderless replication]]
[[single leader replication#Replication — Replication Lag and the problems it causes, guarantees to mitigate|problems with eventual consistency]]


### Partitioning/Sharding
Data gets too big, cant fit in one node anymore. Also read/write throughput  gets limited by single node. Partitioning = Splitting up the table into multiple chunks, to go on different DB nodes.
[[why do you need Partitioning?]]
How to do Partitioning? 
- [[how to do partitioning?#Partitioning by Primary Key (Aproaches) |Partitioning by primary key]]
- [[how to do partitioning?#Partitioning by Secondary Key (Approaches)|Partitioning by secondary key]]
[[rebalancing the partitions]]
[[rebalancing the partitions| fixed  number of partitions? dynamic number of partitions?]]
[[rebalancing the partitions#Partitioning — How many partitions should I have?|How many partitions should I have?]] 
[[routing requests to the correct partition]]
Unlike replication which is non-compromisable for HA, partitioning is done only at scale, and is complicated to get right, ..given the dependency on coordination services like Zookeeper OR complicated protocols like Gossip.

Sharding in the context of RDBMS is significantly different when compared to that in leaderless DBs like Cassandra, mainly in the fact that you have just a single leader and hence lose out on benefits of one leader per shard to scale the writes. See [[#RDBMS - Partitioning (TODO)]] 

TODO:
- clarify first
	- why is a single leader setup best for ordering events? wont the single leader accept parallel writes and have write conflicts cuz leader itself has multiple cpus? does this mean writes are done on a single thread? isnt that bad for write throughput? (apparently skiplist datastructure is used for memtables to write concurrently; redblack tree would need a write lock since they are self balancing)
	- (This section is pretty deep. ReadDynamo paper first. First understnd vNodes and consistent hashing in cassandra and dynamo paper. then, If you understand the design choices of Temporal numHistoryShards and taskQueuePartitions and underlying scylladb shards/vNodes, you'll grasp this concept completely with all nuances) [Designing A Workflow Engine from First Principles | Temporal Technologies](https://temporal.io/blog/workflow-engine-principles) Also very closely related to "how to choose the number of shards for Elasticsearch" [How many shards should I have in my Elasticsearch cluster? | Elastic Blog](https://www.elastic.co/blog/how-many-shards-should-i-have-in-my-elasticsearch-cluster)

- benefits:
	- benefits of sharding in a single leader DB setup (RDBMS) ....
	- benefits of sharding in a single leader-per-shard DB setup (kafka)
	- benefits of sharding in leaderless DB setup (cassandra)
	- benefits of sharding at the application layer(Temporal) on top of a sharded leaderless DB setup (cassandra)
	- benefits of sharding at the application layer(Temporal) on top of a sharded single leader DB setup(RDBMS)
- what exactly are partitions w.r.t to Cassandra? vNodes? token ring? 
- (excluding RDBMS), seems like you have N tables in the same partition WTF!? this makes it easy to write related things to N tables in a consistent, serializable manner without write conflicts. How does this even work!? contents belonging to more than 1 table in a single partition is beyond me. (This concept seems to be used in Temporal where writes within a single partition are serialized with transactional guarantees, whereas writes to task queues are made via a Transactional Outbox pattern.. which clearly means that you have **atomic guarantees within a partition** why?? how??)
- why should number of partitions grow and shrink with number of nodes? why cant you keep it equal to number of nodes? partitions~=100 but nodes~=10 why such a difference in production systems?
- whats the downside of having too many or too less paritions in FIXED partitions mode? too many => too much overhead of rebalancing? why?? ifyou have less partitions, maybe 1 partition will move to new node, if you have more partitiions, maybe 100 from all nodes will move to new node, but net "data" flowing through the network would be the same right?
- FIXED vs DYNAMIC in detail [Understanding Database Partitioning in Distributed Systems : Rebalancing Partitions | by Priya Patidar | The Developer’s Diary | Medium](https://medium.com/the-developers-diary/understanding-database-partitioning-in-distributed-systems-rebalancing-partitions-fa7fee542fd3)
### Transactions | RDBMS | OLTP
[[ACID properties#What is a Transaction?|what is a transaction?]]
[[why do we need transactions?]]
- [[concurrency bugs]]
[[why do we need transactions?#Transactions — Do you really need it?|do we really need transactions?]]
[[ACID properties]]

[[how to implement serializable isolation level?#Isolation Level — Serializable|How to implement serialization isolation level?]]
- [[how to implement serializable isolation level?#Actual Serial Execution|Actual Serial Execution]]
- [[how to implement serializable isolation level?#2 Phase Locking|2PL]]
- [[how to implement serializable isolation level?#Serializable Snapshot Isolation (SSI)|SSI]]
[[locking in databases]]
[[mvcc]]

[[do you really need relational databases?]] /  [[ACID properties#Transactions are super costly!|Transactions are costly]]


[[LWT - light weight transactions]]
[[prepared statements]]
[[consistency models]]


### Analytical Databases | OLAP
[[why OLAP?]]
[[column oriented storage]]
# Data
### Item Size
[[databases should NOT store large blobs]]
[[smaller payload causes memory fragmentation]]
### Item Type

### Dataset size


# Workload 
[[write heavy workloads]] / Cassandra, ScyllaDB
[[read heavy workloads]] / Dynamodb
[[mixed workloads]]
[[delete heavy workloads]]

---
### RDBMS (TODO)
- [Explaining The Postgres Meme (avestura.dev)](https://avestura.dev/blog/explaining-the-postgres-meme?utm_source=devopsbulletin&utm_id=newsletter) 

### RDBMS - SQL Query Performance(TODO)
- [SQL Query Optimization: Understanding Key Principle (devforth.io)](https://devforth.io/blog/sql-query-optimization-understanding-key-principle/) 

### RDBMS - Indexing(TODO)
https://use-the-index-luke.com/

### RDBMS - Partitioning (TODO)
- [When to Consider Postgres Partitioning | Timescale](https://www.timescale.com/learn/when-to-consider-postgres-partitioning)  
- [How To Decide if You Should Use Table Partitioning (brentozar.com)](https://www.brentozar.com/archive/2012/03/how-decide-if-should-use-table-partitioning/) 
- [sql server - Is table partitioning improving performance? Is it worth it? - Database Administrators Stack Exchange](https://dba.stackexchange.com/questions/62707/is-table-partitioning-improving-performance-is-it-worth-it) 
- [sql - What is the difference between partitioning and indexing in DB ? (Performance-Wise) - Stack Overflow](https://stackoverflow.com/questions/66793297/what-is-the-difference-between-partitioning-and-indexing-in-db-performance-wi) 
- [oracle - Partitioning vs Indexes - Database Administrators Stack Exchange](https://dba.stackexchange.com/questions/45937/partitioning-vs-indexes) 
- [oracle - Index vs. partition - Database Administrators Stack Exchange](https://dba.stackexchange.com/questions/1699/index-vs-partition) 
- [This looks very good but after using Cassandra I'd be scared of bumping into fea... | Hacker News (ycombinator.com)](https://news.ycombinator.com/item?id=15016276)[Synthetic Sharding with Cassandra. Or How To Deal With Large Partitions. · Los Techies](https://lostechies.com/ryansvihla/2016/03/15/synthetic-sharding-with-cassandra-or-how-to-deal-with-large-partitions/)
- sharding seems to have less benefits in RDBMS, since you have just ONE single leader and you cannot have one leader per partition to scale the writes. sharding does seem to speed up reads though (im not sure how).
	- "_a massive table is split into multiple smaller tables(horizontal sharding) and now you can avoid scans on a massive table_": but how does that even help? why would you ever want to scan a single massive table? wont you use a WHERE clause(on an index ofcourse)? isn't that enough to trim down the search space and avoid a complete scan of the massive table? i want to understand what exactly is the problem in having a massive table?
	- "_can do parallel sequential scans on multiple partitions at once_": cant you do the same on a single massive table? im failing to understand **what exactly is the problem in having a massive table** ?
	- "_each partition has its own index. each such index is small enough to fit in memory_": but sum of all such small indexes will just equal the index on massive table without partitioning right? also, isnt the index on the disk and NOT on memory?
	- "_imagine a sales table partitioned by date (one partition per month). If you want to query sales for a specific month, PostgreSQL can quickly determine the relevant partition and only scan that partition, ignoring the rest of the table. This can be orders of magnitude faster than scanning the entire table._" : again, how? wont a WHERE clause on the single massive table be enough? what value is partitioning adding here?
	- "_Reduced Lock Contention_": agreed. 
	- -- all in all -- will it make any difference to the massive table which **already has an index? is partitioning still be useful?**
	- there is no concept of "global indexes" across paritions. you can only have a local index per parition.
- Clear benefits of sharding is visible in leaderless replication (nosql like cassandra).

