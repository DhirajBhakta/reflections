![[ddia-70.avif]]
##### Multi Leader (active/active) (master/master)
- each leader is a follower to other leaders. ... asynchronously replicated to other leaders.
- DANGEROUS!, avoid if possible. Rarely makes sense if you just use a single datacenter. Benefits outweigh the complexity.
- Pros
	- "perceived performance" of writes is higher. local writes are faster than writing to a leader on another DC. 
	- Also write throughput is not limited to single node(as in single leader replication).
- Cons:
	- Dealing with (write)conflicts.
- Biggest problem here is _conflict resolution_ between leaders.
	- eg: userA updates title from A->B, userB updates title from A->C **at the same time**. Writes are accepted at their corresponding local leaders. But when changes are replicated to other leaders, "which happened first? A->B or A->C? which one should be accepted?". Conflicts are detected later, not right away as in single-leader setups(which will block the second writer). This makes user intervention difficult.
- use-cases
	- Multi DC
	- clients with offline operation (calendar app)
	- collaborative editing (google docs)
- Topologies (how replication path looks like when changes need to flow across leaders)
	- all-to-all
	- circular
	- star


#### Multi-Leader — Topologies
Communication path along which writes are propagated from one leader to another.
If there are two Leaders, its obvious., the path is leader1-->leader2 or leader2-->leader1. 

But when there are more than 2 leaders... 
![[ddia-30.jpeg]]
- All-to-all is the most common.
- MySQL supports circular only by default.
- Circular and star tag identifiers for each write to **avoid infinite loops**.(the identifies all the nodes it has passed through)
	- When a node receives a data change that is tagged with its own identifier, that data change is ignored.. because the node knows that it has already been processed by self.
- Circular and star are susceptible to node failure along the replication path.

All-to-all topology suffers from the "overtake" problem. Two writes done at T1, T2 (T1<T2)... might get applied at such that second write overtakes the first one. And the subsequent leader might process the writes in different order. This is a **causality problem** 
![[ddia-31.png]]"Version Vectors" can solve this problem.


#### Multi-Leader & Leaderless — Conflict Resolution
Biggest problem in Multi-Leader setup is _conflict resolution_ between leaders.
eg: userA updates title from A->B, userB updates title from A->C **at the same time**. Writes are accepted at their corresponding local leaders. But when changes are replicated to other leaders, "which happened first? A->B or A->C? which one should be accepted?". Conflicts are detected later, not right away as in single-leader setups(which will block the second writer). This makes user intervention difficult.

 (Conflict avoidance is most preferred since most multi-leader implementations handle conflicts poorly)
In Dynamo-Style DBs(Leaderless), where clients write to all nodes,.. conflicts can arise during read-repair and hinted handoff. If each node simply overwrote the value for a key whenever it received a write request from a client, the nodes would become permanently inconsistent. There needs to be away for all nodes to **converge to a common value**.

 Conflict Resolution Techniques...
 - Conflict Avoidance (force writes to go through same leader)
 - LWW (Last Write Wins)
 - On Read
 - On Write
 
 ###### **Conflict Avoidance**(most preferred)
- all writes to a particular record/user/document go through **the same leader** .. this is called "home datacenter"
- From any one user's point of view, this is just a single-leader setup.
- Conflict avoidance needs to deal with failover of the home datacenter's leader.

 ###### **Converging to a consistent state (LWW)**
- **"_Last-Write-Wins(LWW)_"** : each write has a uniqueID (timestamp, UUID, hash of value, whatever).. the bigger value wins. Prone to data loss! LWW achieves the goal of eventual convergence but at the cost of durability. Even if writes are reported as successful, they would be **silently discarded**. if losing data is not acceptable , LWW is a poor choice.
- Cons:
	- do we use client or server timestamp?
	- writes will be lost
	- clock skew on server (clock can go out of sync)
- Each replica has a unique ID. replica with higher ID has precedence. Prone to data loss!
- Sort the conflicts and concatenate them. eg. A->C and A->B happened together. Then final value is "B/C" . User can manually resolve the conflict.
- Record the conflict in a explicit data structure. Let the user resolve it later.

 ###### **Custom conflict resolution( on write, on read )**
 (Note: Conflicting writes occur due to Concurrent writes)
- Write your own conflict resolution logic, since you know your application well.
	- executed on write
		- [[multi leader replication#How to detect Concurrent Writes?|when DB detects a conflict]] in replication log, conflict handler is called.(CRDT)
		- Runs in background, must execute quickly
		- Without user intervention, no prompting the user.
	- executed on read (CouchDB)
		- if conflict is detected, corresponding conflicting writes are stored.
		- During next read, the user is prompted to resolve it himself.
		- resolved value written back to DB


#### How to detect Concurrent Writes?
When you have 2 operations, you have 3 possibilities
- A happened before B
- B happened before A
- A and B happened at the **same time** (concurrent writes)
How to detect concurrent writes? Writes that happen at the same time? how to converge to the same value? without dropping any values?... we can use "version numbers"
1. server maintains a "version number" for every key
2. "version number" for the key is incremented with every write
3. when client reads, latest "version number" is returned, + all values that have not been overwritten
4. when client writes back, it is expected to send the same "version number" it received, + it must merge the values and send a new value. **Client is burdened with the responsibility of merging and resolving conflicts(maybe do a UNION?..this wont work for deletes.. use "tombstones"), and sending a new value**
5. when server receives a write, it can overwrite the value if the version number is latest or below.. But if its higher than the latest "version number", it must keep all the values.. _so that some other client will read and resolve the conflict in the future and write back the resolved value._
6. when a server receives a write without any version number, it is concurrent with all other writes, so the server will not overwrite anything... it will just be returned as one of the values on future subsequent reads.

![[ddia-34.png]]
A single version number is enough for single server. If there are N replicas, you need N version numbers for the same key, one for each replica. Thus you need **version vectors**.

*Here, blue green red are server names*. A version vector contains version numbers for **a given key** as per every server in the system.

|                           |                    |                            |
| ------------------------- | ------------------ | -------------------------- |
| {blue:2, green:1}         | is greater than    | {blue:1, green:1}          |
| {blue:2, green:1}         | is concurrent with | {blue:1, green:2}          |
| {blue:1, green:1, red: 1} | is greater than    | {blue:1, green:1}          |
| {blue:1, green:1, red: 1} | is concurrent with | {blue:1, green:1, pink: 1} |
Two values have a "happens-before" relationship (i.e event B which writes b is causally related to event A which writes a) (i.e NOT concurrent) if one version vector is strictly greater than the other version vector
- for each element of the list, the number is greater than or equal to the corresponding element in the other list
- implies NOT concurrent.
- Else , concurrent.
	- Then, you need to either merge the values (and corresponding version vectors) OR , keep both copies and allow for manual conflict resolution.