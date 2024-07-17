![[ddia-39.png]]
- Your request might get lost in the n/w
- Your request is waiting in the Queue
	- Queue of the sender due to back-pressure
	- Queue of the network switch, since the n/w is overloaded
	- Queue of the destination's OS, since the node is overloaded.
- Destination node isn't responding
	- might've crashed.
	- temporarily stopped (GC pause), it will start responding later.
- Response ACK might be lost
- Response ACK might be queued/delayed. 

The usual way of handling these issues is via **Timeouts**
But you still don't know if 
- request is processed by node or not? request is still in queue? node processed the request and  response from node is still in queue?
#### Unreliable Networks — Circuit Switched vs Packet Switched Networks
**Circuit Switched Network** _(Telephone network)_
- Dedicated Lines. Predetermined route.
- Guaranteed fixed bandwidth. 
- Extremely reliable. No data loss. Predictable. No Queueing, No Delay. Guaranteed low latency.
- Even though data passes through several routers, there's no queueing.. because the 16bits of space is already reserved in the next hop. Maximum end-to-end latency is fixed. Predictable as hell. You can establish **Maximum round trip time** and set timeouts accordingly and know FOR SURE the packets got dropped and retry is required.
- No competition for bandwidth. If you don't use it, its **left idle!**
- Inefficient Resource usage.. Preventing others from using the bandwidth just cuz you dedicated a fixed bandwidth for yourself, and you don't use it.

**Packet Switched Network** _(The Internet)_
- Dynamic Journey. No Predetermined Route. Data is chopped into packets, and each packet _might_ have its own path via routers. They all arrive at the same destination though.
- Efficient Resource sharing, since you are not dedicating (pre-booking) bandwidth for yourself. Bandwidth utilized ONLY when packets are in transit. Opportunistically use whatever bandwidth is available. TCP can dynamically adapt the rate of packet flow based on available network bandwidth.
- If TCP connection is idle, it doesn't use any bandwidth.
- No Bandwidth Guarantees. A Noise Neighbour can eat up all bandwidth(network congestion), leading to your packets to be queued up in switches ...and delayed. 

Circuit switching excels in scenarios demanding guaranteed low-latency and bandwidth, historically used for telephone networks. 
_**Why not use Circuit Switched networks for the Internet, given that its so reliable...no Queueing, no delay**_ ?it has VERY BAD efficiency. unsuitable for the internet's bursty traffic patterns, which also wants a low cost networking solution (low cost = high efficiency of available bandwidth), cost effective. Circuit switched networks for bursty traffic will **waste network capacity**. 

Packet switching, with its dynamic resource sharing, is the foundation for the internet and the majority of modern data networks. Despite its lack of guarantees(fixed b/w allocation, packet loss), it proves to be a highly scalable and cost-effective method for most applications. We just have to live with **network congestion, queueing, and unbounded delays due to queueing** , cuz we poor. poor AF.  Hard to determine the "correct" value for timeouts. Just make a good guess emperically.
#### Unreliable Networks — Network Partitions

#### Unreliable Networks — Detecting Faults with Timeouts
To check if a node is indeed down(automatically) , you have the following feedbacks:
- _You cannot reach the machine_ (Host)
	- ICMP destination Unreachable : IP address unreachable. Sent to you by a router on the path. 
- _You can reach the machine_ (Host)
	- TCP's RST or FIN packets indicate a **Closed port** , no process is LISTENING on that port on a reachable machine (Process might've crashed).
- Timeouts

**How long should the timeout be?** : figure out the near-optimal timeout _emperically_ by getting the median of most response times.
- Long timeouts: Slow to respond to actual failures
- Short timeouts: Risk declaring healthy nodes dead due to temporary load spikes, GC pauses. Node might not actually be dead but slow to respond due to high load.
	- Consequences of premature death declaration of a Node:
		- Actions might be done TWICE
		- cascading failures under heavy load, as responsibilities are shifted to other nodes that might also be struggling.

#### Unreliable Networks — Queueing & Network Congestion
(packet) delays are mostly due to Queueing. 
- The Sender can queue up the packets due to backpressure (Done by the OS, "TCP Congestion Avoidance")
- The Network Switch can queue up the packets("TCP Congestion Control")
- The Receiver node can queue up the packets (Done by the OS, since no CPU free at the moment)
- The VM Hypervisor (if process is running in a VM)
![[ddia-40.png]]

_If the Queue fills up, the packet is **dropped**._ (Resend, Retry. TCP does this by default). 
Queueing delays have a wide range when the system(node) is operating at near capacity(overloaded).... maybe cuz of noisy neighbour too.

>**Note**: TCP packet loss and retransmission is also another reason for delays. TCP internally sets the timeout for retransmission by observing round trip time for packets.



#### Unreliable Networks — Quorum
The "truth" is reliant on _messages_ you can pass around on the network. There is no other way. Quorum declares you dead? then you're dead. Everyone has to agree, even the node being buried alive.

- A node gets all incoming packets but outgoing packets are dropped/delayed. After some timeout, The node is declared dead even if its working totally fine
- The node is able to send out packets, but they're not getting ACK'ed by other nodes. After some timeout, The node is declared dead even if its working totally fine.
- The node goes out of a long slumber (GC Pause) and was declared dead long ago, but now comes out alive.

#### Fencing Tokens (monotonically increasing)
Locks and Leases are not fool proof. What if a dead node comes back alive and assumes it still has the lock and continues writing to the DB/file? _("dead" because of [[process pauses]]/GC pause or something)._
![[ddia-42.png]]

Solution:
- every-time the lock server grants a lock/lease, **it also returns a fencing token** — auto-incrementing value. Everytime a lease is granted, the token value goes up.
- the client MUST send the fencing token for every write to the storage service
- If the storage service detects a lower number than the latest, it rejects such writes.
![[ddia-43.png]]
