_Cuz race conditions_

Take two threads that are running concurrently, both threads are running the following instruction
```cpp
x++;
```
Although it seems like an **atomic operation**, its not. `x++` involves the following steps
1. fetch `x` from memory into the register
2. add 1 to `x` in register
3. write back `x` into memory

If both threads did `x++`, one would imaging the value to be incremented TWICE, but you might sometimes see it incremented just ONCE.
1. both fetched `x` from memory into the register
2. both added 1 to `x` in register
3. both wrote `x` into memory

**You solve this using a LOCK , a.k.a MUTEX**

But Mutex is also a variable. Just a number and you spin until the value changes and then you have "acquired" the mutex.
_What if there's a race condition to even acquire the mutex_
=> Mutex implementations in languages depend on the underlying machine instructions which provide a `lock` instruction in ASM which is essentially **atomic**. No other OS thread/process will be able to access that memory location until the current one is done.
Lookup "atomic test-and-set operation" also called **compare-and-set** operations.