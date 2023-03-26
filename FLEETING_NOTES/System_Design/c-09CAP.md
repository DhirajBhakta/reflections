# CAP Theorem

_It is IMPOSSIBLE for a distributed system to simultaneously provide more than two out three guarantees , CAP_

- Consistency
- Availability
- Partition Tolerance

**_In Presence of a network partition, one needs to choose b/w consistency and availability_**

In any distributed system, network partitions are unavoidable. Hence we must choose between consistency and availability. The network partition forces the designers to either choose perfect consistency or perfect availability.

**_During normal operation (absence of network partition), the CAP theorem does not impose constraints on availability and consistency_**

### CP system

Picking consistency means not being able to answer a client's query as the system cannot guarantee to return  the most recent write. This sacrifices Availability. This is a CP system. **this does not mean the system is NEVER available**. It sacrifices availability ONLY during a network partition.

### AP system

Being available means being able to respond to client's request but the system cannot guarantee consistency (the most recent written value, because of **replication lag**). Available systems provide the best possible answer under given circumstance.

### CA system

No Partition tolerance implies no network (because no network is perfect.). **Implies, a single node cluster**, which can provide both consistency and availability

![](https://jvns.ca/images/drawings/cap.png)

![](https://miro.medium.com/max/473/1*rxTP-_STj-QRDt1X9fdVlA.png)

![](https://dz2cdn1.dzone.com/storage/temp/14018651-chap1_cap_theorem.png)

### Consistency

- All nodes see the same data at the same time
- update all the nodes before allowing furthur reads
- guarantee that every node in the distributed cluster returns the SAME, most recent, successful write.
- all clients has the same view of the data
- **C = linearizability | sequential consistency**

### Availability

- each request gets a response (success/failure)
- EVERY non-failing node returns a response in a reasonable amount of time. EVERY node must be able to respond.
- achieved by redundancy and replication

### Partition Tolerance

- system continues to work despite
  - n/w failure
  - message loss
  - node failure
- network partitions are unavoidable. **So you cannot really "choose" P**. P is part and parcel of every distributed system.

# Links

- <https://arxiv.org/pdf/1509.05393.pdf>
- <https://dzone.com/articles/understanding-the-cap-theorem>
