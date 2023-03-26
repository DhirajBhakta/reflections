# Indexes

Indexing is one of the **first** thing to do when DB read performance degrades.

- improve speed of reads
- (CONS) Increased storage and slower writes
  - write data + update the index.
  - slower insertion
  - slower updates
  - slower deletes.

Data sets that are TBs in size, but each row is very very small(1 KB) - ideal candiate for indexing!

You cannot afford to loop through so many rows just to find Bytes of data(single row)

## Gotcha

 IF the write throughput is very high compared to reads, then dont even think about adding indexes.
