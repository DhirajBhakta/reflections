
- Events is the "System of Record".. Or primary source of data. Everything else is derived from the log of events. Somewhat like Event Sourcing.
- Should be able to reprocess old events in case of worker/consumer failure. (Go back in time)
	- its not just an event stream, but a **ledger** that can be used to go back in time and get old data from.

#### Why not messaging systems?
- AMQP style message brokers **don't guarantee ordering** and **replay-ability**
	- Getting the events out of order can be hazardous (Getting an UPDATE event before a CREATE event)
- Horizontally scaling may not be possible.

#### Kafka - A log-based message broker
_An Event Ledger_
- Distributed
- Redundant (has copies)
- Linear scale (horizontally scalable)
- Designed to look _like_ a typical messaging system. (producers, consumers, events..)
- Durability & Ordering Guarantees.
- Events are _append-only_ into the Log. You cannot update an appended event.
- The log is persisted to Disk.
![[Screenshot 2024-05-19 at 9.42.40 PM.png]]


#### Producers and Consumers
Producers write records(events/messages) to the broker, Consumers read records(events/messages) from the broker.
- NOT push based.
- Consumer connects and ASKS for records (PULL)


#### Topics and Partitions
Topic = Group of partitions
(When producer writes to a topic, it can specify the partition too.. or else, partition can be derived from the hash of the key)
- Partitions are replicated
	- single leader for a given partition.
	- Kafka follows a _Leader-Follower_ approach.
		- This Leader (per partition) is elected via Consensus. Which is why it needs ZooKeeper. (Recently it has removed dependency on Zookeeper. It now uses an internal RAFT quorum to elect a leader)
	- **Writes are always made to a Leader of a given partition** (You always specify (topic+partition) when making a write).
- **Ordering is guaranteed WITHIN a single partition**
- **Single Consumer connects to a given partition**. No two Consumers read from the same partition.
![[kafka-04.png]]


#### Consumer Offsets
- Consumer maintains the offset per partition.(monotonically increasing sequence number)
- .. just in case the consumer dies, it can _continue where it left off_ from the **offset**.
- Offsets also help in **replay**. Since consumers maintain the offset, the consumer can just change the offset to something much lower to process older messages again (replay).

![[kafka-05.png]]

#### Kafka & ZooKeeper
TODO

#### Kafka usecases
- ETL Hub for CDC
- Data pipelines
- Big data Ingest (Buffer. Since consumers wont be able to keep up)

![[kafka-00.png]]




TODO
- Page on Event Sourcing.