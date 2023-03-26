## Prerequisites
- Cassandra Architecture
- Dynamodb Architecture 

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


