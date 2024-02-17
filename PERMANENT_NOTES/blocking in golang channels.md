#golang #channels #concurrency

# Blocking in Un-buffered Channels
Unbuffered channel can hold just ONE value.

**Both Send and Recieve** are BLOCKING!.
```go

func main(){
   ch := make(chan int)
   go func(){
      v := <-ch  // will be blocked here until value is available
      fmt.Println(v) 
   }()
   time.Sleep(10 * time.Duration.Second); 
   ch <-10; // insert value into the chan AFTER 10s
}
```

```go
ch <- 10
```
A send will be blocked until there's someone to receive.

```go
v:= <-ch
```
A receive will be blocked until there's someone to send.

### How to wait for a goroutine to finish?
Naive way
```go
func main(){
   done := make(chan bool)
   
   go func(done chan bool){
      time.Sleep(10 * time.Duration.Second);
      done <- true
   }(done) // i dont really have to pass chan here since its in scope already
   fmt.Println("I will be printed")
   <-done // block main thread until goroutine finishes
   fmt.Println("I will not be printed until 10s elapse")
}
```


# Blocking in Buffered Channels
Buffered channel has more "capacity" to hold N values

**Blocks Send/Receive only if channel is full/empty** 
```go
ch := make(chan int, 3)

ch <- 1
fmt.Println("Sent one value into the channel")
ch <- 2
fmt.Println("Sent one value into the channel")
ch <- 3
fmt.Println("Sent one value into the channel")
ch <- 4 // blocked here..
fmt.Println("I will never be printed. There's no one to dequeue from channel!")
```
If the channel is full, Send is blocked!
