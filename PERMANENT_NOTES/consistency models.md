> Stronger the consistency,  lesser the performance, lesser the fault tolerance, higher the latency.
> Stronger guarantees are "appealing" because they are easier to use _correctly_.  Just like Transactions, stronger guarantees shift a lot of headaches at the application level to the DB level.

#### Consistency models vs Isolation levels
_They appear to be similar and they do have some overlap, but they're independent._
**Linearizability vs Serializability**
[Linearizability versus Serializability | Peter Bailis](http://www.bailis.org/blog/linearizability-versus-serializability/)
[concurrency - Who needs linearizability? - Computer Science Stack Exchange](https://cs.stackexchange.com/questions/13441/who-needs-linearizability/13490#13490)
_"I" in ACID .... vs ..... "C" in CAP_
>**Note**: "C" in ACID is totally irrelevant. that "consistency" means application level consistency, about not violating application level invariants. Infact "C" shouldnt even belong to ACID., its just there for making the acronym look good.

Transaction Isolation is about avoiding race conditions due to concurrently executing transactions; Serialization is an isolation property of _Transactions_

Consistency is about bringing the state of replicas to same value in the face of delays and faults. Linearization is a recency guarantee. Linearizability is not about Transactions, its about a _single object(row/document/..)_

- **Serializability:** (Multi Operation, Multi-Objects, Arbitrary Total Order) Prevents anomalies that arise when transactions run concurrently. Think "lost update", write skew, etc. (see details in the chapter on Transactions). It's about correctness in the face of multiple interleaved actions.
    
- **Linearizability:** (Single Operation, Single Object, Real Time Order) Simulates a world with only one copy of the data. _The emphasis is on always seeing the freshest value once it's been written_ , and having that freshness propagate to other reads in a causal way.

- **Strict Serializability** := Serializability + Linearizability

>**Warning**
>SSI (Serializable Snapshot Isolation) is not linearizable. By design, it makes reads from a consistent snapshot, to avoid lock contention b/w reads and writers. The whole point of a consistent snapshot is that it doesn't include writes that are more recent than the snapshot.
>SO if you make one normal read and one read within a Transaction with SSI Isolation level, with both running concurrently, you may have the first read read one value and second read read an older value (from the snapshot)...=> NOT Linearizable

TODO: Okay then, give atleast ONE example where a set of Serializable Transactions are NOT Linearizable



### Eventual Consistency
_A better name for eventual consistency is "Convergence", as we expect all replicas to eventually converge to the same value_

Eventual Consistency is present in all kinds of replication (Single Leader, Multi Leader, Leaderless)

NOT Linearizable

Eventual Consistency is a **Weak Guarantee**. Although it "eventually" becomes consistent, you don't know **when**. In the mean time, if you make reads, you might get stale values. Read1 might be a fresh value, Read2 might be a stale value(since it hit another replica) — NOT Linearizable. If you Write, and then immediately read it again, there is NO guarantee that you will see the value you just wrote (Unless you "read your own writes" via the same leader).

Eventual Consistency is hard to reason about at the application level(and for application developers). If you set a variable X and then read it again, you expect to see the updated value, not stale value(from stale replica).

The edge cases of Eventual Consistency only become apparent when there is a fault in the system (n/w interruption, n/w congestion) or at **high concurrency**.


### Strongest Consistency — Linearizability 
_(Immediate Consistency, Atomic Consistency, Strong Consistency)_
**The Illusion of Single Data Copy**

_make the system **appear** as if there's only ONE copy of the data, all operations are ATOMIC. value of the read is up-to-date value — **recency guarantee**. Once you read a up-to-date value, you(even others) will never read a stale value again._

> Linearizability is the "C" in CAP Theorem.

In a linearizable system, there is a point in time (between start and end of a write operation) at which the value of X atomically flips from old_value to new_value. If one client's read returns new_value,  then ALL subsequent reads must also return new_value, even if the write operation has not yet completed.
![[ddia-44.png]]

![[ddia-45.png]]
The above is not acceptable in a Linearizable system. If N reads happened one after another, ALL of them concurrent with the write operation, then each read might observe the value flipping between zero and one. Not Acceptable. Once a value is read, same value must be read by subsequent reads.

![[ddia-46.png]]
![[ddia-47.png]]
The above shows that In the absence of ClientA's read request, the read request of clientB returning "2" would've been perfectly alright. Linearizable. 
However, clientA has already read the new value 4 before clientB's read started. So clientB is not allowed to read a value older than A.

- Lower performance
- Lower availability (Less fault tolerant)
- Very strong consistency (Linearizability)
_This is basically just [[CAP theorem]]_


#### Whats the point of Linearizability?
[concurrency - Who needs linearizability? - Computer Science Stack Exchange](https://cs.stackexchange.com/questions/13441/who-needs-linearizability/13490#13490)
_**Consensus** is the point of Linearizability. Getting everyone to agree on the same thing._
[[#Consensus]]
Some event happened (Italy won world cup) and it was recorded in a replicated DB. One user reads the event and exclaims "italy won!!", another user reloads the dashboard and sees the stale result that match is not yet finished. This is NOT Linearlizable!
One you read an up-to-date value, you (and others) should NEVER read a stale value.

(_Its generally Okay for some values to stay stale for some time, ...which is the whole point of eventual consistency. But some applications cannot tolerate it_)
**Applications which cannot tolerate eventual Consistency require Linearizability** (Linearizability=Strong Consistency)
> **Note**: But most Applications probably don't need **Strongest** Form of consistency, maybe they can do with a little weaker [[#Causal Consistency]]

Main Uses of Linearizability:
- **Locking & Leader Election** (Everyone must agree on who owns the lock currently) (Avoid Split Brain; if 2 leaders, then both accept writes and ..inconsistency,data loss)
	- Every node tries to acquire the lock, the one that succeeds becomes the leader.
	- All nodes must agree on who owns the lock. (Linearizable)
	- ZooKeeper, etcd
- **Atomic Commit** (Distributed Commit)
	- transactions spanning several nodes or several partitions
	- TXN may fail on some nodes, succeed on some nodes
	- Need to get all nodes to agree on the outcome of the TXN (commit/abort)
	- An "Atomic" Transaction can commit only if ALL participants vote to commit, and must abort if any participant needs to abort.
	- Solved by the following consensus algorithms
		- 2PC (not a good consensus algorithm. Its "blocking")
		- PAXOS
		- RAFT
- **Unique Constraints**...other constraints..
	- unique username, unique filename(path), bankAccount never goes negative,
	- similar to a "lock" on the username
- **Cross Channel Coordination** (think message queue + s3)
	- More than 1 channels through which two systems communicate.
	- sending a message via MQ to "start an image processing task", input image being written to S3. What if S3 write isn't complete before MQ task arrives at the worker?
	
> These are the same as "benefits of Consensus"



#### How to implement Linearizability?
_Short Answer: Use Consensus Algorithms_

Option1: _"Just use a single copy of data"_ ? then HA is gone out of the window.

Option2: Different approaches BUT have HA (replication)
- **Single leader replication**: you cant hope to have all replicas updated synchronously ; so some staleness might be observed if you don't "read your own writes" by reading through the leader himself. 
	- But if you write to the Leader, and read from only _synchronously_ updated Replicas, then its Linearizable.
	- Common pattern to have(elect) a single leader per shard and make all writes go through a single leader to order the writes.
	- Single Leader approach is sort of similar to Consensus Algorithms which involve a leader election.
- **Multileader replication**: by definition, both leaders may not have each others' writes synchronously available.
- **Leaderless replication**: Thus dynamo-style replication(leaderless) does NOT provide linearizability just because they use Quorum [[#Quorum Reads are not guaranteed to be Linearizable]] .
	- You CAN try to make leaderless linearizable (at the cost of performance) by performing **read repairs** SYNCHRONOUSLY before returning results to the application.. AND ..do a read before every quorum write so that read repair happens before a write too.
	- Riak does NOT do synchronous read repair cuz its too costly
	- Cassandra does synchronous read repair.. but .. if there are N concurrent writes to the same key, then it loses Linearizability due to LWW.
	- This technique of synchronous read repair doest NOT work for _compare-and-set_ Operations where the only option is to use Consensus.
	 
Option3: Consensus Algorithms
So what option have we got then?. **You MUST use *consensus algorithms* made available by ZooKeeper or etcd.** Such algorithms have measures to prevent split brain(for leader election) and stale replicas.


#### Quorum Reads are not guaranteed to be Linearizable
_Quorum != Linearizable_
![[ddia-75.png]]
n=3; r=2; w=3; `w+r>n`
Writer's write is concurrent with Read1 and Read2.
Read1 reads the value "1" 
Read2 reads the value "0"
(_Just because they read from a different set of "quorum" nodes_)

Read1 might read from r nodes such that w+r>n . Read2 might read from _other set of_ r nodes such that w+r>n. Both reads _might_ yield different values. **Quorum reads and writes are NOT guaranteed to be linearizable**. Thus dynamo-style replication(leaderless) does NOT provide linearizability. 

#### Linearizability Gives Total Order
_LInearizable storage gives => total order of operation_
Why?
Cuz "single" data store. The system behaves as if there is only a single copy of the data. 
Every operation is Atomic!
For any two operations, you can say with 100% guarantee which of them happened first.
![[ddia-47.png]]
#### Linearizability is Costly
- _You lose out on Availability_ (CAP Theorem)
- _You lose out on Performance_ (very high latency) (due to incredibly chatty Consensus Algorithms over the network)
So Many Distributed Systems choose NOT to provide Linearizability and just fall back to Eventual Consistency — all for performance.
...
As Per [[CAP theorem]], in presence of a network partition, you need to **give up on Availability** to have Linearizability.

> You have to SWITCH OFF the system (or more correctly, return an error) and make it UNAVAILABLE in presence of a network partition to ensure strong consistency is respected (when a n/w partition happens).
> Else if you keep it available, the system would no longer be Linearizable.
> (Why?: Linearizability requires consensus algorithms, and consensus algorithms depend a lot on votes from rest of the nodes, which implies all nodes(minimum of majority nodes) are required to be up and running)

...
Consensus Algorithms are SLOW (many network calls, network latency). You need consensus to provide Linearizability.


#### RAM on a multicore single node system is NOT Linearizable!
_each core has its own cache_

The CPU cache is written first, and then asynchronously written to memory.
Thread1 might write to memory, but first its written to cache of CPU1.
Thread2 might want to read same memory address, but the value in RAM is stale.
...NOT Linearizable (Fresh value may be read first, followed by a stale read)


## Causal Consistency
_Poor Man's Linearizability(Strongest Consistency)_
- Linearizablity guarantees total ordering.
- total ordering implies, its definitely causally ordered (but not the other way round)
- Thus **Linearizability guarantees Causal Ordering**
- But do you really need Linearizability (at the cost of performance) to guarantee Causal Ordering? _do we have cheaper options?_

_**Causal Consistency** is the strongest possible consistency model that DOES NOT hurt performance due to n/w delays, and remains available in the face of n/w failures!_

In many cases, systems that _seem_ to require Linearizability, in fact , only really require Causal Consistency. 

- **Linearizability = Strong but Costly:** If you absolutely must have a single timeline of events, this is the guarantee you need.
- **Causal Consistency = The Middle Ground:** Preserves correctness in many cases, with better performance than linearizability.

Causal Consistency can be implemented via
- version vectors
- SSI Serializable snapshot isolation.

#### Why is Causality Important?
- **Single Leader** exists solely to ensure it orders the WRITE LOGs correctly and sends them in the same order to all the followers. (to respect causal order. Imagine if you (as the leader)sent the UPDATE sql to your replicas before INSERT sql)
- **Consistent Prefix Reads** ensure the causal order of events during reads.
- "writes overtaking" each other because of network delays, when logs flow to replicas. Causality here might get broken. If you get an UPDATE for a row which didn't even exist (CREATE is yet to arrive), then ..er...
- **Concurrent Writes** detection. If writes A and B happened, any of the below can happen. 
	- A happened before B
	- B happened before A
	- A and B were concurrent
	- _If A happened before B, there might be a chance that B might depend on A. There IS a causal dependency between them._
- in **Consistent Snaphots** in **Snapshot Isolation**, "Consistent" means _consistent with causality_.
- **SSI Serializable Snapshot Isolation** prevent write skews. Write skews break causal dependencies. 
	- Alice an Bob decide to go off call at the same time, but before that, each one of them checks if atleast _somebody_ else is on call. Going off call is causally dependant on observation of who is currently on call.
> **Note**:
> Totally ordering the events is ONE (obvious) way of ensuring/enforcing causal order. But its not the ONLY way to achieve causal order.
> You need Linearizable Storage to enforce Total Order [[#Linearizability Gives Total Order]] 



#### Serializable Snapshot Isolation (SSI) is Causally Consistent
_Snapshot Isolation provides Causal Consistency_
[[how to implement serializable isolation level?#Serializable Snapshot Isolation (SSI)|SSI]] makes you do Transaction READs from a _consistent Snapshot_ of the DB. Here "Consistent" means **Causally Consistent**. All causally consistent events upto that point in time, are present in the snapshot. If there's an effect, the cause also will be there on the snapshot.

#### Linearizability vs Causality | Total Ordering vs Causal Ordering
> **Prerequisite:** Digest the fact that "Linearizability guarantees total ordering of events" [[#Linearizability Gives Total Order]]

**Total Ordering**: EVERY EVENT belongs to a strict timeline, even if the events dont depend on each other (causally). you have a _single timeline_. **Linearizability Guarantees total ordering**.[[#Linearizability Gives Total Order]] But do you really need total ordering? hence do you really need Linearizability? you just saw how [[#Linearizability is Costly|CAP theorem brings down your availability if you want strong consistency(Linearizability)...]]

**Causal Ordering**: Why bother ordering EVERY single event into the single timeline? Why not let only events depending on each other, have a order? (events that are independent, don't have a guaranteed order).
> _Best example of causal ordering is Git. Multiple devs branch off from the main branch and work on their own branches concurrently. Commits on the SAME branch definitely need ordering, they're causally related. Commits across different branches, who cares about which happened first? 
> Imagine if you enforced linearlizability to guarantee total order here. One person wouldn't be allowed to commit until commit from another random dev finishes(might even have to wait in line)!!_


Where do we find Total Ordering ?
- Single Leader Replication — **replication log**; defines the total order of write operations . Obviously, it will be causally ordered too. Implemented by monotonically increasing sequence number to each operation in the replication log. The follower must apply the writes in the same order.
- What about multi leader or leaderless replication?
	- can they create monotonically increasing _unique_ sequence numbers as a group? No. So is pushing ALL writes through the single leader the ONLY option? NO.
	- Maybe Causal Ordering is enough? See [[#Lamport Clock — Implementing Causal Order]]and [[#Total Order Broadcast]]
		- Total Order Broadcast is really hurts performance though.

Some Key Terms for digesting the further explanations..
Related: [Broadcast Ordering - Martin Kleppman lecture](https://youtu.be/A8oamrHf_cQ?si=5RdfFibDaHXCs0VJ)
Related: [Broadcast Algorithms - Martin Kleppman lecture](https://youtu.be/77qpCahU3fo?si=qW-bfPVvfHnueP50)
- **Total Order:**(The Ideal) All events have a defined position on a SINGLE TIMELINE, (regardless of whether the events are causally related or not).
	- Total Ordering is a _Foundation for correctness (and coordination)_ in distributed systems which need to order the events as per causality. (Causal Ordering is a _sideeffect_ of Total Ordering. But you don't _need_ total ordering to guarantee Causal Ordering)
	- Total Ordering is observed in Single Leader Replication, where the single leader prepares the "totally ordered" replication log, and sends the same to followers, which apply the events in the same order. But this isn't scalable beyond single node(leader). 
	- If you partition the single node(leader) across multiple nodes, then you need **consensus** to implement total ordering of events, which has bad performance.(Too many leader elections) [[#Consensus — Limitations]]
- **Total Order Broadcast:** A protocol for reliably delivering messages in the same order to all nodes.
- **Consensus to Implement Total Ordering of events**: Total Ordering is obtained by _repeated Consensus_. Each event's position in the total order is determined via consensus (all nodes agree on the position and the order)
- = = = 
- **Partial Order:** Only causally related events have a defined order, concurrent events can be ordered arbitrarily.
- **Causal Consistency** and **Partial Order**: A weaker consistency model where only causally related events are ordered. (Concurrent events can be ordered arbitrarily)
- **Lamport Timestamps:** A way to generate a total order of events that respects causality (NOT Total ordering. This is partial ordering since it only respects ordering within causally related events)
	- Sequence Numbers (monotonically increasing counters) are the intuitive basis for this algorithm. (Avoiding time-of-the-day clocks, since clocks can have skews).
	- `NodeID + Counter
- = = = 
- Total Order ==> Implies ==> Causal Order
- Total Ordering provides strong guarantees, but has bad performance, expensive. Causal Ordering provides an acceptable middle ground. **Choose your guarantees wisely**, in most cases, you DON'T need total ordering of events(Overkill and impractical), you just need Causal Ordering.


