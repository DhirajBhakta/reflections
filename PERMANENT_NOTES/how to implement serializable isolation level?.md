(*Note that Serialiazable Isolation level is the reason why Transactions are so slow in ACID databases*)

### Isolation Level — Serializable
_The STRONGEST Isolation Level..._
_**Serializable Isolation** is the answer to all problems and race conditions_

a TXN does not span multiple HTTP requests. A New HTTP request starts a new TXN.



How to implement ?
#### Actual Serial Execution
- remove concurrency altogether. **Single thread**, make TXNs execute one after another, on a **single CPU core**.
	- _Single Thread_
	- _Single CPU core_
	- ::: (_Single thread performance can beat multi threaded system which supports concurrency, because it can avoid the coordination overhead of locking_)
- make sure TXNs are very short and fast.
- make sure all data required by TXN can fit in RAM.
	- For high throughput. Disk r/w is very slow
	- Tips(anti-caching): |=>  If a TXN needs to access data which is not in memory, then abort the TXN, load the data into memory asynchronously (while continuing executing other TXNs), then restart the TXN. 

- Use stored procedures, reduces n/w overhead. 
- Cons:
	- But throughput is limited to single CPU (Partitioning can overcome this)
	- Stored Procs can be very awkward to work with.
	- Add data cannot really fit in RAM.
- **Partitioning**: Partition your dataset such that 
	- each TXN only needs to read/write within single partition
	- each partition can have its own TXN processing thread
	- one CPU is responsible for only specific partitions.
	- You can now scale linearly with number of CPUs.
		- But this will be worse if a TXN has to touch multiple partitions.
#### 2 Phase Locking
- Was widely used for ~30years. 2PL is used for the 'Serializable' isolation level in MySQL (InnoDB) and SQL Server.
- Based on Locks. Much stronger than just WriteLocks.
- Multiple Readers can concurrently read a value as long as no one is Writing.
- _Writers Block Readers, Readers Block Writers._
- But if a Write is involved:
	- TXN B cannot write until TXN A (which has previously just read a value) commits.
	- TXN B cannot read until TXN A writes and commits.
- "Two Phases" =  Acquiring Locks +  Releasing Locks. _It has a growing phase and a shrinking phase_. Keeps acquiring locks...and then keeps releasing locks. A TXN cannot acquire new locks once it starts releasing locks.
- **Implementation** (Shared Locks, Exclusive Locks):
	- **Shared Lock:** Multiple transactions can hold a shared lock on an object _for reading_.
	- **Exclusive Lock:** _Required for writing_ (modifying/deleting). No other transaction can hold any lock(shared or exclusive) on the object while an exclusive lock is held.
- You may have Phantoms
	- You made a READ query to check if your required room is booked or not. After you made the READ query, another TXN inserted a row to book that room.
	- why did you not put a LOCK here?
	- **we could not put a LOCK since the row did not even exist!**
	- Solution: **_Predicate Locks_** (to prevent phantoms) 
		- **Predicate Locks** (Very Precise but slow): Locks on to multiple objects(rows/docs/...) which match a search condition(even if the rows dont yet exist). Checking active locks(every row which match the condition) is time consuming.
			- Slight Improvement:  **"_Table of Locks_"** discussed in "_Concurrent Writes — Write Skews and Phantoms_". 
		- **Index-Range Locks** (Approximate but fast): Performant optimised version of Predicate Locks. But not as precise as Predicate locks. It is much faster to lookup the index than individual objects that match the condition. If you apply the lock on the index itself(bigger range than precise rows), then the second TXN MUST attempt to update the index too if it tries to update the row, and hence it would encounter the lock on the index. ~ applying lock on the whole day instead of just the 12-2pm time slot. ~ Or applying lock on all rooms instead of just one room. At worst, apply the shared lock on the entire table.
			- eg: you want to lock on a particular room at given time slot, but you have index on only roomID. so if you put a lock on the index itself for that room, you have essentially blocked anyone from booking that room at ANY time slot (at any time, any day, any year) until you have finished booking/rolling back.
- 2PL _increases the likelihood of deadlocks_ (transactions waiting on each other). The database automatically detects and resolves deadlocks - by aborting one of the transactions.(Needs to be retried)
- **Drawbacks:**
	- Significantly worse performance, response times. Overhead of Locking and releasing locks. Reduced Concurrency due to blocking
	- Potentially super high tail  latencies as transactions may have to wait for others to complete.
	- Can lead to deadlocks:
		- eg: transactions T1 and T2 are reading a value X, hence they both obtained a **shared lock** on X. now both want to write, but neither can get an **Exclusive Lock** to write because the other is holding a **shared lock**. (Exclusive lock can be obtained only if no other TXN is holding a shared lock.)(also, as per 2PL, you cannot obtain a lock once you started releasing the lock ... hence deadlock is happening here in this example)
			- Solution is to **ABORT** one of the TXNs so that the other can proceed. Then **RETRY**.
	- Deadlock resolution can cause wasted work for a TXN. (abort and retry)

#### Serializable Snapshot Isolation (SSI)
_Not yet de-facto. But Promising..._
Let everything run concurrently with **NO LOCKS** and only revert a TXN if a concurrency bug is detected.

_All Reads happen on a **snapshot of the DB**_
- Keep track of all TXNs that have _read_ an item.
	- If any other TXN _writes_ to that item, then abort all TXNs which _read_ that item.
- If you _read_ a value and are about to _write_, if any other TXN wrote that value AND committed, then you must abort and retry.

Pros:
- significantly faster than 2PL. 
- No Locking
Cons:
- if too much conflicts occur -> too much aborts and rollbacks --> 2PL might outperform here.

read more on [[locking in databases]]


