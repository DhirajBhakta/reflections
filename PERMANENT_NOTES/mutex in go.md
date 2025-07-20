`sync.Mutex`
- call `mu.Lock()` and `defer mu.Unlock()`

```go
func protected(){
   mu.Lock()
   defer mu.Unlock()
   // do stuff . its now protected. only THIS goroutine can do stuff
   // any other calls to `mu.Lock()` will BLOCK!
}
```

- Maps are not thread safe in go, use mutexes to lock the map white writing.
- https://www.youtube.com/watch?v=BywIJqYodl4 (try avoiding sync.Map too :(((( )
