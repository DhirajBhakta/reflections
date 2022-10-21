set of cooperative computers that communicate over a network to get a coherent job done

The dream would be to build an interface that abstracts away all the distributed systems concepts underneath.

### Why distributed?

A lot of critical infra out there is built out distributed systems.

- high performance, achieve parallelism
- to tolerate faults
- Physical reasons. Some problems are naturally "spread out and spaced".
- Security Goals - Isolation

### Challenges

- concurrency
- you can have **partial failures**
- network is unreliable
- performance - adding 1000 nodes doesnt mean 1000x performance

### Infrastructure

- Storage
- Communication
- Computation

### Implementation

- RPC
- Threads
  - way of structuring concurrent operations , and simplify them
- Concurrency Control

### Performance

- Scalability
  - can you get me 2x computers -> 2x Throughput?

### Fault Tolerance

_Big Scale turns rare problems into common everyday problems._
A system of 1000 computers, 3 nodes fail every day. There's always a network issue too.

- Availability
- Recoverability
  - Non Volatile Storage
- Replication

### Consistency

- Strong Consistency
  - is a very expensive spec to implement
  - somebody has to do a lot of communication to do this.
  - lot of chit chat just to read one value
  - replicas are usually kept very far away. communications take milliseconds. chit chat just increases this.
- Weak Consistency

# MapReduce

### The problem?

building index of the web = running sort.

- Google wanted to run giant computations on lot of computers, fast.
- They were looking for a framework that allows the programmer to run any high load code without knowing details of distributed computing

### Bottleneck

Network Throughput - 50mbit/sec in 2004

So they ran GFS and MapReduce on same 1000 machines so that "Maps" read from local disk on same machine without relying on moving data across the network

Fetching all the map's outputs to the reduce machine, it had to be sent over the network. Column storage helped a lot instead of Row based storage of Map output
