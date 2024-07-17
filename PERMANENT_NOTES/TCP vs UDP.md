TRANSPORT LAYER protocols

Standards on how the data is formatted, and sent. Job of both is to ensure packets are delivered, but TCP has more stronger guarantees, does handshake before sending the data packets...but UDP sends all packets discretely without any kind of handshake

# TCP
Reliable, ordered(seq number), error checking(checksums) to detect if  bits don't flip around randomly.


#### TCP Three way Handshake
SYN(randomly generated seq number) -> 
<- SYN-ACK (seq+1, another randomly generated seq2 number)
ACK -> (seq2 +1)

> "SYN" : "Synchronize Sequence Number"

![](https://media.geeksforgeeks.org/wp-content/uploads/TCP-connection-1.png)

After handshake is complete, we can start sending packets.

For rest of the packets(segments), ACK is not sent for every single segment..only a CUMULATIVE ACK is sent after observing some N segments on the receiver.

#### Whats the point of this Handshake?
Allows both parties to AGREE on **initial sequence numbers** for data packets that are sent from each side!...

Why do you need sequence numbers? why not send random numbers?
This is v.imp for retransmission scenarios...to enforce order (to detect if packets come out of order)

#### What exactly is a "connection" ?
with the handshake, there no such thing as a "pipe" connection being created between the two parties. TCP  still operates on a packet switched network. See [[FLEETING_NOTES/DDIA/general#Unreliable Networks — Circuit Switched vs Packet Switched Networks|Circuit Switching vs Packet Switching]] 

But with every connection, there is overhead of storing the initial sequence number and subsequent seq numbers in memory (and a lot others)..and that is where the overhead comes from a connection.


#### Retransmission
Sender sends packet with seq 99, gets lost..
Sender sends packet with seq 100, the receiver then sends an ACK with seq 99, the sender realizes it has to resend seq99 packet again.

If the Sender doesn't get an ACK (for a bunch of segments) within some timeout, it retransmits all those segments.
> Timeout is adaptively calculated from round trip time estimate.
> Exponential backoff on the Timeout. Double the estimate of RTT upon timout ..**To avoid DDOS**'ing the Receiver.


#### Flow Control
_prevent the receiver from getting overwhelmed_

Both parties have an in-memory BUFFER .
If it gets filled up, the segments get dropped!

The Receiver will tell the sender about the size of this buffer, and the Sender can send only that much more until new ACK comes in.

If Receiver has no space left in buffer , sender waits for some time , then sends a small packet to see how much space it has left.

> The ACK contains the info regarding space left in the buffer of the receiver.


#### Congestion Control
_prevent n/w from being overwhelmed/congested_
_(Window grows linearly, shrinks exponentially)_

Network only has a fixed bandwidth. Multiple devices use the same bandwidth, even if you are not sending a lot of data, another device might be using up a lot of bandwidth..So you may have to slow down too..

TCP , with its ACKs and retransmission and all that..is more prone to cause network congestion.

The sender keeps a "Congestion Window" and halves it if it detects that network is congested.
keep increasing the window with a step size of 1, linearly and the moment you detect congestion -> reduce the window size by half.

#### TCP Slow Start
TODO

#### TCP Termination: 4way handshake
_Graceful termination_
_each half of the connection terminated independantly. = 2 x 2 way handshakes_
FIN->
<-ACK
<-FIN
ACK->
You close each half of the connection one at a time.

> Either Client or Server can terminate the connection, doesn't matter who initiates.

Sending a FIN from your side implies "you have no more data to send".
_If you send a FIN, you cannot send anymore packets, but the other side is free to send you packets and you MUST receive them.._

This helps each side transmit all the remaining packets before closing.
Once both have closed, graceful termination is complete, nobody can send anymore.

Why 4way? : you cannot terminate both connections at the same time. "2 Generals Problem", how to agree on 

---
# UDP
just spraying out packets

No handshakes.. No ACKs for packets too...
No care for flow control, congestion control, ordering of packets, dropped packets, error detection...nothing! just emit the packets

But this makes them fast (and useful for cases where you dont care about the above)
- Video chats
- VoIP
- stock ticker updates..

