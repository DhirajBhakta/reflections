<https://weblogs.asp.net/dixin/understanding-all-javascript-module-formats-and-tools>

# Why

- You could just attach all your "exported" variables (+functions,classes) to global and then access it from there everytime. but you'd want to access stuff ONLY where you "import" stuff
- In the beginning, Javascript did not have a way to import/export modules. [Now it does](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Modules)

# Module Systems

- So people wrote their own libraries to add import/export capabilities
  - CommonJS &mdash; used by node
  - AMD - Async Module definition
  - UMD - Universal Module definition
  - ESModules

### CommonJS

```js
//importing 
const doSomething = require('./doSomething.js'); 

//exporting
module.exports = function doSomething(n) {
  // do something
}
```

- nodejs uses cjs module format
- cjs **imports synchronously**
- cjs **gives you a copy** of the imported object.
- cjs does not work on browser, needs to be transpiled and bundled.
- meant for backend where modules can be loaded fast from filesystem.

### AMD

```js
```

- loads modules async
- meant for frontend where modules are fetched over network. slow.

### UMD

```js
```

### ESM

```js
import {detectCats} from "kittydar.js";

function go() {
    var canvas = document.getElementById("catpix");
    var cats = detectCats(canvas);
    drawRectangles(canvas, cats);
}
```

- the imported modules are loaded first

- **import async**

### `.mjs` ??

## Browsers now support modules
<https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Modules>

To get modules to work correctly in a browser, you need to make sure that your server is serving them with a Content-Type header that contains a JavaScript MIME type such as text/javascript

# ES Modules

- official, standardized module system of JavaScript
- took 10 years

### How does `import` work?

ES6 leaves it to the implementation

- parsing
  - the implementation reads the source code
  - the implementation checks for syntax errors
- loading
  - the implementation loads imported modules recursively
  - _more on this later_
- linking
  - the implementation creates a module scope and adds imported bindings into that scope
- Runtime
  - the implementation runs all the code in the loaded module

Since the loading implementation isnt specified in the spec, guys like Webpack load all imports statically at _compile_ time and make one massive js file (bundled)

### How does module loading & linking really work

`Module loading = **entrypoint file** ----to---> full graph of **module instances**`
![](https://hacks.mozilla.org/files/2018/03/07_3_phases-500x184.png)

#### 1. Construction

= **fetching the file + parsing it to make module records**

first the file is parsed for import statements, and then the files pointing to the import path are parsed...and so on recursively until all the files make up the dependency tree.

##### finding the file and fetching it

to know which file to load next, you need to read the imports declaration. to know the imports declaration, you need to first fetch the file we're talking about.

Which means we gotta fetch all the files!!!!

![](https://hacks.mozilla.org/files/2018/03/11_latency-500x270.png)

You cant affort to block the main thread for downloads of these files!!!

This is one of the reasons that the ES module spec splits the algorithm into multiple phases. **Splitting out construction into its own phase** allows browsers to fetch files and build up their understanding of the module graph before getting down to the synchronous work of instantiating.

This approach—having the algorithm split up into phases—is one of the key differences between ES modules and CommonJS modules.

In CommonJS, when you hit a `require` statement, the main thread is blocked, the file is loaded, instantiated, evaluated synchronously...

This makes sense because filesystem file loading is much faster, and now that youve loaded it, why not just instantiate and evaluate it

![](https://hacks.mozilla.org/files/2018/03/12_cjs_require-500x298.png)

This also means that you’re walking down the whole tree, loading, instantiating, and evaluating any dependencies before you return the module instance.

<div style="background-color:#afd6f9; padding:1em; border:2px solid">
Implications??
**You can use variables inside `require`, but not in `import` because in ESM, the code isnt yet evaluated and variable is hence not yet available** (possible in dynamic imports though)
</div>

![](https://hacks.mozilla.org/files/2018/03/13_static_import-500x146.png)

While fetching the files(modules), if a call is made to fetch already fetched/fetching module...it is aborted. cache FTW!!
This is done using module maps ...which will eventually serve as cache for modules

![](https://hacks.mozilla.org/files/2018/03/15_module_map-500x170.png)

##### Parsing &mdash; files into module records

each file/module is converted into a data structure called **module_record**
![](https://hacks.mozilla.org/files/2018/03/25_file_to_module_record-500x199.png)

Once module records are made, they are placed into the module map
![](https://hacks.mozilla.org/files/2018/03/25_module_map-500x239.png)

#### 2. Instantiation

module records are converted into **module instances** -> which combine code and state.

Finds "boxes" in memory to place all the exported values (but dont yet place the values) . Then make both exports and imports point to those boxes in memory. _This is called **linking**_

![](https://hacks.mozilla.org/files/2018/03/30_live_bindings_01-500x206.png)

<div style="background-color:#afd6f9; padding:1em; border:2px solid"> Module instances are shared; So even if you import a module 100 times in 100 places, only one instance would be shared.
</div>

#### 3. Evaluation

Run the code to fill the "boxes" with real values

# Resources

- <https://hacks.mozilla.org/2018/03/es-modules-a-cartoon-deep-dive/>
# todo: i left off at instantiation
- <https://weblogs.asp.net/dixin/understanding-all-javascript-module-formats-and-tools>
