## Goroutines
They are "lightweight threads" capable of running concurrently.
You can have 1000s of them running concurrently.
Cost of creating goroutine is incredibly small compared to creating a thread. //TODO: why?

## Channels
Goroutines communicate via **pipes** called Channels.

The goal is to have dead simple synchronization between goroutines(without needing locks, semaphores) and dead simple concurrency.

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