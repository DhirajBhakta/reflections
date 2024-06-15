
#### Partitioning by Primary Key (Aproaches)
(Simple Key-value stores, or just primary key based partitions)
- ###### Partitioning by Key-Range
	- each partition gets a continues range of keys (A-C,  D-E, F-Z) .._like volumes of encyclopaedia_ 
	- key ranges are not necessarily evenly spaced...since data may not be evenly distributed. Goal is to distribute data evenly.
	- Within each partition, keys are stored in sorted order.
		- enables range based queries
	- cons
		- Can lead to hotspots.
		- you could add some prefix like "sensor_name" and then partition first by prefix and then by date. But this is adds overhead during reads.
- ###### Partitioning by Hash of the Key
	- _Consistent Hashing_
	- Reduces hotspots. **Uniform distribution** 
	- A good hash function can take a skewed data and make it uniformly distributed. Hash function need not be cryptographically strong.
	- Cons
		- You lose the ability to make range based queries.
		- keys that were once adjacent, are now scattered.
		- _can lead to hotspots in worst case when large volume of reads accesses **a single key**_ (extreme case)
			- celebrity posted a comment. celebrity UserID or the commentID is ....fucked. 
			- application _can_ reduce the skew here **by adding a prefix to the userID**. 
- Combination of above two
	- Cassandra's "compound primary key" across several columns = first column hashed... rest of the columns concatenated for range based partitioning.
	- You first identify the partition based on the hash of the first column...then you can do range based query once you identify the partition.

>**Note** Common technique to reduce hotspots = Prefixes
>If a single(or few) key is "hot", add a random number as prefix/suffix. 
>But downside affects the reads. You have to loop through all such random numbers and fetch values from every partition and combine it.  _additional bookkeeping_. 
>Please do this only for "hot" keys (small in number), not for all keys.


#### Partitioning by Secondary Key (Approaches)
(Secondary indexes don't map neatly to partitions)
_"filter cars by colour and make"_ - _you need a secondary index on colour and make. But will you choose a local index or a global index?_
_**Local Indexes** optimize for Write speed... **Global Indexes** optimize for Read speed._
- **Local Indexes** ... One Index per partition (scatter/gather)
	- "Document Partitions"
	- Each partition maintains its own secondary index. 
	- _local index_
	- Writes are simple and fast . You could write to the required partition and its corresponding index in "one transaction" action.
	- _writes are fast, reads are slow_
	- Cons
		- You need to query all partitions and combine the results
		- scatter/gather... make queries in parallel to all partitions. 
- **Global Index** 
	- "Term Partitions"
	- Covers data in all partitions. 
	- Can you store this global index on just one node? Yes.. _(But you may partition that index across nodes.(separate from primary key index))_
	- _one monstrous index tries to track it all, (itself split into multiple partitions (optional))_
	- More efficient reads (can use key-range or hash)
	- _writes are slower, reads are faster._
	- Cons
		- Writes are slower
		- Updates to global indexes are asynchronous..take time. Not instantaneous always.
		- Now you need to make sure that writes to data + writes to the index ..are atomic. You'd need distributed transactions if the associated index is on another node.

>**Note** Secondary Indexes
>Doesn't identify a record uniquely. Is just a way for **searching occurrences** of a particular value.
>_"find all articles starting with letter "a" and with colour red"_.
> Secondary Indexes are difficult to implement, so many DB's(k-v stores specially) have avoided them.

