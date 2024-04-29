_cooperative scheduling is good JUST for IO intensive load. worse for a mix of CPU and IO intensive loads, and absolute worst for CPU intensive loads._

Gevent does indeed increase the amount of requests you can take on per second on a IO intensive load. 
**Gevent is JUST useful for a completely IO intensive load. Things which you'd willingly use Elixir for** 

However, it sucks for CPU intensive tasks for obvious reasons. Why would you even run all your CPU intensive requests on the same thread!?

It sucks for even loads with mix of CPU intensive and IO intensive loads too. Why?

Consider a single request which has 
1. CPU intensive part: 2seconds
2. network call: 3seconds
3. CPU intensive part: 2seconds
It should ideally take a total of 7 seconds. **But it will end up taking 8 seconds!,**

But when the request is context switched just after n/w call is made, another request's CPU intensive part of 2 seconds is scheduled. When that is finished, the n/w call is not yet done, so ANOTHER request's CPU intensive part of 2 seconds is scheduled... 

it looks like this..

1. t=0; R1 arrives, R2 arrives, R3 arrives
2. t=0; R1 part1 : 2seconds 
3. t=2; R1 part2 : n/w call started.. 
	1. t=2; R1 is now context switched(_because its n/w call started_)
4. t=2; R2 part1: 2 seconds
5. t=4; R1 part2: n/w call not yet done
	1. t=4; R2 is now context switched(_because its n/w call started_)
6. t=4; R3 part1: 2 seconds
7. t=6; R1 part2: n/w call is finished (_finished one second back tho, **but a CPU intensive block was being executed so it wasn't interrupted**_)
	1. t=6; R3 is now context switched(_because its n/w call started_)
8. t=6; R1 part3: 2seconds
9. t=8; R1 complete

**It took 8 seconds to finish R1, when it should've taken just 7 seconds!!**

