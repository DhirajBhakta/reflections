_Concurrency  = Latency x Throughput_
![[db_06.png]]
When Throughput is kept constant(think nvme, max throughput is say 7 GB/s), and the server is bombarded with more and more requests by rising number of users logging in at the same time, the concurrency increases...hence latency increases, and each user has to wait for a much longer time.
### Concurrency
Concurrency is the number of requests the client(s) send to the DB at the same time, which translates to number of concurrent requests **queueing** at the DB for execution. 
Concurrency is NOT Requests/s .

**unit is a number.**

No system, distributed or otherwise, supports unlimited concurrency.

If concurrency increases when throughput is fixed, latency starts increasing.


### Latency
"Latency" could be any of the following...
- Time spent by the request waiting to be processed by the server.
- Time spent by the request being processed by the server.
- Round trip time, which includes the above two plus the network latency. 

**Unit is seconds** 
### Throughput
Throughput is 
- Number of requests a server can process per second : **rps** 
- Number of requests(read/write) a db can process per second : **qps**
- Number of IO requests a disk can process per second: **IOPS** 

**Unit is X/s**

If clients end up overwhelming the DB with concurrency that it cannot handle, throughput will suffer(usually a constant), and latency will rise.

You can increase throughput but increasing cluster size or power, horizontally or vertically scaling the DB. This will increase the concurrency, and(or), decrease the latency. 