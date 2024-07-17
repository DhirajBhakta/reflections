https://jepsen.io/consistency

_ACID Properties are the guarantees provided by DB Transactions._
> ("C" does not belong in ACID. It was just put there to make the acronym work!)

> "I" Isolation is the main reason why ACID databases take a big penalty on performance. 
> Most of "NoSQL" DB's can actually manage to give you "A" and "D" and not "I" 
> ("C" is out of the picture)
## What is a Transaction? 
_A way to group N writes and reads into ONE logical unit._
a collection of queries, which form a unit of work. All of these queries should be done OR all should not be done.. The DB should be consistent before and after the transaction.

Either the entire transaction succeeds(commit) or the entire transaction fails(rollback, abort), and application can safely **retry**.

You have a sequence of reads and writes to be done as a part of an "action
- R(x) .. R(y) .. W(x) .. W(y). . . . COMMIT
- R(x) .. R(y) .. W(x) .. W(y). . . . ROLLBACK

Transactions were invented in first SQL DB = "IBM System R". General idea is still the same as System R..as in MySQL, Postgres etc.

Safety Guarantees provided by Transactions are called **ACID Properties**. 
> **Note** :
> "ACID" is ambiguous, especially "isolation". "ACID Compliant" is mostly a marketing term, you don't really know what you're getting. Implementations are different.

By using a Transaction, the application can pretend that here are no crashes(atomicity), that nobody else is concurrently accessing the database(isolation), and that storage devices are perfectly reliable(durability). Even though crashes, race conditions, and disk failures do occur, the transaction **abstraction** hides those problems so that the application does't need to worry about them.

### Philosophy of Transactions
**Philosophy of Transactions:** "_If the DB in in danger of violating its guarantee of atomicity, isolation or durability, it would rather ABANDON the transaction entirely than allow it to remain half-finished_"
NoSQL(specially leaderless replicated ones) don't adhere to this, and use "**Best Effort philosophy**": "_The DB will do as much as it can, and if it runs into an error, it won't undo anything. Its the application's responsibility to recover from errors._"

### Transactions — ACID Properties
_The **Safety Guarantees** provided by Transactions._

A: Abort-ability , rollback-ability
I : Serializability 
_A&I together describe what the DB should do if a client makes several writes within same TXN. No partial failures. No interference. If one TXN makes several writes, then other TXN sees either ALL those writes, or NONE at all.. not some subset_. 

> **Warning** : "C" does NOT belong in ACID.
>  It was just used to make the acronym work. Marketing gimmick. Its a application level property rather than a DB guarantee.
>  Also the term is confusing and overloaded
>  - "Eventual Consistency" in replication
>  - "Consistency" in CAP theorem
>  - "Consistent" Hashing for partitioning and rebalancing.

>**Warning**: Multi-put is not necessarily a Transaction
>NoSQL DBs provide a multi-object (multi row/document) PUT operation to write several things at once. These don't necessarily provide "all-or-nothing" guarantee!
>Multi object transactions are difficult to implement across partitions, so its abandoned in most NoSQL DBs. 

### Atomicity
_All or None_ (Commit or Rollback)
"Atom" = "Unit" ; "Unit" = a collection of queries
All queries in the unit must succeed. If one fails, all should rollback. 
- _Abortability_ is a better word.
- "all-or-nothing" principle.
- If TXN hits a snag while doing (one or more) writes,..(crash,n/w failure..) its like it never happened.
- all partial changes get rolled back.
- Application **just needs to retry** . (no need to worry about cleanup/partial writes)
- Single-Object Atomicity
	- Writes to individual records/rows/documents are "Atomic" and "isolated". This is easy to implement.
	- enforced by using "single object operations" like in-built Increment++ operation (which avoids read-modify-write cycles) and Compare-And-Set(CAS) Operations are "atomic" operations 
- Multi-Object Atomicity
	- updating references, foreign keys, related rows
	- updating multiple denormalized documents at once in NoSQL DBs.
	- Secondary indexes. These are "separate" from actual rows(main data) under the hood. Need to be kept in sync.
- Confusions
	- "Atomicity" is NOT about concurrency (thats talked about in "Isolation"), although "atomic operations" in multi threaded parlance IS about concurrent access to same data.
	- Doesn't talk about what happens if N processes try to access same data at the same time.
- Atomicity prevents failed TXNs from littering the DB with half finished results and half updated state. Especially important in multi-object TXNs (secondary indexes) — if you update data, you also need to make a corresponding change on the secondary index. Atomicity ensures the secondary index stays consistent with primary data.


### Consistency (or Linearizability)
>**Warning**: "C" doesn't belong to ACID. 
>**"Consistency" doesn't really belong to the ACID properties, its not a guarantee provided by the database. Its there just to make the acronym work!**
>Consistency here refers to honouring application level "invariants" or "integrity" or "correctness", its less about database guarantees, but more about application's domain's invariants.
>Database guarantees is actually limited to just AID: Atomicity, Isolation, Durability.

Its about maintaining the correctness,integrity of data in the db. Includes enforcement of business rules as per the application. Application-specific notion of DB being in a "good state". Application defined **Invariants** must always be true. ("_Credits and debits must always be balanced_"). 
Even if an error happens in a transaction, it must be rolled back to ensure the db is in a consistent state before and after the transaction.


- **Its the Application's responsibility** to define the invariants correctly and define the transactions as per the invariants. DB cannot guarantee this for you.
- They can help with things like foreign keys, but it's the application's job to write transactions that preserve its own, more complex ideas of "valid" data.
	- A and I => C
	- Atomicity and Isolation => enable "Consistency"

### Isolation
_Can my inflight transaction see changes made by other transactions?_
_Can my transaction AFFECT other inflight transactions?_
_Can my transaction BE AFFECTED by other inflight transctions?_
_Isolation level tells you **how much level of concurrency** is allowed_

Suppose there's an ongoing transaction ( debit 100 for X + credit 100 for Y) and in the mean time, another transaction appears ( debit 50 forX + credit 50 for Z )...what happens?

- TXNs shouldn't mess with each other's work. They live in bubbles. Ideal Goal: **Serializability**. The illusion that each transaction was the only one, even if they ran in parallel.
- Concurrent processes/TXNs accessing/writing same data at the same time.
- "Isolation" — Concurrently executing TXNs are isolated from each other., pretend that its the ONLY TXN running on the entire DB (Serializability).
- As if multiple TXNs are run _serially_. (reality = _concurrently_)
- "Serializable" isolation [[how to implement serializable isolation level?]]
	- **[[how to implement serializable isolation level?#Actual Serial Execution|via Actual Serial Execution]]**: too costly(slow), time consuming, too much locking, its rarely used , rarely implemented these days.
	- **[[how to implement serializable isolation level?#2 Phase Locking|via 2PhaseLocking]]** :  def-facto.
	- **via Snapshot Isolation**:  more commonly used , but Weaker Guarantee.
	- **via Serializable Snapshot Isolation (SSI)**:  _next big thing_.  is a much better improvement(not yet de-facto)
- Increment++ operation and Compare-And-Set(CAS) Operations are "atomic" operations which will prevent another TXN from reading dirty values.
- **Isolation levels**
	- _Isolation level tells you **how much level of concurrency** is allowed_
	- [[#Isolation Level — Read Uncommitted]]
	- [[#Isolation Level — Read Committed]]
	- [[#Isolation Level — Repeatable Read (Snapshot Isolation)]]
	- Serializable
	- _Confusion on these terms_
		- There is no standard naming in SQL standard
		- Snapshot Isolation is called "Serializable" in Oracle , "Repeatable Read" in MySQL and Postgres
		- IBM DB2 uses the term "repeatable read" to refer to serializability. 
- "_Use ACID Database if you're handling financial data!_"
	- Not so simple as that.
	- Even RDBMS (considered ACID) use Weak Isolation. "Serializable" Isolation is just "Snapshot Isolation". 
- **Repeatable Read** Isolation Level
![[ddia-73.png]]
Without "Isolation Levels", we get [[concurrency bugs]]


### Isolation Levels
_Isolation level tells you **how much level of concurrency** is allowed_
define the degree to which an inflight transaction must be _isolated_ from updates made by other transactions running concurrently. 

As isolation levels increase, performance goes down, since you are restricting concurrency in a way.
![[db-19.png]]
#### Isolation Levels and Locking
![[db-20.png]]
#### Isolation Level — Read Uncommitted
_dirty reads are allowed, no dirty writes._
_any change from outside(other inflight transactions) is visible to the inflight transactions_

dirty reads are allowed, is that okay?
- you'll read values written midway in a TXN
- you'll read values which might be rolled back by the TXN.
- its bad!

#### Isolation Level — Read Committed
_no dirty reads, no dirty writes_
_Inflight transaction sees only committed values._

- this is the _default_ in most DBs (Postgres, SQL Server)
- Writes are visible only when the TXN commits. Not before that.
- Writes by second TXN are done only after first TXN commits. Not before that. (Wait for first TXN to finish writing)
- **Implementation** (For Writes):
	- By using "Row level Locks".
	- TXN acquires a lock on the object (row/document/...), hold the lock until commit/abort.
	- If another TXN wants to write, it waits for the lock.
- **Implementation** (For Reads):
	- To prevent Dirty reads, locks will just slow down everything.
	- One long write TXN can block multiple read TXNs to just wait for a really long time.
	- Response time go brrrr.
	- So...instead.....
	- DB "remembers" both old committed value and new value set by the current TXN(holding the write lock). Read only TXNs are given the old value when requested. (Sort of like MVCC, see next section on Snapshot Isolation )

#### Isolation Level — Repeatable Read (Snapshot Isolation)
_Inflight transactions sees only committed values BEFORE the transaction started._
- it does not see values that are updated by other transactions, and which are not committed.
- it does not see values that are updated AND committed by other transactions , committed AFTER the transaction has started.
_You make a read query twice, you get the same results._
_Implemented by **Snapshot Isolation**_
**_Readers never block Writers, Writers never block Readers._**
- (In Contrast to 2phaseLocking for Serializable Isolation "Writers Block Readers, Readers Block Writers)

- You make the read query twice, you get same results. Reads don't get skewed because another TXN was overwriting data concurrently. 
- "non repeatable read" or "read skew" is just a transient issue, not a lasting problem. you reload and the issue/inconsistency is gone.
- But is indeed a big problem when it comes to
	- taking backups
	- analytic queries
- **Implementation**
	- _Readers never block writers, Writers never block readers._
	- Write locks to prevent dirty writes.
	- But for reads ... (Use **Snapshot Isolation**)
		- Each TXN reads from a "consistent snapshot" of the DB. data that was committed at the start of the TXN (frozen in time), and NOT transient values being updated by other concurrent TXNs.
		- maintain several "snapshots" (committed versions) of the object/row/document. **MultiVersion ConcurrencyControl (MVCC)** MVCC is also used for Read-Committed Isolation level as well in some DBs.
			- You can either do versioning, such that the transactions sees only Version X of a row value, even though it got upgraded to version X+1, X+2 AFTER the transaction started. 
		- OR, you can implement locks on the row, not allowing any updates until the transaction commits.
		- By never updating values in-place, but instead creating a new version everytime a value is changed, the DB can provide a consistent snapshot.
		- Every "new version" of the object is tagged with the TXN ID of the TXN which wrote/updated it.
		- When a TXN reads a value, it reads the value tagged by the highest TXN ID _smaller_ that the reader's TXN ID.
![[ddia-38.png]]
Let's say Alice's account starts with a $500 balance.

- Transaction 10 begins and sees this initial $500 balance.
- Transaction 12 begins and also sees the $500 balance (Transaction 10 is ignored because it hasn't committed).
- Transaction 10 now transfers $100, creating a new version of the row with $400, tagged with Transaction 10's ID.
- Transaction 14 begins. It can't see the $400 row because it came from a later transaction. It still sees the original $500 row.

#### Concurrent Writes — Preventing Lost Updates
Some write conflicts can be avoided by **preventing dirty writes (Read Committed Isolation Level)** .
Other write conflicts occur with
- read-modify-write cycle.
- JSON updates (part of the document needs to be updated).
- Concurrent edits (Wiki pages).

**Solutions : LOCK based solutions**
- **Atomic Write Operations**
	-  **Mechanism:**  built-in DB operations for UPDATE. Indivisible Atomic step. No intermediate, inconsistent states visible. `(v) => v+1` Internally uses a LOCK.
	- Removes the need for read-modify-update cycle;
	- Not suitable in every case..(e.g., complex text editing scenarios).
	- **Examples:**
	    - `UPDATE counters SET value = value + 1 …`
	    - MongoDB atomic updates on JSON substructures
- **Explicit Locks**
	- Application enforced LOCKs on objects(rows/docs/...)
	- The application can perform the read-modify-write cycle and then release the LOCK. 
	- Works well when atomic operations are not suitable, or if DB doesn't support atomic operations at all.
	- Examples:
		- `SELECT ... FOR UPDATE` command applies a LOCK.  YOU tell the DB what to lock.
		- Two players want to move a game character. Atomic operation is useless here. You need to enforce rules via code, not possible via database query. So you use a LOCK to prevent two players from concurrently moving the same piece.
		- ```BEGIN TRANSACTION;
			SELECT * FROM figures  
			WHERE name = 'robot' AND game_id = 222 FOR UPDATE;
			
			-- Check whether move is valid, then update the position of the piece that was returned by the previous SELECT. 
			
			UPDATE figures SET position = 'c4' WHERE id = 1234;
		 COMMIT;```

Locks for Writes take a toll on performance. Can we do better?

**Solutions: "Detection" based non-locking solutions** 
- **Compare and Set (CAS)**
	- No Locks
	- Allow update to happen ONLY if value hasn't changed from the last time you read it.
	- If value doesn't match the value you last read, TXN aborted, you gotta retry. 
	- ```UPDATE wiki_pages SET content = 'new content' WHERE id = 1234 AND content = 'old content';```
- **Automatically detect lost updates** 
	- No Locks. 
	- Allow both writes to execute in parallel, abort the offending TXN, allow it to retry.
	- Depends on how well the "TXN manager" can "detect" lost updates.

On Leaderless/Multi Leader replicated DBs, this is far more harder,..LOCKs don't work here! CAS doesn't work here!..  you use techniques like **LWW Last Write Wins** for write conflict resolution, but you will LOSE updates!! Better option is to keep both versions of the values, and let the application do conflict resolution(merge via special data structures  CRDT Conflict resolution data types.) or let it be resolved manually with human intervention.

#### Concurrent Writes — Write Skews , Phantoms
**Write Skew**:
- Is a race condition involving _different_ objects(row/doc/...). N TXNs access/write different data. There is some overarching "invariant" connecting these two data that gets violated when the TXNs run concurrently. Why is this a race condition? if the TXNs ran serially, the invariant would not have been violated. Spoiler Alert: only way to solve Write Skews is by eliminating concurrency and making TXNs run serially.
- This is neither a dirty write nor a lost update, because the two TXNs are updating two different objects(rows/docs/...). 
- **Examples:**
	- The on-call doctor scenario(atleast 1 doc should be on-call):  both doctors see enough coverage and proceed to drop their shifts(click on "OOO today" at the same time), inadvertently leaving no doctors on call.
	- Booking Systems:  Double-booking meeting rooms(at same time slot) despite checks.
	- Game Logic: Two moves could violate game rules(say two pieces moving to the same position), even if individual piece movement is locked.
	- Usernames:  Race conditions during signup grabbing a unique username.
	- Financial Systems(Debits):  Concurrent deductions could overdraw accounts.
- The Pattern of  Write skew usually looks like :
	1. A SELECT query checks if a requirement is satisfied (atleast 2 doctors on call)
		1. Based on its result, the TXN is either allowed to continue or abort.
	2. if allowed to go a ahead, TXN makes a write and commits.
		1. This changes the precondition checked in step#1 (one doctor less on call)

Solutions
- Atomic Operations won't help here. Multiple objects are involved. 
- **Detection is Tricky**: Automatic Detection isn't straightforward. DB cannot detect these things.
- **Constraints Can Help (Sometimes):** If you can express your invariant ("must have at least one doctor") as something the database can enforce(via foreign keys, unique constraints,...), it's a win. However, multi-object constraints are often not directly supported. You may need Triggers, Materialized Views.
- **Explicit Locking to the Rescue:** `SELECT ... FOR UPDATE` remains a tool, but may not always be sufficient.
	```
	BEGIN TRANSACTION
	SELECT * FROM doctors WHERE on_call=true AND shift_id=1234 FOR UPDATE;
	UPDATE doctors SET on_call=false WHERE name='Alice' AND shift_id=1234;
	COMMIT
	```
- **A Table Of LOCKs**
	- The core problem here is you don't have a single object to have a LOCK on. What if you make a table solely for the purpose of storing LOCKs ? _artificially introducing locks!_
	- Each row in the table corresponds to a particular meeting room for a particular time slot. You create rows for all possible combos of meeting rooms and time slots _ahead of time_., say for next six months. 
	- Now the TXNs can LOCK the row `SELECT ... FOR UPDATE` to insert a booking.
	- Use this as a last resort as this approach is error prone.
- **_Serializable Isolation_ is the simplest fix.** True Serialization. make them run serially, eliminate concurrency.



##### Serializable
Transactions are serialized. 
Transactions run one after another, nothing is running in parallel. No concurrency issues. 

### Durability
_COMMITTED transactions must be persisted in a durable non-volatile storage._
> Complete, guaranteed durability is a myth. (think apocalypse. Will you have DC in space?)
-  **COMMITTED data won't just vanish**, even in crashes, h/w faults.
	- WAL : Write-ahead logs (for recovering from corrupted files)
	- Replication (your data in multiple nodes)
	- backups (tape archive)

### Transactions are super costly!
for eg: to enforce the strongest Isolation level "Serializable", you need 2PC 2 phase commits, which slows down the performance significantly due to Locks.

Do you really need Transactions? Do you really need Locks?

Perhaps you can ease out the hard constraints on normalization, and denormalize tables such that related data **are on the same node**. You can then avoid having Locks on multiple tables for a single request.

Perhaps you can choose eventual consistency. 


