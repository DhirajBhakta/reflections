Before a HDD can be used, it needs to be partitioned (atleast one partition). 
**Formatting is done AFTER** the disk is partitioned. You format individual partitions, not the entire disk at once.

There are 2 types of partition tables
- MBR
- GPT

### MBR (Master Boot Record)
- 1983.
- de-facto standard.
MBR allows a max of 4 partitions. The last partition is called "extended partition", which can subdivided into 24 partitions. So effectively, max partitions on MBR is 26

MBR is limited to 2TB max. 


### GPT (GUID Partition Table)

GPT allows 128 partitions.

GPT can support Zettabytes of storage.Since it uses 32 bits to store logical block addresses. (UUID=32 bits)

If you want to boot from a GPT disk, you need
- BIOS which supports UEFI