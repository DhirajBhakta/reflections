An Example:
You have implemented rate limiting on your client, which sends only 100 requests at a time to your DB, to avoid choking your DB or not cause denial of service to other important apps hitting the same DB. Yet you see the DB choking and getting DOS'ed. Out of 100 , just one or few of the requests time out. 
**Its only the client that has perceived the request to be timed out, and in actuality, the server was still processing the request**, and then you bombarded it with 100 more requests. This keeps going and the DB chokes eventually. 
All this happened because the client's timeout was less than DB's timeout. 

So the client's timeout should atleast be twice as much as DB's timeout. 

Some drivers can automatically detect this and raise a warning to increase client timeout.

### Speculative retry can be a footgun
Some drivers can be configured to do a speculative retry, i.e retry a query if it "expects" that the call has likely have failed. This can cause choking as explained above.