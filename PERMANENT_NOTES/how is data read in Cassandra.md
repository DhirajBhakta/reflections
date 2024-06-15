[How is data read? (datastax.com)](https://docs.datastax.com/en/archived/cassandra/3.0/cassandra/dml/dmlAboutReads.html)
[Cassandra Performance: The Most Comprehensive Overview You’ll Ever See (scnsoft.com)](https://www.scnsoft.com/blog/cassandra-performance) 

![[ddia-72.png]]

![[ddia-71.png]]
1. Check the **memtable** (red-black tree)
2. Check the row cache (if enabled)
3. Check bloom filter (to ensure key really exists)
4. Check partition key cache (if enabled)
	1. cache hit
		1. Goes directly to the **compression offset map**
	2. cache miss
		1. checks the **partition summary**
		2. Then goes to **partition index**
		3. Then goes to **Compression Offset Map**
5. Locate the data on disk using **Compression Offset Map**
6. Fetches data from **SSTable** on disk.
![[ddia-69.png]]

Ignoring the caches, the read path mainly seems to be
`bloom filter --> partition summary --> partition index --> compression offset --> SSTable(disk)`

> **Note** : Partitions and SSTable have many-to-many relationship
> One partition can be spread across multiple SSTables.
> One SSTable can contain data from multiple partitions.

**Bloom Filter**: 
- tells if a SSTable definitely does NOT contain the data.
- tells if a SSTable _may_ contain the data.
- So it reduces the search space, and gives you a **list of SSTables** that _may_ contain the data.
	- you need to now traverse these SSTables to get your data.

**Partition Summary** (_sparse Index of the SSTable_)
- For every SSTable above, the partition summary is consulted.
- Partition Summary is a lightweight index of the SSTable.
- (it contains _sampled_ keys) One in every 20 keys is stored in the Partition Summary.
- Helps you narrow down which part of the SSTable _may_ contain the data.
- Stores the offsets of the row from the first value in the SSTable.

**Partition Index** (_dense index of the SSTable_)
- For every SSTable above, the partition index is consulted.
- It gets you the exact position of the data for given key.
- After narrowing down the section of SSTable which _may_ contain the data (with the help of Partition Summary above), you now have a narrowed down section of the Partition Index to search the exact position for the data.
	- Partition Summary is a _sparse tree_ 
	- Partition Index is a _dense tree_.
	- The sparse tree tells you which node in the dense tree to start the O(LogN) search from! (you don't have to start from the root of the dense tree!)
- Stores the offsets of the row from the first value in the SSTable.

**Compression Offset Map**
- Partition Index just stores the Logical address(offset from the first row in the SSTable) of the data blocks, but the data blocks might be further compressed into multiple blocks.
- Compression Offset Map stores the **Physical Address** of the compressed data blocks against the logical address.

>**Note**: _Compression Offset Map? Why??_
>isn't it the job of the Operating System's storage engine(Filesystem eg:Btrfs) ?
>- Not every filesystem does compression (eg: ext4). And even if it does, doing these things at the OS level will be far more inefficient than doing this at application layer. The same reason as why linux page caching is not used and DB's use their own caching.
>- Even a disk driver does these things, like mapping LBA(Logical Block Address) to PBA(Physical Block Address), but disk drivers know nothing about Application specific logic (here application = DB ) so its again better left to the DB.

#### The Caches
**Row Cache** : 
**Partition Key Cache**: stores a cache of the partition **index**. 





![[ddia-70.png]]