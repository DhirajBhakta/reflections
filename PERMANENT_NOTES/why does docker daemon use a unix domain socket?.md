Docker daemon is bound to a Unix domain socket. Unix Domain sockets are used for IPC within the SAME HOST, and are **faster and has less overhead** than localhost socket (IP:PORT) since you **don't have to go through the entire network stack**.

At very high loads, unix domain sockets provide 50% more throughput compared to internet sockets, and sometimes 1/3rd the latency of internet sockets!

> Unlike internet sockets (AF_INET) where the socket is bound to a unique IP+PORT, a Unix domain socket is **bound to a file path**. 