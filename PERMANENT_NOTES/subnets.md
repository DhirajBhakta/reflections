![[linux-16.png]]
A subnet mask reveals how many bits in the IP address are **network bits** and how many are **host bits**.
![[linux-17.png]]

https://networkengineering.stackexchange.com/questions/7106/how-do-you-calculate-the-prefix-network-subnet-and-host-numbers

*IP address :       128.42.5.4
subnet mask :    255.255.248.0
How many hosts ?
First(gateway address) and last IP(broadcast address) address in this subnet?
How to break this subnet into 2 subnets?
How to break this subnet into 4 subnets?
How to break this subnet into 8 subnets?*

#### Calculating number of hosts in the subnet
255.255.248.0 => 11111111. 11111111. 11111000. 00000000 (in binary) => /21
**This is a /21 subnet**
It has 9 zero bits, => 2^11 possible numbers => **2^11 hosts = 2048 hosts**
> **Info**
> total hosts in a subnet = `2 ^ (number of rightmost zeros in a subnet mask)`


### First IP address in the subnet (gateway address)
128.42.5.5        => `10000000`. `00101010`. `00000101`. `00000100`
255.255.248.0 => `11111111`. `11111111`. `11111000`. `00000000` 
bitwise & the IP address with the subnet, to get the first IP

first octet remains the same => 128 (cuz 255, all 1s)
second octet remains the same => 42 (cuz 255, all 1s)
third octet is all zeros => 0 ..(cuz bitwise &)
fourth octet is all zeros => 0 ...(cuz bitwise &)

**the first IP address is 128.42.0.0**
>**Info**
>Copy the network bits of the IP address, and make all the host bits zero except the right most bit (make it 1) to get the first IP address.


### Last IP address in the subnet (broadcast address)
128.42.5.5        => `10000000`. `00101010`. `00000101`. `00000100`
255.255.248.0 => `11111111`. `11111111`. `11111000`. `00000000` 
_The last 11 bits of subnet mask is 0. If you set the last 11 bits of your IP address to 1, you get the last IP address_
first octet remains the same => 129
second octet remains the same  => 
third octet is 00000111 => 7
fourth octet is 11111111 => 255

**the final IP address is 128.42.7.255**
>**Info**
>Copy the network bits of the IP address, and make all the host bits 1 to get the last IP address

### Subnetting
Subnetting is **dividing** the subnet into child subnets (parent will no longer exist post subnetting).

Subnetting is done by changing the subnet mask by borrowing some of the bits from the host portion (right shift).

255.255.255.0     => `11111111`. `11111111`. `11111111`. `00000000`  1 network with 256 hosts
255.255.255.128  => `11111111`. `11111111`. `11111111`. `10000000`  2 networks with 128 hosts
255.255.255.192  => `11111111`. `11111111`. `11111111`. `11000000`  4 networks with 64 hosts
255.255.255.224  => `11111111`. `11111111`. `11111111`. `11100000`  8 networks with 32 hosts
255.255.255.240  => `11111111`. `11111111`. `11111111`. `11110000`  16 networks with 16 hosts
255.255.255.248  => `11111111`. `11111111`. `11111111`. `11111000`  32 networks with 8 hosts
255.255.255.252  => `11111111`. `11111111`. `11111111`. `11111100`  64 networks with 4 hosts
255.255.255.254  => `11111111`. `11111111`. `11111111`. `11111110`  128 networks with 2 hosts



#### If you want to divide this subnet into 8 subnets
you **right-shift** the subnet mask by 3. because 4 = 2^3 and you have
11111111 .11111111. 11111111. 00000000 => **/24 subnets** (8 subnets formed from original subnet)

What is the IP address range of each of those 8 subnets?
The old IP was... 
128.42.5.5 => 10000000. 00101010. 00000101. 00000100 
The old subnet mask was
255.255.248.0 => 11111111. 11111111. 11111000. 00000000
The new subnet mask is
=> 11111111. 11111111. 11111111. 00000000
The difference between them is 3 last digits on the 3rd octet.
The third octet in the first IP address of the old subnet was 00000000.
Now there are 8 combinations of this 3rd octet where last 3 digits can either be 0 or 1
00000000 => 0
00000001 => 1
00000010 => 2
00000011 => 3
00000100 => 4
00000101 => 5
00000110 => 6
00000111 => 7

**hence the 8 subnets are
128.42.0.0/24
128.42.1.0/24
128.42.2.0/24
128.42.3.0/24
128.42.4.0/24
128.42.5.0/24
128.42.6.0/24
128.42.7.0/24**
each of them have 256 IP addresses

#### If you wanted only 2 subnets,
you **right-shift** the subnet mask by 1. because 2 = 2^1 and you have
11111111 .11111111. 11111100. 00000000 => **/22 subnets** (2 subnets formed from original subnet)

The old IP was... 
128.42.5.5 => 10000000. 00101010. 00000101. 00000100 
The old subnet mask was
255.255.248.0 => 11111111. 11111111. 11111000. 00000000
The new subnet mask is
=> 11111111. 11111111. 11111100. 00000000

difference between them is the 6th digit in the 3rd octet. it can either be 0 or 1, only 2 possibilities (we need just 2 subnets)
The third octet was 00000000. two possibilities of the 6th bit being 0 or 1 is
00000000 => 0
00000100 => 4

**hence the 2 subnets are
128.42.0.0/22 
128.42.4.0/22**
each of them have 1024 IP addresses

#### if you wanted 4 subnets
you **right-shift** the subnet mask by 2. because 2 = 2^2 and you have
11111111 .11111111. 11111110. 00000000 => **/23 subnets** (4 subnets formed from original subnet)

The old IP was... 
128.42.5.5 => 10000000. 00101010. 00000101. 00000100 
The old subnet mask was
255.255.248.0 => 11111111. 11111111. 11111000. 00000000
The new subnet mask is
=> 11111111. 11111111. 11111110. 00000000

difference between them is the 6th bit and 7th bit in the 3rd octet. they can give 4 possibilities (00,01,10,11)
The third octet was 00000000. 4 possibilities of 6th and 7th bit are
00000000 => 0
00000010 => 2
00000100 => 4
00000110 => 6


**hence the 4 subnets are
128.42.0.0/23 
128.42.2.0/23
128.42.4.0/23
128.42.6.0/23**
each of them have 512 IP addresses

### Given an IP address , can you get the subnet mask?
No.
> **Info**
> At very minimum, you need a **subnet mask** and an **IP address in the subnet**.

Its similar to asking, given a point, can you get the circle it belongs to? Unless you know he coordinates(and radius) of the circle, you cant know that the point belongs inside the circle.

There are totally 2^32 IP addresses
All these could have been,
in a single `/0` subnet, OR
in 2 `/1` subnets, OR
in 4 `/2` subnets, OR
in 8 `/3` subnets, OR
in 16 `/4` subnets, OR
...
in 2^24 `/24`  subnets, OR

All this is with the assumption that the entire space is divided into **equally sized** subnets. The reality is far from this. Any subnet could be divided any number of times. (for eg: **How do you divide a subnet into 3? You divide it into half, and then divide one half by 2 again**). You cannot guess where an IP address lies, it can be in any of these squares, and you dont even know how many such small/big squares are there.
![[networking-00.png]]


### Given a subnet mask, can you get an IP address in that subnet?
No
>**Info**
>At very minimum, you need a **subnet mask** and an **IP address in that subnet**.

Its similar to asking, given a circle of radius 10, can you find a point in that circle? Since you don't have the coordinates(center) of the circle, the radius is pointless. The 10cm radium circle could be anywhere!

Given a subnet, `/24` you know how big the subnet is.. (here, 256 hosts), but you don't know **where** this range of 256 hosts is ? Look at the image above, given small square of fixed size, can you locate where exactly it is?

A `/22` subnet could be divided into 4 `/24` subnets. Which of these 4 `/24` subnets will you choose to fetch an IP address from?


### Given an subnet mask, and an IP address..can you confirm if an IP address belongs to the subnet?
(**eg**: given the subnet `192.168.1.0/24` , can you tell if `192.168.1.100` is in the subnet? here the subnet is `/24` and `192.168.1.0` is confirmed to be in the subnet. With this notation, it stands for the gateway address or the first address in the subnet. But it _need not_ necessarily be the first IP address. It does not matter. **All you need is any IP** in the subnet. Just to get the **network bits**)

Yes
>**Info**
>At very minimum, you need a **subnet mask** and an **IP address in that subnet**.

Given the subnet mask, and an IP address in the subnet...
you can now find the **network bits** and **host bits** of the given IP address inside the subnet.

Just confirm that **network bits** of the IP address in question is same as the **network bits** of the 

eg: 
_given the subnet `192.168.1.0/24` , is `192.168.1.100` in the subnet?_
Yes. This is easy because `/24` => 24 bits set => first 3 WHOLE octets set. These are the network bits. Any IP in this subnet must have the same network bits as any other IP in this subnet. `192.168.1.100` shares the same numbers in first 3 octets, hence yes, it belongs to the subnet.

_given the subnet `192.168.1.0/22` is `192.168.1.100` in the subnet?_
 `/22` => 22 bits set => first two WHOLE octets are set, third WHOLE octet is not set, just a few bits
1st octet of `192.168.46.100` is 192, same as that of `192.168.1.0`
1st octet of `192.168.46.100` is 168, same as that of `192.168.1.0`
3rd octet of `192.168.1.100` is 1, same as that of  `192.168.1.0` ,
hence yes, it belongs to the subnet

_given the subnet `192.168.1.0/22` is `192.168.46.100` in the subnet?_
 `/22` => 22 bits set => first two WHOLE octets are set, third WHOLE octet is not set, just a few bits
1st octet of `192.168.46.100` is 192, same as that of `192.168.1.0`
2nd octet of `192.168.46.100` is 168, same as that of `192.168.1.0`
3rd octet of `192.168.46.100` is 46 ...
46    => `00101110`

`/22`  => `11111111.11111111.11111100.00000000`
first 6 bits of 3rd octet are **network bits**
3rd octet of the given IP is 1 ...
1 => `00000001`

the first 6 bits of 1 is NOT same as first 6 bits of 46, hence no, `192.168.46.100` does NOT belong to the subnet.

allowed IPs are the ones which have same first 6bits in the 3rd octet
`00000000` => 0
`00000001` => 1
`00000010` => 2
`00000011` => 3
Allowed IPs are
`192.168.0.*`
`192.168.1.*`
`192.168.2.*`
`192.168.3.*`
=> 4 x 256 IPs = 1024 IPs.
which matches with the fact that `/22` should have 22 bits set (network bits), and 10 bits unset (host bits) => 2^10 hosts = 1024 hosts.








