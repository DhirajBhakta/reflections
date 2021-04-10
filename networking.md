<style>
 h1{
     color:red;
 }
</style>
# Big Picture 

  - The internetwork environment consists of hosts connected to networks
  which are in turn interconnected via gateways.   
  - The active agents that produce and
  consume messages are processes.  
  - Various levels of protocols in the
  networks, the gateways, and the hosts support an interprocess
  communication system that provides two-way data flow on **logical
  connections between process ports**.

  - Hosts are computers attached to a network, and from the communication
  network's point of view, are the sources and destinations of packets.
  - Processes are viewed as the active elements in host computers .Even terminals and files or other I/O devices are
  viewed as communicating with each other through the use of processes.

  **Thus, all communication is viewed as inter-process communication.**

  Since a process may need to distinguish among several communication
  streams between itself and another process (or processes),
   each process may have a number of ports through which it
  communicates with the ports of other processes.


# Tools

## &#9874; `ping <host>`
- ICMP 
- IP Layer (Network Layer) (Layer 3)
- tells if the host is up

## &#9874; `traceroute`

## &#9874; `ss` 
- _Socket Statistics_
- is a replacement for `netstat`

#### Usage :`ss` 
- List of only "NON listening" sockets that have "ESTABLISHED" connections

#### Usage : `ss -l`
- List of only "listening" sockets

#### Usage : `ss -a`
- = `ss -l` + `ss` ( listening + established(non-listening) )

#### Usage : `ss -t`  `ss -u` `ss -x`
- Show TCP only, UDP only, Unix sockets only




# Protocol Basics

## ⛳️ ICMP &mdash; Internet Control Message Protocol
- Network Layer 3 Protocol



### Why does it exist?
- To handle **error handling** in Network Layer ( also a bit of "querying" handling, i,e "Are you alive _pings_")
- A lot of variations of errors can happen in Network Layer, ICMP provides diagnostics for the same with enumerised error msgs.
-![](https://static.javatpoint.com/tutorial/computer-network/images/icmp-protocol2.png)
    - (SOURCE QUENCH)Handles congestion/source control 
        - Router asks the source to calm down and send packets at a slower rate
        - It says the packet has been "discarded" due to congestion, and asks for resend -- at a calmer pace
    - (TIME EXCEEDED)
        - if TTL expires midway for a packet, TIME EXCEEDED err is sent back to source
        - or if all the _fragments_ of a packet did not arrive in order, theyre discarded and err is sent back to source
    - ICMP redirects
        - If host A wants to send message to host B, it does through router, and if router realizes both these hosts are on same network, router sends ICMP REDIRECT to host A to update its routing table so that it can communicate with host B directly

        - If host A wants to send message to outside network, it does through default router(gateway), and if router realizes that its next hop is a router which is on the name network as host A, router sends ICMP REDIRECT to host A to update its routing table so that it can take a shorter path and send its messages through router 2

- Primarily used in Routers
![](https://static.javatpoint.com/tutorial/computer-network/images/icmp-protocol.png)

## ⛳️ TCP &mdash; Transmission Control Protocol
> To enable **Process-to-Process communications** _reliably_ across hosts
- Transport Layer (Layer 4)
- **Connection Oriented**
- Note: Provides _reliable_ connection on top of a _less reliable_ Internet Layer

### Where TCP fits in
       +------+ +-----+ +-----+       +-----+
       |Telnet| | FTP | |Voice|  ...  |     |  Application Level
       +------+ +-----+ +-----+       +-----+
             |   |         |             |
            +-----+     +-----+       +-----+
            | TCP |     | RTP |  ...  |     |  Host Level
            +-----+     +-----+       +-----+
               |           |             |
            +-------------------------------+
            |    Internet Protocol & ICMP   |  Gateway Level
            +-------------------------------+
                           |
              +---------------------------+
              |   Local Network Protocol  |    Network Level
              +---------------------------+

### TCP Layer as an "interface"
                        +---------------------+
                        |     higher-level    |
                        +---------------------+
                        |        TCP          |
                        +---------------------+
                        |  internet protocol  |
                        +---------------------+
                        |communication network|
                        +---------------------+
##### Interface to the _Applications_
- open/close a connection
- send/recv data in an _established_ connection 

##### Interface to the lower layer (Internet Layer)
- pass

### TCP as a reliable layer
TCP recovers from data that is damaged, lost, duplicated, or
delivered out of order by the lower Internet Layer.  

##### How does TCP address _out-of-order_ delivery?
- via `sequence-number` attached to each octet sent
- checked at the reciever end. ( also checks for duplicates)

##### How does TCP address data loss?
- sender expects ACK for each octet sent.
- If the ACK is not received within a timeout
interval, the data is retransmitted.

##### How does TCP address data damage?
- Adds a checksum to each octet transmitted

### TCP Connection
Each connection is uniquely specified by a pair of sockets
identifying its two sides.

##### When 2 processes want to communicate
- Connection Establishment  (init status info on each side [ window size, sequence number, socket info etc])
- Close the Connection after use.

Since connections must be established between unreliable hosts and
over the unreliable internet communication system, a handshake
mechanism with clock-based sequence numbers is used to avoid
erroneous initialization of connections.

### How TCP works < the details >
- Processes call the `TCP module` and pass the _data-buffers-to-be-transmitted_ as arguments
    - Yes, TCP would be a module in the OS
    - The TCP/user interface provides for calls made by the user on the TCP
  to OPEN or CLOSE a connection, to SEND or RECEIVE data, or to obtain
  STATUS about a connection.  These calls are like other calls from user
  programs on the operating system, for example, the calls to open, read
  from, and close a file.
    - TCP module would call the IP module, which in turn calls the  [network device drivers](https://www.cse.iitb.ac.in/~bestin/btech-proj/slip/x129.html)
    -

Processes transmit data by calling on the TCP and passing buffers of
  data as arguments.  The TCP packages the data from these buffers into
  segments and calls on the internet module to transmit each segment to
  the destination TCP.  The receiving TCP places the data from a segment
  into the receiving user's buffer and notifies the receiving user.  The
  TCPs include control information in the segments which they use to
  ensure reliable ordered data transmission.

  The model of internet communication is that there is an internet
  protocol module associated with each TCP which provides an interface
  to the local network.  This internet module packages TCP segments
  inside internet datagrams and routes these datagrams to a destination
  internet module or intermediate gateway.  To transmit the datagram
  through the local network, it is embedded in a local network packet.

  The packet switches may perform further packaging, fragmentation, orother operations to achieve the delivery of the local packet to the
  destination internet module.

  At a gateway between networks, the internet datagram is "unwrapped"
  from its local packet and examined to determine through which network
  the internet datagram should travel next.  The internet datagram is
  then "wrapped" in a local packet suitable to the next network and
  routed to the next gateway, or to the final destination.

  A gateway is permitted to break up an internet datagram into smaller
  internet datagram fragments if this is necessary for transmission
  through the next network.  To do this, the gateway produces a set of
  internet datagrams; each carrying a fragment.  Fragments may be
  further broken into smaller fragments at subsequent gateways.  The
  internet datagram fragment format is designed so that the destination
  internet module can reassemble fragments into internet datagrams.

  A destination internet module unwraps the segment from the datagram
  (after reassembling the datagram, if necessary) and passes it to the
  destination TCP.

  This simple model of the operation glosses over many details.  One
  important feature is the type of service.  This provides information
  to the gateway (or internet module) to guide it in selecting the
  service parameters to be used in traversing the next network.
  Included in the type of service information is the precedence of the
  datagram.  Datagrams may also carry security information to permit
  host and gateways that operate in multilevel secure environments to
  properly segregate datagrams for security considerations.






# Concepts

## ɾ⚈▿⚈ɹ  Socket = `IP + Port`
_A pair of sockets uniquely identifies a connection._

#### What is a "Unix" Socket, how is it different from TCP, UDP sockets?

#### "Listening" socket

#### "Established" connection

## Flow Control (Congestion Control)
When the sender sends packets too fast, faster than what the network can handle , "Congestion" of packets happen

## TTL (time-to-live) 
- Number of hops (routers) between source to dest.
- each router decrements the TTL by one

## Fragmentation

# Layer Basics

## Network Layer (Layer 3)
![](https://static.javatpoint.com/tutorial/computer-network/images/icmp-protocol.png)
# Questions
- What does it mean to be a "network layer thing " or "layer 3 thing"?
- What do we mean by "TCP is reliable"?
- List down the "unit" of transfer for each layer (packet, datagram, segment etc)?