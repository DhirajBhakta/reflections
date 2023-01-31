### DB lineage [ IMS -> RDBMS -> NoSQL ]
#### 1966 : Hierarchical Databases 
- IMS (Information Management system)
- Invented in IBM
- became de-facto very quickly
- Used for Saturn V moon rocket.
- IBM DB2

#### 1970 : Relational Databases
- Edgar F. Codd
- Current de-facto


### What's wrong with RDBMS?
- **scalability problems** ..when you become successful and usage goes up.
- **joins are slow**
- **locking for the sake of consistency of transactions** is costly 
- **vertical scaling** is the only option
- When everything else fails, you try to **optimise at application layer**, moving things to stored procedures etc.
- You end up adding **caching layer**  and then deal with consistency problems b/w cache and DB
- You **denormalize the DB** to improve performance, working against the tool.
-synch **DATABASE IS ALMOST ALWAYS THE BOTTLENECK TO SCALE**

