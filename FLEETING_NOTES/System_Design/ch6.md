# Design Key-Value Store

- non relational DB
- `put(Key, Value)`
- `get(Key)`

### Characteristics

- High Availability
  - system responds quickly ,even during failures
- High Scalability
  - system can be scaled horizontally to support large data set
- Automatic Scaling
  - addition/deletion of servers should be automatic based on traffic
- Low Latency

### Single Server

- easy
- use hash table (everything in memory)
- but what if data gets larger and larger
  - compression
  - store frequently accessed data in memory
  - rest in disk

### Distributed Servers
