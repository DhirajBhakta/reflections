
#### How to find ANY file 
```bash
 find /path/to/dir -name "*partoffilename*"
```

#### How to find total size occupied by a directory
`du -ach`

`du -ach --apparent-size`

Why 2 commands?  what is "apparent size"?
![](assets/linux-tips-01.png)

There is a catch here. "File Size" is different than "disk usage". **FileSize <= DiskUsage**. If you observe the output of simple `du` command, you will see all files are multiples of "4K". Why?
**4k is the size of a single disk block. Disk space is allocated in blocks, so even the smallest disk takes up one block (4k) on your disk**

#### How to read a `man` page
- `man man` ಠ益ಠ
- `help <cmd>` Helps you find info on shell builtins


####  What is a Shell BUILTIN ?
- `cd` is a shell builtin!

#### The /proc filesystem?
- Process information pseudo-file system
    - Theyre not "real" files ( `ls -lah` shows file size=0 for all)
- They contain runtime system information (e.g. system memory, devices mounted, hardware configuration, etc). For this reason it can be **regarded as a control and information centre for the kernel**
    - In fact, quite a lot of system utilities are simply calls to files in this directory. For example:
        - `lsmod`  = =  `cat /proc/modules`
        - `lspci`  = = `cat /proc/pci`. 

```haskell
       /etc/services -- The services translation file

       /proc -- Mount point for the proc filesystem, which gives access to kernel status information via the following files.

       /proc/net/dev -- device information

       /proc/net/raw -- raw socket information

       /proc/net/tcp -- TCP socket information

       /proc/net/udp -- UDP socket information

       /proc/net/udplite -- UDPLite socket information

       /proc/net/igmp -- IGMP multicast information

       /proc/net/unix -- Unix domain socket information

       /proc/net/ipx -- IPX socket information

       /proc/net/ax25 -- AX25 socket information

       /proc/net/appletalk -- DDP (appletalk) socket information

       /proc/net/nr -- NET/ROM socket information

       /proc/net/route -- IP routing information

       /proc/net/ax25_route -- AX25 routing information

       /proc/net/ipx_route -- IPX routing information

       /proc/net/nr_nodes -- NET/ROM nodelist

       /proc/net/nr_neigh -- NET/ROM neighbours

       /proc/net/ip_masquerade -- masqueraded connections

       /sys/kernel/debug/bluetooth/l2cap -- Bluetooth L2CAP information

       /sys/kernel/debug/bluetooth/rfcomm -- Bluetooth serial connections

       /proc/net/snmp -- statistics
```
