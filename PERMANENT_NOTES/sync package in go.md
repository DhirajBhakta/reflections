
#### use `sync.Once` to create singletons in go
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

