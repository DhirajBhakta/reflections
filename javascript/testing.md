# General
https://youtu.be/cAKYQpTC7MA



## What makes a good test?
- Runs fast
- Doesnt break often (flaky)
- should serve as a documentation, easy to read and understand
- good coverage to effort ratio
- survives major refactoring. So code to an interface....try to..
- forces you to think about possible issues and edge cases, be empathetic to the user of your function/class

## [What exactly is a JS test?](https://kentcdodds.com/blog/but-really-what-is-a-javascript-test)
- check whether `expected == output`
- it is easier to test pure functions 
- it is difficult to test functions that depend on state
    - we need the `setup` phase to setup all the state, dependencies before running the actual assertion
### What is an assertion library `should` `expect` `assert`
You'd definitely like to do more than just `===` and `!==` and throw errors.
```js
   if(expected!==output)
        throw("expectation failed, expected this, got that")
```
Assertion libraries give you a `expect` function which can do much more than just equality checks..say regex checks, and much more. Also saves you from writing "Expected this, got that". 

`Chai` for example, gives you powerful BDD primitives like `should`
```js
foo.should.be.a('string');
foo.should.equal('bar');
foo.should.have.lengthOf(3);
tea.should.have.property('flavors')
  .with.lengthOf(3);
```
...TDD style `assert`
```js
assert.typeOf(foo, 'string');
assert.equal(foo, 'bar');
assert.lengthOf(foo, 3)
assert.property(tea, 'flavors');
assert.lengthOf(tea.flavors, 3);
```
and the usual default `expect`
```js
expect(foo).to.be.a('string');
expect(foo).to.equal('bar');
expect(foo).to.have.lengthOf(3);
expect(tea).to.have.property('flavors')
  .with.lengthOf(3);
```

Lets write our own minimalistic assertion library
```js
const expect = (actual) => ({
    toBe(expected) {
      if (actual !== expected) {
        throw new Error(`${actual} is not equal to ${expected}`)
      }
    },
  })
```
usage:
```js
expect(sum(3,7)).toBe(10);
expect(sum(7,3)).toBe(10)
```

### What is a testing framework `test` `describe`
We need a wrapper over assertions to `catch` the errors thrown and present the errors in a neat manner "describing" what failed, and possibly...where exactly,(after parsing stack trace intelligently).

We also need a wrapper to run our tests in a isolated manner. ..And even describe our tests in an isolated manner.

Lets write our own minimalistic testing framework
```js
const test = (title, callback) =>{
    try{
        callback();
        console.log(`✓  ${title}`)
    }catch(err){
        console.log(`✕  ${title}`)
        console.log(err)
    }
}
```

usage
```js
test('sum adds numbers', () => {
  expect(sum(3,7)).toBe(10);
});

test('difference subtracts numbers', () => {
  expect(difference(17,7)).toBe(10);
});
```

Now we need a cli to pick up all these test files (*.spec.js, *.test.js)



# Spectrum of Tests
![](../assets/js-testing-01.webp)

## Unit Tests
Fully Isolated.
Tests just one function

## Integration Tests
Testing units along with their dependencies

## End-to-end Tests (Acceptance tests)
Automate what you would do in a browser manually

## Which one should I focus on? (2 schools of thought)
- some say write thousands and thousands of unit tests.
- some say write acceptance tests first.
## Challenges
Testing plain JS functions is fine, but testing UI is **hard** <br/>
 mocking/isolation just reduces test quality and less bugs are caught.


## Write Test Templates 


# Test tool types
Test tools can be categorized based on the _functionality_ they offer. Some go ahead and try to offer more than one functionality (eg: jest)


### Test Runners / Test Launchers
Run your tests on the required environments configured by you...( what browsers to run in, what babel version to use, how to format the output etc)...and summarize test results

Eg: Karma, Mocha

### Assertion Libraries
Libraries that exposes a clean API that help you assert (lol!) 

`expect(XYZ).to.be(ABC)`

Eg: Chai

### Libraries that give you good way to structure your tests
Like cucumber...which helps you arrange your tests in BDD style, just one way of _structuring_ your tests.

<hr/>

All in all, to start testing you need to choose a **testing structure** (BDD?), choose the **style of assertion functions** you like, and decide how do you want to **run the tests**.

Mocha+chai+sinon is a popular combo.

Some provide everything out of the box. Jest, Jasmine, TestCafe, Cypress, Playwright.

<hr/>

As you move closer to the other end of the testing spectrum (e2e), the "**test runners**" will have to create a browser-like environment for you to automate behaviors like scrolling, clicking, access to DOM(obviously), waiting for button to be visible,painted and clickable..etc

How is it done?
1. By simulating a browser-like environment in pure JS (see jsdom, testcafe)
2. By using the **webdriver API**
    ( a language agnostic, REST based API to remotely control browsers )

`Your code on Node.js <> WebDriver <> FF/Chrome/Safari Driver <> Browser`

3. By using the APIs exposed by the browser maintainers, that let you control the browsers directly. Eg: Puppeteer.

`Your code on Node.js <> Browser's API`

# Testing terms
## Snapshot Testing
Take a snapshot of current state ( may have its own internal representation of its 'snapshot' of the DOM ) and warn the user when any change causes the current snapshot to differ even slightly from the new snapshot.

## Webdriver
- This [standard]() is inspired from the Selenium Webdriver project.
- every browser has a "driver" which understands this protocol
    eg: Chromedriver, 
    ```http
    POST /session
    POST /session/<sessionId>/element/<elementId>/click
    ```
- the webdriver is sort of a HTTP server which will then dispatch browser events in response to these REST calls
- write in any language, and communicate with the browser (in the end its just REST API afterall)
![](../assets/js-testing-01.png)



# Jest
pass

# Why so many e2e testing frameworks?
https://youtu.be/emWHeODwcQY

https://www.youtube.com/watch?v=pK-l5P9l-3I

### Selenium

**Cross browser++** : 
Selenium is a **suite** of tools for cross browser frontend testing.

**Flexibility via REST APIs ++**:
Selenium also provides compatibility with different programming languages – C#, Java, JavaScript, Ruby, Python, PHP.

- Selenium IDE 
    - browser extension
    - Just a record/run tool
- Selenium RC 
    - "remote control"
- Selenium WebDriver
    - Selenium RC++
- Selenium Grid
    -Concurrent execution of tests on different OS, machines, browsers

CONS:
    - not yet bidirectional, as its a HTTP server. you can talk to the browser via the webdriver API, but browser cannot talk to you


### Cypress
Focus is on developer experience. Do very very less to get started.

Cypress is _less_ cross browser. It dispatches JS events, and not browser events. So they could only support Chrome until now(now FF recently).

- code looks less like JS and more like just chaining promises.


### Puppeteer
Started as an internal tool at Google.
Same philosophy as WebDriver

### Playwright
When Microsoft based their Edge off chromium, they probably forked puppeteer into Playwright

Biggest flex:
- crossbrowser ( moz, webkit, chrome)
- very well thought of API
- focussed on e2e testing ( waiting for elements to be ready, for example )
- Superfast compared to competitors, on par with Puppeteer.
- custom selector engines


# Cypress talk
- browser driver??









# Playwright

### Playwright Test
A test runner for end-to-end tests
- Run each test scenario in a new **browser context** (for test isolation)

### Questions
- playwright execution context vs browser execution context?
> Playwright scripts run in your Playwright environment. Your page scripts run in the browser page environment. Those environments don't intersect, they are running in different virtual machines in different processes and even potentially on different computers.

What even??

## Closing notes on testing
- Create 2 streams of your tests, one for unit+integration(which is meant to run fast)...another for acceptance e2e testing(which runs much slower) 
- Focus more on getting the e2e testing skeleton up and running at the earliest.
- Unit test the utils, helpers, services ..and keep them "pure" and "functional". More they follow SRP and avoid side effects, easier they are to unit test.


# Resources
- https://medium.com/welldone-software/an-overview-of-javascript-testing-7ce7298b9870
- https://kentcdodds.com/blog/but-really-what-is-a-javascript-test

# Questions
- How do you decide what should be in a global store and what should reside in a local store?
- what exactly is npx
-  make sense of the below error
```bash
(node:2228062) Warning: To load an ES module, set "type": "module" in the package.json or use the .mjs extension.
(Use `node --trace-warnings ...` to show where the warning was created)
/home/dhirajbhakta/Development/setu/gs-equitas/tests/trial.spec.ts:3
import {webkit, devices} from 'playwright';
^^^^^^

SyntaxError: Cannot use import statement outside a module
```
