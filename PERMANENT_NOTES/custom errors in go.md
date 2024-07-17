```go
type error interface {
    Error() string
}
```

Every Error (incl built-ins) must implement the `error` interface (above)


#### `fmt.Errorf` is an Error Object too
```go
func divide(x, y float64) (float64, error) {
    if y == 0 {
        return 0, fmt.Errorf("division by zero")
    }
    return x / y, nil
}
```


## `panic` and `recover`
Panics are unrecoverable errors, and you use the `recover` call to gracefully recover from it (the irony!)
- its just for graceful recovery/ graceful shutdown 
```go
func recoverFromPanic() {
    if r := recover(); r != nil {
        fmt.Println("Recovered from panic:", r)
    }
}

func someFunction() {
    defer recoverFromPanic()
    panic("Something went terribly wrong!")
}
```