_MIT 6.824_
TODO: https://www.youtube.com/watch?v=UEAMfLPZZhE&list=PLeKd45zvjcDFUEv_ohr_HdUFe97RItdiB Martin Kleppman's Playlist.
## Introduction
_If things can be done on a single node, DO IT THAT WAY._

A set of co-operating computers which communicate over a n/w to get a task done

Mostly the benefit is **performance**(Scalable Speedup) and **HA, fault toleration**. Other reasons include..
- parallelism: many disks, many CPUs, many memory sticks..
- HA: tolerate faults.
- Geolocation: geographically spread out, physical reasons, but need to be coherent/consistent.
- Security: "compliance says, this should run just here, isolated" and can synchronise with some conditions.

Challenges
- concurrency.
- partial failure: n/w failure, clocks not consistent, GC pauses
- tuning for performance is hard.

Examples:
- large scale storage
- big data computations like MapReduce
- peer-to-peer file sharing

Distributed systems hide the distributed nature(via Abstractions) of the following
- Storage
- Communication
- Computation

Fault Tolerance : When you have 1000s of nodes, something or the other keeps failing all the time; n/w cables, switches, disks , nodes...
- Availability : under certain kind of failures, the system can keep operating
- Replication:
	- How to keep them in sync ?
- Recoverability: 
	- non volatile storage: to store checkpoints, logs to ...recover from failures
	- But try hard to avoid writing to non volatile storage


Consistency: Given that there are replicas, you _might_ get stale values when you read... 
- Strong Consistency : expensive, lots of chattiness
- Weak Consistency:

## MapReduce
