
# Ch1 - Ch 4 (PART 1)

- data stored on single machine

# Ch5 - Ch 9 (PART 2)

- data stored on multiple machines

## Why distribute data across multiple machines?

- Scalability
- HA
- Latency

## Coping with higher load

- Scaling up
  - **Shared-memory architecture**
  - cost grows faster than linearly
  - due to bottlenecks, _a machine twice the size cannot necessarily handle twice the load_
  - no HA
  - no fault tolerance
  - limited to single geographic location (high latency)
- Scaling out
  - **Shared-nothing architecture**
  - each machine is a _node_

## Replication vs Partitioning

these are the 2 ways to distribute data across nodes

- Replication
  - redundancy
  - HA
  - performance
- Partitioning
  - sharding
  - smaller subsets in distributed to each node.
