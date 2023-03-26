import fetch from 'node-fetch';
/**
 * Implement a rate limiter on top of fetch API such that 
 * at any given time, no more than 3 requests are in flight.
 * any subsequent calls must be queued, and must be processed
 * holding the invariant true all the time.
 * i.e no more than 3 requests are in flight at any given time.
 */
function rateLimiter(rateLimit=3) {
    const q = new Queue();
    let counter = rateLimit;
    function Queue() {
        this._queue = [];
    }
    Queue.prototype.push = function (val) {
        this._queue.push(val);
        executeOne();
    }
    Queue.prototype.shift = function () {
        return this._queue.shift()
    }
    Queue.prototype.isEmpty = function () {
        return this._queue.length === 0;
    }

    function delayResult(result){
        return new Promise((resolve)=> setTimeout(()=>resolve(result),Math.random()*10000))
    }

    function executeOne() {
        if (counter > 0 && !q.isEmpty()) {
            counter--;
            const { resolve, args } = q.shift();
            console.log("\n\nattempting ", ...args);
            fetch(...args)
                .then(delayResult)
                .then(val => resolve(val))
                .then(() => counter++)
                .then(executeOne)
        }
    }
    return function () {
        return new Promise((res, rej) => {
            q.push({
                resolve: res,
                args: arguments
            })
        })
    }
}

const f = rateLimiter(3);

f('https://jsonplaceholder.typicode.com/todos/1')
  .then(response => response.json())
  .then(json => console.log(`\nI am logging the first response:" ${json.title}`, 'color:red'))
f('https://jsonplaceholder.typicode.com/todos/2')
  .then(response => response.json())
  .then(json => console.log(`\nlogging second one:" ${json.title}`, 'color:red'))
f('https://jsonplaceholder.typicode.com/todos/3')
  .then(response => response.json())
  .then(json => console.log(`\nlogging third one:" ${json.title}`, 'color:red'))
f('https://jsonplaceholder.typicode.com/todos/4')
  .then(response => response.json())
  .then(json => console.log(`\nlet me show you the fourth response:" ${json.title}`, 'color:red'))
f('https://jsonplaceholder.typicode.com/todos/5')
  .then(response => response.json())
  .then(json => console.log(`\npresenting you the fifth response:" ${json.title}`, 'color:red'))
f('https://jsonplaceholder.typicode.com/todos/6')
  .then(response => response.json())
  .then(json => console.log(`\nHere's the last frikkin response:" ${json.title}`, 'color:red'))