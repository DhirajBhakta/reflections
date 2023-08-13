## What is ScyllaDB
- Real time big-data DB
- Drop in replacement for Cassandra and Dynamodb
- 10X performance. Low tail latency
    - Closer to the hardware. Built on C++.
    - Completely asynchronous, avoid contention.
    - Low node count. But...Uses bigger and better nodes
    - eg: 900+ Cassandra nodes --> 70 Scylla Nodes
    - No JVM, no garbage collector, no stop-the-world, no latency spikes
    - Less complexity. Best performance out of the box. Not much tuning required. Smaller footprint, self-optimizing.
    - Throughput 10X higher than Cassandra
    - Linear scalability to many-core machines
    - Focussed on modern fast SSDs

## ScyllaDB Architecture
- distributed concepts derived from cassandra
- cassandra in-turn derived distributed concepts from DynamoDB... and data modelling concepts from BigTable.

#### Node

#### Shard 

#### Partition
A Partition is a subset of Data .
Partition Key is the unique identifier for a partition. Hash of partitionKey = Token. 


#### Ring
Scylla cluster = nodes visualised as a RING. 

#### Token/Token-Range
Token = hashed primary key. 
A Token identifies both node and the partition. 


#### Shared-Nothing Architecture

#### Keyspaces
Keyspaces are collection of tables. You define `replicationFactor` at the Keyspace level. "Keyspace" is analogous to "Database" in RDBMS.

#### Partition Key & Clustering Key 
Partition Key uniquely identifies a partition. 

#### Joins are impossible 
TODO




