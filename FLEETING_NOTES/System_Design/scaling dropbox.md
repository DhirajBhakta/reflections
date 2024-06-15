Read:Write ratio = 1:1

#### Challenges
- small client that doesn't hog resources
- mobile device with low b/w
- High Write Volume + ACID Requirement = Hard

#### Evolution
- Started out with a single server (DB + server on same machine) and wrote to primary disk.
- Moved out the disk to S3, and moved out DB to separate server.
- Server had to be split into 2 for scaling individually
	- one accepts all uploads: _block server_
	- one for metadata : _metadata service_   <-> Memcached
	- one as _notification service_ <-> Connected to Millions of Devices.
- Memcached added to avoid database scaling/partitoning
- File --> 4MB Chunks --> Chunk--> S3.

#### Scaling the Load Balancer
AWS LB didn't exist back then. Had to design their own HA cluster for LB.