- single c++ binary!
- shared nothing architecture
- column storage with vectorized query execution
- built in sharding and replication
- scans billions of rows per second -- column oriented
- lock free inserts 
- distributed parallel queries
- doesn't have a cost based query optimizer. why?
- doesn't have a caching layer like in InnoDB(MySQL). why? (but it does use the OS page cache(linux))

## Clickhouse top usecases
_Any usecase where you have very large amount of "structured data"_
_Clean, structured, immutable events._

- network flow logs + analysis on them
- logs. lots and lots of logs. & Diagnose RC of failures from logs.
- adtech: real time ad bidding
- financial markets: marking complex assets to market value
- web analytics. clickstream. analyzing website traffic (original Yandex Metrica usecase for which CH was initially built)
- Observability : sensoring and monitoring data, telecom data

> Why was Clickhouse created?
> . . . . . . . . . . . . . . . . . . . . . . . . . 
> to support Yandex Metrica (#2, Next to Google Analytics)
> needs to ingest 25bn events/day.
> - must store all events (non-aggregated)
> - need to slice and dice across many (any) columns.

When NOT to use clickhouse?
- OLTP workloads. CH doesnt have UPDATE statements/ transactions.
- high load of single row queries (use a k-v store instead.)
- normalized data. bad support for joins
- document storage/ blob storage.
## Why is clickhouse fast?
Vectorized Query Execution
- Specialized hardware : SIMD CPUs with specialized SSE 4.2+ support
- Efficient dispatch on all available cores (all 16 cores go to 100% on htop)

Specialized algorithms 
- by data type: 14 GROUP BY algorithms
- by data size: whether data fits in memory
- by ordering: whether data is already (partly) sorted or not
- data distribution: eg: multi-armed bandits to optimize LZ4 decompression
- ... lots of specialized engines for specific usecases.

Compression:
- LZ4 and ZSTD compression to reduce storage size.
- Codecs to reduce column input to compression.

Append Only:
- insert as quickly as possible (append)
- reorganize - merge - compaction of "parts" on the background.
- Very rapid ingest + very efficient reads.
- ~similar to LSM Trees + SSTables

Other reasons:
- Cached primary key and mark indexes for fast lookup
- Skip indexes, Bloom Filters to eliminate unnecessary I/O
- Sampling to get approximate "good enough" results quickly
- Materialized columns to optimize table storage incrementally
- Materialized views to reshape data structure

## Shared Nothing Architecture
TODO
## Column Oriented DB
- True column oriented DB
- vector engine
Row Oriented DB  - good for updates.
Column Oriented  - good for reads (OLAP reads).

## What is faster, disk or memory ? (trigger warning)
- clickhouse is very mindful about how it lays out data on disk (read optimized), with good compression. to allow loading just very little data into memory.
- clickhouse parallelizes IO -> assemble the aggregates from parallel workers 

## vs Lucene?

ಈಗ ಸದ್ಯಕ್ಕೆ ತಪ್ಪದೆ ಸೋಮವಾರದ ದಿನ ಶಿವನ ದೇವಸ್ಥಾನಕ್ಕೆ ಹೋಗಿ 10 ನಿಮಿಷ ಕುಳಿತುಕೊಂಡು ಬರುವುದನ್ನು ಮಾಡಿ ತಪ್ಪದೆ ಇದನ್ನು 9 ಸೋಮವಾರಗಳು ತಪ್ಪದೆ ಮಾಡಿ ಜೊತೆಗೆ ಒಂದು ಪಂಚಮುಖಿ ರುದ್ರಾಕ್ಷಿಯನ್ನು ಧರಿಸಿ ಇದು ಬಹಳ ಉತ್ತಮವಾಗಿದೆ
## Compression & Codecs
```SQL
CREATE TABLE test_codecs (
	a String,
	a_lc LowCardinality(String) DEFAULT a,
	b UInt32,
	b_delta UInt32 DEFAULT b Codec(Delta),
	b_delta_lz4 UInt32 DEFAULT b Codec(Delta, LZ4),
	b_dd UInt32 DEFAULT b Codec(DoubleDelta),
	b_dd_lz4 UInt32 DEFAULT b Codec(DoubleDelta, LZ4)
)
Engine = MergeTree
PARTITION BY tuple() ORDER BY tuple();
```


## Federated Queries
TODO (using Integration Engines like S3Engine, PostgresEngine, KafkaEngine, MySQLEngine)

## Projections

## TableEngines

MergeTree is the default engine.

MergeTree:
- 

ReplacingMergeTree:
- ...

AggregatingMergeTree:
- ...
- Most used if your workloads are aggregations.

SummingMergeTree:
- specialization of AggregatingMergeTree

CollapsingMergeTree:
- to implement UPDATEs

VersionedCollapsingMergeTree:
- to implement UPDATEs
- MVCC style updates.

---
# Clickhouse Internals

## Architecture
![[ch_013.jpeg]]

### Sparse Index
_Goal is to fit the index in RAM_

Unlike B-Tree Index where we have one entry in the index per row, CH sparse index wants to keep the index as small as possible, which can fit into memory.
**Only the _first row in every granule_ is used to store the (location offset+pk) in the index** 
Every 8192nd Row is held in the index. (just location offset + PK)

![[ch_007.jpeg]]
![[ch_008.jpeg]]
### Granules
_Unit of index lookup_
But NOT the unit of data movement. Its "Blocks"
- read up "adaptive index granularity"
### Parts
- unit of Transaction is a "Part", NOT at the row.
ParitionKey helps decide how to break into Parts.

### Block
- default block size = 65000 rows.
### Mark and Mark Index
TODO

### Skip Indexes
TODO

### TableEngines 
We have 
- Core Engines
- Integration Engines (eg: KafkaEngine, S3Engine, PostgresEngine) to source data from other data sources.
![[ch_001.jpeg]]
MergeTree is the native table engine. It works similar to LSM Trees.
![[ch_011.jpeg]]

![[ch_006.jpeg]]


#### Data layout of MergeTree
![[ch_002.jpeg]]
![[ch_027.jpeg]]






![[ch_003.jpeg]]

The "compressed block" contains multiple granules.

> Note on "parts" and INSERTs
> . . . . . . . . . . . . . . . . . . . . . . . . . . 
> _INSERTS (batches) are append only, merge later._
> every batch of insert immediately creates a "part" and that "part" is immediately query-able.
> But it is costly to query every single "part" during say a `SELECT count(*) from tbl`, so background merges will merge N parts into a single part, on which the query can run later on.
#### Storage Layout of a single "column"
a single column is stored as two files `.mrk` and `.bin`



## Replication
_async, multi-master replication_
![[ch_005.jpeg]]

#### ReplicatedMergeTree -- Distributed
- N "Shards".
- Umbrella Table that knows the locations of all shards and replicas.
![[ch_004.jpeg]]
![[ch_010.jpeg]]

# Query Optimisation & Performance Tuning
#### Usual Performance suspects
- Codecs.
- Compression.
- Datatypes.
- Primary key index.
- Skip index.
- Data partitioning.
- Sharding.
- Read Replicas.
- Projections & Materialized views.
- In-RAM Dictionaries.
- Tiered Storage.
- Distributed Query.


#### Principles for large datasets in clickhouse
- Reduce queries to a single scan
- Reduce I/O
- Parallelize query
- Lean on aggregation (instead of joins).
- Index information with materialized views.

### Unoptimised table
```SQL
CREATE TABLE IF NOT EXISTS readings_unopt (
sensor_id Int64,
sensor_type Int32,
location String,
time DateTime,
date Date DEFAULT toDate(time),
reading Float32
) Engine = MergeTree
PARTITION BY tuple()
ORDER BY tuple();
```
- Suboptimal datatypes
- no codecs
- no partitioning or ordering
	- (just throw in the rows, and order them in the order they arrive)

Better table
```SQL
CREATE TABLE IF NOT EXISTS readings_zstd (
sensor_id INT32 Codec(DoubleDelta, ZSTD(1)),
sensor_type UInt16 Codec(ZSTD(1)),
location LowCardinality(String) Codec(ZSTD(1)),
time DateTime Codec(DoubleDelta, ZSTD(1)),
date ALIAS toDate(time),
temperature Decimal(5,2) Codec(T64, ZSTD(10))
) Engine = MergeTree
PARTITION BY YYYYMM(time)
ORDER BY (location, sensor_id, time);
```
How is this better?
- Optimised data types
- Codecs + ZSTD Compression
- ALIAS Column
- Time based partitioning
- Sorting by key columns + time.

Single unaggregated table data is the key
![[ch_012.jpeg]]


. . . . . . . . . .

### How do queries work?
almost all queries involve aggregation
```SQL
SELECT Carrier, avg(DepartureDelay) as Delay
FROM ontime
GROUP BY Carrier
ORDER BY Delay DESC
```
#### Example case study on query performance, resource usage
![[ch_014.jpeg]]
You need to maintain datastructures(like hashmap) to track unique combinations of grouping keys and their corresponding aggregate values
LHS:
- query groups data only by Carrier. 
- Hashmap needed is small. there are few unique carriers(handful of airlines).
RHS:
- query groups by both Carrier AND FlightDate, plus tracks aircraft info.
- Hashmap is much larger. way more unique combinations (carrier x date)
- key would look like `AirIndia+20230101`. value is current aggregate (sum,count,etc), here avg(delay)

> In database systems like ClickHouse, when you run an aggregation query (using GROUP BY), the system needs to maintain data structures to track the unique combinations of grouping keys and their corresponding aggregate values. Hash maps are the data structure typically used for this purpose.

Here's what's happening in the two examples shown:

**Left example (simpler query):**

- Query groups data only by Carrier
- Uses just 0.84 seconds and 1.6 KB RAM
- The hash map needed is small because there are few unique carriers (likely just a handful of airlines)

**Right example (more complex query):**

- Query groups by both Carrier AND FlightDate, plus tracks aircraft info
- Uses 3.4 seconds and 2.4 GB RAM
- The hash map is much larger because there are many more unique combinations (each carrier × each date)

Why hash maps are used:

1. When aggregating data, ClickHouse needs to maintain a "running total" for each unique group
2. It uses a hash map where:
    - The key = combination of GROUP BY fields (e.g., "Delta" or "Delta+2023-01-01")
    - The value = current aggregate values (the sum, count, etc.)
3. For each row processed, ClickHouse:
    - Calculates a hash of the grouping key
    - Looks up that key in the hash map
    - Updates the aggregates for that key

The performance difference occurs because:

4. More complex grouping = more unique keys = larger hash map
5. Larger hash maps may not fit in CPU cache, causing slowdowns
6. More keys means more hash calculations and lookups
7. When the hash map grows beyond available memory, performance degrades significantly

This is why the slide mentions "simple aggregate, short GROUP BY key with few values" vs "more complex aggregates, longer GROUP BY with more values" - the latter creates much larger hash maps that require more memory and processing time.

![[ch_015.jpeg]]
Why parallelism makes aggregations faster?

When ClickHouse runs an aggregation query with multiple threads:

1. **Data Partitioning**: The dataset is divided into multiple parts, with each thread processing its own portion
2. **Separate Hash Maps**: Each thread creates and maintains its own hash map for its partition
3. **Parallel Processing**: All threads work simultaneously on their own data chunks
4. **Final Merge**: Once each thread completes, their partial results (hash maps) are merged into a final result

This parallel approach dramatically reduces processing time, as shown in the graph - going from 4.486 seconds with 1 thread to just 0.954 seconds with 16 threads.

#### Why RAM Usage Is Surprisingly Lower

The counterintuitive part is that RAM usage actually decreases as threads increase (from 1.91GB to 1.73GB). This is unexpected because theoretically, multiple hash maps should require more memory than a single one. Here's why this happens:

1. **Hash Map Efficiency at Different Sizes**:
    - Hash maps become less memory-efficient as they grow larger
    - A single huge hash map has more overhead for collision handling
    - Multiple smaller hash maps can be more space-efficient in total
2. **Memory Locality**:
    - Smaller hash maps have better CPU cache utilization
    - Each thread works with a hash map that fits better in its CPU cache
    - This improves performance and can reduce overall memory pressure
3. **Per-Thread State Size**:
    - With the partition size reduced by a factor of N (where N = number of threads)
    - Each thread's hash map is smaller by more than a factor of N
    - This is because hash map memory usage often scales non-linearly with the number of entries
4. **Data Distribution Effects**:
    - When data is partitioned, some duplicated keys that would appear across different threads can be merged earlier
    - This can lead to more efficient intermediate aggregation

In this specific case, the total memory footprint actually decreases as parallelism increases, showing that for this particular aggregation query, the efficiency gains from using multiple smaller hash maps outweigh the overhead of having multiple execution threads.

This demonstrates why ClickHouse's parallel aggregation strategy is particularly effective - it not only speeds up processing dramatically but can sometimes reduce memory requirements as well, allowing more complex aggregations to run efficiently.


### Tips to make aggregation queries faster
- remove/exchange "heavy" aggregation functions
- Reduce the number of values in GROUP BY
- Increase max_threads (parallelism)
- Reduce I/O
	- filter out unnecessary rows.
	- improve compression of data in storage.

### Tips to reduce memory usage in aggregation queries
- Remove/exchange "heavy" aggregation functions
- Reduce number of values in GROUP BY
- Change max_threads value
- Dump aggregates to external storage
	- SET `max_bytes_before_external_group_by` > 0
- Filter out unnecessary rows

### How JOIN works
_CH uses Hash Join_.
![[ch_016.jpeg]]
![[ch_017.jpeg]]
![[ch_018.jpeg]]
![[ch_019.jpeg]]
![[ch_020.jpeg]]
Left table (BIG)................................full scan
Right table (SMALL)........................in memory hashmap (keys + columns from Right table.)
- keep the Right table small.
- Minimize the columns joined from the right table.
- Add filters on the right side to reduce rows.
- JOIN after aggregation if possible.
- Use a dictionary instead of JOIN.
	- Dictionaries are just loaded once and can be shared across queries.

Step 1: Understanding the JOIN Challenge
JOIN operations in databases need to match rows from two tables based on a common key. In traditional databases, this is often done using nested loops (checking each row in one table against each row in another), which is very inefficient for large datasets. ClickHouse takes a different approach optimized for its columnar architecture.

Step 2: ClickHouse's Hash Join Strategy -- CH's fundamental approach to joins.
1. **Load the smaller table first**(Right side table): ClickHouse begins by loading the right-side table (typically the smaller one) entirely into memory. _Why?_ This minimizes memory usage since keeping the smaller table in memory is more efficient. If you tried to load a very large table into memory, you might run out of RAM.
2. **Create an in-memory hash table**: ClickHouse builds a hash table from the right-side table's join keys. _Why?_ Hash tables allow for O(1) lookups, meaning ClickHouse can find matching rows almost instantly, regardless of table size. This is crucial for performance.
3. **Scan the larger table in parallel**: The left-side table is processed in chunks by multiple threads simultaneously. _Why?_ Parallel processing dramatically improves performance by utilizing multiple CPU cores. Each thread handles its own portion of data independently.
4. **Match and join as you go**: As ClickHouse scans through the left table, it looks up each row's join key in the hash table to find matches. _Why?_ This "streaming" approach means ClickHouse doesn't need to store the entire result set in memory at once.
5. **Merge the results**: The partial results from multiple threads are combined into a final result set.

Step 3: Inside the Scan Process
what happens during the table scan?
1. **Join condition analysis**: ClickHouse identifies the join keys (in this case, `a.IATA = o.Dest`). _Why?_ The join condition determines which columns will be used for lookups in the hash table.
2. **Stream processing**: As each row is read from the left table (`ontime`), ClickHouse looks up the corresponding value in the hash table. _Why?_ Streaming means ClickHouse can process tables larger than available memory because it only needs to hold a portion in memory at any given time.
3. **Building results incrementally**: When matches are found, ClickHouse combines the data from both tables to form result rows (like the ATL and ORD examples shown). _Why?_ This incremental approach allows ClickHouse to begin producing results immediately, without waiting for the entire table to be processed.

Step 4: Optimizing Joins with Aggregations
optimization strategy:
1. **The problem with direct joins**: When joining after a full table scan, you might be joining far more rows than necessary. _Why?_ Joining at the row level before aggregation means you're processing the maximum possible number of rows, which is inefficient.
2. **Aggregating before joining**: ClickHouse can aggregate the left table first to reduce its size dramatically. _Why?_ If you need aggregated results anyway, it's much more efficient to aggregate first (reducing millions of rows to perhaps thousands) and then join.
3. **Implementation via subqueries**: Image 4 shows how this is accomplished using a subquery. _Why?_ The subquery performs the aggregation first (reducing data from the `ontime` table), and then the outer query performs the join on this much smaller result set.
4. **Performance comparison**: Notice how the performance improves from 2.71 seconds/19.9 MB RAM to 0.663 seconds/1.58 KB RAM. _Why?_ The second approach processes much less data during the join phase. The join hash table is smaller, and there are fewer lookups to perform.

Step 5: How Hash Tables Enable Efficient Joins
1. **Hash table structure**: The hash table maps join keys to row data from the right table. _Why?_ This allows for constant-time lookups regardless of table size, which is crucial for performance.
2. **Memory tradeoffs**: The hash table requires memory, but this investment pays off in dramatically faster lookups. _Why?_ The alternative would be repeatedly scanning the right table for matches, which would be extremely slow for large tables.
3. **Collision handling**: When multiple records have the same join key (like multiple flights to ATL), the hash table maintains links to all matching rows. _Why?_ This allows ClickHouse to correctly perform different types of joins (inner, left, right, full) by tracking all possible matches.

Step 6: Parallelism in Join Operations
1. **Data partitioning**: The left table is divided among available threads. _Why?_ This allows each CPU core to work independently on its own portion of the data.
2. **Shared hash table**: All threads use the same hash table for lookups. _Why?_ The hash table is read-only during the join phase, so multiple threads can access it simultaneously without conflicts.
3. **Thread-local result buffers**: Each thread builds its own result set independently. _Why?_ This eliminates the need for thread synchronization during the join process, maximizing performance.
4. **Final merge phase**: Results from all threads are combined at the end. _Why?_ This step ensures the complete result set is properly ordered and consistent.

This multi-threaded approach is a key reason why ClickHouse can perform joins efficiently even on very large datasets, despite being a columnar database primarily optimized for analytical queries rather than joins.


> SQL. `IN` operator is also a JOIN under the hood.


### How distributed query works?
![[ch_021.jpeg]]
![[ch_022.jpeg]]
![[ch_023.jpeg]]
![[ch_024.jpeg]]
![[ch_025.jpeg]]
![[ch_026.jpeg]]



#### Tips to make distributed queries more efficient
- Think about where your data are located.
- move WHERE and heavy grouping work to LHS of JOIN
- use a subquery to order joins after the remote scan
- Use the query_log to see what actually executes on the remote nodes.
. . . . . . . . . . . . 
- reduce the amount of IO. 
	- TODO: how??
- (h/w) increase the number of CPUs
Initially everyone starts with (default)`MergeTree`, and then as needs arise, you choose MaterializedViews or Projections, and then begin to dive into various forms of MergeTrees.


### Ingestion
- avoid inserting one row at a time.
- CH recommends inserting 1million rows in a single batch!!
- Every batch creates one or more "Parts", and these Parts live in RAM + disk, until compaction (merging) happens. `max_insert_threads` dictates how many threads run in parallel to create and process these Parts.

How to make INSERTs faster?
- write bigger blocks (less merging afterwards)
- increase `max_insert_threads` (parallel creation of parts)
- enable `input_formal_parallel_parsing` to parallelize input parsing. (works well for CSV/TSV/Values data)

How to make INSERTs less memory intensive?
- Write smaller blocks (less memory required at INSERT time)
- Decrease `max_threads` (reduces parts simultaneously in memory)
- Disable `input_formal_parallel_processing`


 
### Codecs 
- if cardinality is 10-15,000 then make it LowCardinality
- Delta Encoding on timeseries ...gives 99.5%
- DoubeDelta on timeseries...gives 99% (because its monotonically increasing)

### Materialized Views
- primarily for aggregations. eg: SummingMergeTree.
- KafkaEngine
- Last-Point Queries (Lvals)

### Projections
TODO

### In-memory Dictionaries
TODO

### Sort Order
- change sorting order (primary key

### Bigger "Parts" are more efficient
- pick a PARTITION BY that gives nice fat partitions (1GB-300GB, < 1000 total parts per table). Can't decide? => Partition by month.
- Insert large blocks of data to avoid lots of merges afterwards. (10 million rows at once!)
- The simplest way to make blocks bigger is to batch input data.
- Avoid different  partition keys in the same block.
- `max_insert_block_size`. but defaults are okay.
- Look at logs and **actual part sizes** to see if you need to do more.

### Querying system tables 
```SQL
SELECT 
event_time,
type,
is_initial_query,
query_duration_ms / 1000 as duration,
read_rows,
read_bytes,
result_rows,
formatReadableSize(memory_usage) as memory,
query
FROM system.query_log
WHERE (user = 'default') AND (type = 'QueryFinish')
ORDER BY event_time DESC
LIMIT 50
```

How to see Part sizes?
```SQL
SELECT
table, partition, name, marks, rows, data_compressed_bytes,
data_uncompressed_bytes, bytes_on_disk
FROM system.parts
WHERE active -- part is in use "active"
AND level=0  -- part has not been merged "level=0"
AND database='default'
AND table='your_table_name'
ORDER BY table DESC, partition ASC, name ASC
```


### Memory Settings
- `max_memory_usage` : default 10GB (single query limit)
- `max_memory_usage_for_user` : default unlimited 
- `max_server_memory_usage` : default 90% of available RAM (all memory on the server, the clickhouse process).
- 
---
MISC
- what to keep in mind while optimizing CH Query performance? data read? WHERE Clause? partitions? marks? parts? 
- whats the point of compression? why does it make query perf better? isn't more CPU cycles wasted on compression/decompression?
- (linked to prev) What are Codecs? how is it related to cardinality ? what consequence on compression? (Codec is not the same as compression. but a prereq to compression)
	- LowCardinality(String)
	- Codec(Delta)
	- Codec(Delta, LZ4)
	- Codec(DoubleDelta)
	- Codec(DoubleDelta, LZ4)
	- ...what is codec + compression here?
- How distributed join works?
- what is the GLOBAL keyword?
- how does CH Cloud version work on object storage given that CH needs full control over how data is laid out on disk
- Is a very wide column (say 100-1000 columns) table an anti-pattern in CH ?
- There is no PK. The Sort Order is itself the PK. how does that even work in terms of data layout of the index??
- Why do you need materialized view to make KafkaEngine work ? is it really required? (see diagram below)
	![[ch_009.jpeg]]
- ![[ch_028.jpeg]]
- Why is the above ^ a common pattern to load data? why the materialized view in the middle?
- "Adaptive Index Granularity"? - Granules.
- Granules vs Parts vs Blocks.
- Whats exactly is inside Part?
- Projections vs MaterializedViews ?
- Multi Armed Bandits ?
- why is a subquery better than a JOIN in clickhouse?
- what is in-mem Dictionary?
- Large table joins are an antipattern. Why?
- `select * from s3('https://...s3.apsout-bucket/


### References
- https://highscalability.com/evolution-of-data-structures-in-yandexmetrica/
- [Secrets of Clickhouse Performance Optimisations - Talk](https://youtu.be/ZOZQCQEtrz8?si=58NA0ssD6RVY2zsV)
- https://tech.marksblogg.com/billion-nyc-taxi-rides-clickhouse-cluster.html
- https://news.ycombinator.com/item?id=21970952 How CH on a NUC beats scylladb on 80 Nodes.
- https://blog.cloudflare.com/http-analytics-for-6m-requests-per-second-using-clickhouse/
- https://blog.cloudflare.com/how-cloudflare-analyzes-1m-dns-queries-per-second/
- BigQuery to Clickhouse workshop (part1,2)
	- https://www.youtube.com/watch?v=u-WqU8MQW9A
	- https://youtu.be/eFhFmlYEsjE?si=xfXjhJgKVXeLW8yl