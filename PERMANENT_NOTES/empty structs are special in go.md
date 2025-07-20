https://stackoverflow.com/questions/47544156/what-uses-a-type-with-empty-struct-has-in-go

- `struct{}` is of ZERO SIZE..and points to the same special memory location.
- you can implement SET with`map[string]struct{}`
-  this is not bound by the string sizes