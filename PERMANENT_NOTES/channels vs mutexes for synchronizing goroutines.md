

#### How would Java's `synchronized` block differ from regular lock + unlock ?


## Mutex
_**Mutexes are very very slow**. Mutexes Lock() and Unlock() make things slow... _
```go
type safeCounter struct{
	counts map[string]int
	mu *sync.Mutex
}

func (sc safeCounter) inc(key string){
	sc.mu.Lock()
	defer sc.mu.Unlock()
	sc.slowIncrement(key)
}

func (sc safeCounter) val(key string)int {
	sc.mu.Unlock()
	return sc.counts[key]
}
```
- `sync.Mutex`
- `sync.RWMutex`

#### `sync.RWMutex` allows multiple readers at the same time
_Good for Read Intensive Process..._
But if writer is writing, no other reader can read it...