(WIP), shouldve gone into fleeting notes. 

Enables data transfer between I/O and memory **without CPU intervention**. 
You need a dedicated hardware to do this - DMA Controller.
https://youtu.be/xAl53-0lmBg?feature=shared

Prior to DMA, we had PIO (Programmed I/O)
![[linux-24.png]]

DMA Controller is a dedicated hardware to free up the CPU from doing this.


![[linux-23.png]]

DMA Controller acts like a traffic cop to orchestrate the data transfer from IO device to RAM.

- Packets arrive at the IO Device, and wants to send it to the kernel
	- the IO device issues a DMA request to the DMA Controller.
- DMA Controller needs access to the system Bus
	- Data transfer(IO device to RAM) can happen only via the system bus. The system bus is under the control of CPU. 
	- DMA Controller has to "request" the CPU to gain access to the system bus (Bus Request Hold).. and
	-  CPU needs to inform DMAC which address in RAM to write the data and size of data to be written . `datacount (bytes) + startingAddress` is sent to DMAC
	- the CPU grants access via Bus Grant (HLDA). 
	- the DMA controller sends DMA ACK to the IO Device
- DMAC allows the IO Device to write data directly to `startingAddress` in RAM via the system bus.


##### CPU (Mostly)Blocked during DMA Transfer!!
(Not really, check DMA Modes section)
Note that for the time period when CPU has granted the control of system bus to DMAC, the CPU has lost control over the system bus..and cannot use it.
During DMA Transfer, CPU can perform only those operations which do not require the system bus (mostly remains blocked)

But if the CPU is anyway blocked for the entirety of the DMA transfer, what was the point of the DMAC? why not do all this via the CPU itself instead of blocking it ?
- If the CPU did all this work, it will have the burden of context switching into the special program which does the IO to memory transfer. Frequent context switches are bad
- the DMAC allows the CPU to keep its current process in the current context. no context switch

But the instructions of programs are in memory, and CPU is blocked from accessing the system bus, hence blocked from accessing RAM, so cannot fetch the next instruction and hence...cant execute anything? 
- Modern CPU caches are significant size of L3 Cache , i3 has 12MB, 19 has 36 MB. Instructions would most probably be cached there. And even the associated data for the program

##### Size of datacount register of DMAC
the size of the datacount register of DMAC will dictate how much data you can transfer from IO device into memory in one go. For subsequent transfers, the DMAC has to ask the CPU for control of the system bus.

If the size of data count register of DMAC is 16bits, then a maximum of 2^16 = 65536 bytes or 65KB.
So if you wanted to transfer a 30 MB file from disk to memory, then DMAC will request system bus access from CPU (30 * 10^6 / 65 * 10^3) = around 500 times !


#### DMA Modes
- Burst Mode
	- entire data transferred by DMAC at once.
	- quickest DMA transfer
	- But CPU is blocked
- Cycle Stealing Mode
	- Most efficient mode for DMA transfer
	- only when a byte/data is ready at the IO device's end, the DMAC will "steal" a cycle from the CPU just to DMA transfer for that particular byte/data.
	- CPU is not blocked the entire time of data transfer
- Interleaving Mode
	- obvious
- Transparent Mode
	- Slowest DMA transfer
	- CPU not blocked at all
	- CPU will yield control of system bus to DMAC whenever it feels like (when it knows it doesn't need it for itself).

