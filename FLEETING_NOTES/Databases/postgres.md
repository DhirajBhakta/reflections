


https://github.com/pgexperts 
https://github.com/pgexperts/pgx_scripts
https://github.com/pgexperts/accidentalDBA
- 
- by default, a page size in pg is 8kb.
# postgres components
todo
- postmaster
- stats collector
# postgres architecture
todo

# MVCC and autovacuum
https://wiki.postgresql.org/wiki/Slow_Counting
https://youtu.be/GtQueJe6xRQ?si=BC285ADcf5tv4zyK
https://blog.sentry.io/transaction-id-wraparound-in-postgres/
http://www.postgresql.org/docs/current/static/routine-vacuuming.html
https://devcenter.heroku.com/articles/postgresql-concurrency

> *One piece of general advice is to stop the database and restart in single-user mode, thus running vacuum in a more isolated and safe environment.*

# Index
https://use-the-index-luke.com/
Postgres indexes store every version of the tuple until the VACUUM runs. So it will store a lot of dead tuples.This means that Postgres has to jump to the heap to get the row to check whether it is visible in the current transaction. This slows down a lot of index scans even if the index is being used.
- `pg_stat_user_tables` Will list all the tables that are having sequential scans. This will be a good indicator on where to add an index.
- `pg_stat_user_indexes` Will list all the indexes and tell you whether they are being used at all. Helpful to DROP useless indexes.
- How to check if index is bloated? dead tuples.due to mvcc. vacuum wont help. probably better to rebuild the index.

## BTree Index
- Multi-column B-tree indexes are sensitive to the order in which you specify the columns. If you specify an index on a, b and the search is just on b, postgres will most definitely NOT use the index.

## BTree unique index

## Covering Indexes...

## Partial Indexes...


## GIN index
- jsonb keys
- fulltext search: tsvector (multiple columns!!) (tokenizes, just like llm)
	- to_tsvector(), to_tsquery(), to_tsrank()
- fulltext search: pg_trgm
- https://youtu.be/cN3h7bgCg_s?si=7ptd9wCXdWN1xacA

## GiST index
nearest neighbor problem. "Starbucks problem"
- see KNN index

## SP-GiST
prefix search

## BRIN index

## Hash index

## Bloom Index
- arbitrary equality search on multiple columns at once! some GUI with tables will allow this kind of search.


# Why queries can be slow?
- pg configuration
- bloat due to dead tuples (mvcc) `check_postgres.pl`
- bad query 

## PG config
- `work_mem`
- `maintenance_work_mem`
#### **1. Memory-related Settings**
- `work_mem` – Defines the memory allocated for sorting, hashing, and query operations (like `ORDER BY`, `GROUP BY`). Increasing this can speed up queries by avoiding disk-based sorting. if its using merge joins, sorting, and u wanna let the planner know that it should use hash join(faster) then increase `work_mem`
- `maintenance_work_mem` – Memory used for maintenance operations like `VACUUM`, `CREATE INDEX`, and `ANALYZE`. A higher value speeds up index rebuilding and autovacuum efficiency.
- - `effective_cache_size` – Helps PostgreSQL estimate available memory for caching data pages. Setting this correctly improves query planning.
- `shared_buffers` – Determines how much memory PostgreSQL uses for caching data pages. Typically set to **25%-40%** of the total RAM.
- `temp_buffers` – Memory allocated for temporary tables in each session. Increasing this helps when using temp tables frequently.
#### **2. Parallel Query Settings**
- `max_parallel_workers_per_gather` – Number of parallel workers allowed for queries. Increasing this can speed up large aggregations and joins.
- `parallel_tuple_cost` – Controls the planner’s decision to use parallel workers based on the cost of fetching tuples.
- `parallel_setup_cost` – Determines the cost threshold for setting up parallel query execution.
#### **3. Autovacuum and Dead Tuple Handling**
- `autovacuum_vacuum_cost_limit` – Defines how much system I/O resources can be used for autovacuum operations. A higher value allows autovacuum to run more aggressively.
- `autovacuum_vacuum_scale_factor` – Controls the percentage of table changes required to trigger an autovacuum. Lower values trigger vacuums more frequently, reducing dead tuples.
- `autovacuum_work_mem` – Memory used by autovacuum processes for cleaning up dead tuples.

#### **4. Planner & Execution Settings**
- `random_page_cost` – Defines the cost of fetching a random disk page. Lowering this favors index usage.
- `seq_page_cost` – Cost of sequential scans. A higher value discourages sequential table scans in favor of index scans.
- `cpu_tuple_cost` – Estimated cost of processing a row. Adjusting this helps PostgreSQL decide between different execution paths.

#### **5. Checkpoint & WAL Settings**
- `min_wal_size`
- `max_wal_size` 
- `checkpoint_timeout` – Defines how often checkpoints occur (default: 5 min). Increasing this reduces frequent disk writes.
- `checkpoint_completion_target` – Controls the spread of checkpoint writes. Higher values reduce sudden I/O spikes.
- `wal_buffers` – Size of Write-Ahead Logging (WAL) buffers. Increasing this helps performance in write-heavy workloads.


# Query tips
- avoid IN, use JOIN
- avoid select * especially if a TOAST is involved. also JSONB parsing is costly.
- CTE results should be small.
# `EXPLAIN`
`auto_explain`
https://www.youtube.com/watch?v=mCwwFAl1pBU
https://www.pgmustard.com/blog/2018/09/07/our-boring-start-up-let-me-explain-analyse < all posts on this blog are good.
- pg runs a cost based optimiser.
- uses statistics to decide best set of steps.
- it actually makes lots of plans, not just 1. and assigns costs to each and then ranks
- the `stats collector` process collects the statistics to aid the planner.
- `EXPLAIN buffers` tells you if data came out from pg dedicated cache or from disk. (it cant know if it comes from OS cache)

### terminology
- nodes
- relation
- cost: no unit, no meaning. all relative
- modifier
- rows
- loops
- .......
- gather merge
- sort
- seq scan: usually v bad. prime candidate for optimization. but if rows are > 8% of the table, its just better to spin the disk and do seq scan. (what about SSD???). if youre pulling 10% of the table, an index scan is not the way to go.
	- Exception: your table is so small tht index is an overhead
	- Exception: you need all rows anyways
	- Exception: You need SO MUCH data from the table that index is an overhead. This usually happens when rate more than 9% of the table.
- nested loop join
- hash join
- hash
- bitmapOr
 - bitmap index scan https://you.com/search?q=explain+all+types+of+scans%2C+joins+and+create+a+guide+on+being+an+expert+on+reading+pg+query+plan+and...&cid=c1_6b924097-eb08-48f6-b820-65657622b80e
 - bitmap heap scan

research:
- joins: nestedloop, hashjoin, mergejoin
- aggregate: groupaggregate, hash aggregate, window aggregate
- when is seq scan better than index scan?

> **Key Insight**: Query execution happens entirely within the PostgreSQL server, not in libpq. The libpq library is only responsible for client-server communication protocol handling and result set delivery .

## Table of Contents
1. Understanding Scan Types
2. Join Algorithms
3. Reading Query Plans
4. Query Optimization Strategies
5. Performance Tuning Best Practices

## 1. Understanding Scan Types

### Sequential Scan
A sequential scan reads every row in the table sequentially. It's used when:
- No suitable index exists
- A large portion of the table needs to be read
- The table is small enough that an index lookup would be overhead 

```sql
EXPLAIN ANALYZE
SELECT * FROM users WHERE age > 30;
```

### Index Scan
Uses an index to locate specific rows, then fetches them from the heap (table):
- Efficient for highly selective queries
- Requires an index on the queried column
- Best for retrieving a small percentage of rows 

```sql
EXPLAIN ANALYZE
SELECT * FROM users WHERE user_id = 5000;
```

### Index Only Scan
Similar to Index Scan but can return results directly from the index:
- All required columns must be in the index
- Avoids table lookups entirely
- Most efficient for covered queries 

```sql
EXPLAIN ANALYZE
SELECT status, COUNT(*) FROM users GROUP BY status;
```

### Bitmap Scan
A two-phase approach combining benefits of both sequential and index scans:
1. Creates a bitmap of matching rows
2. Fetches rows in physical order
- Ideal for medium-selectivity queries 

```sql
EXPLAIN ANALYZE
SELECT * FROM users WHERE age BETWEEN 25 AND 35;
```

## 2. Join Algorithms

### Nested Loop Join
- For each row in the outer table, scans the inner table for matches
- Best for small tables or when one table is much smaller
- Requires an index on the inner table's join key for efficiency 

```sql
-- Example: Small result set join
SELECT u.name, o.amount 
FROM users u 
JOIN orders o ON u.id = o.user_id 
WHERE u.id < 100;
```

### Hash Join
1. Builds hash table from smaller table
2. Probes hash table with larger table rows
- Efficient for large, unsorted datasets
- Requires sufficient work_mem
- Only works with equality conditions 

```sql
-- Example: Large table join
SELECT u.username, COUNT(o.order_id) 
FROM users u 
JOIN orders o ON u.user_id = o.user_id 
GROUP BY u.username;
```

### Merge Join
- Requires both inputs to be sorted
- Scans both tables in parallel
- Efficient for pre-sorted data
- Works best with indexed columns 

```sql
-- Example: Sorted join
SELECT u.username, o.amount 
FROM users u 
JOIN orders o ON u.user_id = o.user_id 
WHERE u.status = 'active' 
ORDER BY u.user_id;
```

## 3. Reading Query Plans

### Query Plan Structure
- Read from bottom to top, inside to out
- Each node shows:
  - Operation type
  - Estimated cost
  - Actual timing (with ANALYZE)
  - Number of rows
  - Loop count 

### Key Metrics to Watch
1. **Actual vs. Estimated Rows**: Large discrepancies indicate outdated statistics
2. **Loops**: High loop counts in nested operations can indicate performance issues
3. **Buffers**: Shows I/O activity when using BUFFERS option
4. **Costs**: Relative values in arbitrary units 

```sql
EXPLAIN (ANALYZE, BUFFERS) 
SELECT * FROM users u 
JOIN orders o ON u.id = o.user_id 
WHERE u.status = 'active';
```

## 4. Query Optimization Strategies

### Index Design
1. Create indexes for:
   - Frequently filtered columns
   - Join keys
   - ORDER BY columns
   - GROUP BY columns

```sql
-- Recommended indexes for common queries
CREATE INDEX idx_users_status ON users(status);
CREATE INDEX idx_orders_user_id ON orders(user_id);
CREATE INDEX idx_orders_date ON orders(order_date);
```

### Statistics Management
- Run ANALYZE regularly
- Increase statistics target for important columns
- Monitor table statistics 

```sql
-- Update statistics
ANALYZE users;
-- Increase statistics detail
ALTER TABLE users ALTER COLUMN status SET STATISTICS 1000;
```

## 5. Performance Tuning Best Practices

### Configuration Parameters
Key parameters affecting query performance:

```sql
-- Memory settings
work_mem = '4MB'         -- Per-operation memory
maintenance_work_mem = '64MB'  -- For maintenance operations
effective_cache_size = '4GB'   -- Planner's estimate of cache size

-- Cost settings
random_page_cost = 1.1   -- For SSD storage
seq_page_cost = 1.0      -- Sequential read cost
```

### Common Optimization Techniques

1. **Rewrite Complex Queries**
```sql
-- Instead of subquery
SELECT * FROM users WHERE id IN (SELECT user_id FROM orders);
-- Use JOIN
SELECT DISTINCT u.* FROM users u JOIN orders o ON u.id = o.user_id;
```

2. **Use LIMIT with ORDER BY**
```sql
-- Add LIMIT to avoid sorting entire result
SELECT * FROM users ORDER BY created_at DESC LIMIT 100;
```

3. **Partial Indexes**
```sql
-- Index only active users
CREATE INDEX idx_active_users ON users(created_at) 
WHERE status = 'active';
```

### Monitoring and Troubleshooting

1. **Identify Slow Queries**
```sql
SELECT query, calls, total_time, rows, mean_time
FROM pg_stat_statements
ORDER BY total_time DESC
LIMIT 10;
```

2. **Check Index Usage**
```sql
SELECT schemaname, tablename, indexname, idx_scan, idx_tup_read
FROM pg_stat_user_indexes
ORDER BY idx_scan DESC;
```

> **Important**: Remember that all query execution happens inside the PostgreSQL server. The libpq library only handles client-server communication and result delivery .

This guide provides a foundation for understanding and optimizing PostgreSQL queries. Regular monitoring, testing, and maintenance are key to maintaining optimal database performance.