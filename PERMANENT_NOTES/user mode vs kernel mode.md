https://www.linfo.org/kernel_mode.html

The CPU spends time in kernel mode AND user mode.

kernel runs in _kernel mode_ . All other processes run in _user mode_ . When these processes need to interact with h/w like R/W to files, they issue a _system call_ which takes the user process into _kernel mode_ and then back. 
**This switching back and forth b/w _user mode_ and _kernel mode_ is expensive**, but helps increase security and prevent bugs.

![](linux-03.png)
What "security?". Code in kernel space are allowed to use the CPU in certain restricted levels(privileged mode), otherwise not allowed for any normal process in user space. The CPU hardware actually has these protection rings.

What "bugs" ?. User space processes benefit from kernel services like scheduling, context switching, **memory management**, etc.. and moving to kernel space basically means, giving up these kernel offerings. Also managing memory by hand is extremely difficult and error prone.


### Which is faster? 
Should a code running in kernel mode be faster always? debatable.

Code which needs to switch frequently between kernel mode and user mode would benefit significantly by just running in kernel mode. If not, the code runs equally fast in both modes. You also might be able to bypass context switching.
Notably, TUX webserver(static) broke all benchmarks by having its code entirely in kernel mode, and soon after, Microsoft IIS followed the same approach.

OTOH, you might see worse performance in some cases, consider network stack, with modern throughput of 100+ Mbps being the norm, the kernel mode process would be overwhelmed, hence blocking critical tasks like scheduling, memory management etc. So to improve performance, this has been pulled up to user mode to give the kernel the headroom to do critical tasks via **kernel bypass networking**. 
