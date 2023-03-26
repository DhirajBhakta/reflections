# Sharding | Data Partitioning

- splitting up a DB/table across multiple machines
- **horizontal partioning**
- scaling out
- shared-nothing architecture

### Why

- you need to scale with data.(dynamically, as its difficult to "predict")
- it is cheaper to scale horizontally than vertically.
- small servers are cheap
- speeds up queries: number of rows in each shard is less | compared to a single DB server with all the rows
- reduced impact of outages. - outage might affect just one shard.

### When should you shard?

Sharding adds a lot of complexity. so do it only when -

- **data** exceeds the capacity of single DB node
- **volume** of reads/writes exceeds the capacity of single node.
- **n/w bandwidth** required by application is far more than what is provided by single node DB

### What to do before considering sharding?

- setting up a remote DB
  - DB has its own machine , separated from application server.
- caching
  - DB cache for improving reads
- create read replicas
  - improves read performance
  - Leader based replication
- Upgrade to a larger server.
  - vertical scaling

## Partitioning Methods

- Horizontal Sharding
![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTHSOecqTuEmjFJAoQfx3N_z7KpKqpSyxFKaw&usqp=CAU)
  - eg: zip codes <1000 in one table, rest in another table
  - Range Based Sharding...
  - make sure that ranges are evenly distributed. if one range is overloaded, and other ranges are underloaded...it leads to unbalanced partitions
  - ranges should be chosen very carefully
- Vertical Sharding
![](https://www.researchgate.net/profile/Gregor-Hackenbroich/publication/230706455/figure/fig3/AS:300472708681731@1448649684416/Vertical-partitioning.png)
  - based on columns (features)
  - instagram
    - profile info in one DB server
    - friends list in one DB server
    - Photos in one DB server
  - what if number of photos increases too much, YOU MAY NEED TO FURTHUR SPLIT - horizontal sharding and what not lol.
- Directory Based Sharding
  - a loosely coupled solution to solve the problems in (vertical | horizontal) sharding
  - a lookup service which knows the current partioning scheme
  - a lookup table which given a shard key, gives the shard ID of the shard.
  - the app doesnt know the details, abstracted away
  - an abstraction on top of the whatever partitioning scheme we choose.
  - we query our directory server that holds the mapping (Key->DB server)
  - loosely coupled + abstraction -> we can add servers to our DB pool or change partitioning scheme without impacting application
  - most flexible
  - need to check the lookup table for every query can hit performance
  - lookup table can become single point of failure - cannot read/write data

## Partitioning Criteria

- **Key/Hash based partitioning**
![](https://assets.digitalocean.com/articles/understanding_sharding/DB_image_2_cropped.png)
  - hash yields the partition number.
  - should ensure uniform allocation of data across servers
  - use **consistent hashing** to enable adding/removing DB servers.
- **List Partitioning** | Range based Sharding
![](https://assets.digitalocean.com/articles/understanding_sharding/DB_image_3_cropped.png)
  - each partition is assigned a list of values.
  - say we store all users living in Norway, Iceland, Sweden, Finland, Denmark in a partition for Nordic countries.
  - problem of even distribution exists
- **Round Robin partioning**
  - ensures uniform data distribution
- **Composite Partitioning**
  - combination of above.
  - Consistent hashing is a combo of hash and list.

## Problems of Sharding

_"Operations across tables or multiple rows in the same table , will no longer run on the same server"_

- Joins
  - not feasible across servers.
  - performance hit.
  - data has to be compiled from multiple servers.
  - Solution?: **Denormalize the data**... but this will introduce data inconsistency
  - difficult to enforce **referential integrity** in a sharded DB, we have to enforce it in application code.
  - cross shard query is difficult
- Rebalancing
  - you may have occasinally change your sharing scheme
    - if your DB data distribution across shards is not uniform
    - lots of load on one shard
  - doing this without **downtime** is difficult
  - use Directory based partitioning
    - but it will cause single point of failure
    - more complexity
- Unbalanced Shards
  - uneven distribution of data across shards.
  - some shards become "database hotspots" - you need to avoid this from happening
- Difficult to return to unsharded architecture.
- not all Databases provide automatic sharding capability
  - but allows manual sharding,
