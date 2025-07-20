TODO:
- `copy` keyword, `delete` keyword, `new` keyword, `make` keyword. stack and heap allocations; escape analysis
- time currentTime , random in go
- sliceTricks in go https://go.dev/wiki/SliceTricks
- websockets in go
- wasm in go

https://dave.cheney.net/ is a goldmine for Golang.

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


# Concurrency
Go Concurrency is mainly
- Goroutines
- Channels
- Mutexes
- Atomic Operations

[[why are threads so diabolical?]]

TODO: **simulate race conditions with worker pools `sync.Waitgroup` || also with go -race flag **

[[channels vs mutexes for synchronizing goroutines]]
- [[channels vs mutexes for synchronizing goroutines#`sync.RWMutex` allows multiple readers at the same time|sync.RWMutex to allow large number of concurrent readers]]
[[sync package in go]]
- [[sync package in go#use `sync.Once` to create singletons in go| use `sync.Once` to create Singletons in go]]
- 
[[use worker pools to avoid spinning up goroutines again and again in go]]
[[use sync.Pool to reduce memory allocation in go]]
[[use sync.Map for concurrency safe caching in go#Maps are not thread-safe|Maps are not thread-safe]] 
[[use sync.Map for concurrency safe caching in go]] (frequently accessed data)
### Goroutines
_Execute tasks independently, **potentially in parallel**_
[[what are goroutines]]
[Performance without the event loop | Dave Cheney](https://dave.cheney.net/2015/08/08/performance-without-the-event-loop)
[[process vs threads vs event loops vs goroutines]]

### Channels
_For **communication & synchronization** between goroutines._
Goroutines communicate via **pipes** called Channels.
[[what are channels in go]]
[[what are channels in go#Buffered Channels|Buffered Channels]]
[[what are channels in go#Unbuffered Channels|Unbuffered Channels]]
BONUS: [[what are channels in go#Channels internals|Channel Internals]]



[[what are channels in go#Select Statement|Select Statement]]
[[why should you close a channel]] TODO


###  Mutexes
_locks_
[[mutex in go]]


# Language Specifics
[[generics in go]]

#### Packages
[[go packages and modules]]

#### Data Types
[[go datatypes]]
[[go slices and maps and channels]]
[[go slices and maps and channels#Slices and Maps are NOT thread-safe|Slices and Maps are NOT thread-safe, use an embedded mutex always]]




### Context
[[context and cancellation in go]]
### Error Handling
[[custom errors in go]]
[[use panic judiciously in go]]

### Garbage Collection
_Go has automatic GC like in Java. But Java needs JVM to be loaded into memory, Go doesn't._ (Although GO includes a **runtime** in every single binary built using `go build`. This runtime does GC)
[[memory management in go(stack and heap)#Tricolor Mark and Sweep Garbage Collection|Tricolor Mark and Sweep Garbage Collection]]
[[memory management in go(stack and heap)#GC Tuning|GC Tuning]]


### Go Compiler
_Compiled to **Native Machine Code**, not bytecode like in some languages(Java)_
_Go includes a **Runtime** in every single binary built using `go build`_ (Makes it little more bloaty compared to Rust, C..but not as heavy as requiring goddamn JVM to be loaded into memory)
[[go compiler#Why does go compile so fast?|Why does go compile so fast?]]


### Performance optimizations
[[memory management in go(stack and heap)]]
[[arrays are more performant than slices in go]]
[[use sync.Pool to reduce memory allocation in go]]
[[pointers can impede performance in go]]
[[use worker pools to avoid spinning up goroutines again and again in go]]
[[memory leaks in go]]
[[memory escape in go]]
[[calling C code from inside go with CGO]]
[[empty structs are special in go]]
### Profiling Performance
[[testing.B for benchmarking memory and time taken in go]]
[[profiling with pprof in go]]


### Server
[[graceful server shutdown in go]]


# Go Proverbs
[[go proverbs]]

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
