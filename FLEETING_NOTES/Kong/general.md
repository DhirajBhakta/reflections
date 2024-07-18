### ??
- KongManager vs Konga?


#### Concepts
**Services** and **Routes** let you expose your services to clients via KongGW.

**Service**: Represents the backend API.
**Routes**: Represends what is exposed to clients.
![[kong-00.png]]



#### Why have two metaphors "Services" and "Routes"?
Say you want to rate limit only the external clients and not internal clients to same service.
Two **Routes** can be created for same service /external and /internal and only /external **Route** can have a rate limit policy attached.



