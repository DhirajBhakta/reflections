_Consensus_
_..To implement LOCKs_
_..To elect LEADER_



PAXOS was created to achieve _consensus_ on a single value on an _unreliable network_. 

4 phases, and you need MAJORITY of votes in each phase

#### Promise Phase
The node asks all other nodes if they PROMISE to accept the value (when it eventually provides the value later)

#### Commit Phase
The node asks all other nodes to COMMIT the value
eg: value = fact that _Alice has booked seat#2_
