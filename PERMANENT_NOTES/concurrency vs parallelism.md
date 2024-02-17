Concurrency is starting a lot of things, and context switching such that you're doing ONE thing at any given time.
Parallelism is starting a lot of things, and running ALL of them at any given time.
![[js-00.png]]

![](js-05.png)

![](js-06.png)

- Goals of Concurrency|Asynchronicity
    - To have a non blocking application
    - To make your application usable (should not hang)
    - **NOT** to increase performance
    - You can do concurrency in just **one thread**. Event loop for example. One thread can time slice between tasks...
    - Every concurrent application is not a candidate for being parallel. Chatty threads (threads depending on each other), are not meant to be run parallely.
    - Concurrency enables parallelism
    - Concurrency simplifies synchronization
- Goals of Parallelism
    - _speed_ , max performance