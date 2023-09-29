Every packet that enters your network interface goes through the kernel and kernel employs `iptables` (`netfilter` particularly,) to decide what to do with that packet(drop? accept? forward?)


`iptables` maintains **tables** to **filter** outgoing and incoming packets to/from your system. Basically a firewall. `iptables` can also be used as a NAT. `iptables` can also do port-forwarding to another IP+Port (internal to the system). `iptables` can also do load balancing and rate limiting!!

Being a firewall, `iptables` helps improve QoS, assuring that resources are not wasted on packets meant to be dropped.

In brief, `iptables` need to maintain configuration to help ALLOW/DENY incoming/outgoing packets. This configuration is in the form of **tables**, each table is a collection of **chains** . Each **chain** has a list of **rules** . Each **rule** may contain a **target**, which decides the fate of the packet(allow/reject/drop). If the packet does not match any **rule**, it will match the **default rule** (called "policy") (which may be configured to "ACCEPT" target, "_accept all packets_"). If there is no default rule(policy), the packet will simply be accepted.

All rules created in given session is lost if you reboot, so use `/sbin/iptables-save` to persist the rules. 
![[linux-09.png]]

Under the hood, `iptables` hooks on to the packet filtering hooks of kernel's networking stack, `netfilter`. Specifically, the kernel modules of `iptables` register with these hooks to ensure that rules in iptables are enforced.

>**Info**
>*What are  these netfilter hooks?*
>- NF_IP_PRE_ROUTING
>- NF_IP_LOCAL_IN
>- NF_IP_FORWARD
>- NF_IP_LOCAL_OUT
>- NF_IP_POST_ROUTING

>**Info**
>Since `iptables` can do NAT in kernel mode (no overhead in switching between kernel mode and usermode, hence very fast and less  load on CPU.)
>Kubernetes uses `iptables` to implement `kube-proxy` which helps create Services. Whenever a service is created, kube-proxy inserts iptables rules on every node, in the `-t nat` table, to be routed to specied PODs' IP addresses (at random) 
### Tables
- filter (default)
- nat
- mangle 
- raw
- security (optional, SELINUX)

#### filter table
serves as firewall. filters incoming/outgoing packets (ACCEPT/DROP)
- incoming packets go through the **INPUT chain**, you can ACCEPT/DROP packets here.
- outgoing packets go through the **OUTPUT chain**, you can ACCEPT/DROP packets there.
- incoming packets that are not intended for the host, but need to hop from this host into another host(forward to target) will go through the **FORWARD chain**. eg: host used as a router to do NAT. you can ACCEPT/DROP packets here. (Note that actual DNAT, SNAT ip translations are done in the **nat table's PREROUTING/POSTROUTING** chains)


#### nat table
helps forward to other network interfaces. Rules in this table(in the chains) will specify how to modify the packet's source and destination address
- **PREROUTING chain** is meant for DNAT
- **POSTROUTING chain** is meant for SNAT
- **OUTPUT chain** is meant for packets destined to the same host (loopback, localhost)

>**Warning**
>You HAVE to enable IP_FORWARD in your PC, else NAT wont work.
>In linux, by default, forwarding packets from one network interface to another is not allowed.
>edit `/proc/sys/net/ipv4/ip_forward` . It contains "0", edit it to "1"

![[linux-11.png]]
some flows
- **_An incoming packet intended for a process in YOUR host_**
	- hits the network interface.
	- goes through **PREROUTING chain** of **nat table**.
	- hits the process in your host.
- **_An incoming packet intended for a process in OTHER host_** (your host is just a hop)
	- hits the network interface.
	- goes through **PREROUTING chain** of **nat table**
	- goes through **POSTROUTING chain** of **nat table**
	- exists via another network interface.
- **_An outgoing packet intended for a process in OTHER host_**
	- originates from a process in your host.
	- goes through **OUTPUT chain** of **filter table**
	- goes through **POSTROUTING chain** of **nat table**
	- exists via another network interface.
- **_An outgoing packet intended for a process in YOUR host_** (loopback, localhost)
	- originates from a process in your host. 
	- goes through **OUTPUT chain** of **filter table**.
	- hits the process in your host.
#### mangle table
helps modify packets, mangle headers.
- modify TTL

#### raw table
`iptables` is by default stateful, i.e packets are treated to be a part of a "session" and are not treated to be disparate and unrelated. This is called **connection tracking** (built into netfilter).
The raw table helps to opt out of this statefulness and mark certain packets to be "disparate".

### Chains
Each **table** contains multiple **Chains**. Each **Chain** can have multiple **rules**. **Chains** determine _when_ the **rule** would be evaluated. **Chains** control where in a packet's delivery path a rule will be evaluated. A table has multiple chains, so a table's influence can be observed at multiple points in the packet's delivery path (not necessarily contiguous).
>**Info**
>The names of the built-in chains mirror the names of the netfilter hooks they are associated with. Its amazing that 4 tables, each with multiple chains ultimately hook on to the following 5 `netfilter` hooks.
>PREROUTING: Triggered by the `NF_IP_PRE_ROUTING` hook.
>INPUT: Triggered by the `NF_IP_LOCAL_IN` hook.
>FORWARD: Triggered by the `NF_IP_FORWARD` hook.
>OUTPUT: Triggered by the `NF_IP_LOCAL_OUT` hook.
>POSTROUTING: Triggered by the `NF_IP_POST_ROUTING` hook.

For eg, 
- **input chain** in **filter table** deals with incoming packets (ingress). 
- **output chain** in **filter table** deals with outgoing packets (egress). 
- **forward chain** in **filter table** deals with incoming packets(ingress) but NOT meant for your IP, its meant to be forwarded to another network interface. (your PC is just a hop).
- **prerouting chain** in **nat table** deals with packets _just after entering the network interface_ 
- **postrouting chain** in **nat table** deals with packets _just before they enter another network interface_ (outgoing, post routing)

Each of the chains has a list of **rules** (eg: a rule called "block incoming SSH connections" in the input chain of filter table). For an incoming packet, every rule in the input chain is matched from top to bottom

Custom chains also can be defined, extending the in-built chains. Attached "custom chains" in `iptables -L` output.
![[linux-12.png]]

### Policy
Policy is just a **default rule** for the chain
```sh
#set default rule to DROP (instead of ACCEPT)
iptables --policy INPUT DROP
```


### Targets
Targets are "actions" that are triggered when a packet matches a rule.
- ACCEPT
- REJECT
- DROP
Targets specify what happens to a packet if it matches a **rule** in the **chain** .



## Examples

#### Flush all the tables/rules
`iptables -F
to start afresh. Everything allowed.

#### Persist all the rules created in a given session
Else the rules will be deleted when you reboot
`/sbin/iptables-save` or `iptables-save` (if in PATH)



#### View the tables
`iptables -L` shows the filter tables
Observe that if there are no rules in the chains, the default is set to ACCEPT.
![[linux-10.png]]

`iptables -L -t nat` shows the nat table

`iptables -L -t mangle` shows the mangle table

`iptables -L -t raw` shows the raw table

use `--line-numbers` option. When you want to delete a rule for a chain, you need to specify the line number of the rule in the chain.
#### Block incoming SSH connections
Insert  a **rule** into the **input chain** of the **filter table**
```sh
iptables -I INPUT -p tcp --dport 22 -j DROP
```
And then to allow just one particular IP to ssh into the system
```sh
iptables -I INPUT -p tcp --dport 22 -s 192.168.1.20 -j ACCEPT
```

#### Block incoming HTTP connections
Insert  a **rule** into the **input chain** of the **filter table**
```sh
iptables -I INPUT -p tcp --dport 80 -j DROP
```
And then to allow just one particular IP to view the site
```sh
iptables -I INPUT -p tcp --dport 80 -s 192.168.1.20 -j ACCEPT
```

#### Block an IP address
Insert  a **rule** into the **input chain** of the **filter table**
```sh
iptables -I INPUT -s 10.0.0.1 -j DROP
```
`-I` to insert at the top of the **chain** (rules are matched from top to bottom). If you just want to append , use `-A`
`-s` to specify the source IP
`-j` to specify the **target**

>**Warning**
>If you block an IP address, you notice that you're not able to access that IP address too, even though you did not add a OUTPUT rule.
>This is because even if you are able to send request packets, the response packets from that IP get rejected because of your INPUT rule.
>You need to add a rule at the very top asking iptables to ALLOW packets belonging to an already ESTABLISHED connection
>`iptables -I INPUT -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT`

#### Block all incoming traffic
override the **default policy** of the **input chain** of the **filter table**.
```sh
iptables -P INPUT DROP
```

>**Warning**
>If you block all incoming traffic, you notice that you're not able to access any external IP (no internet!), even though you did not add a OUTPUT rule.
>This is because even if you are able to send request packets, the response packets from that IP get rejected because of your INPUT rule.
>You need to add a rule at the very top asking iptables to ALLOW packets belonging to an already ESTABLISHED connection
>`iptables -I INPUT -m conntrack --ctstate RELATED,ESTABLISHED -j ACCEPT`
#### Block the entire subnet
Insert  a **rule** into the **input chain** of the **filter table**
```sh
iptables -I INPUT -s 10.0.0.0/24 -j DROP
```

#### Block outgoing connections to an IP
Insert  a **rule** into the **output chain** of the **filter table**
```sh
iptables -I OUTPUT -s 10.0.0.1
```
#### Delete a rule from the chain
Say you blocked an IP and now you want to undo it
```sh 
iptables -D INPUT 1
```
deletes the first rule (1) from the input chain in filter table. 
Why filter table? because its the default. If you had `iptables -t mangle -D INPUT 1` it would have deleted the first rule from **input chain** of the **mangle table** instead.


#### Redirect(forward) port 80 to port 8080
Insert  a **rule** into the **PREROUTING chain** of the **nat table**
Nothing is running on port 80. But a server is listening on port 8080. 

```sh
iptables -t nat -A PREROUTING -p tcp --dport 80 -j REDIRECT --to 8080
```

Breakdown
```sh
iptables \
--table nat \ # work on the nat table (default is filter table)
--append PREROUTING \ # append the rule to PREROUTING chain
--dport 80 \ # match packets whose destination is port 80
--jump REDIRECT \ # if rule matched, jump to REDIRECT target
--to 8080 # change destination port to 8080
```

#### Redirect(forward) to another machine (DNAT+SNAT)
Insert  a **rule** into the **PREROUTING chain** of the **nat table** (DNAT)
Insert  a **rule** into the **POSTROUTING chain** of the **nat table** (SNAT)
Your machine is just a hop. Packet shall enter a network interface and leave through another network interface (hop).
Nothing is running on port 80 of your machine. But a server(on another machine) is listening on port 80 somewhere else..
>**Warning**
>You HAVE to enable IP_FORWARD in your PC, else it wont work.
>In linux, by default, forwarding packets from one network interface to another is not allowed.
>edit `/proc/sys/net/ipv4/ip_forward` . It contains "0", edit it to "1"

>**Warning**
>We are using static IPs here. If you used dynamic IPs, you need to use MASQUERADE and stuff.

Why both DNAT and SNAT? when doing NAT, you need to overwrite both source and destination IPs

```sh
iptables \
--table nat \
--append PREROUTING \
--protocol tcp \
--dport 80 \
--destination 192.168.254.47 \
--jump DNAT \
--to-destination 192.168.254.10:8080

# 192.168.254.10:8080 is running the site
# 192.168.254.47 is your PC (probably a reverse proxy)
```

```sh
iptables \
--table nat \
--append POSTROUTING \
--protocol TCP \
--dport 8080\
--destination 192.168.254.10 \
--jump SNAT\
--to-source 192.168.254.47

# 192.168.254.10:8080 is running the site
# 192.168.254.47 is your PC (probably a reverse proxy)
```


#### Make a load balancer
>**Info**
>Kubernetes' `kube-proxy` actually creates a "Service" and load-balances across different pods(across machines) using `iptables` if configured in iptables mode.
>But loadbalancing with `iptables` is O(N), and there are other modes like IPVS(built on netfilter too) which can do the load balancing in O(1).

>**Info**
>_Why dedicated load balancers like AWS  ELB if `iptables` can do it?_
> `iptables` load balancing is dumb. It does not take into account if the endpoints are overloaded, route to another endpoint etc. This is just a dumb layer-3 load balancer (network layer load balancer)

In this example, we have 3 processes running on same IP on 3 different ports. We shall load balance between them with **round robin approach**
```sh
# DNAT
iptables \
--table nat \
--append PREROUTING \
--protocol tcp \
--dport 80 \
--destination 192.168.254.47 \
--match statistic \ # custom matcher
--mode nth \ # evaluate every nth packet
--every 3 \ # evaluate every 3 packets
--packet 0 \ # evaluate for the first packet (SYN)
--jump DNAT \
--to-destination 192.168.254.10:1111


iptables \
--table nat \
--append PREROUTING \
--protocol tcp \
--dport 80 \
--destination 192.168.254.47 \
--match statistic \ # custom matcher
--mode nth \ # evaluate every nth packet
--every 2 \ # evaluate every 3 packets
--packet 0 \ # evaluate for the first packet (SYN)
--jump DNAT \
--to-destination 192.168.254.10:2222


iptables \
--table nat \
--append PREROUTING \
--protocol tcp \
--dport 80 \
--destination 192.168.254.47 \
--match statistic \ # custom matcher
--jump DNAT \
--to-destination 192.168.254.10:3333

#( no need to provide --mode --every --packet for the last one since rules get evaluated in order and first two rules handle it . If it comes down to 3rd rule, it means first two rules did not match.)

# SNAT
iptables \
--table nat \
--append POSTROUTING \
--protocol tcp \
--dport 1111 \
--destination 192.168.254.10 \
--jump SNAT \
--to-source 192.168.254.47 

iptables \
--table nat \
--append POSTROUTING \
--protocol tcp \
--dport 2222 \
--destination 192.168.254.10 \
--jump SNAT \
--to-source 192.168.254.47 

iptables \
--table nat \
--append POSTROUTING \
--protocol tcp \
--dport 3333 \
--destination 192.168.254.10 \
--jump SNAT \
--to-source 192.168.254.47 
```

BUT, if you want to do a random load balancer (not round robin), 
```sh
iptables \
--table nat \
--append PREROUTING \
--protocol tcp \
--dport 80 \
--destination 192.168.254.47 \
--match statistic \
--mode random \
--probability 0.33 \
--jump DNAT \
--to-destination 192.168.254.10:1111


iptables \
--table nat \
--append PREROUTING \
--protocol tcp \
--dport 80 \
--destination 192.168.254.47 \
--match statistic \
--mode random \
--probability 0.50 \
--jump DNAT \
--to-destination 192.168.254.10:2222


iptables \
--table nat \
--append PREROUTING \
--protocol tcp \
--dport 80 \
--destination 192.168.254.47 \
--jump DNAT \
--to-destination 192.168.254.10:3333

#( no need to provide --mode --every --packet for the last one since rules get evaluated in order and first two rules handle it . If it comes down to 3rd rule, it means first two rules did not match.)

# SNAT
iptables \
--table nat \
--append POSTROUTING \
--protocol tcp \
--dport 1111 \
--destination 192.168.254.10 \
--jump SNAT \
--to-source 192.168.254.47 

iptables \
--table nat \
--append POSTROUTING \
--protocol tcp \
--dport 2222 \
--destination 192.168.254.10 \
--jump SNAT \
--to-source 192.168.254.47 

iptables \
--table nat \
--append POSTROUTING \
--protocol tcp \
--dport 3333 \
--destination 192.168.254.10 \
--jump SNAT \
--to-source 192.168.254.47 
```


## Order of evaluation
![[linux-14.png]]
examples...
_Incoming packets destined for the local system_: PREROUTING -> INPUT
_Incoming packets destined to another host_: PREROUTING -> FORWARD -> POSTROUTING
_Locally generated packets_: OUTPUT -> POSTROUTING

PREROUTING chains of raw, mangle, nat tables evaluated in order.
Then, INPUT chains of mangle, filter, security, nat tables are evaluated in order.
Then, FORWARD chains of mangle, filter, security, nat tables are evaluated in order.
Then, OUTPUT chains of raw, mangle, nat, filter, security tables are evaluated in order.
Then, POSTROUTING chains of mangle, nat evaluated inorder.
..delivered to local socket.

As each chain is called, the packet is checked against each rule within the chain, in order.
The matching system is extensible and very flexible (as noted in how we implemented [[#Make a load balancer]] above)
![[linux-00.webp]]

![[linux-08.png]]
![[linux-00.jpg]]