# Proxies

- sits between client and server
- receives requests from client --- relays them to servers
- can filter requests
- can log requests
- can transform requests
  - add/remove headers
  - encryption/decryption
  - compression
- can cache the responses

## Collapsed forwarding

piggy backing multiple clients on a single origin server connection.

Allow parallel requests for the same object(URI) to be **collapsed into a single request**
![](https://raw.githubusercontent.com/trickstercache/trickster/main/docs/images/basic-collapsed-forwarding.png)

- say client node 1 requested for data X and it is not in the cache
- say client node 2 requested for data X and it is not in the cache
- say client node 3 requested for data X and it is not in the cache
- then the proxy can collapse all the requests and make ONE request to the origin to obtain data X and then pass on the results to node 1,2,3
