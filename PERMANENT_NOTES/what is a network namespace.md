
With network namespaces, you can simulate N number of PCs sitting inside your PC with their own IP address(network interface) and their own routing tables (and ARP tables) and firewall(iptables).

One of the key drivers of container tech is linux namespaces (other being cgroups). You create a namespace for each container, and it gets its own IP address ( a sandboxed environment, where it can use port 8080 even if your'e already running something on port 8080 of your host.)

A network namespace has no idea about the network interfaces in other namespaces ( incl root network namespace ), hence it cannot connect to processes running in other namespaces via localhost. If it needs to communicate, it needs to communicate via IP+PORT pair as if the destination is on a whole other remote machine.

![](https://iximiuz.com/mastering-container-networking/kdpv.png)

### How to create a network namespace
```sh
ip netns add <name>
```
eg: `ip netns add red` creates a network namespace called red

### How to list network namespaces
`ip netns` 

### How to list network interfaces inside a network namespace
```sh
ip -n red link  # red is the name of the network namespace
# OR
ip netns exec red ip link # you can run any command inside this red namespace
```

>**Warning**
>Just running `ip link` will show network interfaces on the host (root network namespace). Don't forget the `-n` option.

### How to allow connectivity between 2 network namespaces (direct connectivity)
This is very similar to connecting 2 PCs in the same LAN. You don't need to configure subnet routing since both PCs are on the same subnet.
>**Info**
>_What is a veth pair?_
>a veth pair is a virtual ethernet cable with two ends being the "veth pair". each of the 2 ends is a network interface (virtual). You usually place each end of the veth pair in a different network namespace. You also sometimes keep on end on a "bridge" network interface when you want connect N network namespaces instead of interconnecting them directly.


![[linux-07.png]]
First create 2 namespaces
```sh
ip netns add red
ip netns add blue
```
Create veth pairs to connect namespaces
```sh
ip link add veth-red type veth peer name veth-blue
```
Attach one end to red namespace, and other end to blue namespace
```sh
ip link set veth-red netns red
ip link set veth-blue netns blue
```
Assign IP addresses to the network interfaces on each namespace
```sh
ip -n red  addr add 10.0.1.0/16 dev veth-red
ip -n blue addr add 10.0.2.0/16 dev veth-blue
```
Set the interfaces "UP"
```sh
ip -n red  link set dev veth-red up
ip -n blue link set dev veth-blue up
```
...
Now they can talk to each other
```sh
ip netns exec red ping 10.0.2.0
```


### How to allow connectivity between N network namespaces (via a bridge)
If you have several network namespaces, you cannot keep connecting them directly, you'd have a total of (N)x(N-1) connections... too much. 
You create a **bridge** and connect all network namespaces to the bridge. This bridge behaves like a switch.
>**Info**
>You do the same thing with LAN. You don't connect every device with every other device. You connect them all to the same bus, the bridge.

First create 2 namespaces
```sh
ip netns add red
ip netns add blue
```
Create the "bridge" network interface
```sh
ip link add br-0 type bridge
```
This bridge network interface should show up in the list of network interfaces on the host
```sh
ip link
```
Set this network interface "UP"
```sh
ip link set dev br-0 up
```
For red namespace, create a veth pair, assign one end to the red namespace, other end on the bridge.
```sh
ip link add veth-red type veth peer name veth-red-br
ip link set veth-red netns red
ip link set veth-red-br master br-0
```
For the blue namespace, create a veth pair, assign one end to the blue namespace, other end on the bridge
```sh
ip link add veth-blue type veth peer name veth-blue-br
ip link set veth-blue netns blue
ip link set veth-blue-br master br-0
```
Assign IP addresses to the interfaces on the namespaces
```sh
ip -n red  addr add 192.168.15.1/24 dev veth-red
ip -n blue addr add 192.168.15.2/24 dev veth-blue
```
... now they can talk to each other
```sh
ip netns exec red ping 192.168.15.2
```

Note that the host is still unable to talk to process in any of these network namespaces..
We add an IP address to the bridge network interface, (its essentially a network interface belonging to the host or root network namespace)
```sh
ip addr add 192.168.15.5/24 dev br-0
```

![[linux-04.png]]
The network namespaces are still sandboxed in the host. They cannot talk to IPs outside the node. They need a gateway to talk to the outside world (here, the node outside). They can use the resident host as the gateway
![[docker-18.png]] ![[docker-19.png]]
```sh
ip -n blue route add 192.168.1.0/24 via 192.168.15.5
# the host has an IP address 192.168.15.5 on the bridge interface, we use it as a gateway
```
The network namespaces still don't have a way to access the outside world, the internet.
They need a "gateway" to the outside world, the host can act as a gateway.

You still observe that `ping 192.168.1.3` doesn't work. This is because NAT is not configured. Your requests are reaching the destination but response is not being sent back to the blue namespace (SNAT not done)
```sh
iptables -t nat -A POSTROUTING -s 192.168.1.0/24 -j MASQUERADE
```
There is still no internet connectivity (outside world) in blue namespace, so we add a default route
```sh
ip -n blue route add default via 192.168.15.5
```

