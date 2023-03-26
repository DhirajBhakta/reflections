SOLID principles tell us how to arrange our functions and data structures into classes, and how those classes should be interconnected.

### Goal

To create mid-level software structures that

- tolerate change
- are easy to understand
- are basis of components that can be used in many s/w systems.

# SRP &mdash; Single Responsibility Principle

_a s/w module has one and only one reason to change._

_a module should be responsible for one and only one actor_

- Separate the code that different actors depend on
- Dont put code that different actors depend on, in close proximity. changes will suck

Misunderstood for "do one thing"

# OCP &mdash; Open Closed Principle

_Open for extension, closed for modification_

_Change should be by adding new code, not modifying existing code._

- Architects separate functionality based on how, why and when it changes and then organize that separated functionality into a hierarchy of components
- Higher level components in that hierarchy are protected from the changes made to lower level components.

# LSP &mdash; Liskov Substitution Principle

Build s/w systems from interchangeable parts, those parts must adhere to a contract that allows those parts to be substituted one for another

# ISP &mdash; Interface Segregation Principle

Avoid depending on things that we dont use.

# DIP &mdash; Dependency Inversion Principle

Code that implements high level policy should not depend on code that implements low level details.

Most flexible systems are those in which source code dependencies refer only to abstractions, not to concretions.

Depend only on interfaces or abstractions.

- interfaces are less volatile that implementations.
- every change to an abstract interface corresponds to a change to its concrete implementations.
- But, changes to concrete implementations do not always require changes to the interfaces they implement.
