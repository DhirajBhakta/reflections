Given that dynamically loading kernel modules into a running kernel has many advantages
- no need to recompile the kernel
- prevent bloating the kernel

There are some **upsides** to statically loaded kernel modules, i.e compiling them into the kernel.
- a driver is absolutely necessary during boot
- you want to disable dynamic loading of kernel modules feature, to prevent runtime modification of kernel code, for security/stability