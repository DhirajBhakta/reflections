# Important topics
1. Estimations - get cozy with numbers, for performance/efficiency/volume/cost estimations.

- Scale estimates, justifications for choice of databases, future requirements ...
- Design a full fledged data ingestion layer for Hotstar...


## HTTP status codes

### Broadly

**1xx**: Informational response

**2xx**: Success

**3xx**: Redirection

- further action must be taken by the client to complete the request

**4xx**: Client Error

**5xx**: Server Error

### Specifically

<hr/>

**200**: OK

**201**: OK, resource created

<hr/>

**301**: Permanent Redirect

**302**: Temporary Redirect

<hr/>

**400**: Bad Request

**401**: UNAUTHORIZED

- lacks authentication credentials

**403**: FORBIDDEN

- not authorized to access

**404**: Not found

**429**: Too many requests

<hr/>

**500**: Internal Server Error

**503**: Service Unavailable

# To cover

- Designing a **storage/sharing service**: Dropbox, Youtube, Instagram, etc.
- Designing a service that deals with **geographical data**: Uber, Yelp etc.
- Designing a **social media service**: Facebook, Twitter.
- Designing a **communication service**: Messenger, High traffic web server, etc.
- Designing a **search related service**: Search engine, web crawler, etc.

### Deep Dives

- Redis Deep dive
- Memcached Deep dive
- Apache Kafka Deep dive

### Networking

- TCP/UDP protocol deep dive
- OSI layers deep dive + TCP/IP layers

### Operating Systems

## Links

- <https://github.com/NirmalSilwal/system-design-resources>
- <https://github.com/jguamie/system-design>
- <https://medium.com/javarevisited/10-best-system-design-courses-for-coding-interviews-949fd029ce65>

## SubLinks

- <https://lethain.com/introduction-to-architecting-systems-for-scale/>
