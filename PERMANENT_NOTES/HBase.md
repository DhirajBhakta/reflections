_"Hadoop Database"_ - _Wide Column DB_

- transactions
- analytics DB
- Both OLTP and OLAP : hybrid
#### HBase is an implementation of BigTable paper


#### HBase is built on top of HDFS
_Just like how BigTable is built on top of GFS_.

HDFS is a **Distributed Filesystem** 
- does replication of data
- fault tolerance (with replication)
- horizontal scalability 
HDFS is slow for reads and writes (disk access involved), and allows only **sequential access** 
HBase adds LSMTrees on top of HDFS and mitigates these limitations.


#### HBase is a wide-column database
_Millions of Columns; Billions of Rows_ = very Wide indeed.
Just like Bigtable and even cassandra..

#### Architecture
![[db-21.png]]
- One Active "HMaster", multiple Passive "HMasters"
- has zookeeper
	- Keeps consensus on who the Active HMaster is (Distributed Lock)
	- Also stores location of HBase Metatable ([[paper review—bigtable]])
> But requests do not hit the HMaster. Dont have to worry about HMaster being the bottleneck.

##### What does the "HMaster" do?
- Perform DDL
- Recovery of Region Servers upon crash
- Load Balancing of Region Servers

##### What is "Region Server" ? | Node
- Holds a bunch of "Regions" belonging to one or more tables.
- Region Server takes care of
	- N "Regions" within it
	- LSM Trees | SSTables | Compaction | Bloom Filters
		- SSTables in column oriented storage (not sure)
	- WAL (fault tolerance)
- Region Server _Sends Heartbeats_ to zookeeper.

##### What is a "Region"? | Partition
_Range Based Partitoning_
- one "Region" is assigned a portion of the table based on row key range: (startkey : endkey).
- This is how billions of rows in ONE table is horizontally scaled, ... by splitting them across "regions" which go into multiple machines (Region Servers)

Even a row partitioned "Region" can be vertically partitioned by **column families** into more child "Regions"

##### Automatic Rebalancing:
The "Regions" can split/merge and a move around Region Servers automatically. ("Regions" are called "Tablets" in Bigtable)

##### Replication
_Taken care by underlying HDFS (GFS)_






#### Data Model
- Table (and regions) are sorted by row key. 
	- Need to be smart on how you construct your row key (it can contain a lot of info say `category+append timestamp`)
- You must have small number of Column Families in one table
- But number of columns in each Column Family can be arbitrary! 
	- you can even have one column per movie name!!
	- Bigtable stores anchors (incoming links) and (outgoing links) as columns!
	- bizarre!
- Each cell can have VERSIONS! with timestamps
	- history
- Sparse data is OKAY!, no overhead for NULLs
- Column family supports a TTL
Use fewer tables, Those tables must be very big and wide.


#### Storage 
_Column-Oriented Indeed!!_
![[db-22.png]]
#### Read Write Path
Client...
1. access the metatable from Zookeeper.
2. metatable helps direct you to correct region server. (metatable holds info of which keyrange belongs to which region; which region belongs to which region server)
3. Read / Write

#### HBase usecases
- Very good for SPARSE data
	- Does NOT incur any overhead for a lot of NULLs
- Big Data (TB/PB)
- High Throughput
- Random reads/writes
- HBase is good as a "data lake", for running huge batch/stream processing on

#### HBase limitations
- not good for WHERE, filters, ad-hoc analysis
- only 1 primary key
- queries with WHERE clause with primary key will have good performance. But not on other columns

> Since it's not good for WHERE (filters), its a BAD candidate for analytical queries. HBase vs Clickhouse is a no contest. Clickhouse uses columnar storage (column-oriented DB), but HBase is "wide-column DB" . It has concept of "column families", but it still lays out data row wise on disk.

- Not good for sequential access (directly use HDFS/GFS for that!)
	- Not good when you want to read petabytes of sequential bytes to feed your spark job. (but why would you even do that??)
- Limited support for Transactions (only at row level)
- Avoid JOINs
- No support for SQL (can use Hive on top of HBase though) (Impala on HBase)

> HBase has no Query Language. Just a CRUD API. CRUD is all you can do by key without much filtering

- not good for timeseries data where PrimaryKey is, say, the timestamp. All rows would attack one node and it would become a **Hotspot**. (Use hash of the key instead)
#### Usecases
Chats | Facebook Messenger
- High Throughput Inserts (Millions of inserts/s but data size per insert is small)
- 

> Facebook created Cassandra, and yet used HBase for messenger


#### HBase vs Cassandra
Both use LSMTrees, and are wide-column

- HBase hits the ceiling on write throughput, due to being limited by HDFS
- Cassandra is built from ground up for high concurrency very high write throughputs
- HDFS cluster across geographical regions might be tricky...So HBase is limited by that. Cassandra has no such HDFS dependency
- Cassandra can truly reside in multiple geographical locations
- HBase is CP. Cassandra is AP
	- Consistency is important in an app Like FB messenger, hence they used HBase and not Cassandra (which they developed in house).
- HBase is Master-Worker architecture, Cassandra is leaderless, peer-2-peer.
- HBase, 1 datacenter is preferred, Cassandra can be across the globe.
- HBase doesn't have a query language natively. Although you can add Hive, Impala on top of it. Cassandra has rich CQL.


