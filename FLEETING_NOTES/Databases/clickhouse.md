# TODO
- CH sparse index ::: Skip index.
- CH what exactly is getting "merged" ?
- CH granules ::: 8000 rows.
- CH materialized views.
- CH alter table page_hits materialize prjection prj; (what is projections?)
- CH best practises. case studies. 
- CH Sort keys ::: ORDER BY
- CH Primary and Secondary Indexes ::: Data Skipping Indexes ::: How data is stored!
- 


## Data Warehouse | OLAP usecases
_Gives quick answers...to open ended questions...on large datasets_
- opposite of OLTP ::: =OLAP
- column compression
- entire compressed col can fit in CPU cache! ::: L1,L2,L3
- Read compressed cols in PARALLEL!
    - via different CPU cores!!!
- If you think, in-mem is much faster than disk access::: https://www.youtube.com/watch?v=zDIK3Ej86GU
    - materialized views are even more faster.
- Vast majority of requests are for READs
    - large number of rows are extracted, but only a SMALL subset of columns.
    - Queries are relatively rare compared to OLTP postgres.
- Data is updated in large batches, (NOT row by row), or is not updated at all!
- Data is added to DB but is NOT modified.
    - HENCE Transactions are not necessary
- Transactions are not necessary.
- Low requirements for data consistency.
- There is one large table per query. All tables are small, except for one.

---

# Clickhouse
- Data Warehouse ::: OLAP.
- Single binary.
- SQL.
- competes with ::: Snowflake, Redshift
- good for aggregates.
- bad for mutations.
    - hence used alongside Clickhouse.
- Excellent compression!
- Vectorized processing! ::: SIMD ::: Parallel
- Store data on disk(cheap) 
    - Unlike presto which loads into memory. You need giant machines with tons of mem.
- Data skipping indexes
- Easy replication ;;; Easy Sharding(zk) ;;; horizontally scalable
- **Clickhouse doesnt use indexes!!** ::: Use materialized view instead.
    - No query optimizer, no EXPLAIN PLAN
    - Primary Index doesn't need to be unique.
- materialized queues.
- multiple specialised engines ::: MergeTree, ReplacingMergeTree, AggregatingMergeTree...
- "Granule" is smallest unit of data ::: 8000 rows.
- Multiple consecutive granules are collected into "Blocks" ::: -> compressed.
- projections ::: skipping indexes ::: 
- . . . .
- Posthost moved from Postgres->Clickhouse ::: solved scaling problems
- Uber uses clickhouse to store Logs!

### Clickhouse CONS
- mutations are not supported fully
    - (waits for parts to be merged)
    - data and mutations are stored separately. Both fetched on demand :(
- Transactions not supported fully.
- Sparse index is not a real index.


### Clickhouse Philosophy
_Insert Now, ... Optimise Later_
...Constantly merging data in background. ::: series data -> single values 

### Clickhouse Table Engines
Table Engine determines _how and where data is stored_
- Virtual Table Engines.
    - to manage/exchange data with external data stores.
    - external OLTP DB | Data Lakes | object stores | pubsub systems | KV stores.

- Special Purpose Table Engines.
    - DistributedEngine.
    - MemoryEngines ::: RAM storage
    - Dictionary ::: Fast lookups.
    - ViewEngines
    - TableEngines ::: TableFunctions

- MergeTree Engines ::: Core of ClickHouse storage
    - columnar storage
    - custom partitioning
    - sparse primary index
    - secondary data-skipping index
    - ORDER BY is very important!!! ::: Dictates how data is stored on disk!
    - **ReplacingMergeTree**
    - **CollapsingMergeTree**
    - **VersionedCollapsingMergeTree**
    - **SummingMergeTree** ;;; **AggregatingMergeTree**
    - **GraphiteMergeTree** (timeseries)
    - **ReplicatedMergeTree**
- Log Engines
    - Good for tmp tables | testing | DONT use these


### MergeTree
Inspired by LSM Trees
- inserts -> immutable parts on disk
- merge operation (compaction) in background job
- - merge operation can do additional data transformations
- - replacing merges | aggregating merges | 
- ...
- So users are encouraged to insert in **batches** 

