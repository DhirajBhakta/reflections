_How systems which **process and store data** work_

Book Overview
- Ch1 - Ch 4 (PART 1) :: data stored on single machine
- Ch5 - Ch 9 (PART 2) :: data stored on multiple machines
- Understand the inner workings/core principles, key DSA, distributed systems concepts  of most used tools that deal with data (store data or process data) : DBs, caches, queues, stream/batch processors. Pros and Cons of each, when to use what. 
- No matter how many of these new systems come and go, enduring principles remain true.
- Learn to develop the intuition to know which set of tools you can mix and match/combine to obtain desirable application behaviour.
- Learn key principles in the above tools, which you can use to make any system scalable and highly available.
- Learn how each tool in a given area(say caching) is similar to other tools in the same area, and what sets it apart.
- Storage & Retrieval — How storage engines lay out the data on disk for faster writes OR(AND) faster reads. Indexing approaches

#### Tools which store and process data
- DATABASES
	- RDBMS
	- NOSQL
		- DocumentDB
		- GraphDB
- MESSAGE QUEUES
- CACHES
- SEARCH INDEXES
- BATCH PROCESSING
- STREAM PROCESSING

The categorization shouldn't end at such a broad level. There are different approaches to caching, different ways to build search indexes.. 

Some tools don't fit neatly into any ONE category. Redis is used as a cache as well as a message queue. Kafka is a message queue but has database-like durability guarantees.

#### Scalability — How to describe/measure load
> **Note**
> The below are NOT necessarily performance metrics, they just describe how much load you are putting on the system. 

Load Parameters
- RPS , Requests Per Second
- Writes per second on DB
- Reads per second on DB
- Ratio of reads to writes on DB
- Cache hit rate
- Number of Concurrent users
- Number of Concurrent requests
- ... or whatever , as per your application metaphors, like...
- {Twitter} Home timeline tweets per page load., everytime a user opens the app.
- {Twitter} NumFollowersPerUser . Its a key load parameter since it determines the fan-out load. (fanout=how many internal requests a single request/query can trigger )

When you increase a load parameter, and keep the resourced unchanged (CPU,RAM,bandwidth), does your performance drop? Or how much should you increase the resources to keep the original performance?... _How do you measure performance in the first place?_

#### Scalability — How to measure performance 
- Throughput
	- RPS
- Response time
	- p50(median) response time
	- p95 response time
	- p99 response time
	- .. average means nothing here...

Why are "Tail Latencies" (p95, p90) important? they tell you how bad your outliers are. Outliers are just random one off/rare things that dont matter, right? - Wrong.  The outliers probably belong to requests causing max processing on the backend, and such requests probably arise from most important customers who have max data on the system.  Tail Latency Amplification — Even if a very small percentage of backend calls are slow, if the client makes N calls for say a single button click(fanout), the probability of him hitting a slow call will get higher and higher 

![[ddia-00.png]]
> **Info** : _Average means nothing. Choose medians_
> A single request causing 10min response time can raise the average of a hundred other requests which had just 1s response time...to an average of say 2 min. Gives a false sense of the distribution.
> OTOH, why would such an outlier exist?
> - maybe it processed far more records than others..
> - random additional latency due to say
> 	- context switch to another process
> 	- loss of packet, TCP retransmission
> 	- GC pause
> 	- page fault , read from disk
> 	- ...

> **Warning** : Latency != Response Time
> Response time is round trip time, what the client sees. 
> Latency is the time spent **waiting** to be processed/handled. 
> time spent being "Latent"(lying dormant) ..awaiting service. 

As load increases, (with resources fixed)
- Throughput increases slowly and then hits a saturation.
- Response time gradually keeps on increasing
![[ddia.png]]
So during load testing, when adding load, bombarding the system with requests, **you should NOT wait for prev req to complete before firing the next req** because it will NOT show the queue getting longer and longer, and the latency getting larger and larger... a symptom you NEED to witness to know that performance drops with load. Or else, you will never know whats the true breaking point of the system with resources kept unchanged. 
#### Scalability — Little's Law
Why does latency increase with load ?
A server can process only a fixed number of things in parallel (limited by number of cores). It takes only a small number of slow requests to block the processing of subsequent requests ., this is called "head-of-line blocking". All subsequent requests take much longer to complete since they spent majority of the time waiting. 

Queueing Theory Basics...
An application requires resources to fulfil a request, and the resources are finite. If a resource is not available, the request must wait for it.
![[ddia-17.png]]
(_pool with servlet threads for DB, memory, CPU_)

`CONCURRENCY = ARRIVAL_RATE(RPS) x LATENCY`

Average number of requests is equal to average arrival rate x average time spent in the system.

Concurrency, arrival rate (RPS), and Latency are things that can be directly measured ...which helps in capacity planning (which is difficult to reason about by observing directly.)
- Concurrency : gives a measure of resources like threads, memory , connections, file handles, anything that is numerically limited. It also gives a indirect way to measure contention. If concurrency is high, then contention is also high.

Put it other way, Little's law kind of hints that throughput levels out after a point: `RPS = CONCURRENCY/LATENCY` . i.e as number of concurrent requests increases, latency also increases, to keep the RPS constant.
But in the real world, throughput DROPS. Throughput drops when contention rises, because contention itself has a cost.

#### Scalability — Amdahl's Law
_How much can parallelization reduce the response time?_

If you can parallelize 200ms of a request taking 500ms, dividing the work on 4 parallel processes, then the response time = 300 + 200/4 = 350ms

This is used for effectiveness. At a particular point, parallelization no longer makes sense since overall gain is so low...

#### Scalability — How to cope with load ?
You can't just add more machines and expect to scale. You MIGHT have to change the architecture of your backend. 
Its easy to run _stateless services_ across multiple machines, but taking _stateful systems_ and splitting them across multiple nodes is difficult. (This is why common knowledge is to scale up a MySQL instance until you cant no more)


#### Data Models
Historically, data started out being represented as one big tree (Hierarchical model) (sounds a little like mongodb(documentDB) too), but that wasn't good at representing many-to-many relationships, so relational model was invented. 
These days, some applications don't fit in relational model either, so some NoSQL datamodels have emerged. 

There are many data models
- Hierarchical (first model)
- Network
- Relational
- NoSQL - Document
	- MongoDB, RethinkDB, CouchDB, Espresso
	- target usecases where data comes in self-contained documents and relationships between documents are rare.
	- Don't enforce schema
- NoSQL - Graph
	- Neo4j
	- target usecases where anything is (potentially) related to everything.
	- Don't enforce schema
Each data model makes some assumptions on how it is going to be used. It defines the **access patterns** that are fast and easy. (It also makes _other_ access patterns slow and difficult) — It gets very important to understand the access patterns in your own application and choose the data model accordingly. 

Although one model can be emulated in another model (graph can be represented on relational model too), but queries get clumsy and you get worse performance on queries(read/write). 
#### Data Models — Relational 
_declarative >>> imperative_
Prior models (Hierarchical, Network) forced the developers to know and think about the internal representation of the data on the DB. How bytes are laid out, how to access a specific data piece. Stuff like "access paths" to reach a DB should be clearly specified in the "query" you write.
Relational model abstracted all of it away(hides implementation detail of a query) with SQL which was a **declarative interface**. The presence of a "query optimizer" changed the way we write queries. Our queries now no longer worry about underlying things like "access paths", or best way to reach a specific data. Our queries don't have to change due to a presence of an index.  The Query optimiser takes care of these things, you just specify WHAT you want in a declarative way (SQL), and query optimised takes care of HOW to obtain it efficiently(and fast). Your queries remain the same with our without the index, even though the underlying approach of obtaining the data with or without the index is significantly different. The fact that the language is declarative, makes it possible for the database system to introduce performance improvements without requiring any changes to queries (like parallel execution across machines, which would be hard if the language was imperative).
> **Note**: Distributed Execution of SQL
> There's nothing stopping SQL from running across multiple machines. Underlying  implementation of SQL(a standard, spec) is totally left to the vendor... and can use MapReduce or whatever to achieve the goal specified by the SQL queries. 

IMS(hierarchical model) and CODASYL(network model) queried the database using _imperative code_. But relational model introduced a new way of querying data — declarative query language (SQL).

The fact that SQL is more limited in functionality , gives the database more room for automatic optimisations. (eg: its nearly impossible to apply parallelism on a imperative code.)


#### Data Models — NoSQL
Arose because people wanted 
- Higher Scalability than relational model. Very large datasets...very high write throughputs...very high read throughputs...
- Some access patterns which relational model did not serve well. (eg: simple things from applications perspective, require far too many joins.. , require ORM to translate every object to relational schema.)

#### Data Models — NoSQL Document DB
Read: [Why You Should Never Use MongoDB « Sarah Mei](http://www.sarahmei.com/blog/2013/11/11/why-you-should-never-use-mongodb/)
Suitable for 
- self-contained "Documents",  locality -> Performance. "obtain everything in one call". 
- youll have better performance due to locality. All that you need is fetched in one go without any kinds of JOINS, because all that you need is present in the same document.
- schema flexibility. no schema at all! Closer to data structures used by the application. No need of ORMs.
- Tree like structure : Has one-to-many relationships
- You don't plan to have joins at all..You're OK with denormalisation and redundancy.
- You hate joins, don't want the performance overhead of joins, and your data inherently has "locality", i.e all related data close by, within the same document.

Not suitable for
- Has many-to-many relationships.
- highly interconnected data, which scream the need for many-to-many relationships, or JOINS.

> *Whether you’re duplicating critical data (ugh), or using references and doing joins in your application code (double ugh), when you have links between documents, you’ve outgrown MongoDB. When the MongoDB folks say “documents,” in many ways, they mean things you can print out on a piece of paper and hold. A document may have internal structure — headings and subheadings and paragraphs and footers — **but it doesn’t link to other documents.** It’s a self-contained piece of semi-structured data.* 
>  
>  *If your data looks like that, you’ve got documents. Congratulations! It’s a good use case for Mongo. But if there’s value in the links between documents, then you don’t actually have documents. MongoDB is not the right solution for you. It’s certainly not the right solution for social data, where links between documents are actually the most critical data in the system.
>  - Why you should never user MongoDB , Sarah Mei. 

But you need to be wary. Even if initial version of your application fits in a "join-free" document model, data has tendency to be more and more interconnected as features get added. If you start out with document DB, and "interconnectedness" of your data keeps on increasing,... your application code has to do all the work to keep all the denormalised data consistent. JOINS can be emulated by doing multiple n/w calls to the DB, clearly slow. **A hybrid DB which can handle both relational and document types, would probably be an ideal** 

It is recommended to keep document size small.

#### Data Models — NoSQL Graph DB
For highly interconnected data, document DB is terrible, relational model is OK, and graph model is the best. 
Graph DB has "vertices" and "edges". 
Google uses GraphDB for storing its web graph, Facebook uses GraphDB(TAO) for its social graph. 

A vertex can be any object, the graphDB need not be limited to storing just vertices of one type (say person), homogeneity isn't mandated. This flexibility is very powerful.
eg: Facebook maintains a single graph where vertices can be people, locations, events, checkins, comments.  Edges represent which people are friends with each other, which checkins happened at which location, who commented on which post, who attended which event,..

There are 2 main data models for graphs,
- **Property Store Model** with Cypher Query language
	- Neo4j, Titan, InfiniteGraph
	- Each Vertex has an ID, set of incoming and outgoing edges, and a set of k-v pairs (properties)
	- Each Edge has an ID, the tail vertex, the head vertex, relationship(b/w connected vertices) label,  and a set of k-v pairs (properties)
- **Triple Store Model**(RDF) with SPARQL Query language
	- Datomic, AllegroGraph
	- (Subject, Predicate, Object).... eg: (lucy, marriedTo, Alain), (lucy, age, 33)
	- Note that there are no k-v pairs(properties). Such things are just handled via predicates. 
- "Much Older" data model with Datalog Query language
	- Cascalog is a Datalog implementation to query large datasets in Hadoop.
	- predicate(subject, object)
	- The Datalog Query language is a subset of Prolog. 
	- The data model is very similar to Triple Store Model (RDF). 

GraphDB features _can_ be implemented on RDBMS via Recursive CTE (Common Table Expressions).But it is very clumsy. You might need 30lines of SQL for what Cypher can do in 4 lines. 

https://stackoverflow.com/q/13046442/5319180 #TODO (Are Graph DBs a superset of RDBMS? are they just better RDBMS since all data eventually get more and more interconnected? Seems like RDBMS is much faster when dealing with querying a lot of row, while Graph DBs excel in digging deep into the path just for one item..)


#### Storage & Retrieval — Logs & Index
#append-only-logs #index #logs
The main job of the storage engine of a DB is to lay out data on disk in a way that does either or both of these
- speed up writing
- speed up reading
- keep the disk usage low (optional)

A "log" file  is a stupidly simple way to store data in a append only fashion, and **writes are obviously the fastest**, O(1), seek to the end and write. (But reads suck here, O(N), full scan)
An "index" is a special additional structure derived from primary data,  which **helps speed up reads, at the cost of writes**. General idea is to keep some additional metadata on the side which acts as a signpost to directly jump or "seek" to the required position to read your data. Presence of an index slows down the writes because you also have to update the index. 

2 families of storage engines (based on how they define and implement an "index")
- **Log-structured storage engines** (Hashtable index, SSTables, LSM Trees)
	- append, never overwrite.
- **Page-oriented storage engines** (B-Trees)
	- overwrite in-place. 
	- the "page" here corresponds to  fixed size "blocks" on hard disk. The algorithm is specifically made for the underlying storage

#### Storage & Retrieval — Indexes |  Hash Indexes
![[ddia-01.png]]
A hash Index is an in-memory hash-table which can give you the location of a key on disk in O(1). 
Imagine the "database" is just a 
- continuously growing file(on disk) with k-v pairs separated by commas
- additional in-memory hash-table to speed up disk seek
Now you've got 
- faster reads, thanks to hash-table.
- faster writes, since its just an append-only log.

>**Note**: 
>_Bitcask (storage engine of k-v store called Riak), does exactly this.
>Gives "High Performance reads and writes"...

Downsides ?
- Entire hash-table should be stored in memory, large RAM needed.
	- Make sure all your keys can fit in memory.
	- why not store the hash-table on disk? random IO on disk is very slow compared to RAM. 
- Range queries are inefficient. 
	- eg: cannot scan over all keys **between kitty000 and kitty999** , each key has to be looked up individually on the hashmap
- (solved) Crash Recovery — you lose all data in memory (hash-table)
	- You _could_ loop through the "database" file and re-populate the hash-table upon startup... though this is slow.
	- Bitcask speeds this "recovery" by storing snapshots of the hash-table on disk regularly. 
- (solved) you might run out of disk space since the same "database" file has lots of duplicates, (since you dont want to overwrite old values)
	- Segmentation, Compaction & Merging will help reduce the growing file size on disk. "Compaction" means throwing away duplicate keys in the log, keeping only the most recent update for each key. 
	- Done on a background thread. 

##### Segmentation and Compaction
Break the logs into _segments_ of certan size. close the file when a segment reaches its max limit, =>  write to new segment. The old(closed) segment is frozen, immutable. 

Why immutable? Since its just way too easier/faster to keep on appending at the end than seeking the exact position to overwrite. Random writes on disk is slow. Also its good for concurrency and crash recovery. 

During reads, the latest segment is checked for the presence of a key, if not, second-most recent segment is checked (every segment has an associated hash-table in memory).

Then, later on, do _compaction_ on these segments ( throw away duplicate keys, keeping only the recent update for each key)
![](../assets/ddia-02.png)

Since compaction makes segment sizes smaller, Compacted segments can then be merged into  new segment, throwing away the old segments.(Why?— merging process keeps the number of segments small, so lookups dont need to check many hashmaps(each segment has one hashmap)) . this can be done in a background thread.

![](../assets/ddia-03.png)
Also, regular compaction and merging of segments significantly reduces fragmentation of disk.

#### Storage & Retrieval — Indexes | LSMTree with SSTables
_sort by keys_
> **Note**
> _whole approach is called LSMTree, which uses memtable(redblack tree) in memory and SSTables on disk_

Within each of the segment files, entries are sorted by key. ( But how do you sort them in the first place? This sounds like you need to perform sorting ON disk? like B-Trees?..But doing it in-memory is far faster. We use AVL Trees or RedBlack Trees to do this in memory . This is a "memtable". When the tree gets big enough, its flushed to a segment on disk, which will be sorted , since you can read values one by one from RedBlack tree in sorted order )

Benefits of Sorting...
- merging segment files get far simpler/faster (compaction)
- no duplication of keys in segment files (smaller size segments)
- "hash index" kept in memory gets much much smaller, since you dont store offset for every single key now. You only store offset of the first key in the segment.
	- For reading a value, you jump to the nearest offset and run a sequential scan(or run binary search!)

![[ddia-04.png]]
Merging segments is just merge sort algo. The merged segment is automatically sorted by the key. if same key appears in multiple segments, consider the key value in the newest segment.

![](../assets/ddia-05.png)
No need to maintain a index(hashtable) of ALL keys in memory. split the segment into blocks and store only offsets of the first key in the block. then for every key that you are searching, you can start at an offset and then do linear search until you find the key(Or binary search).
You DO need an index of few keys though, not totally ignore the index. But the number ofkeys in the index is considerably smaller now because of sorted nature of the segment. saves disk space.
![[ddia-13.jpeg]]
How Writes are handled
1. When a write comes in, add it to in-memory balanced tree DS (redblack tree, avl tree). This tree is called "memtable". (whenever you write to memtable, also write to a log for crash recovery. Every memtable has its own set of logs. When the memtable is flushed later to SSTable on disk, the corresponding logs are discarded)
2. When memtable(tree) size exceeds a limit (few MB), flush it to disk as an SSTable. (This can be done very efficiently since the tree already maintains the k-v pairs in sorted order, by key). The new SSTable becomes the most recent "segment" of the DB. While memtable is being flushed to a SSTable on disk, the incoming writes can continue on a new memtable. 
3. From time to time, compaction and merging of segment files (SSTables) on disk. 
How reads are handled
1. first try to find the key in the memtable, then in most recent SSTable(segment on disk), then in the next older segment, so on
2. Performance will suck if youre looking up a key that doesnt exist in the DB. So you use a BloomFilter to check if the key exists or not;

>**Note**
>_This is used in LevelDB, RocksDB, Cassandra, Google BigTable, Cassandra, HBase, ScyllaDB.
>LevelDB is can be used in Riak as an alternative to Bitcask

>**Note**
>_Also used in Lucene. , inverted index
>memtable contains key=term, value=(list of ids of documents containing the term)
>flushed to SSTable-like sorted files, which are merged in the background._
#### Storage & Retrieval — Indexes | B-Trees
> _overwrites values... in contrast to log structured where values are just appended, and merged asynchronously._

k-v pairs are sorted by Key on disk. (similar to SSTables)
- Lay out data in "pages" on disk. Each page can store references to multiple other pages. *The number of references to other pages = "branching factor"*. page size = 4KB. same as "blocks" on the disk. 
- keys on every "page" are in sorted order. 
- Each "page" is a node in the BTree. 
- Read/write one "page" at a time.
- Only the leaf node "pages" contain the values. 
- To read, you begin at root page, and traverse all the way upto the leaf page to obtain the value.
- Height of most BTrees is upto 4. (Can store upto 256TB)
- Algo ensures that tree remains balanced. Height = O(LogN) always.
- For Crash Recovery -> Write Ahead Logs (WAL)
- For Concurrency -> Lightweight locks or Latches before write.
	- You do all this locking because you are OVERWRITING. Had you followed log structured approach, you'd just keep appending and never overwrite old values, you wouldn't have to worry about concurrency and thread safety. 
	- This is one of the main reasons why WRITES ARE SLOW on BTrees., because of LOCKS! 
		- Incoming writes are blocked. In contrast to log structured where incoming writes keep appending without any lock/block. And compaction happens asynchronously in the background. 
- Optimisations
	- Since sequential scans happen often, its good to try and lay out all leaf nodes side by side on disk
	- Or atleast keep pointers left and right on all leaf nodes.

![[ddia-18.png]]

For Updates, you reach the leaf page, overwrite the value and write out the entire page back to disk.
For Inserts, you reach the leaf page and insert the key and value (ensuring the page is still sorted by keys), and write out the entire page back to disk. If the page doesn't have enough space.. You break the page into 2. The parent page is updated to account for new subdivision of the leaf page.

![[ddia-19.png]]

For Crash Recovery
- WAL (Write Ahead Logs)
#### OLTP vs OLAP
Storage engines are either optimised for "transactional workloads" or "analytical workloads", but not both (mostly). 

#### Column Oriented Storage — OLAP



## Why distribute data across multiple machines?

- Scalability
- HA
- Latency

## Coping with higher load

- Scaling up
  - **Shared-memory architecture**
  - cost grows faster than linearly
  - due to bottlenecks, _a machine twice the size cannot necessarily handle twice the load_
  - no HA
  - no fault tolerance
  - limited to single geographic location (high latency)
- Scaling out
  - **Shared-nothing architecture**
  - each machine is a _node_

## Replication vs Partitioning

these are the 2 ways to distribute data across nodes

- Replication
  - redundancy
  - HA
  - performance
- Partitioning
  - sharding
  - smaller subsets in distributed to each node.
