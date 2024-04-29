The easiest way to improve DB performance(latency,throughput) is to scale up/scale out the DB and tune . But that isn't enough after a point. 
[[always use the official drivers]]
[[clientside driver timeouts should be twice that of server timeouts]]
[[have observability in place]]
[[backups or maintenance tasks should not coincide with high user load times]]
[[concurrency-latency-throughput , little's law]]
[[ACID properties bring a severe performance hit]]
## Concepts
[[LSM Trees & Compaction]]
[[B Trees & B+Trees]]
[[ACID properties]]
[[transactions are costly]]
[[LWT - light weight transactions]]
[[prepared statements]]
[[consistency models]]
# Data
### Item Size
[[databases should NOT store large blobs]]
[[smaller payload causes memory fragmentation]]
### Item Type

### Dataset size


# Workload 
[[write heavy workloads]] / Cassandra, ScyllaDB
[[read heavy workloads]] / Dynamodb
[[mixed workloads]]
[[delete heavy workloads]]

