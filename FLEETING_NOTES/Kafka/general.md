![[kafka-10.png]]

Event streaming platform -- Collect, Process, Store, Integrate data at scale

- Events is the "System of Record".. Or primary source of data. Everything else is derived from the log of events. _Event Sourcing_
- Should be able to **reprocess old events** in case of worker/consumer failure. (Go back in time)
- its not just an event stream, but a **ledger** that can be used to go back in time and get old data from.


#### Why not in-memory messaging systems? Why was Kafka created?
TODO
- AMQP style message brokers **don't guarantee ordering** and **replay-ability** :: Getting the events out of order can be hazardous (Getting an UPDATE event before a CREATE event)
- Horizontally scaling may not be possible. (??WUT??, why not just add more workers?)

Kafka was designed for HIGH THROUGHPUT -- transferring large amount of data in short amount of time.(think of massive diameter pipe vs small pipe)

#### Why is kafka fast?
- Sequential IO - "Append only log"
- Zero Copy Transfer

#### Zero Copy Transfer
_How to efficiently send data on disk over the wire?_

The standard route is: Disk -> OS cache -> application buffer -> socket buffer -> NIC buffer
![[kafka.webp]]
The efficient route is : Disk -> OS cache -> (`sendFile` system call + DMA) --> NIC Buffer

#### Kafka - A log-based message broker
_An Event Ledger_
- Distributed
- Redundant (has copies, replicated)
- Linear scale (horizontally scalable)
- Designed to look _like_ a typical messaging system. (producers, consumers, events..)
- Durability & Ordering Guarantees.
- Events are _append-only_ into the Log. You cannot update an appended event.
- The log is persisted to Disk. (tiered storage (s3 etc) with confluent cloud)
![[kafka-06.png]]

Usecases::
- Pub-sub messaging
- Stream Processing
- ETL Hub for CDC / Data pipelines / Data Integrations
- Big data Ingest (Buffer. Since consumers wont be able to keep up)
- Distributed Logging

![[kafka-00.png]]

#### Kafka APIs
At the base, Kafka just has 2 **Low level APIs**:
- Producer API
- Consumer API
- `ProducerRecords` is a `[]ProducerRecord` --> each of which is a k-v pair
- `ConsumerRecords` is a `[]ConsumerRecord` --> each of which is a k-v pair

**High Level APIs**
- Kafka-connect APIs:
- Kafka Streams API
- ksqlDB API

#### What is an Event?
_K-V Pair_
But within Kafka, K and V both are just series of bytes (bytearrays)
The K defines which partition in the topic the Message(Event) will go into.

Event = "A thing that happened" - action, incident, change identified, user clicks, temperature readings,...

- structured format - JSON/JSONSchema/Avro/ProtocolBuffers...

The "Record" (message/event) has
- key
- value
- timestamp
- headers

#### Brokers
_Network of machines/containers/VMs = Brokers_
these brokers make up the Kafka "Cluster"

The entire architecture consists of
- control plane (metadata) -- related to ZooKeeper/kraft
- data plane
![[kafka-11.png]]
![[kafka-12.png]]

The Broker contains the following thread pools
**Network Threads**:
- pick bytes from socket receive buffer and 
- forms the "request object" --> places it into the Request Queue
- . . . 
- picks "response objects" --> places it into the socket send buffer
- . . . 
- Note that the SAME network thread will handle both the request object and response object for the given incoming request's lifecycle
**I/O Threads**:
- picks "request object" from request queue
- validations, CRC check
- --> append the data to **commit log** of the partition
**Fetch Threads**

Data Structures::
**Purgatory**(Map):
- holds "request objects" until they're replicated to other brokers
**OS Page Cache**:
- /
**Request Queue & Response Queue**: 
- .

Misc:
- **Socket Recv buffer / Socket Send buffer**:
- **Commit Log** of the partition:

**Physical Storage (Disk)**
- `/var/lib/kafka/data/customers-`


#### Producer
Writes "events" to a topic.

> a Producer is configured with a pluggable "partitioner"

- Producer controls which partition the event goes into. (it does the key hashing + modulus) -- if there's no key, round robin would be used (you lose ordering)
- Producer also buffers N events into a "batch" and writes the events in batches(either by time or by batch size). Saves n/w overhead.
- Producer also compresses the entire batch of events before sending.

**The Produce Request** (producing a batch of messages)
-  partition assignment (via the key)
-  record batching+ compression (batching actually helps do compression better on the whole batch)
- draining configuration -- when to actually send the entire batch to broker?
	- by time: when a certain time has elapsed `linger.ms`
	- by size: when batch size reaches a certain size `batch.size`
> Note: `linger.ms` and `batch.size` are the performance knobs for tuning latency and throughput	of producer (and kafka brokers, in a way)



#### Topics
_Topic = Group of partitions_
Kafka is a collection of immutable append-only logs

A Topic is a durable LOG of events. (LOG = file on disk!)
A Topic is NOT a "queue"
- append only
- cannot be indexed, can only **SEEK by offset** (messages are stored sequentially even on disk)
- messages are immutable
- because of the above semantics, Kafka is able to get monstrous single node performance

#### Partitions
_Topic = Group of partitions_
Partitioning is the standard way of scaling anything in distributed systems.
If a topic lied just on a single node, it would be limited by the resources of that single node. To scale horizontally, you would need to split the topic (partition) into multiple nodes.

Partitioning takes a LOG and breaks it up into multiple smaller LOGs (called partitions), each of which can live on a separate node.
- Partitions are replicated
- single leader for a given partition.
- Kafka follows a _Leader-Follower_ approach.
- This Leader (per partition) is elected via Consensus. Which is why it needs ZooKeeper. (Recently it has removed dependency on Zookeeper. It now uses an internal RAFT quorum to elect a leader)
- **Writes are always made to a Leader of a given partition** (You always specify (topic+partition) when making a write).
- **Ordering is guaranteed WITHIN a single partition**
- **Single Consumer connects to a given partition**. No two Consumers read from the same partition.

#### Why should you specify the Key?
(When producer writes to a topic, it can specify the partition too.. or else, partition can be derived from the hash of the key) -> `Hash(Key) mod NumPartitions`
- if the message has no key (message = K-V pair), then round robin would be used to send messages to partitions.but you will lose ordering properties since messages go to different partitions.
- **if you need ordering, please specify the key.** eg: customerID

#### Partitioning is DIRECTED by the PRODUCER!
Its the PRODUCER (on client side) which decides which partition the message should go into!


![[kafka-04.png]]

Pattern::
one topic can hold "filtered" events from another topic (piping)

#### Producers and Consumers
Producers write records(events/messages) to the broker, Consumers read records(events/messages) from the broker.
- NOT push based.
- Consumer connects and ASKS for records (PULL)
- Many consumers can READ from the SAME topic!!(same partition too!)

The API:
- `ProducerRecords` is a `[]ProducerRecord` --> each of which is a k-v pair
- `ConsumerRecords` is a `[]ConsumerRecord` --> each of which is a k-v pair

#### Consumer Offsets
- Consumer maintains the offset per partition.(monotonically increasing sequence number)
- .. just in case the consumer dies, it can _continue where it left off_ from the **offset**.
- Offsets also help in **replay**. Since consumers maintain the offset, the consumer can just change the offset to something much lower to process older messages again (replay).

![[kafka-05.png]]

#### Consumer rebalancing
Initially when there's just ONE consumer on a topic, it pulls messages from all partitions. When you add new consumers, the consumers and the kafka brokers together manage to rebalance the messages among consumers fairly (automatically)

If there are 10 partitions and you add a 11th consumer, the 11th consumer **will be idle!**,

 Just know that **ONE partition will always be PINNED to a SINGLE consumer**
 
---
# Kafka Architecture


---
# Kafka Community Ecosystem
(standard things that are already solved)
- Kafka Connect
- Schema Registry
- Kafka Streams
- ksqlDB

#### Kafka Connect
You just provide some JSON configuration, and you have a producer/consumer ready to go!

Why not write your own connector from scratch? why rely on a community connector??
- not trivial
- lets say you want to pull data from RDBMS and ingest them into Kafka
- you now have a distributed state management problem "what is the last ID that i pulled?"

Source Connector = Producer
Sink Connector   = Consumer
![[kafka-07.jpeg]]

#### Schema Registry
_Schema registry maintains a DB of schemas_ (JSONSchema/Avro/Protobuf)
- stored in a Kafka Topic (cached on the schema registry too)
- exposes a REST API
- producers can consult the schema registry to check if the new message has the same schema / acceptable schema as the last message, before appending message to the topic. (VALIDATION)
- consumer can consult the schema registry to do the same before consuming the message

But why?
- new consumers emerge
- schema of messages will evolve (new fields, old fields might go)
- prevent incompatible messages from being pushed into the topic.
- all this to avoid runtime errors when reading incompatible data with unrecognised schema.

#### Kafka Streams
(Stream Processing) - "Stateful"
(Kafka streams is a LIBRARY!) which runs on top of kafka

- _consumer group_ of consumers make up cluster of stream processors.
- stream-stream JOIN, stream-table JOIN (shipments, customer info..etc need to be joined)
- filtering, grouping, aggregating, joining
- if youre doing this by hand, you allocate memory on heap..and susceptible to data loss if the stream processing worker goes down!
- Kafka provides a stream processing API to handle all that for you.
- (Stores it in local disk on worker + internal topics within kafka too)

NOTE: the same stream processing workers may also expose a REST API!!


#### Ksql DB
_Standalone, SQL powered, **stream processing engine** that performs continuous processing of event streams and exposes results to applications in a very database-like way_
![[kafka-08.jpeg]]
![[kafka-09.png]]
DB optimised for stream processing!
- runs on on its own fault tolerant cluster
- exposes a REST interface
- you "submit" stream processing jobs in SQL, and retrieve the results in SQL

You can either provide a PULL or a PUSH query.
PULL query gives you results once. a PUSH query will give updated results everytime new messages arrive





---
# TODO:
- Logs by Jay Kreps
- I heart logs
- Kafka Paper
- Kafka @LinkedIn Paper
- **Kafka's role in Event Sourcing?**
- Why kafka needs Zookeeper? what is kRaft?
- dedicated topics(kafka ecosystem):
    - kafka connect
    - kafka streams
    - ksql DB
- Questions:
    - Why is kafka fast? why is even single node performance high? why is throughput significantly high?
    - If kafka is so fast, why bother even considering SQS/in-mem queues at all??
    - (paper) kafka uses buffering a lot (page cache on OS) to flush data in bulk via a single system call. What if the failure happens before a flush?? even the client side SDK does buffering!! how are people so confident!??

---
