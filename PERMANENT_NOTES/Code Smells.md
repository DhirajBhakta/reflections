
#### Method level Code Smells

Long method 
- A method consists of many lines of code, performing different calculations. 

Long parameter list 
- A method has many parameters 

Switch statements 
- Code contains large switch statements, while polymorphism could also be used to ease the code 

#### Class level Code Smells
Alternative classes with different interfaces 
- Two different classes seem different at first glance but have similar fields and methods 

Primitive obsession 
- Overuse of primitive types in a class 

Incomplete library class 
- Methods are added to ‘random’ classed instead of to a library class 

Large class 
- A class has too many methods and fields, and it is not clear what abstraction the class provides. 

Lazy class 
- A class is doing too little to justify its existence 

Data class 
- Classes should not contain just data, they should contain methods as well 

Temporary field 
- Classes should not contain unnecessary temporary fields 


Data clumps 
- Data are often used in combination belong together and should be stored together in a class or structure 


#### Codebase level code smells
Divergent change | Shotgun surgery
- Code changes should in general be local, preferably to one class. If you have to make many different changes in different places, that indicates a poor structure in the code 

Feature Envy 
- When methods on class A are referencing a lot from class B, they belong in B and should be moved there. 

Inappropriate intimacy 
- Classes should not be connected to other classes extensively 

Duplicated code or code clones 
- The same or very similar code occurs in multiple different places in a codebase 

Comments 
- Comments should describe why the code is there NOT what it does 

Message chains
- Long chains of message calls, where methods call methods call methods, etc

Middle Man
- If a class is delegating too much responsibility, should it exist?

Parallel inheritance
- When you make a subclass of one class, you need to make a subclass of another. This indicates that the functionality of both classes might belong in one class.

Refused bequest
- When classed inherit behavior that they do not use, the inheritance might not be necessary.

Speculative generality
- Do not add code to a codebase “just in case”, only add features that are needed.