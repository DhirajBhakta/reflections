# K8s the hard way
- Video : he's using baremetal for the entire setup, not GCP as recommended by Kelsey Hightower.- 3 master nodes + 3 worker nodes. (ubuntu containers)
	- each with 2 CPu 2 Gigs RAM
- Need a HAProxy load balancer since this is a multi master setup. Worker nodes dont directly get to talk to a master node, it goes throug the HA Proxy.
- Each master node will have its own etcd node as well. But for a good HA system, etcd cluster should have its own dedicated notes.
- sessions:
	- installing client tools
	- CAs. certficate key pairs for "authorized clients" who use the Kube API.
	- Generate and copy kube config to all worker & master nodes.
	- Data encryption at rest. Encryption key and config. & copy to master nodes.
	- Bootstrap the etcd cluster, node by node .(3)
	- Bootstrap the master nodes, - Api server, controller manager, scheduler, node by node (3)
	- Bootstrap the worker nodes. - kubelet, kubeproxy, containerd, CNI networking config. (3)	
		- Allow pod networks to communicate between hosts..Create routes.Add route for each worker node on the host machine.
- The Kubernetes networking model assumes a flat n/w in which containers and nodes can communicate with each other. In cases where this is not desired, network policies can limit how groups of containers are allowed to communicate with each other and external n/w endpoints.
(VPC)


# Detailed steps:
- Installing client tools
	- cfssl, cfssljson , kubectl
- Setup a dedicated VPC to host the k8s cluster.
- generate and distribute certificates and keys to master and worker nodes.
- generate kube configs for all kubelets in each worker, kube-proxy in each worker(same), kube-controller-manager in each controller(same), kube-scheduler in each controller(same), and a kubeconfig file for the admin user.
	- kubectl config set-cluster
	- kubectl config set-credentials
	- kubectl config set-context
- generate encryption config yaml and distribute it to all controllers.
- bootstrap the etcd cluster
	- kubernetes components are stateless, and store the cluster state in etcd.
- bootstrap the control plane
- bootstrap the worker nodes
	- why did we install socat, conntrack, ipset in each worker?

# To research
- etcd
- Why etcd needs a "cluster"? why HA for etcd?
- kubeproxy
- contianerd
- runc
- coredns
- cni
- cluster CIDR
- ssl certificates and keys and why of distributing them
- <research> Lab04 and Lab05




