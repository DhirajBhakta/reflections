_For Communication/Synchronization in Goroutines_
- Safely pass data between concurrently running Goroutines
- "Safe" = pass data without race conditions 

The goal is to have _dead simple synchronization_ between goroutines(**without needing locks, semaphores**) and dead simple concurrency.

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
### Helps avoid most problems in concurrent programming
- deadlocks
- race conditions
When a Goroutine sends or receives data through a channel, it might be blocked until another Goroutine performs the corresponding communication operation. This coordination ensures proper synchronization and data consistency.


## Select Statement
_To **wait for**  data from **multiple channels** simultaneously_
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
