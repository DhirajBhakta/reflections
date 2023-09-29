#kubernetes #authentication #authorization #serviceaccounts
_For Pods to access `kube-apiserver`'s APIs_

Your Pod might want to run some `kubectl get pods` or some other kubectl command (specifically, kube-apiserver's API). It needs to authenticate as a "bot" or a **serviceaccount**. 

Every namespace has a `default` serviceaccount, and all Pods use this by default.
You can create one too.

The auth token is mounted at `/var/run/secrets/kubernetes.io/serviceaccount/token`


### Create a serviceaccount
```sh
kubectl create serviceaccount test-sa
```

### Create a token
Create a temporary auth token for the serviceaccount.
Tokens are requested directly with the 'TokenRequestAPI' of kube-apiserver.
```sh
kubectl create token test-sa
```