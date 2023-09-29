## Where can a container write data?
- its own writeable layer ( a container is nothing but layers of read only layers and one writable layer on top)
  - this data gets lost on container restart.
- **EmptyDir** type volume
  - is pod level volume, mounted as a volume into the container.
  - has the same life cycle as the Pod
  - useful for temporary storage
  - useful as a local cache (API responses for eg:)
  - if the Pod is restarted, the data survives
  - if the Pod is replaced, the data is lost!
- **HostPath** volume
  - is node level volume
  - if the Pod is replaced, it will have access to the files, but only if it runs on the same node.
  - if the node goes offline, you will lose the data.
  - also, Danger! Mounting a HostPath can give you complete access to the filesystem on the node (if / is mounted)
  - limit what the container can see by declaring subpaths in this case.
  - If node is dead, your data is gone. Also you cannot guarantee pod placement on this node.
- **Persistent Volumes and Claims**
  - distributed storage systems
  - AzureDisk, ElasticBlockStore, NFS, GlusterFS
  - **Note**: there is also a peristentvolume type called "hostPath"  🤷

### EmptyDir
_Transient storage **within the Pod**_
Temporary, Ephemeral storage that can be shared between containers of the same Pod [[#Mount a volume on two containers]]. Temporary...can be used to cache API responses etc.
_Exists for the **Pod's Lifetime**_. When Pod is deleted => data is lost. When the Pod is **restarted** => data survives.
```yaml
volumes:
- name: storage
  emptyDir: {}
```
and mount it to the container by
```yaml
volumeMounts:
- name: storage
  mountpath: /var/lib/data
```


### HostPath
_Borrrow storage from Node's filesystem_
Exposes files on the node to the containers in the Pod.
```yaml
volumes:
- name: storage
  hostPath:
      path: /var/www/html
```
and mount it to the container by
```yaml
volumeMounts:
- name: storage
  mountPath: /usr/share/nginx/html
```

>**Warning**
>There is also a PersistentVolume type called "HostPath"
```yaml
apiVersion: v1
kind: PersistentVolume
metadata:
  name: task-pv-volume
spec:
  storageClassName: manual
  capacity:
    storage: 10Gi
  accessModes:
    - ReadWriteOnce
  hostPath:
    path: "/mnt/data"
```

### PersistentVolumeClaim



## Mount a volume on two containers
_Enable communication between two containers via shared volume_

Sharing storage between two containers on the same Pod. Mount the same volume on both containers to get a shared filesystem(portion of the filesystem).
Useful for sidecars that act as data pullers/data pushers, doing some setup which is used/looked up by the main container.
```yaml
apiVersion: v1
kind: Pod
metadata:
  name: two-containers
spec:
  containers:
  - name: nginx-container
    image: nginx
    volumeMounts:
    - name: shared-data
      mountPath: /usr/share/nginx/html

  - name: debian-container
    image: debian
    volumeMounts:
    - name: shared-data
      mountPath: /pod-data
    command: ["/bin/sh"]
    args: ["-c", "echo Hello from the debian container > /pod-data/index.html"]
	
  volumes:
  - name: shared-data
    emptyDir: {}
```
Since we use `EmptyDir` in this example, **if the Pod is deleted, the data is lost. The volume is deleted too**
