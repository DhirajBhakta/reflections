#### Transactions — Why do we need it?  
**Transactions** simplify the following _things that can go wrong_ .
- **Crashes** in the middle of a write operation
	- DB s/w or h/w failures
	- Application crashes
- **Network Failures**
	- DB Node <-> DB Node
	- Application <-> DB
- **Concurrency & Race Conditions**
	- two writes at the same time, overwriting each other.
	- Reading stale data or partially updated data.
	- Problems with concurrent writes
		- Dirty Writes
		- Lost Updates
		- Write Skew (Phantom Writes)
	- Problems with concurrent reads
		- Dirty Reads
		- Non-Repeatable Reads
Applications don't need to worry about partial failures, they simply retry (because failed TXNs are totally rolled back).
By using a Transaction, the application can pretend that there are no crashes(atomicity), that nobody else is concurrently accessing the database(isolation), and that storage devices are perfectly reliable(durability). Even though crashes, race conditions and disk failures do occur, the transaction abstraction hides those problems so that the application doesn't need to worry about them.

---
#### Transactions — Do you really need it?
Transactions come at a price of performance. **Serializability and Atomic Commit come at a very large cost of performance and inability to scale beyond single leader etc**...Some applications don't need transactions, but may need _some_ safety properties which can be gotten **without transactions.**

But there are some "beliefs" that are not entirely true
- "_Serious applications with valuable data/financial applications NEED Transactions as a requirement._"
- "_Transactions hamper scalability significantly_"
- "_Any large scale system needs to ABANDON Transactions to have high availability and performance._"

Often, simple solutions appear to work correctly when concurrency is low (so low that they don't appear to step on each other), but bugs begin to appear at high volume and high concurrency.
But is Transactions the only way out? Most applications may just do fine with weaker guarantees, causal consistency, eventual consistency etc.. and Transactions can be abandoned for better performance and scalability.

---
#### Transactions — Client side awareness
_Transactions might've succeeded(committed), but n/w failure caused ACK not to be sent back_ . The client **may retry**. Application needs to take care of dedupe. 

_Mindless retrying might lead to overload (or worsen the overload if it was already overloaded)._ 
- set a `Max_retries` value
- use `Exponential Backoff` value

When you retry TXN, make sure the "side effects" are NOT retried. Eg: sending an Email. 