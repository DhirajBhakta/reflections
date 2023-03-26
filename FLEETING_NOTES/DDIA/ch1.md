## Intro

We have RDBMS, NoSQL datastores, stream processors, batch processors, message brokers. <u>Which one is best suited for your application?</u>

This book is about Principles of data systems.

- databases
- caches
- queues

and how they achieve

- reliability
- scalability
- maintainibility

There are many DB systems with different characteristics, because different applications have different requirements

- there are various ways to do caching
- several ways of building search indexesS
- etc

A single tool can no longer meet all of the data processing and storage needs. Instead work is broken down into tasks that can be performed by a single tool, and those tools are stitched together using application code

## Reliability

The system should work correctly even in the face of adversity

Things that can go wrong are called "_faults_"

### Hardware Faults

- Hard disks crash
- RAM becomes faulty
- power grid has a blackout
- someone unplugs the wrong cable
  
"redundancy" is the solution. When one component dies, the redundant component takes its place while the broken component is replaced.

### Software Faults

Much more common than hardware faults.

# Scalability

As the system grows, the system should handle that load

System growing from 1000 concurrent users to 1 million concurrent users.

### What is "Load"?

load parameters :

- requests per second to a web server
- ratio of reads/writes
- number of active users in the chat room (simulataneous)
- hit rate on a cache

### Describing performance

Once you have described the load on your system, you can investigate what happens when the load increases

- throughput
- response time

"average" is not a very good metric because it doesnt tell you how many users actually experienced the delay

"percentile" is better. Median is known as the 50th percentile. Half of the requests return in less than 200ms, rest half take more than 200ms. Median is 200ms.

To figure out how bad your outliers are, consider 95th, 99th percentiles. if 95th percentile is 1.5 sec then it means 95% of requests take less than 1.5 seconds.

### Coping with Load

How to maintain good performance when when load params increase?

**"Shared nothing architecture"**: scaling out - horizontal scaling

- easy for stateless services
- tough for stateful data systems

Common wisdom was to keep your DB on a single node(scale up) until scaling costs or HA forces you to make it distributed.

In early stage startup or an unproven product, its more important to be able to iterate quickly on product features than to scale to some hypothetical future load.

# Maintainibility

System should be maintainable

- Operability &mdash; Making life easy for operations
  - Monitoring health of the system and quickly restoring service if it goes into bad state.
  - tracking down cause of problems ( system failures/ degraded performance)
  - Keeping s/w and platforms uptodate.
  - capacity planning
  
- Simplicity &mdash; managing complexity
  - avoiding big ball of mud
  - remove accidental complexity; not features  -- to make it simpler.Use abstractions.

- Evolvability &mdash; making change easy. Keep software soft

  -
