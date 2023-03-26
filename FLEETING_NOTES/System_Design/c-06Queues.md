Imagine you have an API endpoint to send emails
```py
def send_email(request):
    user = get_user(request)

    user.save_message(request.message)

    for friend in user.friends:
        friend.send_email(request.message)

    return "OK"
```
- Works well if you have 1-10 friends. What about 100,000,000 friends, say FB..
- LOOOONG request response cycle. Say it takes 10 minutes to actually send emails to 1million people
- _Alternative_ : save (friend_user_id, message) in a new table. Use a **cron** every 10 secs... _This is bad. Backlogs are bad._
- _Solution_: Queues...................

# [Queues](https://www.fullstackpython.com/task-queues.html)


- RabbitMQ
- ActiveMQ

### [Why?](https://www.slideshare.net/bryanhelmig/task-queues-comorichweb-12962619)

imagine a system where writes take long, really long.

- because processing may take time
- because system is under load

Then we need to work in an **Asynchronous** Way, Using QUEUES

### Drawbacks of Synchronous

- client is supposed to WAIT for a long time, doing ZERO work, until the request can be responded to.

### Async

All incoming tasks are added to a queue, and as soon as any **worker** can pick up a task, it is picked from the queue.

Clients DONT get the response immediately, they only get an **acknowledgement** that their request was _ACCEPTED_


### Concepts
- **Broker**
    - The middleman holding the tasks(messages)
    - eg: AWS SQS, Redis, RabbitMQ, Kafka
- **Producer**
    - Produces tasks to be placed in the queue...to be processed later
- **Worker**
    - Takes tasks from the queue and performs them...   
    - A daemon under supervision

### Gotchas/Rules
- Adding tasks to the Queue should be faster than the task itself
- Rate(Producing tasks) < Rate(Consuming tasks). Else ,scale up the workers.

### Sidenotes
Very similar concept is "EventLoop" or [Event Driven Asynchronous I/O](http://docs.libuv.org/en/v1.x/design.html) JS event loop, python gevent etc, python asyncio..async def ..asgi..etc. <br/>



"Workers" in Queues are usually separate processes on their own! = Heavy <br/>
**In EventLoop... a single goddamn thread can achieve the same behavior! = Light AF <br/>**




