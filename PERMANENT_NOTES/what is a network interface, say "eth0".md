>**Info**
>IP addresses are always assigned to the network interfaces

Network interface is usually physical... the NIC card, but can be virtual as well. It is a **point of connection** between a **computer(router/switch/PC/...) and the underlying network(network medium)** (private or public).

Network interface (virtual) can be implemented entirely in software. Ex: **loopback interface** 127.0.0.1 or ::1.

When we refer to IP address of a machine, it is indeed the IP address of the network interface. **IP addresses are always assigned to the network interfaces**. 

`ip link` lists all the network interfaces.

### eth0, eth1, enp3s0 , wlan0, wlp2s0..?

- `eth0` , `eth1` , `wlan0` are old style of naming network interfaces in linux.
- `enp3s0` , `wlps9` is the new style of naming.



