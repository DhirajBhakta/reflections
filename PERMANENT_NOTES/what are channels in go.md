_For Communication/Synchronization in Goroutines_
- Safely pass data between concurrently running Goroutines
- "Safe" = pass data without race conditions 
- **goroutine-safe**
- store and **pass values between goroutines**
- provides **FIFO semantics**

> **WARN**: channels can cause goroutines to block and unblock!

The goal is to have _dead simple synchronization_ between goroutines(**without needing locks, semaphores**) and dead simple concurrency.

#### How to create a channel
`ch := make(chan Task, 3)` // creates a buffered channel of capacity 3

```go
func main() {
	// Create a channel
	ch := make(chan int)

	// Send a value to the channel
	go func() {
		ch <- 1
	}()

	// Receive a value from the channel
	v := <-ch

	// Print the value
	fmt.Println(v)
}
```
#### Helps avoid most problems in concurrent programming
- deadlocks
- race conditions
When a Goroutine sends or receives data through a channel, it might be blocked until another Goroutine performs the corresponding communication operation. This coordination ensures proper synchronization and data consistency.

#### Unbuffered Channels
_By default, channels are **Unbuffered**_
Upon sending to the channel, it immediately forwards the value to the receiver. If there's no receiver or all receivers are busy, then **sender is blocked**.
The **Receiver is blocked** if there is no sender or all senders are busy.

Sends and receives **block until the other side is ready**. This allows synchronization b/w goroutines without locks/semaphores.
[[blocking in golang channels]]

#### Buffered Channels
_Can hold N values. N=capacity of the buffer._
Further sends are blocking, once the channel is full. 
[[blocking in golang channels]]

>**Warning**
>An Unbuffered channel IS NOT a buffered channel with capacity=1. it does not do ANY buffering at all!

#### Pass around "empty structs" in channels
_`struct{}` is special. ZERO SIZE!_
[[empty structs are special in go]]



#### Select Statement
_To **wait for**  data from **multiple channels** simultaneously_
_(In the order that messages arrive)_
Enables **Non-blocking** communication by "Selecting" the FIRST CHANNEL that is **ready** to send or receive data.
- useful in Timeouts and Cancellations
```go
func main() {
	ch1 := make(chan int)
	ch2 := make(chan string)

	go func() {
		ch1 <- 1
	}()

	go func() {
		ch2 <- "hello"
	}()

	select {
	case v := <-ch1:
		fmt.Println("Received", v)
	case v := <-ch2:
		fmt.Println("Received", v)
	}
}
```

```go
// notice the INFINITE for loop
func logMessages(chEmails, chSms chan string){
   for {
      select{
	      case email, ok := <-chEmails
		      if !ok{
		          return
		      }
		      logEmail(email)
		  case sms, ok := <-chSms:
			  if !ok{
				  return
			  }
			  logSms(sms)
      }
   }
}
```

A `default` case stops the `select` from blocking!. It executes _immediately_ if no other channel has a value ready


## Axioms
#### A send to a `nil` channel blocks forever
```go
var ch chan string // ch is null
c <- "try to start up!!"
```

#### A receive on a `nil` channel blocks forever
```go
var ch chan string // ch is null
fmt.Println(<-ch) // blocks
```

#### A send to a full channel blocks
...
#### A receive on a empty channel blocks
...
#### A send to a **closed** channel PANICS
```go
var ch = make(chan int, 100)
close(ch)
ch <- 1 // panic: send on closed channel
```

#### A receive on a **closed** channel returns the ZERO VALUE immediately
```go
var ch = make(chan int, 100)
close(ch)
fmt.Println(<-ch) // 0
```


---
# Channels internals
_Channels are **Observer Pattern** on steroids!_
#### What exactly is a channel, under the hood?
_Channel = `hchan` struct containing a Queue and a Mutex and queue of goroutines that are "waiting" on the channel, both senderQueue and recieverQueue_
https://github.com/golang/go/blob/master/src/runtime/chan.go
- **circular queue** 
	- sendx and recvx
- sendq and recvq (Queue of sending goroutines and receiving goroutines)
- `hchan` struct is allocated on **heap**, and `make` returns a pointer to it.
- hence you don't need to pass pointers to channels, cuz by definition, they're references.. just like maps and slices.
![[golang-00.jpg]]

How does a **send** work? `ch <- 10`
1. acquire the lock
2. enqueue (`copy`)
3. release the lock


How does a **receive** work? `t:= <-ch`
1. acquire the lock
2. dequeue (`copy`)
3. release the lock 
   
> **note**: enqueue and dequeue is a memory copy operation. the task is copied into the channel. the task is copied out of the channel into the variable.

#### Unbuffered channel under the hood
G1 sends, G2 is worker.
G2 is taking really long to process the current task., while G1 keeps sending new tasks
```go
ch<- task2
ch<- task3
ch<- task4
ch<- task5 // G1 blocks at this line, since the channel is full.
// G1 execution is paused.
```
How is G1 execution paused? How does it get blocked? and how does it know to resume after a task has been removed by G2?
_How does BLOCKING/UNBLOCKING or pausing/resuming of goroutines work?_
=> the runtime scheduler handles that.
- goroutines are **user-space threads**. , created and managed by Go runtime, not the OS.
- lightweight compared to OS threads. Less expensive , less scheduling overhead.
- The Go runtime scheduler schedules them onto OS threads.
![[golang-01.jpg]]

How does blocking work?
=>When a goroutine has to be "blocked" or paused, the runtime disassociates that goroutine G1 from the OS thread 1, and pops another goroutine to run in its place.

How does unblocking work?
=> the channel maintains a list of pointers to the Goroutines that are waiting on the channel (see [[design patterns#Observer Pattern|Observer Design Pattern]]) and the element that the sender wanted to send, but was blocked. When a task is finally popped from the channel(circular queue), the sender goroutine at the front of the Queue is popped, its corresponding element is enqueued into the circular queue, and the Goroutine "G" is make **runnable**, by associating it back to an OS thread!
![[golang-02.jpg]] 
- implicitly enqueue-ing the task that the sender was blocked on sending , is a performance optimization. It helps avoid the lock/unlock before writing to the queue. Or else, the sender goroutine would have to lock/unlock the channel while writing the task
- Similarly, when a receiver goroutine is blocked on a empty channel, the moment a new task is enqueued by sender goroutine, the receiver waiting list of goroutines is consulted and the task is **directly written** to the memory location within the receiver goroutine's stack. This too is a performance optimisation. Lesser memory `copy` operations, and no need to lock/unlock the channel while reading from the channel (dequeue). Or else, the receiver goroutine would have to lock/unlock the channel while reading the task.
![[golang-03.jpg]]
Read up "gopark" and "goready" 



# Goroutine internals
_OS level M:N Threading_
_Very similar to event loops in Javascript's runtime and python...but includes **work stealing**_ [Work Stealing Scheduler](https://rakyll.org/scheduler/) 
_(Read more on "virtual threads architecture". Same concept as green threads / coroutines / microtasks ) [[process vs threads vs event loops vs goroutines]]_

N Goroutines are scheduled onto M OS Threads. So each of the M OS Threads has a queue of Goroutines waiting to be RUN on that OS thread. If one of the OS Thread is totally IDLE, it can actually _steal_ half of the goroutines in another OS Thread....all this to balance out and keep the CPU always busy.
![[golang-00.webp]]
