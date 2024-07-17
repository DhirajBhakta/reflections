- S (Single Responsibility Principle)
- O (Open Close Principle)
- L (Liskov Substitution Principle)
- I (Interface Segragation Pattern)
- D (Dependency Injection)
#### Why SOLID Principles
They're just "clean code" principles. You get
- better readability -> maintainability -> flexibility to add features
- reduce complexity
- DRY code (although WET is not so bad)

#### S - Single Responsibility Principle
_A Class should have only 1 reason to change_
> **Warn**: don't take this too far, especially when starting out on a fresh project. Unnecessary blowup of classes.

Eg:
if there's a class with following methods
- printInvoice
- calculateTotal
- saveToDB
Then its doing 3 things (hence 3 reasons to change)
Solution: Have 3 classes which do one single thing each
- InvoicePrinter class
- Invoice class (to calculate total)
- InvoiceDAO (to save to DB)

Concerns:
- Doesn't this cause a blowup of classes?
- can you just not apply SRP to functions/methods rather than at classes ?


#### O - Open Closed Principle
_A Class should be Open for **extension** but Closed for **modification**_
>**Info**: Closely related to SRP

If a Class (SRP) is already tested and is live in production, you should
- ADD new methods, extend the functionality
- NOT MODIFY existing functionality

But will not adding extra methods  in the name of "extension" not break SRP?
Yes. Hence you shall use Interfaces and do extension by creating new classes which implement the same interface.

`InvoiceDAO` is the interface with `save` method
`SQLInvoiceDAO`, `MongoInvoiceDAO`, `FileInvoiceDAO` classes all implement the `InvoiceDAO` interface.


#### L - Liskov Substitution Principle
_Subclass should be able to replace the parent class_

For this to work, Subclass should **extend** (or ADD to) the functionality of Parent class. NOT narrow it down.


#### I - Interface Segregation Principle
_Interfaces shouldn't force classes to implement methods they don't need_

Implies=> break up the interface into smaller interfaces

#### D - Dependency Inversion 
_Class should depend on Interfaces, not Classes_

DON'T instantiate deps within the Constructor.
Accept deps from the Constructor. 
- Benefit = Supplier can supply ANY object which honors the interface. This is good for flexibility + makes testing/mocking easier.

