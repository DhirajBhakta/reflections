## Session Token authorization

- pass sessionID for every request
- sessionID in cookie Header
- verified with the row in the session table in DB
- cons: assumes just one monolithic server
  - sucks in HA ,LB case
  - use sticky session
- **reference token**

## JWT authorization

- you dont store anything about the session in your DB, unlike session token authorization
- sign the token with private key or HMAC
- verify it every time a request comes
- **value token**
- can be used in cookie or bearer
