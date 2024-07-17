#linux #index

![](linux-00.png)

[[linux booting process]]
[[user mode vs kernel mode]]
[[kernel modules]]
[[why arent ALL kernel modules dynamically loaded via modprobe?]]
[[steps in compilation of c program]]
[[static linking vs dynamic linking in c]]

### Shell
[[grep]]
[[find]]
### Installation (archlinux)
[[creating a liveusb]]
[[archlinux installation]]
vmlinuz? initramfs? /boot/initramfs-linux-fallback.img ? mkinitcpio? /etc/mkinitcpio.conf
networkManager vs netctl ? wpa_supplicant?
grub ?

### Disk Management
[[lsblk]]
[[partitioning a disk - fdisk]]    [[Logical volumes, LVM]]
[[formatting a disk - mkfs]]
[[repairing a disk - fsck]]
[[dd command]]


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
[[TCP vs UDP]]
[[DMA — Direct Memory Access]]


[[how to check if a port is open (port->PID)]]
[[how to check if a port is open (port->PID)|which process is listening on given port(port->PID)]]
[[how to check port opened by a given process (PID->port)]]

[[what is a network interface, say "eth0"]]
[[what is a network interface, say "eth0"#How to list all the network interfaces?|How to list all network interfaces]]
[[what is a network interface, say "eth0"#How to list all the network interfaces?|How to list all network interfaces of type bridge]]
[[what is a network interface, say "eth0"#How to find my IP address?|How to find my IP address]]
[[what is a network interface, say "eth0"#How to assign IP address to a network interface?|How to assign IP address to a network interface?]]
[[what is a network interface, say "eth0"#How much data has passed through a network interface?|How much data did I consume?]]
[[what is a network interface, say "eth0"#Simulate 2 LANs connected|Simulate 2 LANs connected with a router]]
[[what is a network namespace]]
[[what is a network namespace#How to create a network namespace|How to create a network namespace]]
[[what is a network namespace#How to allow connectivity between 2 network namespaces (direct connectivity)|What is a veth pair]]
[[what is a network namespace#How to allow connectivity between 2 network namespaces (direct connectivity)|How to allow connectivity between 2 network namespaces(direct connectivity)]]
[[what is a network namespace#How to allow connectivity between N network namespaces (via a bridge)|How to allow connectivity between N network namespaces(via bridge)]]

[[what is iptables]]
[[what is iptables#Block an IP address|How to block an IP address]]
[[what is iptables#Block all incoming traffic|How to block all incoming traffic]]
[[what is iptables#Block incoming SSH connections|How to block incoming SSH connections]]
[[what is iptables#Make a load balancer|How to make a load balancer with iptables]]

[[subnets]]
[[subnets#Subnetting|How to divide a subnet into smaller subnets]]
[[subnets#Given an IP address , can you get the subnet mask?|Given an IP address can you find the subnet mask]]
[[subnets#Given a subnet mask, can you get an IP address in that subnet?|Given a subnet mask, can you find an IP address in that subnet]]
[[subnets#Given an subnet mask, and an IP address..can you confirm if an IP address belongs to the subnet?|Given a subnet mask and an IP address, can you confirm if an IP address belongs to the subnet]]
[[how to monitor packets on a network interface]]
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
