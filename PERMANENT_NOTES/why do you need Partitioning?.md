#### Partitioning—Why do you need it?
- Main reason = scalability
	- add more nodes  => more throughput
- More throughput
	- same query executed on ... many disks, many processors.
	- queries can be parallelised. 
- When one node cannot fit the entire dataset, dataset is too huge.
Each piece of data(row,document) belongs to exactly ONE partition. Although partitions can be replicated across replicas (with leader partition and follower partitions)



#### Goals of Partitioning
- even distribution (data and query load)
	- can 10 nodes handle 10x the load? If only you can avoid hotspots.
- avoid **"hotspots"** : partitions which get (unfair)disproportionately high keys/load... 
	- adding nodes wont help you at all here! negates the benefit of horizontal scaling
- Try to make range queries happen. 