_also called "Compare And Set Transactions"_
_also called "Conditional Statements"_
> Allow the update operation to run ONLY IF a certain condition is True
>  = Linearizable Consistency

```sql
UPDATE employees SET join_date='2020-01-01' 
WHERE id='1234'
IF join_date != null;

-- You want to update the row ONLY if the row exists. (sometimes the update operation might arrive out of order on a replica that doesn't even have the row yet)
```


```sql
INSERT INTO employees (id, email, join_date)
VALUES ('1234', 'john@gmail.com', '2020-01-01')
IF NOT EXISTS

-- You want ONLY one write to succeed (if multiple concurrent requests are made at multiple nodes by multiple users at the same time). 
-- [In Cassandra, every node can accept the write (and replicate the write to other nodes)]
```

![[db-00.jpeg]]
Conditional Batches look quite close to traditional [[ACID properties|Transactions]] 
![[db-01.jpeg]]

When eventual consistency is not enough, and you need something much closer to actual [[ACID properties|ACID Transactions]] , you can use LWT

extension of [[PAXOS protocol]] , "_consensus_"
- quorum based algorithm
- no need of a single master to _serialize the writes_ at once place
- no need of 2PC (2Phase Commit)

The node makes 4 round trip calls to other nodes to gather votes (quorum), hence use LWT sparingly (performance tanks)

> implemented by Cassandra, ScyllaDB

> **Note**: LWT is NOT supported _across_ partitions.



#### LWT — Why is it expensive?
_4 times more work than eventual consistency (quorum reads/writes)_

LWT has to do a read before writing... and reads are expensive on LSMTrees, nearly 100times more expensive than writes

- **network latency**: 4x more expensive(compared to normal writes) in terms or 4x round trips
- **I/O latency**: 100x more expensive(compared to writes)since it involves a READ operation (READ operations are 100x slower than writes on a LSMTree storage engine)
- PAXOS in general causes a lot of contention and starvation.
Although n/w latency far exceeds I/O read latencies... you might actually saturate the I/O bandwidth far before saturating the n/w bandwidth because READs in LSMTrees are exceptionally terrible. Whole disk blocks(64KB) need to be fetched just to read 1-2KB in that block within the associated SSTable.

#### LWT — When to use?
_Only when you want strong consistency_
- You don't want to make a booking twice (on the same slot)
- You don't want to book the same meeting room for two people
- 

