```go
func Max[T comparable](slice []T) T {
	if len(slice) == 0 {
		panic("Slice is empty")
	}

	max := slice[0]
	for _, val := range slice {
		if val > max {
			max = val
		}
	}
	return max
}
```

Another example: Generic Stack
```go
type Stack[T any] []T

// Push adds an element to the top of the stack.
func (s *Stack[T]) Push(val T) {
	*s = append(*s, val)
}

//Pop removes and returns the top element from the stack.
func (s *Stack[T]) Pop() T {
	if len(*s) == 0 {
		panic("Stack is empty")
	}

	index := len(*s) - 1
	element := (*s)[index]
	*s = (*s)[:index]
	return element
}

// IsEmpty checks if the stack is empty.
func (s *Stack[T]) IsEmpty() bool {
	return len(*s) == 0
}

func main() {
	// Example with integers
	var intStack Stack[int]
	intStack.Push(10)
	intStack.Push(20)
	intStack.Push(30)

	for !intStack.IsEmpty() {
		fmt.Printf("Popped: %d\n", intStack.Pop())
	}

	// Example with strings
	var stringStack Stack[string]
	stringStack.Push("apple")
	stringStack.Push("orange")
	stringStack.Push("banana")

	for !stringStack.IsEmpty() {
		fmt.Printf("Popped: %s\n", stringStack.Pop())
	}
}
```


#### Generic can lead to increased binary size
_more the **specializations**, bigger the binary size_

Each type can lead to a new specialization => increases binary size

Type constraints can limit the number of specializations (narrowing down the types)
```go
type Number interface {
    ~int | ~float64
}

func Multiply[T Number](a, b T) T {
    return a * b
}
```