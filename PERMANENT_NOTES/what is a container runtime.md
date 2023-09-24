https://www.youtube.com/watch?v=Utf-A4rODH8
https://opensource.com/article/18/1/history-low-level-container-runtimes
https://www.ianlewis.org/en/container-runtimes-part-1-introduction-container-r

When docker came out, it was doing the following functionalities in a **monolithic way**
- build images
- pull, store, push, delete images
- configure networking
- configure volumes
- create, start, stop , monitor containers

It also...
- assumed a particular container image format

These functionalities _could_ have been factored out into individual pieces which could do one job well. OCI ("Open Container Initiative") was then formed which **standardized the approach of running a container**  and called it "OCI Runtime spec".
`runc` is a **low-level container runtime** which adheres to OCI spec of "running containers". But note that it does  NOT do everything that docker did (listed above), it just took care of spawning containers.  Everything else is taken care by "high level runtime" (which calls the low level runtime)



## Low level Runtime
eg: runc
#### "Running a container" ?
At the lowest level, a container is just cgroups and namespaces. a low-level container runtime does just that, handles kernel calls dealing with creating cgroups and namespaces. The job of the container runtime is ..
1. create cgroup
2. run commands in cgroup
3. `unshare` to move to its own namespaces
4. setting up root filesystem, chrooting the container's process to the root file system
5. cleanup cgroup after command completes

#### Big deal?
not so much.
cgroups, namespaces, security constraints are built into linux kernel, and IF every process has resource constraints, security boundaries, and namepaces...**_then every process could be called a "container"_**. 

>**Info**
>`containerd` and `runc` were factored **out** of docker. So they originally came from docker monolith.

>**Info**
>`containerd` uses `runc` under the hood.
>containerd **outsources** the implementation of running a container to runc.

## High level Runtime
eg: Docker, containerd

![](../../assets/docker-22.png)
If Docker uses containerd internally which in-turn uses runc internally, what value is docker really adding?
containerd, although being a high level runtime, does NOT help you build images, that job is still well done by docker (as a wrapper on containerd).

