# Distros
See [Distrowatch](https://distrowatch.com/)

A little bit of history &mdash; The grand-daddy is UNIX. Created by Ken Thompson and Dennis Ritchie( C creator) in Bell Labs, 1969. UNIX was born out of a failed attempt at Multics, an ambitious time-sharing OS which can run on the then Mainframes.
>What we wanted to preserve was not just a good environment in which to do programming, but a system around which a fellowship could form. We knew from experience that the essence of communal computing, as supplied by remote-access, time-shared machines, is not just to type programs into a terminal instead of a keypunch, but to encourage close communication <br/>
             --<i>Dennis Ritchie</i>

![](https://upload.wikimedia.org/wikipedia/commons/c/cd/Unix_timeline.en.svg)
All the distros that we talk about belong to an umbrella term called "*NIX" or "UNIX-like", which technically means they all are [POSIX compliant](https://opensource.com/article/19/7/what-posix-richard-stallman-explains). 

So at the very top level of all Distros, we have the following *NIX families
 - Linux
 - Solaris
 - BSD

 Out of which LINUX is not a derivative of UNIX.

 Solaris branched off from Commercial UNIX (v7) and developed/maintained by Sun Microsystems/Now Oracle, and BSD (Berkeley Unix) was based on the source code of the original UNIX of Bell Labs, developed (extended) at University of California. That's why BSD is said to be the closest possible UNIX variant.<br> Note that MacOS is a derivative of BSD

 ## Solaris Distros
 - OpenSolaris
 - SmartOS

 These are just not famous.

 ## BSD Distros
- NetBSD
- FreeBSD
- OpenBSD
- GhostBSD
- Darwin --> Mac OSX + iOS

Why would one use BSD? Its _sorta_ performant on certain hardware, especially embedded. Also they dont have the strict GNU policy/license issue of being forced to release your code if you tweak it. Big Companies dont like to release their internal code/tweaks, so they might use BSD




## Linux Distros
#### Why was LINUX born? 

BSD was already sued by AT&T for including UNIX code in their kernel. There was a major need to get a free alternative. Richard M Stallman created the GPL, and hell lot of GNU software to create a full blown OS. But HERD, the GNU kernel, was really bad.

Around same time, Tannenbaum released MINIX, to aid his OS texbook. This OS was mainly for academic use and served as a "best-practise exemplar" of an OS. Source code of MINIX was prohibited from modification and distribution. Also it was built for 16 bit architecture. Intel's 32 bit CPUs were already getting popular, in PCs at the time.

Linus Torvalds didn't have money for buying a UNIX at the time for his Masters thesis, and ended up creating a clone , from scratch -> LINUX kernel, taking MINIX as an inspiration. He admits that had GNU HERD or BSD kernels for 32 bit been available, he would not have made LINUX. The Linux Kernel was the missing piece for the GNU software to become a full blown OS.
[Linus' famous mail](https://www.linux.com/news/linuss-famous-email/)

#### on linux distros
Most distributions offer pre-compiled packages of most common tools, such as RPM packages on RedHat and Debian packages (also called deb or dpkg) on Debian, so you needn't be a programmer to install a package on your system. However, if you are and like doing things yourself, you will enjoy Linux all the better, since most distributions come with a complete set of development tools, allowing installation of new software purely from source code. This setup also allows you to install software even if it does not exist in a pre-packaged form suitable for your system.

- Debian
    - Ubuntu
    - Linux Mint
- Fedora
    - RHEL
    - Centos
- Mandriva
- OpenSUSE
- Gentoo
- ArchLinux




Before we proceed into Linux, [this](https://wiki.osdev.org) is the god reference 
## Package managers
[How package managers work](https://opensource.com/article/18/7/evolution-package-managers)
![](https://i2.wp.com/itsfoss.com/wp-content/uploads/2020/10/linux-package-manager-explanation.png?w=800&ssl=1)

### .deb vs .rpm
**.deb** : for Debian, and its derivatives (Ubuntu, Linux Mint)<br>
**.rpm** : for Fedora, and its derivatives (RHEL, centOS), and openSUSE

**.deb and .rpm are just compressed tar files**, files with specific directory layout understood by the associated _package installer_ ( dpkg, RPM). Howewer, they will NOT install the required dependencies, thats why using dpkg,RPM is a nightmare! Recognising this weakness, Debian developed apt-get on top of dpkg - their own packaging tool. Apt-get does automatically install dependencies. Similarly, RedHat developed Yum install on top of RPM.  Could RedHat have just used .deb format? Yes! but rpm format was already so mature, they didnt try to fix what aint broken. Sure you can convert deb/rpm/tgz into one another.. checkout `alien` package

an "installation" involves
- creating user accounts on the system
- creating/modifying configuration files that aren't actually contained in the .deb or .rpm file
- set ownership/permissions on the files after installation
- run commands as root on the system that's installing the package
dependencies, both formats can include names or packages and/or service names that they require to be present on a system, prior to installation.

### `sudo apt-get update` and related
"update" the <u>metadata</u> of all the packages from the subscribed repositories

### `sudo apt-get upgrade` and related
actually installs

##  _Everything is a File_
 A wide range of input/output resources such as documents, directories, hard-drives, modems, keyboards, printers and even some inter-process and network communications are simple streams of bytes exposed through the filesystem name space.
 
 Why? Interoperability! The same set of tools, utilities and APIs can be used on a wide range of resources. Also, things are transparent this way
#### Types of files
Check the first char of `ls -al`
1. Regular files (-)
2. Directory (d) : references the files
3. Symbolic Links . Softlinks (l)
4. Block device files (b) : sda, sdb : Harddrives
5. Character device files (c) : Mouse, Keyboards
6. Sockets
7. Named pipes


**UNIX Philosophy** Small things combined in many ways to create useful large things. --Common underlying format -- file

Commands are files (check /bin)

Processes are files (check /proc)





## [Filesystem Hierarchy Standard (FHS)](https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html)
![](assets/linux-01.png)

### /bin 
Binaries essential for the entire OS
.Binaries from the base system

### /sbin
System Binaries that should only be executed by root. eg: mount.

Only Sysadmins mess with this dir.

### /lib
Many of the Binaries in /bin and /sbin may use shared libraries, which is present in /lib

### /usr
Has its own /bin /sbin ..which has NON-ESSENTIAL binaries. non-essential to the operating system. Usually the "installed" apps go here.

##### /usr/local .../usr/local/bin
This is for housing binaries that you manually compiled and placed.. so it doesnt clash with binaries installed with package manager.

### /etc
"Editable Text Configuration" &mdash; Houses the config files

To customize the behavior of the software via config files.


### /boot
Holds the Linux Kernel, bootloader

### /dev 
Holds Device Files

### /opt
Holds "Optional"/Add-On Software

### /var
Variables files that will change as the OS in in use. Eg: logs, caches

### /proc
Pseudo dir. Is created in-memory by the Linux Kernel to keep track of running processes and Ports.
### /tmp
No explanation needed.

### /run
Sort of similar to /tmp  as its ephemeral too
### /home
No explanation needed


Go to the bottom to understand Disks--> Formatting(making a filesystem) --> mounting
#### How to find ANY file 
```bash
 find /path/to/dir -name "*partoffilename*"
```

Let's become a `find` poweruser.

Besides using the find command to locate files, you can also use it to execute other Linux commands (grep, mv, rm, etc.) on the files and directories that are found, which makes find even more powerful.
```
basic 'find file' commands
--------------------------
find / -name foo.txt -type f -print             # full command
find / -name foo.txt -type f                    # -print isn't necessary
find / -name foo.txt                            # don't have to specify "type==file"
find . -name foo.txt                            # search under the current dir
find . -name "foo.*"                            # wildcard
find . -name "*.txt"                            # wildcard
find /users/al -name Cookbook -type d           # search '/users/al' dir

search multiple dirs
--------------------
find /opt /usr /var -name foo.scala -type f     # search multiple dirs

case-insensitive searching
--------------------------
find . -iname foo                               # find foo, Foo, FOo, FOO, etc.
find . -iname foo -type d                       # same thing, but only dirs
find . -iname foo -type f                       # same thing, but only files

find files with different extensions
------------------------------------
find . -type f \( -name "*.c" -o -name "*.sh" \)                       # *.c and *.sh files
find . -type f \( -name "*cache" -o -name "*xml" -o -name "*html" \)   # three patterns

find files that don't match a pattern (-not)
--------------------------------------------
find . -type f -not -name "*.html"                                # find all files not ending in ".html"

find files by text in the file (find + grep)
--------------------------------------------
find . -type f -name "*.java" -exec grep -l StringBuffer {} \;    # find StringBuffer in all *.java files
find . -type f -name "*.java" -exec grep -il string {} \;         # ignore case with -i option
find . -type f -name "*.gz" -exec zgrep 'GET /foo' {} \;          # search for a string in gzip'd files

5 lines before, 10 lines after grep matches
-------------------------------------------
find . -type f -name "*.scala" -exec grep -B5 -A10 'null' {} \;
     (see https://alvinalexander.com/linux-unix/find-grep-print-lines-before-after-search-term)

find files and act on them (find + exec)
----------------------------------------
find /usr/local -name "*.html" -type f -exec chmod 644 {} \;      # change html files to mode 644
find htdocs cgi-bin -name "*.cgi" -type f -exec chmod 755 {} \;   # change cgi files to mode 755
find . -name "*.pl" -exec ls -ld {} \;                            # run ls command on files found

find and copy
-------------
find . -type f -name "*.mp3" -exec cp {} /tmp/MusicFiles \;       # cp *.mp3 files to /tmp/MusicFiles

copy one file to many dirs
--------------------------
find dir1 dir2 dir3 dir4 -type d -exec cp header.shtml {} \;      # copy the file header.shtml to those dirs

find and delete
---------------
find . -type f -name "Foo*" -exec rm {} \;                        # remove all "Foo*" files under current dir
find . -type d -name CVS -exec rm -r {} \;                        # remove all subdirectories named "CVS" under current dir

find files by modification time
-------------------------------
find . -mtime 1               # 24 hours
find . -mtime -7              # last 7 days
find . -mtime -7 -type f      # just files
find . -mtime -7 -type d      # just dirs

find files by modification time using a temp file
-------------------------------------------------
touch 09301330 poop           # 1) create a temp file with a specific timestamp
find . -mnewer poop           # 2) returns a list of new files
rm poop                       # 3) rm the temp file

find with time: this works on mac os x
--------------------------------------
find / -newerct '1 minute ago' -print

find and tar
------------
find . -type f -name "*.java" | xargs tar cvf myfile.tar
find . -type f -name "*.java" | xargs tar rvf myfile.tar
     (see https://alvinalexander.com/blog/post/linux-unix/using-find-xargs-tar-create-huge-archive-cygwin-linux-unix
     for more information)

find, tar, and xargs
--------------------
find . -name -type f '*.mp3' -mtime -180 -print0 | xargs -0 tar rvf music.tar
     (-print0 helps handle spaces in filenames)
     (see https://alvinalexander.com/mac-os-x/mac-backup-filename-directories-spaces-find-tar-xargs)

find and pax (instead of xargs and tar)
---------------------------------------
find . -type f -name "*html" | xargs tar cvf jw-htmlfiles.tar -
find . -type f -name "*html" | pax -w -f jw-htmlfiles.tar
     (see https://alvinalexander.com/blog/post/linux-unix/using-pax-instead-of-tar)
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

####  What is a ramdisk?

#### The /proc filesystem?
- Process information pseudo-file system
    - Theyre not "real" files ( `ls -lah` shows file size=0 for all)
- They contain runtime system information (e.g. system memory, devices mounted, hardware configuration, etc). For this reason it can be **regarded as a control and information centre for the kernel**
    - In fact, quite a lot of system utilities are simply calls to files in this directory. For example:
        - `lsmod`  = =  `cat /proc/modules`
        - `lspci`  = = `cat /proc/pci`. 
        - ps, htop too.. nearly every monitoring command you use

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


## Honourable mentions
#### commandline
##### (Sudo bangBang) Re-run the previous command as root
`sudo !!`

Know that BangBang `!!` re-runs previous command

##### learn to use less

##### <CTRL+x+e>  for editing laarge commnds 
you need to `export EDITOR=vim` for this


# 60 Days of Linux

## The Shell
**Shell**  is a "program"  which processes commands and returns an output. eg: sh, bash, zsh<br>



### Pipes
```bash 
prog1 | prog2

$ ps aux | less
```

### STDOUT, STDERR, STDIN &mdash; Input-output redirection
Every process has 3 channels<br>
STDOUT - 0 : the shell<br>
STDIN  - 1 : the keyboard<br>
STDERR - 2 : the shell<br>

The echo command writes to the STDOUT, which is the console by default
```shell
$ echo "This will go into the console"
```
" Output Redirection "
```bash
$ echo "This will go into the file" 1> somefile.txt
OR
$ echo "This will go into the file" > somefile.txt

# the output redirection ' > ' by default, means " redirect the STDOUT
# So, 1> and > mean the same thing.
$ ls -lah "This will spit out errors into file" 2> somefile.txt

```


## Filtering, Searching, Sorting data &mdash; the usual grind 

#### The thing about logical AND (&&) and logical OR (||)
```bash
$ prog1 && prog2
# prog2 will run iff prog1 ran successfully

$ prog1 || prog2
# prog2 will run iff prog2 failed
```

#### Learn these
1. `cut`
2. `sort`
3. `grep`
4. `wc`
5. `uniq`

## File Permissions and Access Control
-rwxrwxrwx = u g o (rwx)(rwx)(rwx)

chmod 777 file = u=7, g=7, o=7. => everyone can do everything
```
r-- = 4
rw- = 6
rwx = 7
```

[Why can you `chown` only as root?](https://unix.stackexchange.com/a/27374)

#### User creation `useradd` `passwd`
Generally when you create a user, automatically a group will be created with same name. Once you add the user, you can check the new entries made in `/etc/passwd` , `/etc/shadow` and `/etc/group`

`whoami` and `id` gives you everything about yourself, your groups etc.

#### Understanding ` cat /etc/passwd`
#### Understanding ` cat /etc/shadow`
#### Understanding ` cat /etc/group`

#### How to login as someone

#### How to login as root
2 ways
- `sudo -i`
- `su - root`

#### How to run a command as another user?
- `sudo -u bob thecommand`






## Process Management
Every Process runs as a user. You can check this with `top` or `htop`.
You own the files you create and processes you spawn

#### PID 1 &mdash; init

#### Signals
Used by processes to communicate. Also can be sent by the Kernel. Child process can return info to Parent using Signals

`kill -l` Will show you the list of signals that you can send to processes. Yes, `kill` is not just used for "killing" a process.

SIGTERM: Kernel to Process: _Hi can you please shutdown gracefully?_<br>
SIGKILL: Kernel to Process: _Im gonna end your existence right here right now!_


Every CPU has one or more cores which can run just N hardware threads. Say N=1. Every process contends for the CPU time and **Kernel is responsible for scheduling**.

##### "Nice"ness of a process

Checkout `nice` and `renice` commands 
How nice a process is to other processes... in terms of respect for resource usage, contention.

A Nice value of -20 = ULTRA CRITICAL! **not nice**<br>
This will freeze up your CPU, all the CPU time thats available will be given to this process. Time sharing gone.


A Nice value of 19 = LOW PRIORITY! **very nice**<br>

Checkout [this article](https://scoutapm.com/blog/restricting-process-cpu-usage-using-nice-cpulimit-and-cgroups) on how nice, renice, cpulimit and cgroups can help


#### Process States
![](https://webeduclick.com/wp-content/uploads/2019/02/process.png)

1. New: Just Created
2. Running
3. Waiting
4. Ready: The process is waiting to be assigned to a processor.
5. Terminate

### Using `ps` properly

## Boot
### BIOS &mdash; Basic Input Output System

## Disks

### Block Storage Device
First know the difference between [FileStorage, BLockStorage, ObjectStorage](https://www.redhat.com/en/topics/data-storage/file-block-object-storage)

Block Storage Devices, or simply "Block Devices" examples
- HDD
- SSD
- flashdrives 

Its called a **block device** because the kernel interfaces with the h/w by referencing FIXED size BLOCKS.
- Block storage - Oldest form of data storage
- stored & referenced in CHUNKS - fixed length BLOCKS
- for this reason of being stored in a primal fashion, block storages **need** an application to manage them (virtualize over them, make abstractions over them) and present them to the Operating system (which knows only shit like / /dev /boot /home /root)
- primal BLOCKS = massive scope to build upon
    - <u>Each block exists independently and can be formatted with its own data transfer protocol and operating system</u> — giving users complete configuration autonomy. 
    -  does not concern itself with investigative file-finding duties as the file storage systems, **block storage is a faster storage system**. 
    - (speed + configuration flexibility) => makes block storage ideal for raw server storage or rich media databases.


Once it is setup (after formatting+mounting), you can use it as an extension of your filesystem tree ( maybe to extend /home). Remember how you [added a "Disk"](https://cloud.google.com/compute/docs/disks/add-persistent-disk) in Google Cloud to an existing Compute Instance? Also AWS EBS works similarly when you want to add EBS volumes to Existing EC2 machines

![](assets/storage-01.png)


Big Picture...

_Before being able to do shit like `mv file1 file2`, you should mount the partition. Before mounting, you should have **formatted** the partition, before formatting, you should **partition**ed the device_ See [this](https://askubuntu.com/questions/841497/how-to-mount-a-partition)

/dev/sda is a device<br>
/dev/sda1 is the partition

One mounts a partion, not a device(for disks)

A filesystem is just one big tree. Then why bother about "N disks"? well...you may want to spread your tree across multiple disks...because your single disk is too small to hold the entire tree...(well its kinda not the only motivation to have multiple disks, but ok). Each of these disks have filesystem on it.(Really?? did you just assume that they were already formatted??)
 You create the single tree view of the filesystem by **mounting** the filesystems on different devices at a point in the tree called a mount point.

 now, when you cannot affort N disks, you **partition** a single disk to achieve the same behavior.

 Usually, the kernel starts this mount process by mounting the filesystem on some hard drive partition as /. You can mount other hard drive partitions as /boot, /tmp, or /home. You can mount the filesystem on a floppy drive as /mnt/floppy, and the filesystem on a CD-ROM as /media/cdrom1, for example. You can also mount files from other systems using a networked filesystem such as NFS. There are other types of file mounts, but this gives you an idea of the process. **While the mount process actually mounts the filesystem on some device, it is common to simply say that you “mount the device,” which is understood to mean “mount the filesystem on the device.”**

 ![](assets/storage-04.png)

 **Sector**?<br>
 Sector is the smallest physical storage unit on a disk (sector size=512bytes).

 ![](https://1.bp.blogspot.com/-A1aht6e1zFs/XFlvbIGEeMI/AAAAAAAAGbg/p8D50NwdQk0SmUzgZ0DkCkyTgZEEPLf0ACLcBGAs/s1600/1.png)

 On a hard disk, data is stored in thin, concentric bands. A drive head, while in one position can read or write a circular ring, or band called a **track**. There can be more than a thousand tracks on a 3.5-inch hard disk. Sections within each track are called sectors. 

 Tracks are numbered, starting at 0 (the outermost edge of the disk), and going up to the highest numbered track, typically 1023, (close to the center).

 Similarly, sectors are numbered, starting from 0 to 250069646 (in my example above)

 Why "**clusters**" of sectors? Your files tend to be much greater than 512 bytes right? data is easily accessed if they are stored next to each other. so "clusters" of contiguous sectors are allocated to store files. Now what happens if the file size outgrows the cluster size? then the next available cluster is taken up. But if continguous clusters are not available, then a free cluster somewhere else, maybe in some other track is taken up .

 ![](https://getdata.com/img/scr_RMF/disk-sectors.jpg)

 Files stored in this non-contiguous manner are said to be **fragmented**. This can significantly slow down the reads.. imagine how much the head has to move around just to read parts of the file in different clusters. Cluster size can be changed to optimize file storage. _A larger cluster size reduces the potential for fragmentation, but increases the likelihood that clusters will have unused space_.

 [Block vs sector](https://stackoverflow.com/questions/12345804/difference-between-blocks-and-sectors)

**`dd` : you can directly read sectors using this command**



### What are Disk Partitions?
break up a drive into multiple drives when youre too poor to buy many hard disks 	:hurtrealbad: .  A partition is a section of a storage drive that can be treated in much the same way as a drive itself.

A "volume" is usually a logical drive (partition)

**`fdisk` does the partitioning**


Why do it?
- Restriction of access
- Restriction of growth
- Performance
    - eg: dedicated partition for swap  massively boosts perf
    - eg: dedicated partition for /root
    - eg: dedicated partition for /home
    ![](https://managementmania.com/uploads/article_image/image/5580/hdd-hard-disk-drive-example.PNG)
    The outermost rings of the disk can be accessed the fastest. The Disk spins at a constant angular velocity, but the linear velocity of the outermost ring (relative to the read/write head) is the highest at the outside. This is why perhaps boot partitions tend to be on the outside. Even inodes prefer to stay outside

    Also data that is not modified often can be put in a separate partition, to avoid them getting involved in defragmentation process of regularly accessed partitions

- Efficiency
    - say you have large number of small files. Then youre better off with BLOCK SIZE of say 512bytes instead of the default 1KB. So you should partition your big disk such that one of them can be formatted with a smaller block size

- backup & recovery
    - recover a corrupt filesystem
- You can boot multiple OSes from a single USB stick!!

_partitioning is not compulsory. People do install OSes without ever partitioning. But dual boot systems need to be partitioned_

#### Partition tables &mdash; MBR v GPT

For the act of partitioning, you need to choose what "kind" of partition table you want (scheme). 

##### MBR - old scheme

This scheme allocates 512 bytes at the beginning of the device to hold the **Bootloader code** (which launches the OS)+ **partition table**(which holds metadata of each partition)

Remember that sector size of a disk =512bytes. So MBR allocates the FIRST sector of the disk for holding ^
![](assets/storage-02.webp). 


- MBR supports only till 2TB
- MBR supports only 4 **primary** partitions ( the final one can be made an "extended partition" which can be further split into 23 "logical"partitions, so totally 26..logical partitions nevertheless)
- MBR is usually paired with Legacy BIOS ( both are old af )

It's very easy to ruin the MBR sector of the drive, making it impossible to boot up again. Then you'll either need to create a recovery USB (liveUSB) and try to repair the MBR, or completely wipe the drive and reinstall the operating system.

##### GPT - new scheme
GUID Partition Table.

![](assets/storage-03.webp)

Protective MBR is just empty so that old systems that do not understand GPT dont cry

- GPT supports 128 partitions
- GPT supports 9.7 billion TBs. lol lol lol
- GPT is paired with UEFI 












##### `lsblk`
##### `fdisk`
##### `mkfs`
##### `mount`

## BIOS
[Greatest article](https://www.happyassassin.net/posts/2014/01/25/uefi-boot-how-does-that-actually-work-then/) ever written on booting process
> BIOS is the first thing you see on your monitor when you boot your PC

* Are all devices that are connected..work properly?
* Do we have all the REQUIRED devices, like RAM..
* Load the bootloader(which inturn loads the OS)

Every PC deals with 3 kinds of s/w
- OS
- Software  
- BIOS (firmware)

<u>BIOS first runs device health checks, and then passes control to the bootloader stored in the first sector (MBR) of the storage disk, the bootloader loads the OS</u>The BIOS is a small program that controls the computer from the time it powers on until the time the operating system takes over. The BIOS is firmware, and thus cannot store variable data. So all configs are stored in CMOS. ( configs include the params for starting up)
- date & time
- bootsequence
- fan speed etc...

<u>BIOS is stored on ROM </u>

<u>BIOS configs(variables) are stored in CMOS</u>. CMOS is just another small RAM chip. Then why not store it in RAM itself? RAM chips lose info stored in them when PC is turned off. CMOS Li battery keeps this small RAM always powered on..to keep the BIOS settings


#### Responsibilities (in sequence)
- P.O.S.T - Power On Self Test
- Load interrupt handlers
- Load Device Drivers
- Initialize other BIOS ( BIOS of peripheral devices)
- Determine which devices are bootable
- Initiate bootstrap sequence


##### POST - Power on Self test
BIOS checks if the video card works. Most video cards have a small BIOS of their own which initializes memory and graphics processor on the card. If they done, there would a video driver info on another ROM on the motherboard that the BIOS can load.

Then BIOS checks if its a cold boot or reboot. If coldboot,  BIOS verifies the RAM by doing a read/write test of each memory address.

BIOS checks PS/2 ports( & USB ports) to look for keyboards, mouse.

BIOS checks for the PCI bus, if found, checks all the PCI cards

If any error is found => series of beeps or some text on screen. Any error here signifies a hardware issue.



##### Bootstrap sequence
BIOS pulls BIOS config from CMOS

BIOS wil cycle through all listed storage disks and looks for a bootloader (first sector of a disk). If found, BIOS hands over the control to the bootloader. (GRUB is one such bootloader). The bootloader then loads the kernel into the memory. The kernel runs the init process.

Know that the BIOS doesnt have a clue what a bootloader is , or what an operating system is, or  what a partition is.... all it knows is HOW to load a bootloader. thats it








## UEFI
"Extensible Firmware Interface"
Go [here](http://jdebp.uk./FGA/efi-boot-process.html) for detailed boot process with UEFI

What is "extensible" exactly?

BIOS were desinged with very old h/w in mind. 

UEFI booting is completely different that BIOS

### Problems with BIOS
BIOS is so simple &mdash; firmware(BIOS) knows only about "disks" and one magic location per disk (first sector, the MBR) where the bootloader code **might** reside
- **You cannot boot from anything except disks**. What if you wanted to boot from a remote server?
- **no native multi-boot support**. It has to be rubbishly handled by the bootloader..because, well..all BIOS knows is to load the bootloader and die. Even if bootloaders handle it, theres no good convention on how to do this ( standardization RIP)
- **MBR's first sector 512 bytes is not enough for modern bootloaders**. So what people do is write the core part of the bootloader in MBR and write it beyound the 512 bytes!  This causes huge confusions regd where the first partition starts ( standardization RIP)

UEFI's solution to the last point is a special partition - EFI system partition(basically FAT). The UEFI firmware, unlike BIOS, is capable of reading some filesystem formats (FAT32). Note the shift from "512byte at the start"/magicspace of the disk ....to a dedicated disk partition to hold bootloader code!!! Check the **EFI System** partition (sda1) in my system
![](assets/storage-04.png)

But wait...mounting partitions is done by OS, OS is not yet loaded. Does UEFI know how to mount partitions? ..**yes**

Mind=Blown. UEFI mounts a "partition" just to load a bootloader, but who understands the partitions and partition tables? = GPT. er... see the disconnect?

BIOS expects MBR to store both bootloader and partition table in sector0(512 bytes). UEFI expects GPT to maintain partitions ,and expects bootloader code to be INSIDE a partition. wow

the Bootloader programs are just `.efi` files in the EFI System partition(special partition type). The EFI executable programs are standalone programs, ..dont need OS to run...machine firmware services are enough.


But how does the firmware know which order to use the bootloaders, and how does it allow us to override the default settings? &mdash; `efibootmanager`
```
[root@system directory]# efibootmgr -v
BootCurrent: 0002
Timeout: 3 seconds
BootOrder: 0003,0002,0000,0004
Boot0000* CD/DVD Drive  BIOS(3,0,00)
Boot0001* Hard Drive    HD(2,0,00)
Boot0002* Fedora        HD(1,800,61800,6d98f360-cb3e-4727-8fed-5ce0c040365d)File(\EFI\fedora\grubx64.efi)
Boot0003* opensuse      HD(1,800,61800,6d98f360-cb3e-4727-8fed-5ce0c040365d)File(\EFI\opensuse\grubx64.efi)
Boot0004* Hard Drive    BIOS(2,0,00)P0: ST1500DM003-9YN16G        .
[root@system directory]#
```
![](assets/storage-05.png)



stores config in an `.efi` file instead of CMOS. This file is stored on a special partition called EFI System Partition on the HDD itself. This partition also contains the bootloader.

BIOS could only support drivers stored in its ROM, but UEFI has discrete driver support
- User friendly GUI, mouse support to navigate

## GRUB
GRand Unified Bootloader

We talked a lot about "bootloader"s in MBR(sector0) and in EFI System Partitions present as EFI executables...We also know "bootloaders" load the OS into RAM

GRUB2 is an example of a bootloader. Others include
- GRUB 
- LILO (Linux Loader)
- systemd-boot
- BURG
- syslinux...etc

As a bootloader, it should be agnostic to the OS it loads. You should be able to instruct the bootloader to load a specific OS by just specifying the kernel's file name & the partition where it resides ( and not be forced to specify its physical position and shit). 

**"/boot/[vmlinuz-linux](http://www.linfo.org/vmlinuz.html)" is the location of the Linux kernel executable**, and we specify this path in grub's config. this file is actually compressed, and its "bootable". once loaded by grub into memory, it will remain in the memory till poweroff

**/boot/initrd-linux.img** is the location of [initial ram disk](https://landley.net/writing/rootfs-intro.html)

You might see "initramfs-linux.img" and "initrd" being used intechangeably

[**ramdisk vs ramfs**](https://landley.net/writing/rootfs-intro.html)

What is a ramdisk?

initramfs is a small filesystem
- which is embedded in the linux kernel image
- it helps the kernel to mount the root file system

look at the sequence of handing over the control<br>
UEFI -> bootloader -> kernel & initramfs -> PID1

But what does the PID1(init or systemd) need ? atleast a filesystem. thats why we have initramfs as a placeholder for the eventual root filesystem







![](assets/grub-01.png)




## The summarized Linux Boot Process (BIOS vs UEFI)
![](https://cdn.thegeekdiary.com/wp-content/uploads/2016/05/RHEL-CentOS-7-Boot-process-systemd.png)
![](https://www.incibe-cert.es/extfrontinteco/img/Image/BLOG/2015Julio/bootkits/bios_vs_uefi.png)

## Filesystems & formatting

Great [book](http://www.nobius.org/dbg/practical-file-system-design.pdf)

The term "[Filesystem](http://www.linfo.org/filesystem.html)" is loosely used to mean one of three things
 1. The linux directory structure (/)
 2. A specific type of data storage format, such as EXT3, EXT4, BTRFS, XFS, and so on.

 for now, EXT4 is de-facto root filesystem format in linux


 
  Linux supports almost [100 types of filesystems](https://opensource.com/article/18/4/ext4-filesystem), each of these filesystem types uses its own metadata structures to define how the data is stored(along with stuff like data_created, date_modified, size, location, name etc) and accessed.

  ![](https://opensource.com/sites/default/files/filesystem_diagram.png)

  Implementing a filesystem is a two-part process.
 1. **Linux virtual filesystem.** this provides a single set of commands for the kernel, and developers, <u>to access all types of filesystems</u>. The virtual filesystem software calls the specific device driver required to interface to the various types of filesystems. 
 2. **The filesystem-specific device drivers** are the second part of the implementation. The device driver interprets the standard set of filesystem commands(exposed by Virtual FS) to ones specific to the type of filesystem on the partition or logical volume.

`mkfs` command creates a filesystem on a device ( given a filesystem format ; default ext4), after which you will be able to create hierarchy of directories inside that device.

#### Some interesting filesystems
###### [tmpfs](http://wiki.deimos.fr/images/1/1e/Solaris_tmpfs.pdf)
Appears as a mounted filesystem, but its actually on RAM(Virtual Memory, to be specific)

> Not necessarily kept in RAM, but on Virtual Memory..which can be swapped out into disk as well

On reboot, everything in tmpfs will be lost.

/tmp is actually tmpfs, mostly used as a shared memory space. (tmpfs was initially called shmfs)
###### [ramfs](http://wiki.deimos.fr/images/1/1e/Solaris_tmpfs.pdf)

##### tmpfs vs traditional ramdisks


## Mounting
What exactly is mounting?

In early days people used to "physically mount" a tape or removal disk pack onto an appropriate drive ...thats how the word stuck. 

These days, ffter being "physically placed" on the drive, the **the filesystem has to be logically mounted by the OS** to make the contents accessible by the OS, other apps etc

**A mount point** is just a directory somewhere (deeply) under the root (a dir created as a part of root filesystem)

so filesystems can be mounted on mountpoints of the root filesystem

/ is a mountpoint<br>
/home is a mountpoint<br>
/boot is a mountpoint<br>
/mnt/point1 is a mountpoint<br>
/mnt/point2 is a mountpoint<br>

filesystems can ALSO be mounted on mountpoints of non-root filesystems as well!
for ex: i can mount something on /home/mnt/point1

![](assets/mounting-01.jpg)


**The Linux root filesystem is mounted on the root directory (/) very early in the boot sequence.** Other filesystems are mounted later, by the Linux startup program(systemd). Mounting of filesystems during the startup process is managed by the **filesystems table**, [/etc/fstab](https://wiki.archlinux.org/title/fstab) configuration file. 

Note that if you use an existing directory full of files as a mountpoint, its original contents will be hidden and will be visible only after you unmount whatever you mounted there.

- Use `lsblk` to list the block devices and their mount points
    - But it will miss virtual filesystem mounts like tmpfs
- Use `df -h` for complete mount info ( incl virtual)

## dd  | Data Duplicator - Block by Block
from one device to another device

## Inodes
What?
They are datastructures that hold **metadata** of all files. 

2 cases where you cannot create any more files
- Disk space exhaustion
- Inode count exhaustion

The number of inodes is fixed. you cannot exceed that. _So, you may not run out of disk space but you CAN run out of inodes, and may not be able to create any files!_ 

The **metadata** held by inodes include
- size
- physical location (addresses of blocks)
- file owner & group
- access permissions
- timestamps
- reference counts of how many hardlinks point to this inode

(note that name of the file and contents of the file is not "metadata")
![](https://pc-freak.net/images/what-is-inode-find-out-which-filesystem-or-directory-eating-up-all-your-system-inodes-linux_inode_diagram.gif)

Where?

Inodes are stored in the Filesystem itself.
In some filesystems like ext4, inodes are created at the time of filesystem creation... in xfs, inodes are created on the fly.


Why?

**When a file is created,** it is assigned a filename and a unique inode number. Its the directory's responbility to hold the filenames and corresponding inode numbers

Why couldnt inodes be stored in the directory itself (instead of mapping)? then it makes the directory bigger, makes it difficult to move a file from one dir to another..(instead of just updating the pointer, you need to move the entire metadata arount)

To read the data in a file, given a name...the OS must first query its directory about its inode number, then go to the inode, get the address blocks that contain the data, and then read it from there

Note: Directories are special files whose data blocks are tables of name-to-inode mappings

**`stat` command gives you inode info for a file.** This gives you clue regd how `ls -l` works.. it actually goes to the containing directory, get the name-to-inode mappings, `stat`s every name..and thats how it prints all the metadata you see in `ls -l`


### Hardlinks &mdash; New names for the name inode

Many-to-one mapping is possible when it comes to mapping multiple names to the same inode number, thus the same file. Infact, two different directories can contain same filename-to-inode mapping, thus the same file.
Thus, on Unix, a file can have many names, even across different directories. You may use any of the several names of a file to find the inode for the file. Unix calls these names "pointers" or "links" to the file.

The permissions you need to change the name of a file are contained in the inode corresponding to the directory that contains the name. The permissions you need to change the data in the file itself are contained in the inode corresponding to the file. These are two different inodes, and each inode may be owned by a different userid.

Users Pat and Leslie can each own directories containing a name-inode map (a name) for a file whose inode is owned by Chris. Chris can control access to the file data. Pat and Leslie can only manipulate the name-inode maps in their directories. They can change their names for the file in their directories; but, they can't affect the file data itself.

Decoupling of the file(and its name) and its metadata enables hardlinks.

_Every file on the Linux filesystem starts with a single hard link_

`ln` command makes **additional** hard links.

`rm` removes the link(just like removing files).

When the `link count` of a file goes to zero, no directory points to that inode, Linux is free to reclaim diskspace of the inode and its associated data blocks.

**`rm` DOESNT clear the data blocks. It just removes the links... its only when all links are gone that the data blocks are cleared**

Since linking is a directory operation (think about it, all youre doing is adding an entry to the name-inode mapping inside datablocks belonging to the directory), you need write access on the directory.

**only files can be hardlinked, not directories**, think of it, had you been able to hardlink a directory then a dir would be present in more than one dir..then `..` would be ambiguous. **Every dir must have a unique parent dir**. This is also done to prevent loops and cycles in filesystem.

#### `.` and `..` are hardlinks to dirs
Everytime you create a subdir, the link count of the parent dir goes up by 1. Why? because `..` is a hardlink.
Originally, when the parent dir is created (no subdirs at this point), it will have linkcount=2 (itself + `.`) . By the time it has 5 subdirs, it will have linkcount=2+5=7

### Softlinks &mdash; symlinks..symbolic links
Softlinks are Special files which point to existing file

Softlinks are links to the filename.<br/>
Hardlinks are links to the inode

Say you created a file f1, and hardlinks f2 and f3 to the same underlying inode. It doesnt matter if you delete f1, or rename f1 to g1...you will still be able to read f2 and f3


Say you created a file f1, and symlinks f2 and f3 to f1. you delete/rename f1...f2 and f3 are dead. - - - -**dangling softlink**

Symlinks have their own inodes, which reference datablocks having the contents in the lines of "please look up the file name _"/abc/def" because im just a symlink to that file"_..ofc not in stupid english, but using flags and stuff...but contents nevertheless




### Hardlinks v Softlinks
![](https://i.stack.imgur.com/ka2ab.jpg)
Hardlinks are faster.

Harlinks help you create backup

# Linux Memory Management
Like it or not, **youre actually not directly addressing the real physical memory addresses**. You're addressing a layer ABOVE it (virtual address space), so that it abstracts out stuff like paging, swap in swap out etc

This layer/interface is handled by the MMU(Memory Management Unit) that sits between the CPU and physical memory.

MMU has a TLB (Translation Lookaside buffer) which just holds the mapping between virtual addresses and actual physical addresses.
![](assets/memory-mgmt-01.png)

When CPU addresses a virtual address, the MMU consults the TLB. the associated physical addresses may be RAM/disk. If there is no associated physical address, MMU generates a **page fault exception** and interrupts the CPU

### Page Fault
its a CPU exception, generated when CPU attempts to use an invalid virtual address.
- No physical address mapping against the virtual address in TLB => virtual address is invalid
- The process has insufficient permissions for the address
- The virtual address is valid, but swapped out

![](https://hotsushi.github.io/assets/linux-virtual-memory/abstract.png)


Using a disk as an extension of RAM, when youre too poor to buy bigger RAM.



The part of the disk that's used as virtual memory is called "swap space". The **swap partition** serves as the swap space. But if youre not sure about the swap size you need, you dont have to make a partition for it, a normal **swap file** will suffice

A swap partition(linux swap type) is not a special partition.. it just doesnt have any filesystem at all

A swap file...is just a file. Just make sure its a [file without holes](https://en.wikipedia.org/wiki/Sparse_file) and that it has been made ready to be used as a swap space using `mkswap`

Why?..because a file with holes, aka sparse files, tend to be fragmented, and they keep efficiency in mind..i.e allocate disk blocks only when write is requested. This is BAD for a swap file which doesnt have time for "allocating disk blocks". It would be conveninient to the kernel if the disk blocks are already allocated (dedicated disk block space) for swapping in and out the RAM pages

```
# create a file without holes
dd if=/dev/zero of=/extra-swap bs=1024 

# create swap
mkswap /extra-swap 1024
```













## cron
#### list my crontab
`crontab -l`
## Monitoring

#### `top` &mdash; Monitor processes
- which process is taking up most CPU, memory.
- how much memory is being used/free.
- alternative is `htop` which is more fancy
    - Scroll through the process, and send signal using f9

#### `netstat` &mdash; Monitor network
- `sudo netstat -tupln`  : Open ports .
    - `sudo` for /proc access. else it wont be able to show process IDs

#### `who` and `w` &mdash; Monitor users
Show who is logged in and what they are doing.

## Admin level stuff

### `chroot` &mdash; fake root
Change the "apparent" root for the current running process and their children.

The programs cannot access files and commands outside that tree. 

This modified environment is called "chroot jail"

- Should be used for processes that dont run as root

Why all this? =>
You create a directory tree where you copy/link all the system files needed for a process to run. Then you `chroot` to change the root dir to this new dir tree. the processes run here will only look for binaries within this tree . They also cannot read/write outside this tree. They dont have a clue that world exists outside this jain. If you really want to use files/binaries from outside(and the libs used by those binaries), you can use bind mounts.

As a matter of fact, `arch-chroot` does exactly this. Its a wrapper on `chroot`. We use `arch-chroot` while installing archlinux. (its a part of `arch-install-scripts` package)...Before it runs `chroot` internally, it will mount API filesystems like /proc and all so that they're available in the chroot jail

[practical](https://www.unixmen.com/chroot-jail/)

[Fixing your system](https://superuser.com/questions/111152/whats-the-proper-way-to-prepare-chroot-to-recover-a-broken-linux-installation)

[Fixing your system - vid](https://www.youtube.com/watch?v=43dpS35Hzq8)




# Saved Movement Shortcuts

`ctrl + a ` : Beginning ,<br/>
`ctrl + e ` : End <br>
`alt + f ` : Forwards <br>
`alt + b`: Backwards <br>

`ctrl + u`: clear whatever youve typed<br>
`ctrl + l`: short for `clear` command


# Saved Commands
[Cheatsheets](https://devhints.io/)
```bash
# List all installed packages with their sizes
pacman -Qi | awk 'BEGIN{sort="sort -k2 -n"} /Name/ {name=$3} /Size/ {size=$4/1024;print name":",size,"Mb"|sort}'

# Common commands
----------------
pacman -Syu <pkg> 	....Install (and update package list)
pacman -S <pkg> 	....Install only
pacman -Rsc <pkg> 	....Uninstall
pacman -Ss <keywords> 	....Search
pacman -Syu 	....Upgrade everything

# Query
-----
pacman -Qii <pkg> 	...List information on package
pacman -Qe 	        ...List explictly-installed packages
pacman -Ql <pkg> 	...What files does this package have?
pacman -Qo <file> 	...Who owns this file?
pacman -Qs <query> 	...Search installed packages for keywords

# Orphans
-------
pacman -Qdt 	....List unneeded packages
pacman -Rs $(pacman -Qdtq) 	...Uninstall unneeded packages+deps

# pactree
-------
pactree <pkg> 	....What does pkg depend on?
pactree -r <pkg> 	....What depends on pkg?
```

```
To find out where disk space is being used:
1. Get to the root of your machine by running cd /
2. Run sudo du -h --max-depth=1.
3. Note which directories are using a lot of disk space.
4. cd into one of the big directories.
5. Run ls -l to see which files are using a lot of space. Delete any you don't need.
Repeat steps 2 to 5.
```

# Troubleshooting

### [Bad USB flash drive](https://dottheslash.wordpress.com/2011/11/29/deleting-all-partitions-on-a-usb-drive/)

Lists all the disks/partitions. ( /dev/sdX is the device, /dev/sdX1 is partition)
```sh
sudo fdisk -l
```
Unmount partitions if any.

Permanently delete all data with 
```sh
sudo dd if=/dev/zero of=/dev/sdb bs=1M
```

**2 choices at this point**
1. Create a bootable USB (note: NOT for Windows ISOs. Use `woeusb`)
    ```
    dd if=arch.iso of=/dev/sdb bs=4M
    ```
2. Get back a fully functional flash storage 
    - delete existing partitions and create one or more new partitions using `fdisk`
    - Create a filesystem ( just use FAT32 cas its universal )

# Questions
- "wht" is a TTY and pts/0 and all?
- [Why cant pipes and filters be used interchangeably?](https://askubuntu.com/a/172989)
- What is the difference between SHell and Terminal Emulator?
- what is 0.0.0.0 and how is it different from localhost?
- what is ncurses? 
- what actually happens when i ctrl+c or ctrl+z? ctrl+d?
- What does modprobe do? what are kernel modules? waht are kernel drivers? dmesg ? lspci -k ? 
- what are systemcalls?
- `ldd` command -- list the libraries required by a binary ( understand bin vs lib) ..understanding glibc ./see [this](https://www.unixmen.com/chroot-jail/)
- statically vs dynamically linked libraries [this](https://cs-fundamentals.com/tech-interview/c/difference-between-static-and-dynamic-linking)
- what is a journal? why does systemctl ask me to check journalctl for more logs/details? what is dmesg? is it related to journal?
- What is kernel space userspace  etc?
- kernel vs distros?
- did not understand tmpfs ramfs ramdisk concepts
 ( closely related to inital ramdisk & the chicken and egg problem during booting)