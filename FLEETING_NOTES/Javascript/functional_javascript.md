https://medium.com/javascript-scene/composing-software-the-book-f31c77fc3ddc

# Important concepts 
- Immutability
- Separation
- Composition
- Conservation
- Flow
- pure functions
- currying
- monads
- tail call optimization
- HOF...for function reusability
- avoid shared state
- avoid mutating state
- keep side effects separate from rest of logic.

### What is a "Function"
does one or more of these things
- serves as a **Mapping**. 
    - Mapping inputs to outputs. classic f(x)
- serves to work on a **procedure** of steps
- Does **I/O**
    - to talk with other parts of the system. Screen, storage, n/w...

> Sometimes, the elegant implementation is just a function. Not a method. Not a class. Not a framework. Just a function.

### What is a "Pure Function"
- Given the same input, will produce the same output
- Produces NO side effects

Pure functions are completely independent of outside state.
- free from bugs with arise from shared mutable state
- best for parallel processing

They should ideally be 
- Simple & Concise
- Decomposable
- Recomposable
- Independent
- Reusable

### What is a "Higher Order Function"
- accept a function
- return a function
- or both

`.map()` and `.filter()` are higher order functions


Functional programming tends to reuse a common set of functional utilities to process data.

### What is a "Curried function"
A function that takes multiple parameters, **one at a time**.
- takes one param
- - returns a function
- takes next param
- - returns a function
-... so on
```js
const highpass = (cutoff) => (n) => n>=cutoff;
/**
highpass is a function which takes cutoff and returns a function
which takes n and returns the result of n >= cutoff
**/
const greaterThan0 = highpass(0);

if(greaterThan0(100)){
    ...dothis
}
else{
    ...dothat
}
```
#### What is "partial application"
Partial application is a function which has been applied to some but not **yet** all of its arguments.
it’s a function which has some arguments fixed inside its closure scope. A function with some of its parameters fixed is said to be partially applied.

> add(a)(b)(c)

>The add function takes one argument, and then returns a partial application of itself with a fixed in the closure scope. A closure is a function bundled with its lexical scope. Closures are created at runtime during function creation. Fixed means that the variables are assigned values in the closure's bundled scope.

- _All curried functions return partial applications, but not all partial applications are the result of curried functions._
- _The unary requirement for curried functions is an important feature._
- All curried functions are a form of higher-order function which allows you to create specialized versions of the original function for the specific use case at hand.

Say you have the need for an "increment" function. Assume you already have the following
```js
function add = (a) => (b) => a+b;
```
Then all you need is a partial application of the above
```js
const increment = add(1);
console.log("Incrementing 4:", increment(4))
console.log("Incrementing 5:", increment(5))
```

In this case, increment is just a specialized version of add. 
- All curried functions are abstractions. 
- All higher-order functions are generalizations that you can specialize by passing one or more arguments.

#### What is the biggest benefit of currying?
It makes function composition simpler

They transform functions which expect multiple parameters into functions which can take a single argument, allowing them to fit in a function composition pipeline.

#### What is "point free style"?
When you use pipe() (and its twin, compose()) You don't need intermediary variables. Writing functions without mention of the arguments is called point-free style. To do it, you'll call a function that returns the new function, rather than declaring the function explicitly. That means you won't need the function keyword or the arrow syntax (=>).
```js
const g = n => n + 1;
const f = n => n * 2;

const h = pipe(
  g,
  trace('after g'),
  f,
  trace('after f'),
);
```


### What is "Functional Programming"
Buiilding software by 
- **composing** pure functions, 
- avoiding shared state, mutable data, and side-effects. 

Functional programming is 
- declarative rather than imperative.
- application state flows through pure functions. 
- more concise
- more testable 
- more predictable

> Contrast with object oriented programming, where application state is usually shared and colocated with methods in objects.

### Problems with shared state
- race conditions
- changing order of functions causes failures
    - because functions which act on shared state are timing dependent.
- refactoring is harder,

Pure Functions makes function calls completely independent of other function calls, which can radically simplify changes and refactoring. A change in one function, or the timing of a function call won’t ripple out and break other parts of the program.

### Immutability
Immutability involves making many many copies, deep clones..inorder to maintain history and **never** mutate existing objects. [This naturally means **immutability is a memory hog**](https://stackoverflow.com/q/2527412/5319180)

In many functional programming languages, there are special immutable data structures called trie data structures (pronounced “tree”) which are effectively deep frozen — meaning that no property can change, regardless of the level of the property in the object hierarchy. Tries use structural sharing to share reference memory locations for all the parts of the object which are unchanged after an object has been copied by an operator, which uses less memory, and enables significant performance improvements for some kinds of operations. For example, you can use identity comparisons at the root of an object tree for comparisons. If the identity is the same, you don’t have to walk the whole tree checking for differences.

There are several libraries in JavaScript which take advantage of tries, including Immutable.js and Mori.

### What are "side effects"
Any state change other than the return value
- modifying global variable
- modifying variable in parent scope
- writing to screen/console/file/network
- Triggering an external process
- calling another function that produces side effects

What to do when you desperately need to do a side effect, but cant because youre "purely" functional? - **monads**

### What are "Functors"
Functors are mappables. Things that you can map over,


<hr/>
 TIP : Keep your side effects separate from rest of the logic.
<hr/>




# Lambda Calculus
- Functions are first class. 
    - Functions can be inputs to functions, 
    - Functions can be returned from functions
- Functions are always anonymous
- Functions accept single input . Use **currying** to simulate n-ary functions

# What JS lacks to make it the best platform for functional programming
- purity
    - side effects should be banned natively by the language.
    - -> You can enforce this in your code by discipline. Keep your functions pure.
- immutability
    - mutations should be banned natively by the language.
    - Immutability may sound inefficient, but most functional languages use trie data structures under the hood, which feature structural sharing: meaning that the old object and new object share references to the data that is the same.
    - use **Immutable.js**
- recursion
    - **for, while, dowhile** loops should be banned natively by the language
    - use recursion for the same.


# Composition
The process of software development is breaking down large problems into smaller problems, building components that solve those smaller problems, then composing those components together to form a complete application.
> Software solutions should be decomposable into their component parts, and recomposable into new solutions, without changing the internal component implementation details.
- What is *function composition*?
- What is *object composition*?

## Function Composition
`f(g(x))`

## Object Composition
**The Composite Design Pattern** where you define one object whose aggregate also can be treated as the same object (for recursing)...is ONE of the approaches of object composition. eg : a DOM node has DOM children.and so on.


> “Composite objects are formed by putting objects together such that each of the latter is ‘part of’ the former.”

**The Mixin Concatenation**
A.K.A Object Concatenation

You start with an object(like vanilla ice-cream), and then mix in the features you want.





# Utils
### pipe( f, g )
or better, `pipe( f, g, x, y ,z )`

`pipe()` creates a pipeline of functions, passing the output of one function to the input of another. When you use pipe() (and its twin, compose()) You don't need intermediary variables. Writing functions without mention of the arguments is called **point-free style**. To do it, you'll call a function that returns the new function, rather than declaring the function explicitly. That means you won't need the function keyword or the arrow syntax (=>).
```js
const pipe = (...fns) => x => fns.reduce((y, f) => f(y), x);
```


### compose( f, g )
The reverse of pipe. compose is nothing but f(g(x))
```js
const compose = (...fns) => x => fns.reduceRight((y, f) => f(y), x);
```

### trace (label)(value)
```js
const trace = label => value => {
  console.log(`${ label }: ${ value }`);
  return value;
};
```

### stack
```js
const stack = (...items) => ({
  push: item => stack(...items, item),
  pop: () => {
    const newItems = [...items];
    const [item] = newItems.splice(-1);
    return [item, stack(...newItems)];
  },
  toString: () => `stack(${ items.join(',') })`
});
```


# Questions
- Will immutability take too much memory?
    - This may sound inefficient, but most functional languages use trie data structures under the hood, which feature structural sharing: meaning that the old object and new object share references to the data that is the same.
- What is the cons of currying.
