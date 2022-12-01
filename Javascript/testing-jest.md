
# Jest Packages
- jest-cli
- jest-config
- jest-haste-map
- jest-worker
- jest-circus 
- jest-runtime

## jest-cli
- `jest-cli` package pulls together rest of the packages
    - talks to `jest-config` to parse the jest.config.js and the command line args
    - talks to `jest-haste-map` to parse imports for each file, get the list of tests and detect changes to files
    - builds `Context` which consists of 
       - HasteContext
       - GlobalConfig + ProjectConfigs
    - `SearchSource` class within jest-cli figures out which tests to run, returns an `Array < Test >` where **Test** is
        - path
        - duration
        - Context ( defined above )
    - `TestSequencer` class  decides which order to run the `Test`s in
    - `TestScheduler` class decides how to run the tests among worker processes and talks to `jest-worker`
    - talks to `jest-circus` (earlier, `jest-jasmine`)
    - talks to `jest-runtime`
        - makes sure that each test runs in a separate `vm` context even if theyre running in the same process/worker.
        - `vm` is a nodejs library to create isolated environment to run anything.
        - loops over the imports given in the context by `jest-haste-map` and transforms those files


## jest-config
- parses the jest.config.js
- parses the command line args passed to jest cli
- GlobalConfig + ProjectConfigs

What configs exactly?
- the reporter to use
- the number of workers to run tests
- the number of projects to run the tests

## jest-haste-map
- parses imports, requires from each test file 
- finds out which files changed to understand which tests to re-run by using `watchman`
- uses `HasteFS`
- 


### `jest testfile.test.js` What happens?

# [Building a Toy Javascript Test Framework](https://cpojer.net/posts/building-a-javascript-testing-framework)

What should it do
- Efficiently search for test files on the file system
- Run all the tests in parallel
- Use an assertion framework for writing tests and report results
- Isolate tests from each other







# resources
- Jest architecture 1 https://youtu.be/3YDiloj8_d0
- Jest architecture 2 https://youtu.be/B8FbUK0WpVU