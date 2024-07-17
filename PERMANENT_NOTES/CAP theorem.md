https://martin.kleppmann.com/2015/05/11/please-stop-calling-databases-cp-or-ap.html


https://codahale.com/you-cant-sacrifice-partition-tolerance/

https://www.the-paper-trail.org/page/cap-faq/

https://www.infoq.com/articles/cap-twelve-years-later-how-the-rules-have-changed/

https://mwhittaker.github.io/blog/an_illustrated_proof_of_the_cap_theorem/
[[PACELC]]
**_In Presence of a Network Partition_**
- you can either have Strong Consistency[[consistency models#Strongest Consistency — Linearizability|Linearizability]]
- OR you have have Availability
- But not both
> **Note**: In ABSENCE of n/w partition, you can have both Consistency and Availability though

Generally defined as : _You can pick only 2 out of 3: Consistency , Availability and Partition Tolerance. You can't have all 3._


C = strong consistency (Linearizability) (NOT weak consistency/eventual consistency)

A = availability

P = partition tolerance 

Let's assume network partitions can never be avoided, hence you definitely need partition tolerance. So now you need to choose b/w **Strong Consistency** and **Availability**.
- CP systems : If there are failure conditions(n/w partitions), I will NOT accept your reads/writes to maintain consistency. All clients see the SAME view, even in the presence of updates.
- AP systems : Since i'm a highly available, i shall accept your writes anyways. I shall also serve your reads anyways, since there are live replicas. But you _may_ read stale/incorrect values if there are failure conditions(n/w partitions).

Do you need to choose a CP or AP database and strictly stick with it? Not necessarily. Most applications are just workflows. eg: shopping cart. 
- Amazon.com must stay highly available to customers despite internal faults. Customers should still be able to add items into cart *no matter what* , so you need a **AP database** highly available DB for this part of the workflow
- order creation must be extremely consistent, so that must go to a **CP database**. If you reload the page, you should NOT see stale values regarding the order.
- 

## Linearizability(Strong Consistency)
_Linearizability is a better term for C in CAP theorem._

**C in CAP != C in ACID**. see [[ACID properties#Consistency (or Linearizability)]]

**The Illusion of Single Data Copy**
Linearizability means "system behaves as if there is only one copy of data." see [[FLEETING_NOTES/DDIA/general#Strongest Consistency — Linearizability| Linearizability]]

_make the system **appear** as if there's only ONE copy of the data, all operations are ATOMIC. value of the read is up-to-date value — **recency guarantee**. Once you read a up-to-date value, you(even others) will never read a stale value again._

In a linearizable system, there is a point in time (between start and end of a write operation) at which the value of X atomically flips from old_value to new_value. If one client's read returns new_value,  then ALL subsequent reads must also return new_value, even if the write operation has not yet completed.
![[ddia-44.png]]

![[ddia-45.png]]

![[ddia-46.png]]
![[ddia-47.png]]

- Lower performance
- Lower availability (Less fault tolerant)
- Very strong consistency (Linearizability)

In a Weaker Consistency (eventual consistency) models, the system _accepts the writes anyway_, despite underlying issues, which it will resolve _later_(best effort)
## Availability

## Partition Tolerance


#### C in CAP is different from C in ACID
C in CAP isn't really Consistency, but is actually "Linearizability" or Strong Consistency.


