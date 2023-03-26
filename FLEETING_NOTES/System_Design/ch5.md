# [WIP]: Consistent Hashing

- to distribute requests/data evenly across servers
- distributed cache serversS
- distributed hash table

### The Question

What criteria are used to determine which keys to host in which servers?

- Simplest way
  - `serverIndex = hash(key) %N`
- Consistent hashing
  - a distribution scheme that DOES NOT depend directly on the number of servers

### The rehashing Problem

Say you have N cache servers.( distributed cache to support huuuge number of keys)

Say you use the simple
` serverIndex = hash(key) % N `

- works well if data is evenly distributed
- what happens mostly is that one of the server ends up with lots of data and maybe one server has very little or no data.
- _what happens if number of servers change?_
- _what happens if one of the cache servers goes down_. hashes will be wrongly calculated as N=N-1 now. Most cache clients will connect to the wrong cache server and will cause a storm of cache misses.

## Consistent Hashing

- not dependant on number of cache servers
- assign objects a position in the hash ring
- assign servers a position in the hash ring
- each server gets some virtual nodes depending on their weight.
- each object/key is assigned the nearest virtual node in clockwise direction.

## Result

Only `k/N` keys need to be rehashed where

k= number of keys<br/>
N= number of servers

In normal hashing, you would have to rehash all the keys if any one server is removed or added.
