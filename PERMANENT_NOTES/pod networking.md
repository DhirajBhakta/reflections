#kubernetes #cni #networking 
 ![[kube-59.png]]

-> Every Pod gets an IP address.
-> Any Pod can communicate with any other Pod(same Node or any other Node) **without using NAT**.
-> A node can communicate with a Pod **without using NAT**.
-> _A Host does NOT mask a Pod's IP address_. A Pod's awareness of its own IP address is same as how other resources see the address. "True IP address without NAT". (opposite of how the world sees us through the router's gateway IP address, when we sit as private IPs behind the gateway).

Kubernetes does NOT implement the networking solution. Instead it specifies a spec and vendors implement CNI Plugins which do the Pod networking,

>**Info**
>_CNI is not mandatory!_
>If you use host networking for every pod, then you dont need pod networking (CNI) at all, you dont need kube-proxy or even core-dns!
>You dont need a working overlay network. 
>In this setup, your Pods can communicate with the outside world, just like any other process on your host does.
## CNI Plugin
eg: Calico, Flannel, Weave, Romana, Cilium
_Any container runtime should be able to work with any CNI Plugin_

A CNI plugin adheres to the CNI Spec, and mainly the following
- IPAM (IP Address management),
	- assigns IP address to the Pod
	- assigns a subnet to each Node
-  Builds an **Overlay Network**(of Pods) on top of multiple nodes.
	- An Overlay Network implies every Pod has an IP address, and every pod can refer to other Pod's by its IP address (without worrying about which nodes they're on) and can communicate with other Pods **without a NAT**
	- Maintains a stable mapping of nodes to internal subnets (subnets of Pods) and keep every node updated with that mapping. They also do cleanup when nodes are added/removed, Pods are added/removed.
	- Make sure the Pods can **make requests outside the cluster too**

### CNI Spec
The CNI Spec sets expectations from both sides, container-runtime and CNI plugin, for the APIs they're supposed to expose.

For Container runtime side, it specifies...
- Container runtime **must create network namespace**
- Container runtime **must identify the network namespace a new Pod has to be assigned to**
- Container runtime **must invoke the CNI plugin when a container is ADDed**
- Container runtime **must invoke the CNI plugin when the container is DELeted**
- Container runtime **must cleanup network namespaces after the container is DELeted**

For the CNI Plugin side, it specifies...
- Plugin must **support CMD-line args for ADD/DEL/CHECK/LIST**
- Plugin must **support the params < containerID > < namespaceID > **
- Plugin must **handle IPAM for the Pods, assign IP address to the Pod**
- Plugin must **return results in specified format**

How the CNI Plugin implements this spec is left to it. Layer2, Layer3, VXLAN, Overlay network, mesh network, BGP, eBF one dedicated subnet per node, creating veth-pairs, adding route table entries in each Pod... Plugin can do whatever it wants.

![[kube-00.jpeg]]
Notice how
- kubelet interacts with container runtime
- container runtime interacts with CNI plugin to establish the connection between Pod (and the Host)
- Read [[what is a network namespace]] and [[what is a network interface, say "eth0"]]
### Sample implementation of a CNI Plugin
![[kube-62.png]]![[kube-61.png]]

Pre-requisite
- [[what is a network interface, say "eth0"]]
- [[what is a network namespace]]
- [[what is iptables]]
Your nodes are on 192.168.1.0/24 network, each of them has an IP address.
Every time a Pod is created,
- the container runtime creates a network namespace ,
- the container runtime informs the CNI plugin of podID, networkNamespaceID.
- the CNI plugin creates a **bridge network**(a network interface) on every Node, and brings it "UP". 
	- The bridge network will be its own subnet, hence every node contains a separate subnet, since every node contains a bridge network. 
	- The CNI plugin chooses 10.244.1.0/24 as the subnet for this Node. Other Nodes shall have 10.244.2.0/24 , 10.244.3.0/24 . 
- The CNI plugin associates an IP address to the bridge network interface  - 10.244.1.1/24
	- IP address is assigned to the network interface on the host which is connected to this "bridge network", so that incoming packets on the host can be forwarded to this network interface "bridge", so that it can be propagated to the network namespace of the Pod
	- The host sits on both networks, one subnet on which it is connected to other nodes, another subnet on which the Pods inside the Node reside. Hence it has two network interfaces.
>**Info**
>Pod CIDR can be found on IPAM section in the cni config in `/etc/cni/net.d/*`. The location is configured on the container runtime startup arguments.
```sh
ip link add v-net-0 type bridge
ip link set dev v-net-0 up
ip addr add 10.244.1.1/24 dev v-net-0
```
- The network namespace of the POD is connected to the bridge network by creating veth-pair. 
	- One end of the veth-pair is kept inside the Pod's network namespace. 
	- The other end is attached to the bridge network 
	- an IP address (within the subnet of the bridge network) is assigned to the veth pair end inside the Pod's network namespace.
```sh
ip link add veth-red type veth peer name veth-red-br
ip link set veth-red netns red
ip link set veth-red-br master v-net-0
ip -n red addr add 10.244.1.2/24 dev veth-red
ip -n red link set dev veth-red up
ip link set dev veth-red-br up
```
- The CNI Plugin adds a route to the bridge network for outgoing connections. The host Node acts as a gateway for all the Pods on the Node. A default route is also added (default gateway) to have internet access.
```sh
ip -n red ip route add 192.168.1.0/24 via 10.244.1.1
ip -n red ip route add default via 10.244.1.1
```
- The CNI Plugin adds a `iptables` rule in `-t nat` table in `POSTROUTING` chain to allow incoming packets on the Node to be NAT'ed correctly to Pods. the `iptables` rule is added on the host Node.
```sh
iptables -t nat -A POSTROUTING -s 10.244.1.0/24 -j MASQUERADE
```
<<<<<<<
We managed to establish connectivity between Pods on the same Node. What about connectivity to Pods on other Nodes?
<<<<<<<
- For every Pod, we could continue to use the host Node as a default gateway for every other Pod subnets
```sh
# assuming there are 4 other nodes, hence 4 subnets (4 bridge networks in each node)
ip -n red route add 10.244.2.0/244 via 10.244.1.1
ip -n red route add 10.244.3.0/244 via 10.244.1.1
ip -n red route add 10.244.4.0/244 via 10.244.1.1
ip -n red route add 10.244.5.0/244 via 10.244.1.1
```
- This gets cumbersome when number of nodes and Pods is too much. For every Pod you need to add N routes to the bridge where N=total number of subnets=total number of Nodes. _You could instead use a dedicated router, put all these routing information on that router, and use it as a default gateway_.


### Why cannot kubernetes implement Pod networking by itself?
You can indeed setup Pod networking using barebones setup as described above in [[#Sample implementation of a CNI Plugin]], its also been described in detail in Kelsey Hightower's Kubernetes The Hard Way.

**But it does not scale** . Not viable for clusters with 50+ nodes etc.

CNI plugins are made by network "expert" companies and you can trust them do some hocus pocus on stuff like VXLAN, BGP, eBF etc to have improved performance.

