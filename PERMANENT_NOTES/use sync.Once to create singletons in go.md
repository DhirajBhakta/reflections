Creating singletons which is safe from getting created more than once by concurrent goroutines => use `sync.Once`

Naive way of instantiating after checking for `nil` is bad in golang where concurrent goroutines might be running in different CPU Threads, probably running in parallel.
(This problem does not exist in Python/JS since all "coroutines" are on the same CPU Thread, although being concurrent)

```go
package main

import "sync"

type Config struct {
    Value string
}

var cfg *Config
var once sync.Once

func GetConfig() *Config{
    once.Do(func() {
       cfg = &Config{}
    })
    return cfg 
}
```

Not really sure if `nil` check needs to be done here..
```go
package main

import (
    "fmt"
    "sync"
)

var once sync.Once

type single struct {
}

var singleInstance *single

func getInstance() *single {
    if singleInstance == nil {
        once.Do(
            func() {
                fmt.Println("Creating single instance now.")
                singleInstance = &single{}
            })
    } else {
        fmt.Println("Single instance already created.")
    }

    return singleInstance
}
```