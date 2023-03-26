# Proxy server

### How do the env variables HTTPS_PROXY HTTP_PROXY ALL_PROXY work underneath?

## mitmproxy

## SOCKS protocol

## NAT


A NAT device performs "address translation" (tuple [TCP/UDP port:IP address] to another tuple) whereas a proxy terminates (in networking terms) a protocol layer, performs adaptation (again in networking terms) and rebuilds another a connection towards the destination.

In other words, a NAT tries to be as "transparent" to the client protocol as can be whereas a PROXY is really "two connections back-to-back" (same or different protocols on each side).


https://portforward.com/

https://superuser.com/questions/284051/what-is-port-forwarding-and-what-is-it-used-for