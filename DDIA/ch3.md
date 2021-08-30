# Ch3&mdash; Storage and Retrieval

Why? &mdash; to suit your needs, to choose a kind of DB, you need to have a rough idea of what the storage engine is doing under the hood

Big Difference &mdash; in storage engines optimized for

- Transactional workloads
- Analytical workloads (column oriented storage)

#### World's simplest DB

_append only sequence of records_ (sounds like logs? yeah)

- APPEND key value pairs to the end of the _file_ (awesome performance)
- SEARCH the entire file for keys when queried (bad bad performance) O(n)
- an UPDATE, is just an APPEND at the end of the file with new value for the same key
  
CONS? &mdash;<br/>

- reclaiming space so that the log doesn't grow forever
- handling errors and partially written records

<hr/>
## Index

&mdash; a trade off; <br/>

- speeds up reads
- slows down writes

Log structured indexes &mdash; Hash Indexes, SSTables and LSM trees

Page strucured indexes &mdash; BTrees

### Hash Indexes

![](../assets/ddia-01.png)
Scenario

- append only DB as discussed above
- _in-memory_ hashmap (key -> offset)
- as you append key-value pairs, you also update the hashmap
- every "update" is nothing but an append
  
CONS

- all keys need to fit in memory.
- if we just keep on appending to the file, it just grows way too large (segmentation and compaction and merging wil solve this issue)

##### Segmentation and Compaction

Break the logs into _segments_ of certan size. close the file when a segment reaches its max limit, &rarr; write to new segment

Then, later on, do _compaction_ on these segments ( throw away duplicate keys, keeping only the recent update for each key)
![](../assets/ddia-02.png)

Since compaction makes segment sizes smaller, Compacted segments can then be merged into  new segment, throwing away the old segments.(Why? &mdash; merging process keeps the number of segments small, so lookups dont need to check many hashmaps[each segment has one hashmap]) &mdash; this can be done in a background thread.

![](../assets/ddia-03.png)

real implementation &mdash;

- File Format
  - csv is poor. binary format is faster and simpler
  - first store length of the string in bytes
  - ...followed by the raw string in bytes
- Deleting records
  - append a special deletion record called _tombstone_
  - during merge, discard all prev values for the deleted key
- Crash recovery & partially written records
  - in-memory hashmaps are lost
  - you can ofcourse regenerate the hashmap for a segment by going through all records
  - better to just store snapshot of the in memory hashmap in disk
  - use checksums for detecting and ignoring partially written records
- Concurrency control
  - only one writer thread to append in strict sequential order
  - multiple reader threads for reads.

#### Pros of Hash Indexes

- appending and segment merging are sequential write operations &mdash; much faster than random writes
- Concurrency and crash recovery are simpler if append-only and immutable
- merging segments avoids disk fragmentation over time.

#### Cons of Hash Indexes

- hash table must fit into memory. what if you have large number of keys
- range queries are inefficient. " scan all keys between X and Y " &mdash; you have to lookup all keys one by one in hash map

### SSTables and LSM-Trees

Sorted String Tables &mdash;<br>
Sort the "logs" of key values pairs...by the key
![](../assets/ddia-04.png)
Merging segments is just merge sort algo. The merged segment is automatically sorted by the key. if same key appears in multiple segments, consider the key value in the newest segment.

![](../assets/ddia-05.png)
No need to maintain a index(hashtable) of ALL keys in memory. split the segment into blocks and store only offsets of the first key in the block. then for every key that you are searching, you can start at an offset and then do linear search until you find the key.
You DO need an index of few keys though, not totally ignore the index. But the number ofkeys in the index is considerably smaller now because of sorted nature of the segment. saves disk space.

##### How to maintain sorted order ? (LSM - Log structured merge trees)

In disk &mdash; BTrees
In memory &mdash; self balancing trees - AVL tree, red-black tree

Writes

- add to the in-memory self balancing tree (memtable)
- when memtable gets bigger than threshold, write to an SSTable file. tree is already sorted---so its efficient.
- Continue the writes to the memtable as the memtable is being written out to disk
- from time to time..run merging and compaction in background.

Reads

- first find the key in the memtable
- if not found, search the most recent on-disk segment
- if not found, search the next recent on-disk segment.
- looking up keys that are NOT in the DB can be very expensive
  - Use **Bloom filters**

Crash recovery?<br>
memtable is lost if crash happens. (this memtable is not yet written to disk). So write every single write to a log file. This will not be sorted ofc. but its purpose is just to restore memtable after a crash.

**Lucene**&mdash; full text search
Uses LSM trees. Key="terms" value=List of all documents in which that key occurs. So Lucene stores its term dictionary in LSM trees.

<https://yetanotherdevblog.com/lsm/>

### B-Trees

# Notes

- Cassandra and HBase use storage engines similar to LSM trees. Inspired by Google Bigtable paper.
