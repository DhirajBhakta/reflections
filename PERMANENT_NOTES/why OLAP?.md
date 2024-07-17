
#### OLAP — Created to decrease the load on primary OLTP Databases
At first, the same DB was used for OLTP and OLAP. But then OLAP queries started affecting concurrently running critical OLTP queries. So they had to be made separate.

#### Storage & Retrieval — OLTP vs OLAP
Storage engines are either optimised for "transactional workloads" or "analytical workloads", but not both (mostly).

>**Note** _Transaction  <> ACID
>_The term originated from money transfer use-cases "commercial transaction"..making a sale, paying salary, placing order. But databases expanded into other areas and the term "transaction" stuck._
>_The term "transaction" refers to a group of reads and writes that form a logical unit, need not necessarily have ACID properties. 
>Transaction Processing just means allowing clients to make **low latency reads and writes** — in contrast to Batch Processing which run periodically._


**Transactional workloads (OLTP)**
- OLTP = _an "interactive"(online) application looks up a small number of records by some key, using an index. Records are updated/inserted based on user's input. _ 
- Size =_GBs to TBs_
- Read Pattern = _small number of records , fetched by key_
- Write Pattern = _random-access, low-latency writes from user input._
- Used by end users, so ..Huge volume of requests
- touch only small number of records in each query
- queries depend on a key; index is made on that key
- BOTTLENECK: Disk seek time is the bottleneck here
- All values in a row are laid out next to each other.
  
**Analytical workloads (column oriented storage) (OLAP)**
- OLAP= _data analytics. query needs to scan over HUGE number of records, only reading FEW columns per record, & calculates aggregate stats(sum,count,avg). Helps business intelligence...business to make better decisions._
- Size = TBs to PBs
- Read Pattern = _Aggregate over LARGE number of records_
- Write Pattern = _Bulk import via ETL or event stream_
- Cons:
	- Writes are really slow.
	- Why?: data laid out in columns. One file contains just one column of all rows. You have to INSERT in between and SHIFT all the subsequent values DOWNWARDS!
	- (_Can use [[LSM Trees + SSTables]] to speed up_) : in memory memtable --> flush to SSTables
- used by business analysts, .. so low volume of requests
- each query will need to scan millions of records
- indexes are less relevant [[#OLAP — Traditional indexing (like in OLTP) does not work here]]
- encoding data compactly is very important, to minimize the amount of data the query needs to read from disk.
- BOTTLENECK: Disk Bandwidth is the bottleneck here
- [[column oriented storage]] suit well here. All values in a Column laid out next to each other, say in a single file meant for a particular column
	- To reconstruct a row, you visit the Nth value in each column file.
	- You can **compress** a given column file. , but say **bitmap encoding** or **run-length encoding**. 
	- Allows more data to live on the CPU cache.
	- Vectorized SIMD operations
- Data Model = **_Star Schema or Snowflake Schema_**
	- Central "fact table".  Will have too many columns, >100 >1000. Number of rows is HUUGE, petabytes
	- Multiple "dimension tables". Will have too many columns, >100
- You almost never run queries like `SELECT * from table` here. You'd just need a few columns, that too aggregates.


#### OLAP — ETL
![[ddia-20.png]]
"Data warehouse" is a separate database for OLAP queries. It contains a read-only copy of the data in all the other OLTP DBs  obtained via **ETL (Extract - Transform - Load )**  = _extracted via Bulk import, periodic import or a continuous stream of updates., transformed into analysis-friendly schema, cleaned up, and then loaded into the data warehouse_


#### OLAP — Traditional indexing (like in OLTP) does not work here
Indexing algorithms like HashIndex, BTrees, LSMTrees work for OLTP databases, but not for OLAP. **_in OLTP, rows are laid out next to each other. In OLAP, columns are laid out next to each other_**, because their access patterns are different. 
- data warehouse can be optimised for analytic access patterns
- data warehouse frees up OLTP DB from overhead of running analytic loads.
- Both OLTP and OLAP use a relational (SQL) interface.
- small companies can continue to use OLTP DB as OLAP too.

#### OLAP — Materialized Views
_Pre-computing most used queries_
- speeds up reads
- slows down writes, since you have to do additional work to populate the materialized views
	- Not a big deal since writes are done by batch jobs / ETL in background anyways. Not realtime.

#### OLAP — Materialized Views: Data Cubes
Data cubes are special types of materialized views
![[ddia-74.png]]

#### OLAP — Data Model: Star Schema
TODO: how does star schema improve read performance ? less joins? how does it improve perf in relational DBs and in columnar storage ?
Star Schema for OLAP (Wiiiiiide)
![[ddia-21.png]]
- Core idea is to avoid joins. 
- At the centre, there's "Fact table"
	- has too many columns
	- has way too many rows . Petabytes..
	- each row represents an event that happened at a time. A page visit, a click, a sale. This gives max flexibility (although it sounds like youre blowing up the number of rows since the number of events is too much)
- Connected to the fact table, there are "Dimension tables"
	- has too many columns
	- has very few rows
	- eg: Employee, Product, Customer etc. Pretty much like normalization. 
	- Dimension tables represent _who, what,where, why, how_ of the event in fact table.
	- > In "Snowflake Schema" , dimension tables are further broken down into subdivisions. More normalized.

