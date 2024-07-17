_Visualize CPU, memory profiles_

Built-in package `net/http/pprof`

Just import `import _ "net/http/pprof"` and you can see profile data at `http://localhost:6060/debug/pprof/heap`.

### Profiling and Visualization
```go
f, _ := os.Create("mem.pprof")
pprof.WriteHeapProfile(f)
f.Close()
```
Then `go tool pprof mem.pprof`

