#### First Principle of Redux

- single JS object
- single state tree

### Second Principle of Redux

- the state tree is _immutable_
- the state tree is _read only_
- the only way to change the state tree is via **actions**
- **actions** are JS objects that describe the change

### Third Principle of Redux

- The **Reducer**  is a pure function which takes
  - previous state
  - action
- and returns the new state

### Redux Methods

- getState()
- dispatch()
- subscribe()

### Redux Selectors

### Redux Middleware chain

### Thunk

### normalizr

### Pitfalls

- Avoid Array Mutations with `concat`, `slice` and ,`...spread`
- Avoid Object Mutations with `Object.assign()` and `...spread`
