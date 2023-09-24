CRI-O is a container runtime **specially made** for kubernetes, and nothing else. 

Whereas other runtimes like containerd, docker serve a lot of usecases (including kubernetes), CRI-O is built just to satisfy the CRI spec created by kubernetes. Other runtimes resort to writing shims to comply to kubernetes (eg: dockershim, cri-containerd), CRI-O doesn't need to do this.
