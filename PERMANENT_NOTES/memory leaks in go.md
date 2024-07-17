_When you allocate memory and forget to deallocate_
> Consistent Memory growth even during idle periods => memory leak

Capture Heap dumps with `/net/http/pprof` package and `go tool pprof` [[profiling with pprof in go]]
### Long Lived References
_As long as there is a reference pointing to it, it will NOT be garbage collected (even if it is not being used)_
_Also, caching **without bounds** will cause memory leak_
```go
var cache = map[string][]byte{}

func cacheData(key string, data []byte) {
	cache[key] = data
}

func main() {
	for i := 0; i < 1000000; i++ {
		data := make([]byte, 1024) // 1 KB
		cacheData(fmt.Sprintf("%d", i), data)
	}
	//We've accumulated a lot of data in cache and never removed it
	select {} // Prevent exit
}
```

Solution:
- either use a LRU cache to **bound** the cache.
- or periodically evict the cache entries.
```go
var cache = map[string]struct {
	data []byte
	timestamp time.Time
}()

const ttl = 10 * time.Second

func cacheData(key string, data []byte) {
	cache[key] = struct {
		data      []byte
	timestamp time.Time
	}{
		data:      data,
		timestamp: time.Now(),
	}
}

func evictOldEntries() {
	for key, item := range cache {
		if time.Since(item.timestamp) > ttl {
			delete(cache, key)
		}
	}
}

func main() {
	// ... your application logic ...

	// Periodically clean up old cache entries
	ticker := time.NewTicker(time.Second)
	for range ticker.C {
		evictOldEntries()
	}
}
```


### Bloked Goroutines keep piling up
```go
func leakyFunc(c chan int) {
	val := <-c
	fmt.Println(val)
}

func main() {
	for {
		ch := make(chan int)
		go leakyFunc(ch)
	}
}
```

Monitor with `runtime.NumGoroutine()`..

Use the `Context` to Cancel 
(Cancel, Timeout, Deadlines)
```go
func worker(ctx context.Context, ch chan int) {
	for {
		select {
		case val := <-ch:
			fmt.Println(val)
		case <-ctx.Done():
			return
		}
	}
}

func main() {
	ch := make(chan int)
ctx, cancel := context.WithCancel(context.Background())
	go worker(ctx, ch)

	// ... some code ...

	cancel() // Signal the worker goroutine to stop
}
```


#### `CGO` or `unsafe` code
```go
// #include <stdlib.h>
import "C"

func main() {
	mem := C.malloc(1000) // Allocate memory using C's malloc
	// ... do something ...
	// Forgot to free, hence memory is leaked
	// Correct way: C.free(mem)
}
```
Solution:
```go
// #include <stdlib.h>
import "C"

func main() {
	mem := C.malloc(1000)
	defer C.free(mem) // Ensure that the memory is freed at the end
	// ... use the allocated memory ...
}
```