TODO:
- what is a Schedule?
- What is a Serial Schedule and Concurrent Schedule?
- Why do we need Conflict Serializability and View Serializability?
- Why are they not Practical and why do we instead depend on locks?
- what is optimistic and pessimistic locking?
	- MVCC is optimistic
	- 2PL is pessimistic
- why 2PL is pessimistic locking?
- basic 2PL suffers from 
	- starvation (one TXN might get starved)
	- deadlocks
	- allows non-recoverable schedules (T1 messes up and rollsback; but T2 already read value written by T1 and committed before T1 rolled back)
- Strict PL
- Rigorous PL
- Strict and rigorous PL dont have dirty reads


### Why do you need Locking ?

### Optimistic and Pessimistic Locking


### Conflict Serializability & View Serializability


### Pessimistic Locking — 2 Phase Locking (Basic)

### Pessimistic Locking — 2 Phase Locking (Strict)

Other versions of 2PL
- Pessimistic Locking — 2 Phase Locking (Rigorous)
- Pessimistic Locking — 2 Phase Locking (Conservative)

### Timestamp based

### MVCC


#### Conflict Equivalence
2 DB statements are called conflicting if and only if
1. Both are in **different** transactions.
2. Both are accessing the **same data item(value)**.
3. At-least one of them is a **write operation**. 
> A "Schedule" is a set of Transactions. 
> Its a "combination" of statements of given Transactions.
> A "Serial Schedule" is such that the Transactions in the set are run serially, without interleaving the statements.

Using the above rules, _Two "Schedules" of Transactions are said to be "Conflict Equivalent" .. if they yield the same results_
![[db-04.png]]

#### Conflict Serializability
Given a Concurrent Schedule S, find a Serial Schedule S' such that S and S' are conflict Equivalent, then S is _Conflict Serializable_.

- A schedule with 4 Transactions will have 4! = 24 Serial Schedules.
- Will you sit and compare with all of them?
- A precedence graph approach is a shortcut approach to find the Serial Schedule S' which is conflict Serializable with the given Concurrent Schedule S. But if you find cycle(s) in the precedence graph, then there is NO Serial Schedule S'. implies S is NOT conflict serializable.
![[db-05.png]]
The required _serial_ order within the Serial Schedule S is T1->T3->T2.
![[db-06.png]]
![[db-07.png]]
![[db-08.png]]


#### View Equivalence
1. who reads from db
2. who reads from other's written value
3. who writes last
_2 Schedules S1 and S2 are view equivalent if both are following similar sequence rules of view serializability_
![[db-09.png]]
- T1 reads X from DB in S1 ; T1 reads X from DB in S2; (all good)
- T2 reads X from value written by T1 in S1; T2 reads X from DB in S2 (therefore, not view equivalent!)

#### View Serializability
A Concurrent Schedule S  is "View Serializable" if it is view equivalent to any Serial Schedule.

- A schedule with 4 Transactions will have 4! = 24 Serial Schedules.
- Will you sit and compare with all of them?
	- You note which transaction writes the last. That must write the last even in the Serial Schedule. Now you have reduced your sample set from 24.

#### Why do we need LOCKs?
everything discussed above is pointless since you need to know all statements in advance to decide if the concurrent Schedule is view serializable or conflict serializable.
Which is not practical at all! 
(_If Im transferring 100$ to my account, how would I ever know there would be 2 more TXNs which will transfer 5000$ to my account 2s after I started my TXN ?_)

Instead, **Use Locks** to allow only one TXN to run. _Shared Locks and Exclusive Locks_
- shared lock for reading. 
- exclusive lock for writing.
- N TXNs can share a shared lock.
- If any TXN has shared lock, other TXNs can get a shared lock.
- If any TXN has shared lock, no other TXN can get exclusive lock.
- If any TXN has exclusive lock, no other TXN can get exclusive lock.
- If any TXN has exclusive lock, no other TXN can get shared lock.
![[db-17.png]]

But, locking and (busy)waiting on locks seems so wasteful. Would you do a `while` loop and keep checking if the lock is available?
No. We use somewhat of a a pub-sub approach to notify the relevant TXNs when the lock is released. (the "blocked transactions" are the subscribers)
![[db-10.png]]
^above, T2 is blocked on T1 for x.

Since multiple TXNs can obtain the shared lock if they're **reading the same value** which is already within a shared lock by some other TXN, we need to maintain **count**. So that when count eventually reaches 0, the exclusive lock can be granted to whichever TXN is **waiting** on the value.
![[db-11.png]]
But this can lead to **starvation** for the TXN waiting on an Exclusive Lock for the value. (in the above example: T2). May remain blocked for a really long time if multiple concurrent TXNs keep taking shared locks.

We can enforce a rule here to _avoid starvation_.
> **DON'T allow more than 1 shared lock**, if there exists at-least 1 TXN waiting on an exclusive lock for the same value.
![[db-12.png]]


**Upgrading and Downgrading the locks**
If the same TXN which held the _shared lock_ now wants to write the same value, and hence needs an _exclusive lock_, it can **upgrade the lock** from shared->Exclusive.. if and only if _NO OTHER TXN is HOLDING A SHARED LOCK!!_

Similarly, if the TXN was holding an _exclusive lock_ and now wants to read the value, it can **downgrade** the lock from exclusive->Shared. (why?: so that other TXNs have a chance at reading the value. Holding a shared lock is always better to not starve others)


Locks are not the solution for everything. You still have the problem of **non-repeatable reads**. Eg: 
- T1 takes sharedLock on X
	- and releases when done reading
- T2 takes exclusiveLock on X
	- and releases when done writing
- T1 takes sharedLock on X (AGAIN).  ...... **_non repeatable read_**
	- and releases when done reading
![[db-13.png]]

**_You need SYSTEMATIC LOCKING PROTOCOLS_**  (like 2PL)
- basic 2PL
- strict 2PL
- rigorous 2PL


### Basic 2 Phase Locking
1. phase1: locking
2. phase2: unlocking
_After phase1(once you begin unlocking), you cannot take more locks!_

_Every Schedule allowed by 2PL is **Conflict Serializable** too._
![[db-14.png]]

![[db-15.png]]

But 2Phase locking creates starvation for some Transactions, and even suffers from deadlock at times.
![[db-16.png]]

### Strict 2Phase locking
_**Exclusive lock** is released only after COMMIT_
_...guarantees recoverable transactions...unlike Basic 2PL_

Strict 2PL works similarly to the basic 2PL protocol at first. It gradually obtains locks as needed, but the locks are only released after a commit.

Strict 2L allows only strict schedules.
(because Exclusive Locks are released only after COMMIT of T1, other TXNs can read/write only after commit of T1)


### Rigorous 2Phase locking
_Every lock should be released only after COMMIT_
_...guarantees recoverable transactions...unlike Basic 2PL_

### Conservative 2Phase locking
_Lock all items **before TXN begins** by pre-declaring its read set and write set_

![[db-18.png]]