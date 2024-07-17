_Stack=Fast, Heap=Slow_

#### Stack
Memory alloc/dealloc is **fast** on stack,
automatically managed by the language (go runtime)
- NO GC overhead!

#### Heap
Dynamically allocated memory:
- pointers
- slices
- maps
- structs allocated on the heap due to [[memory escape in go|Memory Escape]]
Heap Allocations are Slow
Managing Heap memory is crucial and **deciding factor** for performance.
[[pointers can impede performance in go]]

---
_Stack=Fast, Heap=Slow_

Pointers although save you from copying large structs again and again while doing "pass by value" during function calls,...
Pointers require memory allocation **on the heap**, whereas non pointers(pass by value) allocate memory on the stack.
In go, stack allocations are much faster and managed by the go runtime , whereas, **heap allocations are costly** and involve the GC for deallocation.

[Why is memory allocation much slower on Heap than on Stack | Stackoverflow.com](https://stackoverflow.com/q/2264969/5319180)
> Creation of data on stack area : Just move the stack pointer 
> Creation of data on heap area : Search for area on the pool of memory that satisfies given requirement(You can use first fit,Best fit or worst Fit).After finding the area store the information(Book keeping)
> _the heap is a far more complicated data structure than the stack. For many architectures, allocating memory on the stack is just a matter of changing the stack pointer, i.e. it's one instruction. Allocating memory on the heap involves looking for a big enough block, splitting it, and managing the "book-keeping" that allows things like `free()` in a different order._
> Memory allocated on the stack is guaranteed to be deallocated when the scope (typically the function) exits, and it's not possible to deallocate just some of it.
>  Deletion on stack : Deletion on stack is easy.Just move stack pointer down Deletion on heap area : Find where the element is stored on heap(using book keeping) and merge two adjacent free blocks if necessary;

## Tricolor Mark and Sweep Garbage Collection
 Objects in memory are colored:
- **White** (unmarked/unvisited)
- **Grey** (marked but referenced objects not yet scanned)
- **Black** (marked and scanned)
 
Initially all objects are marked White.
GC traverses the object graph, coloring the visited nodes as Black or Gray.
Post Traversal, white objects (unvisited) are garbage collected.

 > Go's GC works **concurrently** with the program, which means it tries to minimize process pauses (stop the world). 
 
### GC Tuning
_Adjust the frequency of GC_
`GOGC` environment variable
: Lower value = more frequent GC. Lowers Heap Usage, Increases CPU usage