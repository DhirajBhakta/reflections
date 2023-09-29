
## Pod
[[containerPort is merely for documentation]]

## Service
[[kube-proxy and iptables|k8s service is implemented by kube-proxy via iptables]]
[[kube-proxy and iptables#View `iptables` rules for a Service|View iptables forwarding rules for a given Service]]
[[kube-proxy and iptables#`kube-proxy` logs|Check kube-proxy logs to make sure Service creation or Endpoint registration is detected and iptables rules are updated]]

## PV and PVC
[[approaches to give storage to Pod]]
[[approaches to give storage to Pod#EmptyDir|EmptyDir]]
[[approaches to give storage to Pod#HostPath|HostPath]]
_the other widely used approach is ....PVC+PV_

[[PVC and Pods]]
[[PVC and Pods#PVC to PV binding|PVC to PV binding]]
[[PVC and Pods#Deletion of the PVC is manual|Deletion of PVC is manual]]


## Authentication
[[serviceaccounts in k8s]]
## Networking
[[pod networking]]
[[pod networking#CNI Spec|CNI Spec]]
[[pod networking#CNI Plugin|CNI Plugin]]
[[pod networking#CNI Spec|Relation between kubelet, container-runtime and CNI Plugin]]
[[pod networking#Sample implementation of a CNI Plugin|Sample implementation of a CNI Plugin]]


