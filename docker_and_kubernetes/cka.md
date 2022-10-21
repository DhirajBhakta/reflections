
### Materials
- K8s Official K8s documentation https://kubernetes.io/docs
- John Tucker Youtube CKA videos

### Insights
- You CAN have everything in one node! Control plane on the same node, etcd service on same node, same node acts as worker node too.
- HA: multiple nodes for control plane nodes; multiple nodes for hosting etcd; multiple worker nodes. 




### 01
- "Control Plane" - 
- "etcd" - database 
##### Networking
Simplest way is one public subnet, and dump everything there.
Secure way is to have a private subnet with etcd, control plane, worker nodes etc; and public subnet for front facing load balancers etc.
