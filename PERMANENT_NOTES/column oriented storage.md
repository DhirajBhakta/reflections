#### OLAP — Column Oriented Storage
_enables compression -> smaller size --> can fit in L1 cache --> reduces CPU cycles for a query -> SIMD -> vectorized processing(Bitwise&|) --> extremely fast!_

All values in a given column are laid out next to each other, say in a single file meant for the column. If you want to reconstruct the row, you visit the Nth value in each column file.

Read performance would suck for OLAP queries if you had row-oriented storage. For a query that requires just 3 out of 100 columns, you would have to load ALL the rows (containing ALL the 100 fields) from disk into memory, parse them, and filter out the rows that you don't need.(and also wasteful column loading.)
![[ddia-22.png]]
![[ddia-23.png]]


#### OLAP — Column Oriented Storage — Compression 
If a given column file contains a lot of repeated values, then its a **good candidate for compression**.
- compression helps increase CPU L1 cache hit rate, best for reducing branch misprediction and heavily reducing CPU cycles to execute the query. using SIMD to its fullest.
	- (so small that it fits in the CPU cache)
	- _tight loop_ where memory access is minimal.
- compression helps perform bitwise AND , bitwise OR to get desired result..all loaded from L1 cache (optimistically). Avoiding function calls and just doing bitwise operations ...this is called **vectorised processing** in CPU jargon.
How to compress?
- Bitmap encoding
	- Say you have the column file of "age" column: 32, 10, 4,10,10,10, 32, 30
	- then 32 will be encoded as "10000010"
	- then 10 will be encoded as "01011100"
	- then 4 will be encoded as "00100000"
	- then 30 will be encoded as "00000001"
	- Compressed column file will now have : 1000010, 01011100, 00100000, 01011100, 01011100, 01011100, 10000010, 00000001 
	- _give me the total number of people with age=10 or age=32_
		- load the bitmap for 32 and 10 and do bitwise OR.
		- you get 11011110.
		- count the number of "1"s , = 6
		- Imagine the efficiency of doing all this by just loading 2 integers (one for each bitmap value) and doing a bitwise OR in a single CPU cycle, values loaded from the L1 cache! 
			- now imagine doing multiple such bitwise operation in a single CPU cycle thanks to vectorized processing with SIMD !
- Run-length encoding

Downsides
- Writes are really slow.
	- Can use LSMTrees to solve this problem.