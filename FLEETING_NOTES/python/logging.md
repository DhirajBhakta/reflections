
#### `basicConfig`
`logging.basicConfig` configures the root logger with things like 
- loglevel
- format
- log destination
- handlers 

`logging.basicConfig(..)` can be called ONLY once. Any further calls are ignored !

Custom loggers created via `logging.getLogger(__name__)` cannot be configured via `logging.basicConfig`, you have to configure it via Handlers and Formatters.

#### Logging Exceptions
`logging.exception("Exception Occurred")` is the best way to log inside a `catch` block. This will print the stack trace too.
**Should be only called from inside an exception handler**. 

This above is same as calling `logging.error(exc_info=True)`. 

#### Loggers
You use the `Logger` object to do any kind of logging.
```
logger = logging.getLogger()
logger.info("hello")
```
But by default, if you do `logging.info`, then you're using the root logger.
#### Handlers
A Handler takes care of sending logs to a specified destination. File? stream(stdout) ?..
A single `Logger` object can have multiple `Handlers`


#### Formatters