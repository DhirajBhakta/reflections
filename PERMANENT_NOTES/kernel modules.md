> **Info**
> tldr; kernel modules = device drivers (..._mostly_)

Linux kernel is monolithic (more monolithic than Windows NT and MacOS). To add functionalities, you'd have to _recompile_ the kernel. 
![[linux-02.png]]

What "functionalities" would you want to add? Linux kernel is _mostly_ comprised of driver code (apart from code for IPC, memory management, scheduling). Lots and lots of drivers would make the kernel bloated. You can't possible dump drivers of every h/w on earth into the kernel.

There is a way to _extend_ the kernel **while it is running**, without needing to recompile the kernel,.. and that is via kernel modules (or just "modules"), using the `modprobe` command. 

### `lsmod` lists currently loaded modules

### `modinfo <module>` shows module info

### `modprobe <module>` will load a dynamically loadable kernel module
make sure its not already loaded using `lsmod`. 
The loadable modules are located in `/lib/modules/$(uname -r)/kernel/<SUBSYSTEM>/`

Verify it has been loaded via `lsmod | grep <module>`

### `modprobe -r <module>` will unload the kernel module

### Load a module at boot
Add to `etc/modules-load.d/<module>.conf`

Why?`modprobe` will load the module **only for the current session**, and it will not be loaded during next boot.


### Prevent a module from being loaded at boot
Add to `/etc/modprobe.d/blacklist.conf`

### Device drivers are NOT processes or libraries
They are not something you just `sudo apt-get install driver` or `pacman -S driver`. They're the **part of the kernel**. 
> **Warning**
> There ARE some drivers running entirely in user space, and some in both user and kernel space.


### Kernel modules run in kernel space
Kernel modules run in the **kernel space** , which allows them to have direct access to hardware and memory. This bypasses everything related to the OS (scheduling, context switching that a traditional user-space process goes through). Running in kernel space also grants full access to h/w.

This means you have NO access to functions like `printf` in the C program, cuz stuff like `<iostream>` are not available in kernel space. All you have is `<linux/module.h>` and this instead provides you `printk` ...

> **Info**
> Most device drivers are kernel modules.
> However, not all kernel modules are drivers. Some custom schedulers are also shipped as kernel modules.
