
### Slices and Maps and Channels are passed by reference
Anything created via `make` is by definition, a reference (a pointer) and its allocated on the **heap**.


### 2D Slice 
```go
a := make([][]uint8, dy)
for i := range a {
    a[i] = make([]uint8, dx)
}
```


### Structs act well as Keys in maps
_to avoid N dimensional maps_

Only `comparable`  values can be Keys in maps. A Struct is comparable only if it contains comparable types inside it.

What isn't comparable?


### Slices and Maps are NOT thread-safe
_...or goroutine-safe_
[[mutex in go]]
[[use sync.Map for concurrency safe caching in go]]

You should use a `mutex` while writing to or reading a map. 
Even for maps that are never written to? yes, you'd need a mutex there too.
Because re-hashing a map involves recomputing the hash values of all keys, and thus the "cached" hash values of the keys change..and you might get inconsistent results or even panic! 

> **Note**: Always use a `map` with an embedded `mutex` and the stay the hell away from the pretentious `sync.Map`

