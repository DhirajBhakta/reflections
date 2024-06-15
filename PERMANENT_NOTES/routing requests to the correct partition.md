
#### Partitioning — Request Routing
How does the client know which node to connect to? (IP+Port) ... _**Service Discovery**_ . As partitions get rebalanced, this info changes.

Approaches...
![[ddia-36.png]]
- **Node Hopping** : Clients contact any node, that node will forward to appropriate node if needed.
	- May use "Gossip Protocol"
	- Spread news of partition changes to each other.
- **Dedicated Routing Tier** : Partition-aware Load Balancer.
	- May use separate "coordination service" like ZooKeeper.
	- Each node registers itself to ZooKeeper.
	- ZooKeeper maintains mapping: Partitions<->Nodes.
	- routing tier subscribes to ZooKeeper.
	- Whenever node added/removed, or partition changes/rebalanced.. ZooKeeper **notifies** the routing tier.
- **Thick Client** : Clients are aware of assignment of partitions to nodes. Clients can connect directly to a node _without a middleman_.
![[ddia-37.png]]


