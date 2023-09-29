#network-interfaces #linux #networking

>**Info**
>IP addresses are always assigned to the network interfaces

>**Info**
>"Network interfaces" are sometimes called "Network devices"

>**Info**
>A newly created network namespace **has no network interfaces** at all.
>You **cannot** communicate with the outside world from inside this new network namespace.
>You **cannot** even connect to servers you created on localhost since there is **no loopback interface**. There IS NO localhost to begin with.

>**Info**
>When you send a packet to an IP+Port, your route table decides which network interface it goes through (since you have multiple network interfaces on the SAME machine!)

Network interface is usually physical... the NIC card, but can be virtual as well. It is a **point of connection** between a **computer(router/switch/PC/...) and the underlying network(network medium)** (private or public).

Network interface (virtual) can be implemented entirely in software. Ex: **loopback interface** 127.0.0.1 or ::1.

When we refer to IP address of a machine, it is indeed the IP address of the network interface. **IP addresses are always assigned to the network interfaces**. 

### How to list all the network interfaces?
`ip link` 
To see only the "bridge" network interfaces `ip link show type bridge`.
There is no such thing as a "bridge network" entity in linux. You create a network interface (device) of type "bridge" and set it as "master" to other newly created network interfaces (typically one end of veth-pairs). This gives a feel of a "bridge network" where all other virtual devices are connected, and the host itself is connected to the bridge network via the network interface called....the bridge itself. (look below for the bridge diagram. The "bridge" arrow and br01 network interface are one and the same thing, although it would have been absurd if they weren't virtual).

### How to check status of the network interface? 
`ip link`
![](linux-05.png)
To turn on, `ip link set dev enp1s0 UP`
To turn off, `ip link set dev enp1s0 DOWN`
### eth0, eth1, enp3s0 , wlan0, wlp2s0..?

- `eth0` , `eth1` , `wlan0` are old style of naming network interfaces in linux.
- `enp3s0` , `wlps9` is the new style of naming.

### What is "dev" or DEVICE in `ip link` parlance?
Device is synonymous to network interface.

### Why does my machine have so many network interfaces?
Fair. You have just one NIC card. So one network interrface (?)

Your PC is connected to your LAN via the `eth0` interface. 

You might have also created multiple network namespaces (think of these as VMs) and also connected them all to a (virtual) bridge. **Now think  of these are real (not virtual). Helps your mental model...**, what would it take for you to have connectivity between your PC and these VMs? you'd need to somehow connect to the bridge too, and **that implies you need an extra network interface to connect to the bridge**

![](../../assets/linux-04.png)

`docker0` is one such bridge created by docker to attach all containers to. Each container is in its own network namespace.

### How to find my IP address?
>**Info**
>A PC doesn't have an IP address. A PC has network interface(s) and that's the one which has an IP address. You don't ping a PC, you ping a network interface.


an IP address **is assigned to the network interface**, NOT to your PC itself. A PC can have multiple network interfaces, physical and virtual.. so the question "How to find my IP address" depends on _from which_ network interface are you looking at my PC ?

The key is ..again "**IP address is assigned to network interfaces**". (refer to the diagram above), 
- From the perspective of the VMs, the IP address assigned to `br01` is my PC's IP address.
- From the perspective of other PCs on my main LAN, the IP address assigned to `eth0` is my PC's IP address.
- If I was connected over WIFI, the IP address assigned to my WNIC, `wlan0` interface is my PC's IP address.

the `ip addr` shows the IP address assigned to every network interface on the system. Most often , "whats the IP address of my PC" translates to "whats the IP address of the network interface which is on the same network as the router/gateway to talk to the outside world(internet)". You need to look at the route table to find which network interface that is, with the `route` command.
![[linux-06.png]]

### How to assign IP address to a network interface?
`ip addr add 192.168.10.2/32 dev eth0`


### How much data has passed through a network interface?
Helps you check how much data is consumed
`ip -s link` .
You can also use `ifstat`

![[linux-13.png]]
### Simulate 2 LANs connected
Say there are 2 PCs .. PC1 & PC2 on the `192.168.1.0/24`  network. Let's assign IP addresses to these (specifically, network interfaces of these...)
```bash
# on PC1, 
# obtain the name of the network interface
ip link
# assign IP address to the network interface
ip addr add 192.168.1.11/32 dev eth0

on PC2,
# obtain the name of the network interface
ip link
# assign IP address to the network interface
ip addr add 192.168.1.12/32 dev eth0

# now PC1 can talk to PC2
ping 192.168.1.12
```

There's another LAN (`192.168.2.0/32`) with PC3 & PC4 . How can PC1 talk to PC4? you need to teach this via route tables on every PC. 
You will have a **dedicated router** connected to both these networks LAN1, LAN2. The router will have two network interfaces, one each for each network it is connected to, hence it will have 2 IP addresses, one each for every network interface it has.
The router has `192.168.1.1` in LAN1, and `192.168.2.1` in LAN2. 
```shell
# on PC1
ip route add 192.168.2.0/24 via 192.168.1.1
# PC1 can reach PC3
ping 192.168.2.11
```
For reaching the outside internet, we add the default gateway too
```bash
# on PC1
ip route add default via 192.168.1.1 dev eth0
```
Your packets will still not pass through the gateway, you need to enable this on the gateway
By default, linux does not allow packets to be forwarded from one network interface to another on the same host(here, router). 
`cat /proc/sys/net/ipv4/ip_forward` is set to "0". Set it to "1".

### What is a "switch" ?
a hardware device which acts as a bridge.
connects hosts to form a LAN.
If not for SDNs, to create a bridge, you'd have to buy a switch.


### What is a "router" ?
Sounds like both switches and routers help connect multiple devices...

while a switch helps connect say 50 devices in a LAN, a router helps connect upto 4 switches,  forming an even larger network. Routers connect multiple LANs into WANs.

a router mainly acts as a gateway to internet, with the ability to **decide the next best hop** to the destination. a switch cannot do that, it blindly accepts a packet from one network interface and forwards it through another network interface (switching).

>**Info**
>A layer-3 switch is both a switch and a router!





