_Cooperative multitasking_

### Cooperative vs Preemptive multitasking
cooperative: yield the control back to the scheduler
preemptive: scheduler steals back the control out of nowhere. 


### Processes | Threads | Coroutines
https://youtu.be/GSiZkP7cI80?si=qij6GoSrOEqGmhn4
Processes
- one stack+heap per process
Threads use preemptive multitasking. 
- more threads means more context switching. might get context switched at a critical time.
- all threads use same stack and heap.
Coroutines use cooperative multitasking.


### Generators are coroutines!
...


### The event loop

```python
def wait(ts: Iterable[Task]) -> List[Any]:
	orig: List[Task] = list(ts)
		pending: Set[Task] = set(orig)

	while pending:
		for task in list(pending):
			task.run()
			if task.ready():
				pending.remove(task)
	return [task.result() for task in orig]
```