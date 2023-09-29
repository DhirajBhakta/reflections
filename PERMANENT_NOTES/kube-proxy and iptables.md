#networking #kubernetes #kube-proxy #service
A **Service** helps get a stable IP and is sort of a reverse proxy for the N **Pods** behind it.
The **Service** load balances between the set of pods.

<<<<<<<<<<
_kube-proxy's job is to redirect requests from ClusterIP to Pod's IP_
<<<<<<<<<<<

>**Info**
>_Packet Flow_
> When a **Pod** wants to communicate with a **Service** by its name (eg:"db-service"),  it makes a DNS query. `core-dns` Pod resolves the DNS query to the cluster-internal IP address of the **Service**. When the **Pod** sends packets to the **Service**'s IP address, `kube-proxy` in `iptables` mode ensures that the packet is correctly forwarded to one of the **Pod**s selected by the Service.

Each **Pod** exists in a separate _network-namespace_ [[what is a network namespace]] . 
This proxy-ing and load-balancing are achieved via `iptables` [[what is iptables#Make a load balancer]] . When a packet arrives at the host **Node**, it must decide how to forward it to one of the Pods(network-namespaces). The **Pod** may or may not lie on the same node. With `iptables`  in `-t nat` mode, you can setup forwarding rules to forward the packet to leave via a network interface and reach another **Node**. 

Every time a **Service** is created, `kube-proxy`  _listens to these events and creates `iptables` rules on ALL **Nodes** to route packets to appropriate **Pods** whenever they're sent to the Service's IP+Port._
The **Service** Resource has a **controller** which updates the endpoints list everytime Pods are replaced/deleted/added. This is done by constantly querying the `kube-apiserver`  to get events. 
>**Info**
>`kube-proxy` runs on ALL nodes as a **DaemonSet**. `kube-proxy` updates `iptables` of ALL nodes each time a new Service is created. This is because a Service should be able to route packets to Pods in **any Node**.

>**Info**
>A Service is NOT a Pod, even though it has an IP address. There is no resource for Service. As such, the Service does not even exist. It exists only in-memory, represented as a set of `iptables` rules on the Host **Node**. 

>**Warning**
>This results in a overall 2 levels of load-balancing for a packet.
>Once at the primary load balancer(or Ingress), and again by `kube-proxy` when it hits a **Service** to eventually reach a **Pod**.

> **Info**
> `ipvs` mode is far more efficient than `iptables` since it does lookups in `O(1)` whereas rules in `iptables` are looked from top to bottom in `O(N)`.
> `--proxy-mode` argument on `kube-proxy` specifies whether it is using `ipvs` or `iptables`(default). 

#### View `iptables` rules for a Service
```sh
iptables -L -t nat | grep <service-name>
```


#### `kube-proxy` logs 
These logs show how `kube-proxy` detected new Service creation, or new endpoints being registered/deregistered.
`/var/log/kubeproxy.log` 

