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
Some nice observations:
- Decorator Pattern changes the SKIN of the object, Strategy pattern changes the GUTS of the object.
- a Decorator HAS-A and IS-A decorated.
- a Proxy HAS-A and IS-A proxied.
- a Adapter HAS-A existing interface and IS-A expected interface.
- a Adapter wrap just ONE object, a Proxy wraps just ONE object, a Decorator wraps just ONE object, a Facade wraps multiple objects to hide complexity.
- A Facade HAS-A all the objects it wraps and abstracts.
- In Bridge Pattern, the Abstraction HAS-A Implementation.
- Bridge _sortof_ seems very similar to Strategy in that, both attempt to change the GUTS of the object at runtime. But intent of Bridge is to allow both Abstraction and Implementation to grow independently, who says It cannot apply to strategy?(Bridge seems to be a superset of Strategy pattern).
- Prototype pattern helps do a deep copy, Flyweight pattern helps to a shallow copy.
- Command and Memento seem to work well for undo-redo+snapshotting.
- Mediator feels like a superset of Observer Pattern.
**Creational Patterns** 
_object creation mechanisms_
- * [[design patterns#Singleton Pattern|Singleton]]  _Only ONE instance globally_ **(double locking)**
- * [[design patterns#Factory Pattern|Factory]]  _Hide complexity of Choosing a class to instantiate_
- * [[design patterns#Abstract Factory Patter|Abstract Factory]] _Factory of Factory_ , _Create FAMILY of objects_
- * [[design patterns#Builder Pattern|Builder]]   _Create obj step-by-step_... _Avoid ugly LONG constructor calls_
- [[design patterns#Prototype Pattern|Prototype]]  _Make cloning easier `.clone()`, when initialization is heavy/verbose_ _, when you don't know which concrete class the obj belongs to_
- [[design patterns#Object Pool|Object Pool]] _Borrow from the pool, use it, put it back into the pool.

**Structural Patterns**
_how to assemble objects into larger structures_
- * [[design patterns#Adapter Pattern|Adapter]] _Intermediate b/w 2 incompatible interfaces_
- * [[design patterns#Decorator Pattern|Decorator]] (Wrapper)_Add more functionality to existing object, by wrapping it_.. _object inside object inside object inside..._ _(preprocessing/postprocesssing)_
- * [[design patterns#Facade Pattern|Facade]] _Hide complexity(Too many classes/objects) from the client_
- [[design patterns#Proxy Pattern|Proxy]]  _Wrap the original (expensive)object, to control access to it. Preprocessing/Postprocessing_
- [[design patterns#Composite Pattern|Composite]] _Object inside Object...Tree structure (eg:FileSystem)_ .. _useful when core model of your app is a Tree_ _(Simple "Leaves",, and Complex "Containers")_
- [[design patterns#Bridge Pattern|Bridge]] _Decouple ABSTRACTION from IMPLEMENTATION, so both can grow independently(separate hierarchies). Avoid subclass blow up due to combinations_
- [[design patterns#Flyweight Pattern|Flyweight]] _Reduce memory usage. Cache heavy objects and share (re-use) them among Huuuuuuuge number of objects_.

**Behavioural Patterns**
_communication b/w objects_..._Splitting responsibilities b/w objects_.
- * [[design patterns#Strategy Pattern|Strategy]] _Extract out shared behavior as strategy_. _Turn set of behaviors into objects_
- * [[design patterns#Observer Pattern|Observer]] _Notify other objects(observers) about change in state in one object(observable)_
- [[design patterns#State Pattern|State]] _FSM_ every state is a object with methods.
- [[design patterns#Chain Of Responsibility Pattern|Chain of Responsibility]] _Allow a request to be handled by a **chain of handlers**, not knowing which handler will handle it._
- [[design patterns#Iterator Pattern|Iterator]] _Allow elements of the Collection to be accessed sequentially, without knowing the underlying representation of the Collection._
- [[design patterns#Command Pattern|Command]] _Turn requests into Command Objects. Decouple sender and receiver_
- [[design patterns#Mediator Pattern|Mediator]] _Restrict direct communication between objs. Make them communicate via the Mediator._
- [[design patterns#Memento Pattern|Memento]]  _Snapshot design pattern. Undo-Redo_
- [[design patterns#Interpreter Pattern|Interpreter]]
- [[design patterns#Template Pattern|Template]]  _Interface Dictates the high-level steps, but concrete classes can decide what to do in each step_
- [[design patterns#Visitor Pattern|Visitor]] _Decouple the operations from the object_... _Open Closed Principle_