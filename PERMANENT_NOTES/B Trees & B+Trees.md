**Model your data as a TREE on DISK**
\>>> Biggest Downside is unlike LSMTrees(memtable in RAM), here we don't write to RAM first and write directly to disk.


> _overwrites values... in contrast to log structured where values are just appended, and merged asynchronously._
> 

k-v pairs are **sorted** by Key on disk. (similar to SSTables)
- Lay out data in "pages" on disk. Each page can store references to multiple other pages. *The number of references to other pages = "branching factor"*. page size = 4KB. same as "blocks" on the disk. 
- keys on every "page" are in sorted order. 
- Each "page" is a node in the BTree. 
- Read/write one "page" at a time.
- Only the leaf node "pages" contain the values. 
- To read, you begin at root page, and traverse all the way upto the leaf page to obtain the value.
- Height of most BTrees is upto 4. (Can store upto 256TB)
- Algo ensures that tree remains balanced. Height = O(LogN) always.
- For Crash Recovery -> Write Ahead Logs (WAL)
- For Concurrency -> Lightweight locks or Latches before write.
	- You do all this locking because you are OVERWRITING. Had you followed log structured approach, you'd just keep appending and never overwrite old values, you wouldn't have to worry about concurrency and thread safety. 
	- This is one of the main reasons why WRITES ARE SLOW on BTrees., because of LOCKS! 
		- Incoming writes are blocked. In contrast to log structured where incoming writes keep appending without any lock/block. And compaction happens asynchronously in the background. 
- Optimisations
	- Since sequential scans happen often, its good to try and lay out all leaf nodes side by side on disk
	- Or atleast keep pointers left and right on all leaf nodes.

![[ddia-18.png]]

For Updates, you reach the leaf page, overwrite the value and write out the entire page back to disk.
For Inserts, you reach the leaf page and insert the key and value (ensuring the page is still sorted by keys), and write out the entire page back to disk. If the page doesn't have enough space.. You break the page into 2. The parent page is updated to account for new subdivision of the leaf page.

![[ddia-19.png]]

For Crash Recovery
- WAL (Write Ahead Logs)
