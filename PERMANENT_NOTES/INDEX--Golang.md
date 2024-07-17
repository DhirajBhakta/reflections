TODO:
- websockets in go
- wasm in go

Why is golang so fast?
- goroutines are _lightweight_. Cheap to create, Cheap to context-switch.
- golang's GC ensures process pauses are optimally minimized.
	- GC runs _concurrently_.
- But avoiding CPU Thread context switching overhead (using above), and keeping CPU fairly busy all the time with goroutines.._golang is so fast_.
- Easy to build **high performance network applications**(Systems Programming)
	- Laarge number of concurrent connections
	- networking package from the stdlib
- No Unnecessary memory allocations, with unique data types like **maps** and **slices** 
	- each has "capacity"

Go Concurrency is mainly
- Goroutines
- Channels
- Mutexes
- Atomic Operations

### Goroutines
[[what are goroutines]]
[Performance without the event loop | Dave Cheney](https://dave.cheney.net/2015/08/08/performance-without-the-event-loop)
[[process vs threads vs event loops vs goroutines]]

### Channels
Goroutines communicate via **pipes** called Channels.
[[what are channels in go]]
[[what are channels in go#Select Statement|Select Statement]]
[[why should you close a channel]] TODO



#### Unbuffered Channels
By default, channels are **Unbuffered**
Upon sending to the channel, it immediately forwards the value to the receiver. If there's no receiver or all receivers are busy, then **sender is blocked**.
The **Receiver is blocked** if there is no sender or all senders are busy.

Sends and receives **block until the other side is ready**. This allows synchronization b/w goroutines without locks/semaphores.
[[blocking in golang channels]]


#### Buffered Channels
Can hold N values. N=capacity of the buffer. 
Further sends are blocking, once the channel is full. 
[[blocking in golang channels]]

>**Warning**
>An Unbuffered channel IS NOT a buffered channel with capacity=1. it does not do ANY buffering at all!


### Language Specifics
[[generics in go]]
[[use sync.Once to create singletons in go]]

### Context
[[context and cancellation in go]]
### Error Handling
[[custom errors in go]]
[[use panic judiciously in go]]
### Garbage Collection
[[memory management in go(stack and heap)#Tricolor Mark and Sweep Garbage Collection|Tricolor Mark and Sweep Garbage Collection]]
[[memory management in go(stack and heap)#GC Tuning|GC Tuning]]


### Go Compiler
_Compiled to **Native Machine Code**, not bytecode like in some languages(Java)_
[[go compiler]]

### Performance optimizations
[[memory management in go(stack and heap)]]
[[arrays are more performant than slices in go]]
[[use sync.Pool to reduce memory allocation in go]]
[[use sync.Map for concurrency safe caching in go]] (frequently accessed data)
[[pointers can impede performance in go]]
[[use worker pools to avoid spinning up goroutines again and again in go]]
[[memory leaks in go]]
[[memory escape in go]]
[[calling C code from inside go with CGO]]
### Profiling Performance
[[testing.B for benchmarking memory and time taken in go]]
[[profiling with pprof in go]]


### Server
[[graceful server shutdown in go]]


---
- why channels? why can i just pass around variables, arrays?
- how select works!!
- need for buffered, unbuffered channels? applications of unbuffered channels and buffered channels ?
- channel types
	- bidi channel
	- send only channel
	- recv only channel
- why should channels be blocking? whats significance?
	- sender is blocked
	- reciever is blocked 
	- wtf are all these clauses??
- WTF is "dont communicate by sharing memory, share memory by communicating" ??
- Why bother closing a channel?