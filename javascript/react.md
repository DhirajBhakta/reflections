### Library v/s Framework
Simple definition
- a framework is a software where you plug your code into
- a library is a software that you plug into your code

**_React is a javascript library_**

Angular, Ember.js and ExtJS are frameworks, but React isn't, because it only gives you the means to build components and render them into the DOM.

## React &mdash; [Design](https://github.com/reactjs/react-basic)
The mental model for React.
.. Things that went into its design..

### Transformation &mdash; pure functions
Same input should give same output
```js
function NameBox(name) {
  return { fontWeight: 'bold', labelContent: name };
}

//---------
'Sebastian Markbåge' ->
{ fontWeight: 'bold', labelContent: 'Sebastian Markbåge' };
```

### Abstraction & Composition &mdash; Reusable "components"
Components house components; Functions call functions...

"Reusable" Functions/Components.

```js
function FancyUserBox(user) {
  return {
    borderStyle: '1px solid blue',
    childContent: [
      'Name: ',
      NameBox(user.firstName + ' ' + user.lastName)
    ]
  };
}

///----------------------------
{ firstName: 'Sebastian', lastName: 'Markbåge' } ->
{
  borderStyle: '1px solid blue',
  childContent: [
    'Name: ',
    { fontWeight: 'bold', labelContent: 'Sebastian Markbåge' }
  ]
};
```
### State &mdash; Immutable data model
UI components **need** local state.
Immutability greatly optimizes reconciliation.
TODO:How?

### Memoization 
Re-executing pure functions is wasteful. Just cache the outputs of previous inputs and return them.



## React &mdash; Concrete 

### [React Elements](https://reactjs.org/blog/2015/12/18/react-components-elements-and-instances.html)

Creating a React element is cheap (JS obj). Once an element is created, it is never mutated.
- DOM elements
    - When an element’s **type** is a `string`, it represents a DOM node with that tag name, and props correspond to its attributes. This is what React will render
- Component elements
    - the **type** of an element can also be a `function` or a `class` corresponding to a React component
    - An element describing a component is also an element, just like an element describing the DOM node. You can mix and match DOM and component elements in a single element tree:



#### DOM elements
```html
<button class='button button-blue'>
  <b>
    OK!
  </b>
</button>
```
```js
{
  type: 'button',
  props: {
    className: 'button button-blue',
    children: {
      type: 'b',
      props: {
        children: 'OK!'
      }
    }
  }
}
```

#### Component Elements
```js
{
  type: Button,
  props: {
    color: 'blue',
    children: 'OK!'
  }
}
```

### Mix and match DOM elements and Component elements
```js
const DeleteAccount = () => ({
  type: 'div',
  props: {
    children: [{
      type: 'p',
      props: {
        children: 'Are you sure?'
      }
    }, {
      type: DangerButton,
      props: {
        children: 'Yep'
      }
    }, {
      type: Button,
      props: {
        color: 'blue',
        children: 'Cancel'
      }
   }]
});

/**  ---OR--- **/
const DeleteAccount = () => (
  <div>
    <p>Are you sure?</p>
    <DangerButton>Yep</DangerButton>
    <Button color='blue'>Cancel</Button>
  </div>
);
```
<div style="background-color:yellow; padding:1vw; border:3px solid ; border-radius:4px">
<strong>
React is like a child asking “what is Y” for every “X is Y” you explain to them until they figure out every little thing in the world
</strong>
- Button is a DOM < button > with specific properties.
- DangerButton is a Button with specific properties.
- DeleteAccount contains a Button and a DangerButton inside a < div >.
</div>
We let React create, update, and destroy instances. We describe them with elements we return from the components, and React takes care of managing the instances.






## How React works
- maintains a tree (vDOM, in js) which helps do efficient diff computations on nodes
- re-constructs your DOM in JavaScript( as vDOM) and push only those changes to the DOM which have actually occurred. vDOM is synced with real DOM through a library such as **ReactDOM**


### JSX  = React.createElement
- JSX is simply syntactic sugar for creating very specific JavaScript objects.
- `const tag = <h1>Hello</h1>` <==> `const tag = React.createElement("h1", {}, "Hello")`
- The last param is `children`
- **A Babel preset** `@babel/preset-react` converts JSX to javascript
- Once all the JSX is parsed and all the React.createElement calls have been resolved, we land with one giant nested object

### ReactDOM
Once the giant nested object is resolved(see above section), `ReactDOM` recursively creates actual `div`s and `p`s , the DOM nodes and append them to the real DOM tree.

- react and ReactDOM are decoupled! (react library and the renderer)
- react simply construct a tree of UI which could be used not only on web, but on environments like mobile too, given that a renderer is available which is able to communicate with the host OS. Here, React Native comes to play.
- React Native uses React library, but not ReactDOM as the render. Instead, the package react-native itself is a renderer.
- React Native doesn't have methods like appendChild...it doesnt have a DOM environment. Instead, for mobiles, we need support for UI directly from OS. But the React library doesn't need to know that, the renderer (React Native) takes care of that.

### Reconciliation
Complete heavy diffing O(n^3) is much more expensive. So React uses a O(n) heuristic for diffing.
- React assumes that **if a parent has any change, then all its children have changes**
- hence it destroys all its children and re-creates it

#### The Diffing Heuristic Algorithm O(n)
Compares the two root elements
- Root elements have different types
    - full rebuild (unmount, remount)
- Root elements have same type, but different attributes
    - only attributes are updated by say `node.addClass('class1')`
    - React then recurses over the children
- React elements are same, but props have changed
    - no unmount
    - component updates by calling `render()` again
    - React then recurses over the children

If you provide the `key` prop to children, or in general any react component, possible re-renders could be avoided(in accordance with the above algorithm). for eg:
```html
<!--old tree-->
<ul>
  <li key="2015">Duke</li>
  <li key="2016">Villanova</li>
</ul>

<!--new tree-->
<ul>
  <li key="2014">Connecticut</li>
  <li key="2015">Duke</li>
  <li key="2016">Villanova</li>
</ul>
```

#### Reconciliation is top-down
<div style="background-color:yellow; padding:1vw; border:3px solid ; border-radius:4px">
This happens when you call ReactDOM.render() or setState(). 
</div>

```js
/**
 * 
 React will ask the Form component 
 what element tree it returns, given those props. 
 
 It will gradually “refine” its understanding of your component tree 
 in terms of simpler primitives:
 */

// React: You told me this...
{
  type: Form,
  props: {
    isSubmitted: false,
    buttonText: 'OK!'
  }
}

// React: ...And Form told me this...
{
  type: Button,
  props: {
    children: 'OK!',
    color: 'blue'
  }
}

// React: ...and Button told me this! I guess I'm done.
{
  type: 'button',
  props: {
    className: 'button button-blue',
    children: {
      type: 'b',
      props: {
        children: 'OK!'
      }
    }
  }
}
```





#### React Fiber
is the new reconciliation engine

## [React Fiber architecture](https://github.com/acdlite/react-fiber-architecture)
### Incremental Rendering
ability to split rendering work into chunks and spread it over multiple frames.


## React Performance Optimisations
### Immutability
It is very fast to calculate whether the props have changed if they are immutable, so React and immutability work great together, and can provide great optimizations with the minimal effort.
# React Router &mdash; Client-Side-Routing
### Why Client side routing?
...
...

### BrowserRouter
...
...

#Left off at https://github.com/acdlite/react-fiber-architecture and linked articles
Left off here too https://reactjs.org/docs/optimizing-performance.html
