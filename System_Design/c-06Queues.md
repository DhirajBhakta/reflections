# Queues

- RabbitMQ
- ActiveMQ

### Why?

imagine a system where writes take long, really long.

- because processing may take time
- because system is under load

Then we need to work in an **Asynchronous** Way, Using QUEUES

### Drawbacks of Synchronous

- client is supposed to WAIT for a long time, doing ZERO work, until the request can be responded to.

### Async

All incoming tasks are added to a queue, and as soon as any **worker** can pick up a task, it is picked from the queue.

Clients DONT get the response immediately, they only get an **acknowledgement** that their request was _ACCEPTED_
