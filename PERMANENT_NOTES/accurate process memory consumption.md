`ps aux` or `top` are inaccurate when it comes to memory usage. They add the memory consumption of shared libraries too, even though they are loaded JUST ONCE(for any number of processes using them.)

### Use `smem`
`smem` gives a more accurate number
```
smem msedge
```

## Terms 
- **VSZ**: Virtual Memory Size:
	- Total Memory a process **might** access .
- **RSS**: Resident Set Size:
	- Total Memory actually allocated to process **during** execution.
	- Includes Shared library memory usage.
- **PSS**: Proportial Set Size:
	- Total Memory actually allocated to process **during** execution.
	- Includes **only a part** of shared library memory usage. Say shared library took 10M. There are 10 processes using it. Every process will include just "1M" as shared library utilization. 
	- Prefer this metric to **RSS**
- **USS**: Unique Set Size:
	- Total Memory actually allocated to process **during** execution.
	- Excludes shared library memory usage.
	- **ONLY this process** 
	- Actual cost of running a process.