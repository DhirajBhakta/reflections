_Memory Escape = When scope of a variable expands such that the **go runtime decides** to allocate the variable **on the heap** rather than on the stack_

You need to monitor the memory escapes and try and limit excessive Heap Allocations since Heap Allocations are always slower, and incur GC overhead
[[memory management in go(stack and heap)|Why stack allocation=faster, but limited in size....Heap allocation=much slower, but more flexible in size]]

Use the build flags to see compiler decisions on memory allocations
```go
go build -gcflags='-m' your_package.go
```
gives insights on which variables are allocated on the Heap and Why.




### When does memory escape happen

##### Returning Local Pointers
If you create a object inside a function and return its address,
then the object _escapes to the Heap_.
```go
func NewObject() *Object {
    obj := Object{}
    return &obj
}
```

##### Storing Pointers in Global Variables
Local variables assigned to Global Pointers, will _escape to the Heap_.
```go
type Object struct {
    Value int
}

// A global pointer variable
var global *Object

func assignToGlobal() {
    // Local variable
    obj := Object{Value: 42}

    //Assign the address of the local variable to the global pointer
    global = &obj
}

func main() {
    assignToGlobal()
    fmt.Println(global.Value)
}
```


##### Slices and Dynamic Data Structures ..._beyond capacity_ 
When you append to a Slice beyond its capacity, it _escapes to the Heap_.


##### Closure Captures
If a inner function(with closure) using parent function's variable is executed after the parent function's stack frame has ended, then such variable _escapes to the Heap_.
```go
func generateFunctions() []func() int {
	var funcs []func() int

	for i := 0; i < 3; i++ {
		funcs = append(funcs, func() int {
			return i
		})
	}
	return funcs
}

func main() {
	functions := generateFunctions()

	for _, fn := range functions {
		fmt.Println(fn())
	}
}
```

##### Interface Conversions
Sometimes, converting types or using `interface{}` empty interface can cause memory escape.

