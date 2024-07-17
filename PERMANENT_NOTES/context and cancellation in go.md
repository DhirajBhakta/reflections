_propagating **Deadlines**, **Cancellations**, **request-scoped values**_
Propagate "Cancellation event" from somewhere in the top of the Context Tree to ask goroutines(with the leaf level contexts) to stop doing heavy work and hence free up resources.

**_Listen to Context Cancellations to gracefully handle the cancellation_**
- Context cancellations do not kill goroutines automatically, 
- they only propagate signals to implement graceful cancellations. The logic to abort the goroutine still needs to be implemented by the developer.
- Context can be cancelled only once.
- **Only the creator of the context must call the cancel function**, it is NOT recommended to pass around the `cancel` callback
- Passing an already cancelled context may cause unwanted results.
- Same context should be passed to all the functions and goroutines from parent.

[Go: Context and cancellation :: Prakhar Srivastav](https://www.prakharsrivastav.com/posts/golang-context-and-cancellation/) 

Managing "lifetime" of resources tied to the context

```go
func doSomething(ctx context.Context) {
    // Check for cancellation
    select {
    case <-ctx.Done():
        return
    default:
        // Continue with work
    }
}
```


The Context interface
```go
type Context interface {
  Deadline()(deadline time.Time, ok bool)  // time when the ctx will cancel
  Done() <-chan struct{}                   // channel to track ctx cancellation
  Err() error                              // reason for ctx cancellation
  Value(key interface{}) interface{}       // to pass request-scoped values
}
```


### Context Tree
`Context`s are usually derived from another context, and thus form a Tree.
At the root is usually the `req.Context()`
```go
ctx := request.Context()
anotherCtx, _ := context.WithCancel(ctx)
```
`.WithCancel`, `.WithTimeout` and `.WithDeadline` return a second argument which is a callback for cancelling the context.

> `.WithTimeout` takes in a timeDelta. `.WithDeadline` takes the exact timestamp

####  Emitting a cancellation event
> **Note**
> **Only the creator of the context must call the cancel function**, it is NOT recommended to pass around the `cancel` callback
```go
func main(){  
	ctx := context.Background()	
	ctx, stop := context.WithCancel(ctx)
	//OR ctx, stop := context.WithTimeout(ctx, time.Second*3)
	//OR ctx, stop := context.WithDeadline(ctx, time.Now().Add(time.Second*5))

	//use the context to do some work in the background
	go doSomething(ctx) 

	// other operation that results in a error
	if err != nil {
		stop() //send the cancellation signal to all functions using ctx
	}
}
```

#### Listening to cancellation event
_Somewhere at the bottom of the Context Tree, you're doing heavy work in a goroutine. Catch the cancellation event and stop the heavy work to free up resources_

```go
func doSomething(ctx context.Context) error {
	for {
		// do something
		select {
		case <-ctx.Done(): 		// closes when the caller cancels the ctx
	  		return ctx.Err() 	// has a value on context cancellation
		}
	}
}
```
Examples:
The heavy job in the `longRunningOperation`should be modified in such a way that it possible to check `ctx.Err()`value after regular interval.
```go
func task(ctx context.Context) {
    i := 1
    for {
        select {
        case <-ctx.Done():
            fmt.Println("Gracefully exit")
            fmt.Println(ctx.Err())
            return
        default:
            fmt.Println(i)
            time.Sleep(time.Second * 1)
            i++
        }
    }
}
```

Another (Complete)Example:
```go
func main() {
	ctx, stop := context.WithCancel(context.Background())
	defer stop()
	
	go func() { // run the work in the background
		if err := work(ctx, "./example.txt"); err != nil {
			log.Println(err)
		}
	}()

	// perform some operation and that causes error
	time.Sleep(time.Millisecond * 150)
	if true { // err != nil
		stop()
	}
	time.Sleep(time.Second)
}

func work(ctx context.Context, filename string) error {
// costly work (reading a file and doing costly work)
	if ctx.Err() != nil {
	    // abort if context was already cancelled
		return ctx.Err()
	}

	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	rd := bufio.NewReader(file)
	for {
		line, err := rd.ReadString('\n')
		if err != nil {
			if err == io.EOF {
				break
			}
			return err
		}
		time.Sleep(time.Millisecond * 100)
		log.Print(line) // do something with the line
		if ctx.Err() != nil {
		    // abort if context is already cancelled
		    // check in every iteration
			return ctx.Err()
		}
	}
	return nil
}
```


#### Listening to a Timeout (cancellation) event
_To Prevent functions running too long, abort and free up the resource_
```go
func main() {
	// create a parent context
	ctx := context.Background()

	// create a context with timeout of 2 seconds
	timeout, stop := context.WithTimeout(ctx, time.Second*2)
	defer stop()

	if err := longRunningOperation(timeout); err != nil {
		log.Println(err)
	}
}

func longRunningOperation(ctx context.Context) error {
	if ctx.Err() != nil {
		return ctx.Err()
	}
	for i := 0; i < 1000; i++ {
		time.Sleep(time.Millisecond * 20)
		if ctx.Err() != nil {
			return ctx.Err()
		}
	}
	log.Println("done")
	return nil
}
```


#### Listenting to a Timeout (cancellation) event with Deadline
_`.WithTimeout` is exactly like `.WithDeadline`, just that the input is an exact timestamp in WithDeadline, and a timeDelta in WithTimeout_

```go
func main() {
    ctx := context.Background()
    cancelCtx, cancel := context.WithDeadline(ctx, time.Now().Add(time.Second*5))
    defer cancel()
    go task(cancelCtx)
    time.Sleep(time.Second * 6)
}

func task(ctx context.Context) {
    i := 1
    for {
        select {
        case <-ctx.Done():
            fmt.Println("Gracefully exit")
            fmt.Println(ctx.Err())
            return
        default:
            fmt.Println(i)
            time.Sleep(time.Second * 1)
            i++
        }
    }
}
```
