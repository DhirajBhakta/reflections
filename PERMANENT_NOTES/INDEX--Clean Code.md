[[object oriented programming basics]]
- inheritance
- polymorphism
[[aggregation vs composition]]
[[inheritance vs composition]]
[[SOLID principles]]
[[UML]]
[[MVC]]

[[Quad Tree]]

### Design Patterns
[[design patterns]]
**Creational Patterns** 
_object creation mechanisms_
- [[design patterns#Factory Pattern|Factory]]  _Hide complexity of Choosing a class to instantiate_
- [[design patterns#Abstract Factory Patter|Abstract Factory]] _Factory of Factory_ , _Create FAMILY of objects_
- [[design patterns#Builder Pattern|Builder]]   _Create obj step-by-step_... _Avoid ugly LONG constructor calls_
- [[design patterns#Prototype Pattern|Prototype]]  _Make cloning easier `.clone()`, when initialization is heavy/verbose_
- [[design patterns#Singleton Pattern|Singleton]]  _Only ONE instance globally_
- [[design patterns#Object Pool|Object Pool]] _Borrow from the pool, use it, put it back into the pool.

**Structural Patterns**
_how to assemble objects into larger structures_
- [[design patterns#Decorator Pattern|Decorator]] (Wrapper)_Add more functionality to existing object, by wrapping it_.. _object inside object inside object inside..._
- [[design patterns#Proxy Pattern|Proxy]]  _Wrap the original object, to control access to it. Preprocessing/Postprocessing_
- [[design patterns#Composite Pattern|Composite]] _Object inside Object...Tree structure (eg:FileSystem)_ .. _useful when core model of your app is a Tree_ _(Simple "Leaves",, and Complex "Containers")_
- [[design patterns#Adapter Pattern|Adapter]] _Intermediate b/w 2 incompatible interfaces_
- [[design patterns#Bridge Pattern|Bridge]] _Decouple ABSTRACTION from IMPLEMENTATION, so both can grow independently. Avoid subclass blow up due to combinations_
- [[design patterns#Facade Pattern|Facade]] _Hide complexity(Too many classes/objects) from the client_
- [[design patterns#Flyweight Pattern|Flyweight]] _Reduce memory usage. Cache heavy objects and share (re-use) them among Huuuuuuuge number of objects_.

**Behavioural Patterns**
_communication b/w objects_..._Splitting responsibilities b/w objects_.
- [[design patterns#State Pattern|State]]
- [[design patterns#Strategy Pattern|Strategy]]
- [[design patterns#Observer Pattern|Observer]]
- [[design patterns#Chain Of Responsibility Pattern|Chain of Responsibility]] _Allow a request to be handled by a chain of handlers, not knowing which handler will handle it._
- [[design patterns#Iterator Pattern|Iterator]] _Allow elements of the Collection to be accessed sequentially, without knowing the underlying representation of the Collection._
- [[design patterns#Command Pattern|Command]] _Turn requests into Command Objects. Decouple sender and receiver_
- [[design patterns#Mediator Pattern|Mediator]]
- [[design patterns#Memento Pattern|Memento]]  _Snapshot design pattern. Undo-Redo_
- [[design patterns#Interpreter Pattern|Interpreter]]
- [[design patterns#Template Pattern|Template]]  _Interface Dictates the high-level steps, but concrete classes can decide what to do in each step_
- [[design patterns#Visitor Pattern|Visitor]] _Decouple the operations from the object_... _Open Closed Principle_