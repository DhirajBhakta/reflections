
All programs can be constructed from just three structures:

- sequence
- selection
- iteration

## Structured Programming

Edgar W Dijkstra

- Use of "goto" statements prevented decomposition into smaller and smaller modules.
- He converted goto into if/else conditionals and do/while iterations.
- Modules that use only if/else and do/while could be recursively subdivided into units.
  
## Object Oriented Programming

Dahl and Nygaard moved the function call stack frame into the heap and invented OO.

OO is the ability, through the use of polymorphism, to gain absolute control over every source code dependency in the system.

It allows the architect to create `plugin architecture` in which modules that contain high level policies are independant of modules that contain low level details.
The low level details are relegated to the plugin modules that can be deployed and developed independantly from the modules that contain high level policies.

- encapsulation
  - of data and function
- inheritance
- Polymorphism
  - Existed since long ago
  - unix requires that every IO device driver provide 5 functions : open, close, read, write, seek. with standard signatures
  - plugin architecture
- Dependency Inversion
  - Insert an interface to bring in DI
  - Independant developability

## Functional Programming

All race conditions, deadlocks, concurrent update problems are due to mutable variables.

all the problems that we face in concurrent applications—all the
problems we face in applications that require multiple threads, and multiple processors
—cannot happen if there are no mutable variables

Well-structured applications will be segregated into those components
that do not mutate variables and those that do. This kind of segregation is supported by
the use of appropriate disciplines to protect those mutated variables

If we have enough storage and enough processing power, we can make our applications entirely immutable, and therefore entirely functional...

- immutability
  - variables do not vary, you dont modify them. theyre immutable
- Event sourcing
  - we store transactions, but not the state. when state is required, we simply apply all the transactions from the beginning of time.
