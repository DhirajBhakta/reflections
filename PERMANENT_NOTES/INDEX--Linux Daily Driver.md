#linux #index

![](linux-00.png)

[[linux booting process]]
[[user mode vs kernel mode]]
[[kernel modules]]
[[why arent ALL kernel modules dynamically loaded via modprobe?]]
[[steps in compilation of c program]]
[[static linking vs dynamic linking in c]]
### Querying about the machine
[[find my linux distro]]

### Process Management
[[ps aux]]

IPC
- Shared files & Shared memory
- Pipes & FIFO Queues (named and unnamed)
- Message Queues
- Signals and Semaphores
- Sockets
	- Unix Domain Sockets
	- Internet Sockets
- [[D-Bus]]


### Service(Daemon) Management
[[what is a service?]]
[[init system . systemd systemctl]]
[[journalctl]]


### Package Management
[[what is a package]]
[[what is a package manager]]
TODO: [[building from source]]


### Miscellaneous 
[[self signed certificates]]




# Networking 

[[how to check if a port is open (port->PID)]]
[[how to check if a port is open (port->PID)|which process is listening on given port(port->PID)]]
[[how to check port opened by a given process (PID->port)]]
[[what is a network interface, say "eth0"]]
[[how to view all network interfaces]]
switch
bridge
router
can one network interface have more than one IP address? can same IP addres
difference between "device" and "interface" in ip link command...
why is the "interface" assigned an IP address. can "device" be assigned IP address too?
does every "interface" have a MAC address even if the interface is virtual?
why should IP address be assigned to the bridge network interface? i heard that it is done so that it can act as the gateway? how and why??
how many NICs does a switch have? one per port? 
what layer is switch bridge router...
learn `iptables`
im confused a lot: 2 ways to do the same thing: add a route to routing table || OR || add rule to iptables  ?? wtf why?? and how??
what and why is dhcp required??
### Tools
[[ip is the new ifconfig]]


# Hardware
### CPU 
[[hyperthreading - CPUs vCPUs]]
Single Socket CPU vs Multi-socket CPUs (i3 cpu is for eg: single socket, with 4 cores on same socket)
What is NUMA? memory controller attached to every cpu socket. Enabled on only multi-socket CPUs.
### Memory 
[[accurate process memory consumption]]
What is SRAM and DRAM? SRAM is extremely fast, and is used for L1,L2,L3 cpu caches.
Why do we have both SRAM and DRAM in single PC? SRAM is for CPU caches.

# TODO ---
3. study bootloaders
4. virtual filesystems
5. pathname lookups in linux & Linux dcache
6. lockfree reference counting | linux kernel's lockref lock