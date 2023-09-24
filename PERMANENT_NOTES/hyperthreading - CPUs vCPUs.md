
### Calculating Total Logical Cores.
`=CPU(s)`
`=[Socket(s)] * [Core(s) per socket] * [Thread(s) per socket]`

On your Local system, you run `lscpu`, you get 
```
Architecture:            x86_64
  CPU op-mode(s):        32-bit, 64-bit
  Address sizes:         39 bits physical, 48 bits virtual
  Byte Order:            Little Endian
CPU(s):                  4
  On-line CPU(s) list:   0-3
Vendor ID:               GenuineIntel
  Model name:            Intel(R) Core(TM) i3-9100 CPU @ 3.60GHz
    CPU family:          6
    Model:               158
    Thread(s) per core:  1
    Core(s) per socket:  4
    Socket(s):           1
    Stepping:            11
    CPU(s) scaling MHz:  19%
    CPU max MHz:         4200.0000
    CPU min MHz:         800.0000
    BogoMIPS:            7202.00
...
...
```


On EC2 (c6a.large \[2vcpu] ), you get
```
Architecture:        x86_64
CPU op-mode(s):      32-bit, 64-bit
Byte Order:          Little Endian
CPU(s):              2
On-line CPU(s) list: 0,1
Thread(s) per core:  2
Core(s) per socket:  1
Socket(s):           1
NUMA node(s):        1
Vendor ID:           AuthenticAMD
CPU family:          25
Model:               1
Model name:          AMD EPYC 7R13 Processor
Stepping:            1
CPU MHz:             3471.960
BogoMIPS:            5299.98
Hypervisor vendor:   KVM
Virtualization type: full
L1d cache:           32K
L1i cache:           32K
L2 cache:            512K
L3 cache:            4096K
NUMA node0 CPU(s):   0,1
...
```
Of course, these values are obtained from the hypervisor, and are not coming directly from underlying resources.