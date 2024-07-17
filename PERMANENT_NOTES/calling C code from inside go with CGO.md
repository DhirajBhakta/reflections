_CGO enables Go programs to call C code and vice versa_

eg:
```go
/*
#include<stdio.h>
*/
import "C"

func main() {
    C.puts(C.CString("Hello from C!"))
}
```

Why would you want to do this?
- performance
- Using an existing C library which does exactly what you want
- Platform specific functionality available only in C

Pitfalls:
- C might be fast, but CGO overhead might be more than the speedup benefits of C
- Go's GC does NOT manage C's memory. **Dealloc the memory yourself with defer**
- C doesn't understand Goroutines. If a Goroutine calls a C function and that function blocks, it can block the entire OS thread, affecting other Goroutines.