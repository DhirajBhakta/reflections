# Caching

- short term memory
- limited amount of space
- faster than original data source (servers)
- contains most recently accessed items (Locality of reference principle)

**Caches are often found at the level nearest to the frontend , to return data quickly without taxing the downstream levels**

Used in every computing layer

- h/w
- OS
- web browsers
- web applications

### Locality of reference Principle

recently requested data is likely to be requested again.

## Application Layer caching

- placing cache directly on request layer node
- use local memory (v fast)
- use local disk (faster than network storage)
- single node - good
- multiple nodes?
  - each node -its own cache
  - cache misses (bcas Load Balancer randomly distributes requests)
  - **solution: use Distributed Cache or Global Cache**

## Distributed Cache

- each node own a **PART** of the cached data.
- divided using **consistent hashing**
- ease of increasing the cache space, just by adding nodes.
- if a request is sent to a node, and that node doesnt have the data,,,it will lookup the consistent hashed structure and send request to the appropriate node to get data --- before hitting the original server for real data.
- what if the node is missing?
- store multiple copies in different nodes - redundancy.

## Global Cache

- single powerful cache
- separate service
- who is responsible for populating the cache? (2 approaches)
  - **cache itself is responsible.** fetches the missing piece of data from orginal store. responsible for eviction too.
  - **request nodes are responsible**  Application logic understands the eviction strategy better than the cache

## CDN

- large amount of **static** media
- geographically distributed group of cache servers - low latency - bring it closer to where the users are.
- caches content at the **edge locations** or "Points of Presence (PoPs)"
- edge locations = **Internet Exchange points(IXPs)**
- geographically closest data center

## Cache Invalidation

keep cache consistent with the original data source.

- **Write-through-cache**
  - written to cache and DB at the same time.
  - fully consistent
  - slow
  - high latency for writes.
- **Write-around-cache**
  - written to DB
  - cache is bypassed.
  - can lead to cache misses.
- **Write-back-cache**
  - written to cache only.
  - DB is bypassed.
  - completion is immediately confirmed to client.
  - written to DB after certain intervals
  - low latency. fast
  - risk of data loss.

## Cache Eviction

- FIFO
- LIFO
- LRU
- MRU
- LFU
- Random replacement
