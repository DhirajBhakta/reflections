https://neosmart.net/wiki/mbr-boot-process/

1. BIOS
	- POST.
	- detect bootable devices.
2. Bootloader (GRUB2)
3. Kernel
4. Init 

![](https://routingnull.files.wordpress.com/2020/08/linux-boot-process-1.jpg?w=700)

### BIOS (POST)
POST "Power On Self Tests" is done by BIOS to check if all the h/w is alright.
Then BIOS issues INT13H (BIOS interrupt) to locate the **boot sectors** on any attached bootable devices. The first found boot sectors with valid boot record is loaded into RAM... the code in boot sector takes control... 

> **Warning**
> BIOS is superseded by UEFI. And MBR is superseded by GPT. MBR works only with BIOS and GPT works only with UEFI.

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




