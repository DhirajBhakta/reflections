ScyllaDB, Cassandra.. which rely on **LSM Trees**, where writes don't have to read/update something else before actually writing (like in BTree indexes), and can directly write it off.
But comes at a cost of higher storage requirements, and slower reads. -.- you need a lot of space to keep all the immutable files that build up, until compaction runs. Efficient compaction can help solve this though. Efficient caching at DB level can mitigate slower reads too!

Important to have underlying disk (nvme) to be fast enough. Write speeds "theoretical" at db is useless if the disk cant support the throughput

Generally, DBs will charge far higher for write heavy workloads **at scale** , than read heavy. 
## Immutable Files ??