>**Info**
>A given process CAN listen on multiple ports.
>Its just about creating multiple sockets.

## via `netstat` (or `ss`)
```shell
netstat -ap | grep PID
or 
netstat -tupln | grep PID
```

By default `netstat`  or `ss` lists only non-listening sockets. Hence you provide `-a` 
`-l` to show ONLY listening sockets.

However, a process can open one or more ports just for _connecting_ to other listening sockets, to view all ports opened by a PID, remove the `-l` `netstat -tupn | grep PID`