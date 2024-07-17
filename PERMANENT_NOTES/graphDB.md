TODO:

Interconnected data. Facebook friends..

Neo4J is a native GraphDB.


#### Native GraphDB vs Non-Native GraphDB
_Avoiding the Index_ O(N) vs O(NLogN)

Neo4J is just a linked list on Disk. But on SQL DB's you have to hit the index, do a binary search to get the parentID and its corresponding next child.


#### CONS:
ACID properties
- 2PL locking
On a distributed scale, its hard to ensure consistency..youre forced to use 2PC
