_Return **error** whenever possible, use **panic** judiciously_

Although `panic` and `recover` provide the semantics of `try-catch`, **panic** must be used only in cases where the errors cannot be gracefully handled, and aborting the entire process is the ONLY option left to ensure consistency.

> **warn**: DON'T `recover` always
> Blindly recovering from all panics might mask critical issues. It's better to let the program crash (and thus alert you to the problem) than to continue in an consistent way.

> **warn**: `recover` only recovers the "current" goroutine
> If you have multiple goroutines, and ONE panics, only that goroutine would be `recovered`
```go
func main() {
    defer handlePanic()
    panic("Something went wrong!")
    fmt.Println("This won't be printed.")
}

func handlePanic() {
    if r := recover(); r != nil {
        fmt.Println("Recovered from panic:", r)
    }
}
```

For all other "standard" error handling, use the `error` paradigm

#### One goroutine `panic` cannot crash the entire server
> The panic will be propagated up the call stack within that goroutine, and if it reaches the top of the goroutine's stack, the runtime will terminate that goroutine.

But with  `net/http` package to handle HTTP requests, the behavior is slightly different. When a goroutine handling an HTTP request panics, the `net/http` server will catch the panic and write an error response to the client with a 500 Internal Server Error status code. This is done to prevent the panic from crashing the entire server.