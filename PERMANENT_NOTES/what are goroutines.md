_"Lightweight Threads" managed by **go runtime**_
- capable of running concurrently, Efficiently making use of multi core processes.
- 1000s can run concurrently scheduled on a single CPU thread.
- The cost of creating a goroutine is incredibly small compared to threads.
- cheap to create
- cheap to switch between (context switching)
[[process vs threads vs event loops vs goroutines]]
[Performance without the event loop | Dave Cheney](https://dave.cheney.net/2015/08/08/performance-without-the-event-loop)
```go
func printNumbers() {
    for i := 1; i <= 5; i++ {
        fmt.Println(i)
    }
}

func main() {
    go printNumbers()
    fmt.Println("Main function")
    time.Sleep(time.Second) //Adding sleep to wait for goroutine to complete.
}
```
### What are "Lightweight Threads"
[Performance without the event loop | Dave Cheney](https://dave.cheney.net/2015/08/08/performance-without-the-event-loop)
Go's runtime includes a **Scheduler** => manages goroutines
- automatically starts/suspends goroutines as needed
- maintains the **pool** of goroutines => distributes them across CPU cores..by **multiplexing** available goroutines into a (smaller)set of CPU Threads managed by the go runtime
- uses **Cooperative Scheduling**
	- goroutines VOLUNTARILY yield control at specific points in their execution (contrast this with the CPU scheduler which PREEMPTS processes for context switching out of nowhwere)
	- specific points of yielding control = channel operations, I/O operations (file/network), function calls
	- Prevents the need for explicit locking and contention
- If a certain goroutine blocks the associated CPU Thread(eg: for file I/O), then another goroutine would be scheduled on another CPU Thread. _CPU is always kept busy_




### Mutexes
_Its like a LOCK_[[lock vs mutex vs semaphore]]
_Allow only ONE goroutine to have exclusive access to a shared resource._
- prevents race conditions
eg: why do you need a counter for something as simple as `counter++`? An increment involves loading the variable to a register, reading the value of the register, adding 1, and writing it back. **If two Threads** do this at once, then instead of adding 2, you end up with just a single increment.
_tldr; counter++ operation is NOT atomic._
```go
import (
    "sync"
    "time"
)

var counter int
var mu sync.Mutex

func increment() {
    mu.Lock()
    counter++
    mu.Unlock()
}

func main() {
    for i := 0; i < 10; i++ {
        go increment()
    }
    time.Sleep(time.Second) //Adding sleep to wait for goroutines to complete.
    fmt.Println("Counter:", counter)
}
```
### Waitgroups
_To WAIT for all goroutines to be DONE executing... to proceed further_
_Similar to `join` in Threads_

eg: Ensure that the `main` function waits for all goroutines to complete processing the files
```go
package main

import (
	"bufio"
	"fmt"
	"os"
	"sync"
)

func countWords(filename string, wg *sync.WaitGroup) {
	defer wg.Done()

	file, err := os.Open(filename)
	if err != nil {
		fmt.Printf("Error opening file: %s\n", filename)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	wordCount := 0

	for scanner.Scan() {
		words := scanner.Text()
		wordCount += len(words)
	}

	fmt.Printf("File: %s | Word Count: %d\n", filename, wordCount)
}

func main() {
	var wg sync.WaitGroup
	files := []string{"file1.txt", "file2.txt", "file3.txt"}

	for _, file := range files {
		wg.Add(1)
		go countWords(file, &wg)
	}

	wg.Wait()
	fmt.Println("All file processing completed!")
}
```


### Atomic Operations
_Manipulate shared variables WITHOUT the need for Locks(mutex)_
- atomic, free from race conditions
---
## Concurrent Programming examples
##### Speeding up Merge Sort with goroutines
```go
package main

import (
	"fmt"
	"sync"
)

func merge(left, right []int) []int {
	result := make([]int, len(left)+len(right))
	
	i, j := 0, 0
	for i < len(left) && j < len(right) {
		if left[i] < right[j] {
			result[i+j] = left[i]
			i++
		} else {
			result[i+j] = right[j]
			j++
		}
	}
	
	for i < len(left) {
		result[i+j] = left[i]
		i++
	}
	
	for j < len(right) {
		result[i+j] = right[j]
		j++
	}
	
	return result
}

func mergeSort(arr []int) []int {
	if len(arr) <= 1 {
		return arr
	}

	mid := len(arr) / 2
	var left, right []int

	// Use a WaitGroup to wait for goroutines to finish
	var wg sync.WaitGroup

	// Sort the left half concurrently
	wg.Add(1)
	go func() {
		defer wg.Done()
		left = mergeSort(arr[:mid])
	}()

	// Sort the right half concurrently
	wg.Add(1)
	go func() {
		defer wg.Done()
		right = mergeSort(arr[mid:])
	}()

	// Wait for both goroutines to finish
	wg.Wait()

	return merge(left, right)
}

func main() {
	arr := []int{38, 27, 43, 3, 9, 82, 10}
	fmt.Println("Unsorted:", arr)
	sorted := mergeSort(arr)
	fmt.Println("Sorted:", sorted)
}
```

---
# Debugging Random Goroutine/Channel/Waitgroup bugs

#### Closures and goroutines
```go
for i := 0; i < 3; i++ {
    go func() {
        fmt.Println(i)
    }()
}
// Prints 2 2 2 (but you expected 1 2 3)
```
This is due to **Closures**. By the time the goroutines are executed, the for loop would have finished, and the goroutines _capture_ the current value of the loop variable which is 2. Hence you print 2 2 2.
Solution:
```go
for i:=0; i<3; i++{
   go func(j int){
       fmt.Println(j)
   }(i)
}
```

#### Stuck main method (Deadlock)
```go
package main
import (
	"fmt"
	"net/http"
	"sync"
)

func getTitle(url string, wg *sync.WaitGroup, titleCh chan<- string) {
	defer wg.Done()

	fmt.Printf("fetching URL: %s...\n", url)
	resp, err := http.Get(url)
	if err != nil {
		fmt.Printf("Error fetching URL: %s\n", url)
		return
	}
	defer resp.Body.Close()
	fmt.Println("done..")
	titleCh <- resp.Status
}

func main() {
	var wg sync.WaitGroup
	titleCh := make(chan string)

	urls := []string{
		"https://www.google.com",
		"https://www.google.co.in",
		"https://www.bytebytego.com",
	}

	for _, url := range urls {
		wg.Add(1)
		go getTitle(url, &wg, titleCh)
	}
	// never reaches here.. because nobody has read from the channel yet.
	// DEADLOCK. wg.Wait is waiting for goroutines to finish, and goroutines are waiting for someone to read the value from the channel
	// Solutions:
	// - keep reading from the channel in a separate goroutine.
	// - wait and close the channel in a separate goroutine.
	wg.Wait()
	close(titleCh)

	for title := range titleCh {
		fmt.Println("Title:", title)
	}
}
```
We're using an **Unbuffered Channel** here. 
- Only ONE value can be written to the channel and it will block until the recipient reads the value. **you can only write to a channel if the receiver is ready, else the writer will block** (value not yet written to channel).
- First goroutine cannot even write to the channel(blocked)
- Second  goroutine cannot even write to channel(blocked)
- Third goroutine cannot even write to channel(blocked)
- main method(culprit)(was supposed to read from the channel) cannot read from the channel because its blocked on `wg.Wait()`, its waiting for the goroutines to finish
- Classic DEADLOCK!

Solution:
- Schedule another goroutine and WAIT for the goroutines to end there,and then close the channel.
```go
for _, url := range urls {
		wg.Add(1)
		go getTitle(url, &wg, titleCh)
	}
	go func(){
		wg.Wait();
		close(titleCh)
	}()

	for title := range titleCh {
		fmt.Println("Title:", title)
	}
}
```

