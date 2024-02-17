https://neosmart.net/wiki/mbr-boot-process/

1. BIOS
	- POST.
	- detect bootable devices.
2. Bootloader (GRUB2)
3. Kernel
4. Init 

![](https://routingnull.files.wordpress.com/2020/08/linux-boot-process-1.jpg?w=700)

### BIOS (POST)
<<<<<
BIOS code is located on the ROM (EEPROM). Also referred to as "Firmware", present directly on the motherboard. BIOS settings are located on CMOS(volatile), which needs a dedicated battery (wristwatch battery) to keep the data when system is powered off.
<<<<<
POST "Power On Self Tests" is done by BIOS to check if all the h/w is alright.
Then BIOS issues INT13H (BIOS interrupt) to locate the **boot sectors** on any attached bootable devices. The first found boot sectors with valid boot record is loaded into RAM... the code in boot sector takes control... 

> **Warning**
> BIOS is superseded by UEFI. And MBR is superseded by GPT. 
> Though MBR can work with UEFI and BIOS can work with GPT, this is not recommended.
> Windows only supports (BIOS+MBR) & (UEFI+GPT) pairing, while Linux doesn't mandate this.

## Bootloader
is a program which "finds" the OS Kernel and loads it into memory.

The bootsector (first sector of any hard disk) has a very small size to store bootloader details, once the bootloader is loaded, it will help load the actual OS.

GRUB is a Bootloader, allows user to choose an OS during startup.

## Kernel
The bootloader has now loaded the Kernel. Then
1. Kernel decompresses itself in-place (vmlinuz is the compressed kernel. "z" indicates that its compressed)
2. Perform h/w checks and gain access to h/w
3. Run init process `/sbin/init` (load systemd)

## Init
Kernel initiates the init process, the parent of all linux processes. `/sbin/init` which is usually Systemd .
Systemd does the following to bring to a state where any productive work can be done on the OS.
1. probe h/w
2. mount filesystems (`/etc/fstab`)
3. start services
4. manage user login
5. (optional) run a Desktop Environment




# The Bootloaders 
Older computers (PDP11) were booted by **entering a memory address** by flipping switches, asking the computer to start executing instructions at that memory address. Even now, when a PC starts, CPU begins loading instructions from a **predefined standard address in memory** (0xFFFF0) which points to the beginning of BIOS, which then chooses a boot device.

BIOS code is located in the ROM (EEPROM), and BIOS has been superseded by UEFI.

MBR and GPT are schemes to define the partition tables on the disk.

GRUB and LILO and systemd-boot are all bootloaders.
## MBR (Master Boot Record)
Though primarily MBR represents how the partition table is laid out, it also has a tiny "code" section to store the "loader" to load an operating system.
Code(bootloader code) required to load OSes of these days is way too huge to fit into this tiny "code" section, hence the bootloader would be divided into stages, and the first stage is made so small so as to fit into the code section of MBR, stage1 loads stage1.5..which in-turn mounts filesystem containing stage2...

![[linux-18.png]]

- (0.5KB) The Stage1 bootloader lives in the MBR's "boot code" section. 
- (31.5KB) The Stage1.5 bootloader lives in the DOS compatibility region. This stage is capable of mounting filesystems.
- The Stage2 bootloader is just a regular file on disk (thanks to the fact that grub understands filesystem.)

![[linux-19.png]]
#### Inspect the contents of the MBR
Save the content of MBR to a file.
```sh
dd if=/dev/sda of=mbr.out bs=512 count=1

#use the file command to get file type
file mbr.out
```

## GPT (GUID Partition Tables)
Can store more information about the partitions and the disk.
GPT layout has a "Protective MBR" section at the beginning to prevent legacy systems from interpreting the disk as an MBR disk. 
GPT also keeps backup of the partition table at the end of the disk!

![[linux-20.png]]
However, UEFI requires an explicit separate partition for itself called **boot partition** . ESP = EFI System Partition. This will be the location where the UEFI firmware looks for bootloaders. In MBR, such a separate  partition to hold bootloader code was not required since it was held in the MBR itself (first 512 bytes).
In BIOS world, the MBR section HAS to contain the initial boot code. Therefore, if you use BIOS on GPT disks, you'd need to have a "protective MBR" section at the beginning which just hands over to the GPT ESP boot partition. This is called "Booting a BIOS based system from a GPT disk".
![[linux-21.png]]
![[linux-22.png]]
You can check the boot order with `efibootmgr -v`. 


##  GRUB 
Grand Unified Bootloader... was created as a bootloader for ANY operating system. 

Grub files are located in `/boot/grub` but you shouldn't edit them directly since they lie in the EFI partition. The correct way to edit it is by editing templates in `/etc/grub.d/*` and settings in `/etc/default/grub` and running `grub-mkconfig -o /boot/grub`
### LILO vs GRUB
LILO is Linux's original bootloader, succeeded by GRUB (Grand Unified Bootloader). 

With LILO, for every change in bootloader config, LILO had to be reinstalled at disk's MBR. But GRUB understands filesystem. So you can just update the grub file /etc/default/grub and this file would be picked at stage2 of grub.


# lll
- what is bios chip? does uefi also have bios chips?
- why does the MBR section just have 512 bytes!?
- what is the need for DOS compatibility region?
- what is cmos memory chip? 
- why is bios stored in ROM, and not on disk's MBR ? If its on ROM, then wtf is on MBR's "code section"?




