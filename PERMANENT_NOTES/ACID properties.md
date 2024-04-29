https://jepsen.io/consistency

_ACID Properties are the guarantees provided by DB Transactions._

("C" does not belong in ACID. It was just put there to make the acronym work!)

#### What is a Transaction? 
a collection of queries, which form a unit of work. All of these queries should be done OR all should not be done.. The DB should be consistent before and after the transaction.

### Atomicity
"Atom" = "Unit"
"Unit" = a collection of queries
All queries in the unit must succeed. If one fails, all should rollback. 

### Isolation
_Can my inflight transaction see changes made by other transactions?_

Suppose there's an ongoing transaction ( debit 100 for X + credit 100 for Y) and in the mean time, another transaction appears ( debit 50 forX + credit 50 for Z )...what happens?

Without something called "Isolation Levels", we get "Read Phenomena"

#### Read Phenomena
"Read Phenomena" are undesirable effects that can happen when multiple concurrent transactions are reading data from the DB. These lead to unexpected outcomes.
##### Dirty Read
_The inflight transactions READS a row that was written by another transaction but NOT YET COMMITTED._ 
The other transaction might rollback, in which case, the inflight transaction has read a WRONG value. 
![[db_01.png]]
![[db_02.png]]
##### Non Repeatable Read
_The inflight transaction makes same query N times, and gets different value each time..._
Data might've changed due to another transaction committing.
This is NOT a dirty read , since youre reading a legit, committed value.
![[db_03.png]]
##### Phantom Read
Similar to Non Repeatable read, but here another transaction INSERTS a new row, instead of updating an existing one.

This is hard since you cant create a lock on the new row., since the first transaction didn't even know about its existence initially, during the first read.
![[db_04.png]]
Serializable isolation level can fix this. 

##### Lost Updates
_The inflight transaction wrote some data, and before it could commit, another transaction overwrote some other data._
The inflight transaction "lost the update".


### Isolation Levels
define the degree to which an inflight transaction must be _isolated_ from updates made by other transactions running concurrently. 

As isolation levels increase, performance goes down, since you are restricting concurrency in a way.
![[Pasted image 20231015201809.png]]
##### Read Uncommitted
_No Isolation_
Any change from outside is visible to the inflight transaction.
##### Read committed
Inflight transaction sees only committed values.
This is OK sometimes, and sometimes not.
##### Repeatable read
Inflight transactions sees only committed values BEFORE the transaction started.

- it does not see values that are updated by other transactions, and which are not committed.
- it does not see values that are updated AND committed by other transactions , committed AFTER the transaction has started.
You can either do versioning, such that the transactions sees only Version X of a row value, even though it got upgraded to version X+1, X+2 AFTER the transaction started. 
OR, you can implement locks on the row, not allowing any updates until the transaction commits.

##### Serializable
Transactions are serialized. 
Transactions run one after another, nothing is running in parallel. No concurrency issues. 

### Consistency (or Linearizability)

**"Consistency" doesn't really belong to the ACID properties, its not a guarantee provided by the database. Its there just to make the acronym work!**

>**Warning**: "C" actually does NOT belong in ACID. It was just put there to make the acronym work!
>Consistency here refers to honoring application level "invariants" or "integrity" or "correctness", its less about database guarantees, but more about application's domain's invariants.
>Database guarantees is actually limited to just AID: Atomicity, Isolation, Durability.

Its about maintaining the correctness,integrity of data in the db. Includes enforcement of business rules as per the application. 
Even if an error happens in a transaction, it must be rolled back to ensure the db is in a consistent state before and after the transaction.

A and I => C
Atomicity and Isolation => enable "Consistency"


- Consistency in Data
	- Sometimes it matters, sometimes it does not.
	- Enforced by referential integrity (foreign keys).
	- Enforced by Atomicity and Isolation.
- Consistency in Reads
	- Sometimes it matters, sometimes it does not.
	- _If a transaction committed a change, will a new transaction immediately see the change?_  : -> Strong consistency(Linearizability), Eventual consistency.
	-  Both RDBMS and NoSQL suffer to get strong consistency. Think read replicas. 
### Durability
_Committed transactions must be persisted in a durable non-volatile storage._





### Transactions are super costly!
for eg: to enforce the strongest Isolation level "Serializable", you need 2PC 2 phase commits, which slows down the performance significantly due to Locks.

Do you really need Transactions? Do you really need Locks?

Perhaps you can ease out the hard constraints on normalization, and denormalize tables such that related data **are on the same node**. You can then avoid having Locks on multiple tables for a single request.

Perhaps you can choose eventual consistency. 

