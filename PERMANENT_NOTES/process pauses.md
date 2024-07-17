![[ddia-42.png]]
_The paused process, when comes back alive..believes that it still holds the LOCK and tries to access the shared resource(here,file)_

Processes get **preempted** (for upto seconds and even minutes)
- by other processes — OS Context Switching
- by Garbage collection 'stop the world' (java)
- VM moved from one host to another


#### Impact of Process Pauses
- **Leader, Split Brain Problem:** Imagine a leader got a lease of 2mins, and it paused for some random reason for 3 mins, and then came back alive. Its lease was expired, another node became the leader, and this node might come back alive and believe its still the leader.
- **Incorrectly declaring a node dead:** ..it was just temporarily slow, or paused. Unnecessary failover, service disruption, unnecessary load on other nodes to transfer the load... can lead to **cascading failures** magnifying the problem.
- **Unpredictable Request Latency:** Process pauses contribute significantly to tail latency (the worst-case response times). This means clients might sometimes see very slow responses, even if the average performance is acceptable.

#### Why do process pauses happen?
Mostly because of arbitrary context switches and preemption of running threads. The thread won't even notice that it was paused. Following are the **reasons for process pauses** —
- OS Context switches 
- Hypervisor VM switches , _"steal time"_
	- _the next running VM has heavy load and refuses to release CPU time._
- Synchronous I/O can block the running thread
	- sync file access
	- sync n/w calls
- OS Thrashing.
	- A simple memory access might cause Thrashing.
	- Constantly wasting time writing pages to disk and back, cuz your'e too poor to afford bigger RAM
	- rather kill the process to free up memory, than do thrashing.
- GC Pause - Stop the world. , _can last for several minutes!_
-  VM suspended and resumed. _used for live migration of running VM from one host to another_

#### Hard Deadlines - Where Process Pauses can be fatal
stuff like car safety sensors cannot wait for GC pause to fire your Air bag systems when you crash. They have _hard deadlines_! You need

Safety critical embedded devices, with hard deadlines
- _"guaranteed allocation of CPU time in specified intervals"_
- disabling dynamic memory allocation , to prevent GC and GC pause. disallow GC entirely perhaps?
- document the worst case execution time
Such real time systems with hard deadlines will have lower performance and lower throughput because they have to prioritise timely responses above all else

#### Limiting the Impact of GC
(_Used by latency sensitive financial trading systems_)
- treat GC pauses like brief planned outages of a node, other nodes should handle the requests when one node is collecting garbage. Warnings when a node requires a GC pause soon. 
- use GC only for short lived objects, fast to collect. 
- Restart processes periodically.

#### The need for Distributed Locks
The above can be easily handled on a **single node** system with thread safety : 
- mutexes, 
- semaphores, 
- atomic counters, 
- lock-free data structures, 
- blocking queues, ... 
But these wont work in distributed systems, cuz **no shared memory**... only messages sent over unreliable n/w. Processes WILL get paused and you cant do anything about it. Pause long enough, and other nodes may declare you dead.. and you may even come back alive and continue executing ... _which is BAD at times._ imagine a leader coming back to life.


