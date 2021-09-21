- there is a need to store and process big data
- demand for high performance when reading and writing with low latency
- High scalability High Availability

does your Relational table have

- a lot of nulls
- you find yourself denormalizing for read performance

Then you should consider NoSQL

# NoSQL &mdash; Not only SQL

- reading and writing data quickly
- support mass storage
- easy to expand
- low cost

## Data Model

- Key-value
  - Eg: redis, BerkeleyDB, Voldemort
- column oriented
  - Data is stored separately for each column
  - suitable for aggregation and data warehousing
  - eg: HBase, Cassandra, BigTable
- Document based
  - similar to key value but value is JSON
  - not concerned about high performance concurrent read/write
  - concerned about big data storage
  - concerned about query performance
  - eg: MongoDB, CouchDB, SimpleDB

## Redis

- key-value database
- data is entirely loaded onto memory (pure memory = good performance)
  - 100,000 read/write per second
  - limits the capacity
- periodically save data to hard disk in async fashion

Redis is suitable for providing high performance to small amount of data

## Cassandra

- Column oriented
- flexible schema &mdash; does not require to design DB schema at first
- adding or deleting fields is convinient

## MongoDB

- document based
- supports complex data types
- bson data type

## CouchDB

- document based
- ACID properties

-
