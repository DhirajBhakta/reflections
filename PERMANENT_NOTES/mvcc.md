_Multi Version Concurrency Control_


#### Phantoms are a thing !
_You can only lock existing rows_
_You can't lock rows that don't yet exist!_
> Even [[how to implement serializable isolation level?#2 Phase Locking|2 phase locking]]  cannot handle Phantoms! 
- T1 reads something... `SELECT COUNT(*) WHERE...`
- T2 inserts a row matching the **same condition**
- T1 reads again `SELECT COUNT(*) WHERE...`
You get different values within the SAME TXN , _**non repeatable reads**_

"Phantom" : tuples _can appear or disappear_ WHILE my txn is running, and cause non repeatable reads issue within my transaction

Wouldn't have happened if I ran the TXNs in **serial isolation**, but we can't afford such stupid low concurrency


#### How to Solve Phantoms?
1. Re-execute Scans
2. Predicate Locks
3. Index Locks


