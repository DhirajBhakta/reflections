
#### Critical Section
The piece of Code which is trying to access a **Shared Resource**


#### use Synchronized block for critical section
Works only for concurrency control among Threads of the same Process
...
_But this will NOT work in distributed setting_

---
## Distributed Concurrency Control
1. Optimistic 
2. Pessimistic
Optimistic concurrency control is more efficient but may lead to rollbacks.
Pessimistic concurrency control is more conservative but may lead to contention(Deadlocks).

[[how to implement serializable isolation level?#2 Phase Locking|2 Phase Locking]] is a Pessimistic Concurrency Control mechanism.
#### Optimistic Concurrency Control
_Isolation Levels BELOW REPEATABLE READ_ = **READ COMMITTED**
Underlying Assumption = _"**Conflicts will happen rarely**, hence its better to use max concurrency without strict locking, and then detect conflicts and rollback if conflicts happen"_
**Shared Locks are released just after Reading.**
**Exclusive Locks are released only after COMMIT of TXN**

**MVCC** [[mvcc]]
> Version number increments after every write.
> _Version validation_ is done everytime SELECT FOR UPDATE (attempt at Exclusive Lock) is done, ..checking if version has been incremented(by another TXN). If yes -> ROLLBACK

- HIGH concurrency
- **_Assumes_ chances of conflicts is rare** so it can drive up the level of concurrency without strict locking
- Checks for conflicts at commit time (Version Validation before Acquiring Exclusive Lock)
- No Deadlocks
- Conflict ? -> Overhead of rollback + retry.

#### Pessimistic Concurrency Control
_Isolation Levels REPEATABLE READ and ABOVE_ = **REPEATABLE READ** / **SERIALIZABLE**
Underlying Assumption = "_**Conflicts WILL happen, frequently**_"

**Shared Locks are released after COMMIT of TXN**
**Exclusive Lock are released after COMMIT of TXN**

- LOW concurrency
- **_Assumes_ chances of Conflicts is HIGH**
- Problem of Deadlocks!
	- Aborted after timeout --> ROLLBACK + retry

How Deadlock?
say 
T1 = Read(A), Write(B) ... _Has obtained **Shared Lock** on A, will release only post COMMIT_
T2 = Read(B), Write(A) ... _Has obtained **Shared Lock** on B, will release only post COMMIT._

To Write, both TXNs need an Exclusive Lock, and Exclusive Lock cannot be obtained if there's already a Shared Lock. Hence Deadlock.

[[how to implement serializable isolation level?#2 Phase Locking|2 Phase Locking]] is a Pessimistic Concurrency Control mechanism.






