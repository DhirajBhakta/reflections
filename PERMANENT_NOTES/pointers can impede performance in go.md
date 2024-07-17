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
