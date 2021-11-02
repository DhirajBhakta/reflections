- JS is single threaded
- no native support for performing multiple tasks simultaneously
- But UI needs async behavior

**JS solves this using the event loop**

- callbacks
- Promises

## Promise

Promise: Promise object represents the eventual completion or failure of an async operation and its resulting value.

### Promise states

- Pending
- Fulfilled
- Rejected

### Example

```js
const getNumber = () =>
    new Promise((resolve, reject) =>{
        const randomNumber = parseInt(Math.random() *100);
        setTimeout(()=>{
            if(randomNumber%5 ===0)
                reject(`Rejected with num: ${randomNumber}`);
            resolve(`Resolved with num: ${randomNumber}`);
        }, randomNumber *10)
    })

/**
-------------USAGE------------------------
**/
const numberPromise = getNumber();
numberPromise
    .then((val) => incrementBy(val, 10))
    .then((val) => incrementBy(val, 20))
    .then((val) => incrementBy(val, 30))
    .then(display)
    .catch(display)
```

### Custom Promise (Implementing Promises)

CustomPromise should support initialization in the following way

`new Promise((resolve, reject) => ...)`

```js
class CustomPromise{
    constructor(fn){
        this.resolver = this.resolver.bind(this);
        this.rejector = this.rejector.bind(this);
        fn(this.resolver, this.rejector);
    }

    resolver(resolvedData){
        return;
    }
    rejector(rejectedData){
        return;
    }
}
```

CustomPromise on resolution should call the method it was passed using then.

CustomPromise on rejection should call the method it was passed using catch.

```js
class CustomPromise{
    constructor(fn){
        this.resolver = this.resolver.bind(this);
        this.rejector = this.rejector.bind(this);
        this.thenFn   = null;
        this.catchFn  = null;
        fn(this.resolver, this.rejector);
    }

    resolver(resolvedData){
        this.thenFn && this.thenFn(resolvedData);
    }
    rejector(rejectedData){
        this.catchFn && this.catchFn(rejectedData);
    }
    then(thenFn){
        this.thenFn = thenFn;
        return this;
    }
    catch(catchFn){
        this.catchFn = catchFn;
        return this;
    }
}
```

We need to keep track of CustomPromise's state

- PENDING
- RESOLVED
- REJECTED

Once a promise is resolved, rejector method should have no effect on it. It shouldn't be executed.

```js
const State = {
    PENDING : "PENDING",
    RESOLVED: "RESOLVED",
    REJECTED: "REJECTED"
}
class CustomPromise{
    constructor(fn){
        this.state = State.PENDING;
        this.resolver = this.resolver.bind(this);
        this.rejector = this.rejector.bind(this);
        this.thenFn   = null;
        this.catchFn  = null;
        fn(this.resolver, this.rejector);
    }

    resolver(resolvedData){
        if(this.state === State.PENDING)
            this.thenFn && this.thenFn(resolvedData);
        this.state = State.RESOLVED;
    }
    rejector(rejectedData){
        if(this.state === State.PENDING)
            this.catchFn && this.catchFn(rejectedData);
        this.state = State.REJECTED;
    }
    then(thenFn){
        this.thenFn = thenFn;
        return this;
    }
    catch(catchFn){
        this.catchFn = catchFn;
        return this;
    }
}
```

### Chaining

```js
const State = {
    PENDING : "PENDING",
    RESOLVED: "RESOLVED",
    REJECTED: "REJECTED"
}
class CustomPromise{
    constructor(fn){
        this.state = State.PENDING;
        this.resolver = this.resolver.bind(this);
        this.rejector = this.rejector.bind(this);
        this.thenFns  = [];
        this.catchFn  = null;
        fn(this.resolver, this.rejector);
    }

    resolver(resolvedData){
        if(this.state !== State.PENDING)
            return;
        while(this.thenFns.length){
            const thenFn = this.thenFns.shift();
            this.resolvedData = thenFn(this.resolvedData || resolvedData)
        }

            this.thenFn && this.thenFn(resolvedData);
        this.state = State.RESOLVED;
    }
    rejector(rejectedData){
        if(this.state === State.PENDING)
            this.catchFn && this.catchFn(rejectedData);
        this.state = State.REJECTED;
    }
    then(thenFn){
        this.thenFns.push(thenFn);
        return this;
    }
    catch(catchFn){
        this.catchFn = catchFn;
        return this;
    }
}
```
