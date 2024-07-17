#### Singleton Pattern
_Create only **ONE** object of a class_
_Noone should be able to call the constructor!_
_Eager Initialization_
- Static object of the class = object of the same class. The Singleton
- Return that object everytime someone asks for a object
> expose a `.getInstance()` method 

** Private Static Field to hold the singleton
** private `constructor`
- the static `getInstance` method will still be able to access the `constructor`
** public static `getInstance` method . .. (Lazy initialization)

>  [[#Abstract Factory Pattern|Abstract Factories]], [[#Builder Pattern|Builders]] and [[#Prototype Pattern|Prototypes]] can all be implemented as [Singletons](https://refactoring.guru/design-patterns/singleton).

What if two threads simultaneously call `.getInstance()`? 
Use `synchronized`
```java
synchronized public static DBConnection getInstance(){
   if(conn == null){
      conn = new DBConnection();
   }
   return conn;
}
```

You need a "Double Locking" solution
WHY? TODO
```java
public static DBConnection getInstance(){
	if(conn == null){
		 synchronized(DBConnection.class){
			  if(conn == null){
				  conn = new DBConnection(10);
			  }
		 }
	}
}
```
Issues with the above Double Locking Solution
- Instruction Reordering
- L1 cache (use volatile keyword)
- 


TODO: What exactly is Java's synchronized keyword?
TODO: What exactly is Volatile keyword?





#### Factory Pattern
_Choosing a subclass based on a condition_
A "Factory Method" will choose a Subclass as per business logic.
Avoid using the `new` keyword to directly instantiate objects

> The "factory method" is actually a method specified in the INTERFACE that all "creator" classes must implement

> **Note** : factory method doesn’t have to **create** new instances all the time. It can also return existing objects from a _cache, an object pool, or another source._


![](https://refactoring.guru/images/patterns/diagrams/factory-method/structure-2x.png)
The following is a simple factory, but NOT the factory method design pattern
```java
class UserFactory {
    public static function create($type) {
        switch ($type) {
            case 'user': return new User();
            case 'customer': return new Customer();
            case 'admin': return new Admin();
            default:
                throw new Exception('Wrong user type passed.');
        }
    }
}
```

The following IS the real factory pattern, **inheritance well used on the CREATOR class**
```java
abstract class Department {
    public abstract function createEmployee($id);

    public function fire($id) {
        $employee = $this->createEmployee($id);
        $employee->paySalary();
        $employee->dismiss();
    }
}

class ITDepartment extends Department {
    public function createEmployee($id) {
        return new Programmer($id);
    }
}

class AccountingDepartment extends Department {
    public function createEmployee($id) {
        return new Accountant($id);
    }
}
```

#### Abstract Factory Pattern
_Factory of Factories: creating a "family" of objects_

> The **Abstract Factory** interface declares a set of methods for creating each of the abstract products. 
> For every "product" type in the family, you have a creator method in the abstract factory. Each method is sort of a factory. Hence "factory of factory"

> **Note**: Upon careful observation, Abstract Factory == Factory Method
> Just that the concrete classes have multiple methods, one each for every product type in the family. But Factory method, just one method for ONE product type.
> _"family of products"_
> Also, as your number of Factory Method classes keep growing, it might make sense to collect all of them into a full blown Abstract Factory pattern. All (creator)methods in one place.
> 
![](https://refactoring.guru/images/patterns/diagrams/abstract-factory/solution2-2x.png)
The Client doesn't care what type of factory it is using, nor does it care what kind of "Chair" it gets. It just cares that it gets _some_ Chair. Therefore,
- All Chairs (regardless of family) must implement a Chair Interface
- All Factories must implement a AbstractFactory interface(or abc)

![[lld-00.png]]
#### Object Pool Pattern
_Pool of Objects. Use it, put it back into the pool_
- reduces the overhead of creating and destroying costly resources
- avoid added latency for the same ^
- prevents memory leakage / resource exhaustion
**Resource Pool Manager**
- freeList, inUseList
- getResource()
- releaseResource()
>**Note**: The ResourcePoolManager HAS to be Singleton
>And Singleton comes with Thread Safety problems

`ResourcePoolManager.getInstance()`  // cuz Singleton
#### Strategy Pattern

Make a "Strategy" Interface, accept that interface as a dep in the Constructor. **Constructor Injection**

Strategy Pattern is useful when N subclasses **share the same code** NOT present in the parent class (base). You make a Strategy object(interface) and share the functionality among the classes that need it.
![[lld-00.jpg]]
Strategy Pattern opens up an alternative to mindless use of inheritance. 
Consider this. You have a class and you DO NOT subclass it. All polymorphic behavior is injected to the objects of the SAME class by injecting different strategies. The objects of the same class now behave in different way without the need of subclassing the parent.

Cons:
- You still have a hierarchy to maintain. Even if you don't have the hierarchy of Actual Classes, you still have the hierarchy of Strategies.

Usecases:
- You have N classes implementing an interface, and most classes implement the same behavior for a particular method, or maybe extend on top of it. this **shared behavior** is now duplicated code. This **shared behavior** could be extracted out as a "strategy". Note that although all child classes obtain the reference to the parent's implementation of the said method, sharing common behavior across sibling classes isn't possible via inheritance, which is why you need Strategy Pattern.



#### Observer Pattern
_Observable and Observer_
An Observable maintains a LIST of observers. And whenever the Observable state changes, it loops through this list and calls `notify()` method of the Observers.
> Observable is also called "Subject"
![[lld-01.png]]

Observervable Interface
- _attach_ : add observer
- _detach_: remove observer
- _notifyAll_: loop through all observers and call their `notify` method

Observer Interface
- _notify_: do something upon being notified of a change in Observer.

If some state changes on the observer,..
```python
def setState(self, newvalue):
    self.value = newvalue
    # notifyAll 
    for observer in self.observers:
        observer.notify(newvalue)
```



#### Decorator Pattern 
(WRAPPER)
_Adding additional features via "wrappers"_
_**Has-A  + Is-A**_
_Composes the underlying object._ (Can do preprocessing/postprocessing)
_Also extends the same parent class as the underlying object_ 
_Extend the object's behavior without adding a new Subclass (avoid class explosion)_

> **Wrapper** implements the same Interface as the **Wrapped** object

> Add extra behavior to objects at runtime.
> Several behaviors. One Decorator per behavior

You have a Base Pizza
- Base Pizza (Abstract Class, Base Class)
- Base Pizza + Capsicum (Created via Decoration)
- Base Pizza + Capsicum + CheeseBurst (Created via Decoration)
_Did not use Inheritance here_
```java
Pizza pizza = new CheeseBurst(new Capsicum(new BasePizza))
// CheeseBurst , Capsicum and BasePizza classes all extend the same interface Pizza
```
![[lld-02.png]]


With Inheritance![[lld-03.png]]

but with Decorator pattern (Without Inheritance)
![[lld-04.png]]

Why use Decorator Pattern?
- avoid Class Explosion (if you use just inheritance to do this)

> Decorator changes the Skin of the object, [[#Strategy Pattern]] changes the Guts

#### Chain Of Responsibility Pattern
_Pass the request along a chain of Handlers._
![](https://www.softwareideas.net/i/DirectImage/445/Chain-of-Responsibility)
Usecases:
- ATM/Vending Machine
- Logger

#### Proxy Pattern
_Wrapper on a **client** which talks to an expensive resource._
_Proxy **IS-A** client, AND Proxy **HAS-A** client_
![[lld-04.webp]]
- A proxy **controls access to the original object**, 
- allowing you to perform something either before or after the request gets through to the original object.

eg:
- You have `EmployeeDAO` interface...implemented by `EmployeeDAOImpl`
- `EmployeeDAOProxy` implements the same `EmployeeDAO` interface
- `EmployeeDAOProxy` contains an instance of `EmployeeDAOImpl` within it.

You use a _Proxy Server_ for:
- Getting past Access Restriction.
- Caching on the Proxy Server, to reduce load on actual server.
- Preprocessing , Postprocessing,...Logging of the requests/history of logs.
- Lazy initialization of the inner obj
> usually Proxy creates and handles the lifecycle of the inner object.
> But you can pass it via constructor too.



#### Null Object Pattern
_To Avoid NullPointerException NPE_
To avoid checking `if( obj != NULL)` again and again

> In [[#Factory Pattern]] if  no SubClass/Class of Interface satisfies the given condition, instead of returning `null`, return a Null Object....avoid NPE


#### State Pattern
_FSM_

youll have a "State" Interface, and then concrete classes implementing the State Interface
- StateX
- StateY
- StateZ
- ...
The State Interface will require all the classes to implement methods corresponding to all possible operations. 

> All "Actions"/Operations that cause a state change become the methods on the State Interface

Each Concrete class 
- implements only the methods(operations) relevant to THAT state, and 
- implement default behavior/throw exception on methods(operations) that are NOT relevant to it.

#### Composite Pattern
_Useful when **core model of your app** == Tree_
_Simple **Leaves** and complex **Containers**_
_... **Container** contains **Leaves** and other **Containers** = Array of **Nodes** = Array of Children_
_Treat Leaves and Containers Uniformly. Both are "Nodes"_
_Leaves do most of the work.. everything else is just delegation until it reaches leaves_
_Nested | Recursive_ = Tree
_Object inside Object .. .. .. OR Tree Like structures_
_.... .... ......Hierarchies.... ..... ...._
_.... .... ...... Recursion...... ..... ...._

Define a common central "Node" Interface which all types of nodes will implement.
Node `Interface`
- contains methods that all types of nodes will have (superset)

![](https://refactoring.guru/images/patterns/diagrams/composite/structure-en-2x.png)
Usecases:
- Design FileSystem 
	- _Directory can contain Directories can contain Files..._
- Design Calculator

```go
package main

type Component interface {
    search(string)
}
```

```go

package main

import "fmt"

type Folder struct {
    components []Component
    name       string
}

func (f *Folder) search(keyword string) {
    fmt.Printf("Serching recursively for keyword %s in folder %s\n", keyword, f.name)
    for _, composite := range f.components {
        composite.search(keyword)
    }
}

func (f *Folder) add(c Component) {
    f.components = append(f.components, c)
}
```

```go
package main

import "fmt"

type File struct {
    name string
}

func (f *File) search(keyword string) {
    fmt.Printf("Searching for keyword %s in file %s\n", keyword, f.name)
}

func (f *File) getName() string {
    return f.name
}
```

> You usually use [[#Iterator Pattern]] to traverse the Tree 

> [[#Visitor Pattern]] to execute operation on the entire Tree



#### Adapter Pattern
_Existing Interface --> Expected Interface_
_Adapter **IS-A** Expected Interface_ (Inheritance)
_Adapter **HAS-A** Existing Interface_ (Composition)

> Translator b/w current code and a Legacy class. 
> (You badly want to use the functionality of the Legacy class)

Usecases:
- Socket Plug
- XML <-> JSON
- Several existing classes might be missing out on a common functionality .
	- You could use Adapter and wrap that subclass and add the functionality
	- [[#Decorator Pattern]] also works here

The "Adapter" Interface exposes the methods expected by the Client.  
(Client talks to the Adapter only)
A Concrete Class Implements this Adapter Interface --> AdapterImpl
This Concrete Class will **have an instance** of the Existing Interface
(Adapter talks to the Existing Interface)

Adapter usually wraps ONE object, whereas [[#Facade Pattern|Facade]] may wrap MULTIPLE objects to hide the complexity


#### Builder Pattern
_To tackle very large constructor argument list_
_Think 10-20 fields..._
_Laborious Step-by-Step initialization of MANY fields, nested objects.._
_Avoid ugly long constructor calls_
_..... Step by Step Object Creation......._
```c
obj = House(foundations)
      .addRoof(roof)
      .addDoors(doors)
      .addWindows(windows)
      .build()
```
Has a **Build()** method at the end.

> Each of those methods must return `self` or `this` to enable **chaining** 

> Use Builder pattern to build [[#Composite Pattern|Composite]] Trees, object trees, or other complex objects

A builder **doesn’t expose the unfinished product** while running construction steps. This prevents the client code from fetching an incomplete result.


#### Facade Pattern
_Hiding complexity from the Client_
_Subsystem provides a million features when used together, but the Client needs just a few_
_....avoid the Client having to interact with **Multiple Classes**......_
_Facade Object **HAS-A** all the underlying classes that it abstracts away_


Facade vs [[#Proxy Pattern]]
- Proxy Pattern abstracts away just ONE object
- Facade Pattern abstracts away multiple objects

Facade vs [[#Adapter Pattern]]
- TODO


#### Bridge Pattern
_Decouples "Implementation" from the "Abstraction", so that the two can vary independently_
_Avoid subclass blowup due to sheer number of combinations possible_
_Switch Inheritance with Composition_
_Helps split ONE LARGE heirarchy(inheritance), into N smaller hierarchies_
_Use it when you want to extend a class in several orthogonal(independant) **dimensions**_ 
_Helps create **platform independant** s/w_

Abstraction/Implementation:
- Software/Hardware
- Domain/Infrastructure
- Frontend/Backend
- Desktop App/Platform(OS)
You want the feature development on either side of the equation to happen without blocking each other.

**_Subclass blowup?_**
![](https://refactoring.guru/images/patterns/diagrams/bridge/problem-en-2x.png)


**_Splitting the hierarchy into smaller hierarchies..._**
![](https://refactoring.guru/images/patterns/diagrams/bridge/solution-en-2x.png)

> **Note**: "Abstraction" here doesn't imply an Interface or a Abstract Base Class. 
> "Abstraction" simply means ..say a Layer on top for client to easily consume. Is it a Facade? maybe.. sounds like it.
> The "Abstraction" delegates most of the work to the "Implementation" object **it contains** (_HAS-A_)

The Abstraction
- exposes N features.
- can later grow to N' features
- **contains** the implementation object, _HAS-A_
- The Abstraction utilizes the methods of the implementation object
The Implementation
- exposes M methods
- can later grow to M' methods
Both grow independently 

> **Note**: Usually the Client is interested only in the methods exposed by the "Abstraction"
> - But Client is also responsible to link the "Abstraction" to a concrete "Implementation" object
![](https://refactoring.guru/images/patterns/content/bridge/bridge-2-en-2x.png)

![](https://refactoring.guru/images/patterns/diagrams/bridge/structure-en-2x.png)

```py
implementation = ConcreteImplementationA()
abstraction = Abstraction(implementation)
client_code(abstraction) # do something with the abstraction

    print("\n")

implementation = ConcreteImplementationB()
abstraction = ExtendedAbstraction(implementation)
client_code(abstraction) # do something with the abstraction
```
Bridge vs [[#Strategy Pattern]]
- Both aid in switching the "implementation" at runtime.
- Intent of Strategy Pattern is to change the behaviour of the object **at runtime**.
- Intent of Bridge Pattern is to allow the two Interfaces to grow independently.

#### Prototype Pattern
_`.clone()` complex structures instead of reconstructing them from scratch._
_When you want to create **clones** of the object and the creation of the object is expensive._
_When setting the attrs one by one for cloning..gets too damn verbose._
_...Some attrs may even be `private`, so you can't really set values one by one too._
_You have to know the object's class to clone it. Would be nice if you needn't know that._
_...Even worse, you may know just the `Interface` of the obj, not even the concrete class._

>**This pattern is NOT based on inheritance**

> eg: Gorm's `Connection` struct exposed a `.clone()` method to create a clone without knowing how to instantiate an object.

>Cloning should not be the responsibility of the Client, but ..the Class itself should do it, expose a `.clone()` method

Expose a `.clone()` method on the object/Interface

**The object that supports the cloning is called the Prototype**.


#### Flyweight Pattern
_Share data among objects = Efficient Cloning_
_Huuuuuuuge number of objects_
**IMMUTABLE** intrinsic state.

>**Intrinsic Data**: Data that doesn't change across objects. Worth creating just ONCE and sharing..
>Must be IMMUTABLE. No setters

> The object that stores the intrinsic state is called **Flyweight**

When to use:
- When Creation is expensive
- When memory is limited, object is heavy... cannot afford to make **1lac deep clones** of the object

Usecases:
- Design Games
- Design Text Editor / Word Processor
	- for each character, say "t", you create a single object and re-use that object wherever "t" occurs
> You could use a Flyweight **factory** or a Flyweight **object pool**

#### Command Pattern
_Undo-Redo_

Invoker --> Command --> Receiver 

Create a "Command" Interface
- Exposes a `execute()` method and `undo()` method
- Create Concrete Commands
Maintain a **Stack** for Command History.


#### Iterator Pattern
_Iterate through elements of a Collection sequentially without exposing underlying representation of the Collection_

"Iterator" Interface, expose the methods
- `hasNext()`
- `next()`
Concrete Impl of the Iterator Interfact = Concrete Iterator
- tracks the current position
- contains a ref to the underlying collection instance

The Collection Class **_Creates_** an instance of the concrete Iterator.


#### Mediator Pattern
_Loose coupling by **communicating** via the Mediator Object_
Objects don't know about each other = Loose Coupling
Objects talk to each other via the Mediator Object

> Mediator Pattern seems similar to [[#Proxy Pattern]] and [[#Observer Pattern]]

Usecase:
- Online Auction. 
All bidders "register" themselves to the Mediator obj. And talk only to the Mediator obj. Mediator obj broadcasts the messages (or sends to appropriate bidders), notifies the relevant bidders.
Mediator maintains a LIST of bidders.

#### Memento Pattern
_Snapshotting. Undo-Redo_
Originator: = Current State
- methods:
	- createMemento
	- restoreMemento
Memento:
History : = Stack of Mementos (snapshots)



#### Template Pattern
_Dictate high-level steps, but concrete classes can decide what to do in each of those steps._



#### Interpreter Pattern

usecases: 
- evaluating Expressions
BinaryExpression, TerminalExpression
a*b = new  BinaryExpression( new TerminalExpression('a'), new TerminalExpression('b'), '\*')

#### Visitor Pattern
TODO: confusing!
_Decouple the Operations from the object_
Allows you to ADD new operations without changing the structure of the object.

> For Each operation, you create a Visitor

- `Element` Class
- `Visitor` Class
- `Element` "accepts" a `Visitor`

**Double Dispatch**
- ? TODO

---
#### Decorator vs Composite vs Adapter vs Proxy vs ChainOfResponsibility

All of these use **Composition** , hence the confusion.

Decorator vs Composite:
- Decorator wraps ONE object 
- Composite contains a LIST of children

Decorator vs Adapter:
- Decorator implement the SAME interface as the wrapped object (decorated obj).
- Adapter's interface is totally different from the inner object 

Decorator vs Proxy:
- Decorator implements the SAME interface as the wrapped object and **enhances it**
- Proxy just implements the SAME interface as the inner object
- Composition of the Decorator is **controlled by the client**
- The Proxy hides how it uses the inner object, **abstracted away from the client**.

Decorator vs ChainOfResponsibility:
- Decorator must pass the request throughout the chain
- CoR can choose to cut the request midway in the chain if its already handled by a handler.
