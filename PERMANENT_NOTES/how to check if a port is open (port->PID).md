OR "Which process is listening on a given port?"
## via `netcat`
```sh
netcat -w 2 <host> <port>
## and then check if it succeeded
echo $?
```
eg: `netcat -w 2 localhost 8090`  and then `echo $?`

`netcat` is sort of like `telnet` for checking if connection can be established.
`-w 2` is to specify a timeout, else it can keep hanging. 

> **Info**
> `netcat` can also create a simple server and **listen on a port**. On the other side, as usual, you can use `netcat` to connect to this server.
> This can be extended to even transfer files.

Unlike other approaches like `lsof` or `netstat` or `ss` , this approach does NOT scan all processes to get bounded ports.

## via `lsof`
```shell
lsof -i:<port>
```


## via `netstat` (or `ss`)
```shell
netstat -tupln | grep <port>
```

`netstat` can check ports only on localhost. If you need to check port on a remote host or inside another namespace in the system (eg: containers), you need to ssh into them (or exec)
```shell
kubectl exec python-server-pod -- netstat -tupln | grep <port>
```

> **Info**
> `netstat` is superseded by `ss`

>**Info**
> A socket can be in multiple states 
> - CLOSE
> - LISTEN
> - ESTABLISHED
> -  .. many other states pertaining to SYN/ACK handshakes
> **By default, netstat doesnt show LISTENing sockets**, hence we provide `-l` option as `netstat -tupln` to list listening sockets too.
