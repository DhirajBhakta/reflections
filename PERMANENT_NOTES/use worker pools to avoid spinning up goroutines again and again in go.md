_Set(pool) of pre-initialized goroutines(workers)_
_**Neat trick** using Channels_

Goals:
- limit the concurrency (number of running goroutines)
- Avoid the (small, but can add up) overhead of creating goroutines over and over again.

You have a very large stream of incoming tasks, and you spin up new goroutines for each task.
Instead **REUSE** the goroutines by first creating a pool.


### How it works
_**Channels** are used as Task queue and Result Queue_
```go
func worker(id int, jobs <-chan int, results chan<- int) {
    for job := range jobs {
        // process the job
        results <- job * 2
    }
}

func main() {
    jobs := make(chan int, 100)
    results := make(chan int, 100)

    // Start 3 workers
    for w := 1; w <= 3; w++ {
        go worker(w, jobs, results)
    }

    // Send jobs
    for j := 1; j <= 9; j++ {
        jobs <- j
    }
    close(jobs)

    // Retrieve results
    for a := 1; a <= 9; a++ {
        fmt.Println(<-results)
    }
}
```
