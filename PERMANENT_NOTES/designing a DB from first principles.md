#### Just using a Simple Array of Tuples
Seek to the position, overwrite.. O(N)
- adding removing tuples will be expensive. Need to find the correct position to add, and **shift** massive number of elements to maintain contiguity.

#### Append only log
Keep appending entries to the end of the "log". (updates to existing entries go as appends too)
- much higher write performance. No need to shift tuples
- reads will be slow since you read from the end of the log, upwards until you find the up-to-date value for the key.

#### in-memory Hashmap
But if the hashmap grows too large (>RAM), you're in trouble (Not scalable).

hashmap on disk is bad because _random access on disk is really slow_. [[aim for sequential operations on hard drive]] 

#### Indexes (on disk)
Extra metadata to help locate main data faster.
To Avoid O(N) scan on the entire dataset.

**Types of Indexes**
- [[hash indexes]] (key->byte offset on disk)
	- Pros
		- Fast. RAM > Disk
		- Easy to implement
	- Cons
		- All keys must fit into RAM. (if you store hashmap on disk, slow..cuz hashmaps work poorly on disk (random access sucks))
		- Bad for range queries
- [[LSM Trees + SSTables]] (memtable --> gets too big? => flushed --> SSTable --> compacted)
	- Pros
		- Fast Writes! Append-only writes.
		- Fast Writes! writes directly go to in-memory memtable
		- Good for range queries (Sorted nature of memtable, SSTable)
	- Cons
		- Slow reads (in worst case). Memtable--> SStable1-->SStable2... ->SSTableN
		- compaction in background can take up resources.
- [[B Trees & B+Trees]]
	- Pros
		- Fast Reads! atmost 3-4 levels for TBs of data.
		- Good for range queries(Sorted nature of BTrees (Physically next to each other!))
	- Cons
		- Slow Writes. Have to **write directly to disk** rather than in-memory.
		- Slow Writes. LOCKing is required when writing to a node in BTree (disk).

**How to Choose the best Index??**
- **Hash Index**: Fastest, but useful only on small datasets
- **LSMTree+SSTables**: Fast Writes, Slow Reads
- **BTrees**: Fast Reads, Slow Writes

