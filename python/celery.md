Asynchronously execute work OUTSIDE the HTTP req-resp cycle

# Why??
- You want to offload long running tasks outside the request cycle
- Moving work outside the HTTP request-response cycle is important!
	- Your WSGI server should respond to incoming requests AS QUICKLY AS POSSIBLE
	- bcos each request ties up a worker process UNTIL the response is finished.
	- moving work OFF THOSE WORKERS by spinning up async jobs as tasks in a queue is a straightfwd way to improve WSGI server response times.

## Why not just a Thread?
	- GIL
	- Python is SINGLE THREADED due to GIL
	- Only way out --> multiprocessing (which is what celery does)




# Celery
- distributed TASK QUEUE
