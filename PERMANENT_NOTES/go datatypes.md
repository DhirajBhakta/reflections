```go
bool

string

byte  //alias for uint8

rune  //alias for int32; represents a Unicode code point

int  int8   int16   int32   int64
uint uint8  uint16  uint32  uint64

float32 float64

complex64 complex128
```

`int uint float64` are your daily drivers, unless you need to heavily optimize for performance.

### `byte`
_..is just an alias to `uint8`_

### `rune`
_... is just an alias to `int32`_

### Getting the type of the variable
To print the type of the variable(for debugging purpose)
```go
count := 3
fmt.Printf("datatype of count is %T", count)
```

Programmatically, you'd need the `reflect` package
```go
count := 3
countType = reflect.TypeOf(count)
```


### Type Casting


### Constants
_cannot use the `:=` syntax here_
```go
const ENV = "PROD"
```
> `const` variables are assigned values at **compile time**, not run time.
> But a `const`  variable can depend on another `const` variable.



