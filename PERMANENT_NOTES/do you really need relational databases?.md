#### Relational databases
- Tables | rows of _structured data_. 
- Each table has a preset schema (rigid)
- Rows of one Table can have _relations_ to rows of another table (foreign key)
- Fetch related data via JOINs.
- _Declarative_ SQL (specify WHAT, and HOW is abstracted away)
	- Built-in _query optimiser_.
- Mostly on [[B Trees & B+Trees]].
- All reads and writes go to Disk.
- Hide concurrency bugs and partials failures via [[ACID properties|Transactions]].
- Support [[ACID properties|Transactions]] with [[how to implement serializable isolation level?#2 Phase Locking|2 Phase Locking]] for (near serial)Isolation, and also [[ACID properties#Isolation Level — Repeatable Read (Snapshot Isolation)|Snapshot Isolation]] (near serial) Isolation. As of date, Postgresql uses [[how to implement serializable isolation level?#Serializable Snapshot Isolation (SSI)|Serializable Snapshot Isolation(SSI)]] which is the closest to being serial.
- Generally use  [[single leader replication]]
- MOST IMPORTANTLY,
	- lots of people have experience building atop relational DBs, easy to onboard. 

#### Relational databases  — Scaling
Vertical Scaling (most usually done)

Horizontal Scaling would involve sharding/partitioning the dataset (with single leader per partition to make best use of linearly increasing write throughput with addition of nodes). This is where things get **hard** for relational databases.

Problems with sharding
- Data in different partitions would now require a **distributed transaction**, extremely slow - Paxos, 2PhaseCommit
- Cross partition writes are extremely slow
- JOINs across partitions => too many network calls

#### Relational databases — Cons
- [[B Trees & B+Trees]] are too slow for writes (_although fast for reads_).... compared to LSMTrees which have in-memory buffers.
- Locking for the sake of enforcing Isolation in Transactions - reduces concurrency by a huge margin, reduces throughput and overall makes things slow.
- Cannot take advantage of Horizontal scaling. If you do, then you have
	- distributed transactions (slow)
	- JOINs across partitions/nodes (slow)
- Generally use [[single leader replication]] which **limits write throughput**.
	- Story would've been different if it could have one single leader per shard, but that is not possible here.


#### NoSQL - design patterns
- **Data locality on Disk**
	- embrace redundancy, denormalization
	- most data you need is found together at once place
	- ...gives you _faster reads_, _faster writes_
- **Schema-less**
- **Work well with Sharding/Partitioning**
	- Easier to shard
	- everything that you need can be within the same shard (no restriction on "same table rows in given shard", you can actually have rows across tables within a given shard).
