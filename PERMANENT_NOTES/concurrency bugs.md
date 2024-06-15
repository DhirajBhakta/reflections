_Read Phenomena_
"Read Phenomena" are undesirable effects that can happen when multiple concurrent transactions are reading data from the DB. These lead to unexpected outcomes.
- [[#Dirty Read]]
- [[#Non Repeatable Read|Read Skew(Non Repeatable Reads)]]
- [[#Lost Updates]]
- [[#Phantom Read]]
On Writes
- [[#Dirty Writes]]
- Write Skew
- Phantom Writes

(As obvious, **Serializable Isolation** level is the answer to all problems, but sadly we CANNOT tolerate such stupid level of concurrency in the real world)
![[db-19.png]]


#### Dirty Read
_(Temporary Update Problem)_
_The inflight transactions READS a row that was written by another transaction but NOT YET COMMITTED._ 
The other transaction might rollback, in which case, the inflight transaction has read a WRONG value. 
![[db-01.png]]
![[db-02.png]]
Solution?
- use READ COMMITTED Isolation level
- does NOT use LOCKS. 
	- why block readers
- Database remembers old values of the writes until a write gets committed ("snapshots")


#### Non Repeatable Read
_The inflight transaction makes same query N times, and gets different value each time..._
_(Read Skew)_
Data might've changed due to another transaction committing.
This is NOT a dirty read , since you're reading a legit, committed value.
![[db-03.png]]
Solution:
- [[ACID properties#Isolation Level — Repeatable Read (Snapshot Isolation)|Snapshot Isolation]] (No LOCKS involved)


#### Phantom Read
(_Similar to Non-Repeatable Reads_)

Similar to Non Repeatable read, but here another transaction INSERTS a new row, instead of updating an existing one.

This is hard since you cant create a lock on the new row., since the first transaction didn't even know about its existence initially, during the first read.
![[db_04.png]]
Solution:
- (obviously)Serializable isolation
- Predicate Locks
- Index Locks
- MVCC

#### Lost Updates
_The inflight transaction wrote some data, and before it could commit, another transaction overwrote some other data._
The inflight transaction "lost the update".
Solution:
- Atomic Writes: (Atomic inc/dec, Atomic CAS(compare-and-set)) 
- Explicit Locking : Exclusive Locks.  `FOR UPDATE` in SQL to lock the rows you just read.
- Automatic Database Detection:
	- use snapshot isolation to detect lost updates (can see that the value has changed), then ROLLBACK and retry
	- removes the need to LOCK



#### Dirty Writes
_Writing on top of uncommitted values_
Solution:
- LOCK on each value
- any writer first grabs an Exclusive LOCK on the object before writing


#### Write Skew
_Invariant gets broken due to concurrent write_
https://www.cockroachlabs.com/blog/what-write-skew-looks-like/
- T1 and T2  make a read
- based on the result of the read, they make a write
- Invariant has now failed!
eg:
- there needs to be atleast ONE doctor on night duty.
- two docs query to see how many are on call(2), they both want to take off.
- each one decrements.
- now there's no one on night duty! (invariant failed)

Solution:
- Predicate Locks


#### Phantom Writes
_Invariant gets broken due to concurrent write (inserts)_
Same as write skew, but invariants get broken when new rows are created by the inflight transactions... nothing to put a lock on

Solution:
- Predicate locks will not work here since there is nothing to put a lock on
- [[materializing conflicts]] (Table of Locks)
	- dummy rows populated ahead of time.

