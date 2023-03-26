# Functional requirements

- password authN
- (?)google, FB, twitter login SSO???
- email verification
- 2FA
- access token
- refresh token
- /logout
- /password-change

## Tokens

- opaque vs structured

## JWT

- signed with public/private key pair or HMAC
- can be validated locally in the server
- iss: issuer
- exp: expiry timestamp
- aud: audience
- sub: subject
- name:
- roles: [.....]

## JWT

- decode it on the server
- verify it on the server
- check if not expired
- check for roles in the decoded body < authZ >
- expose a endpoint to publish public key /publik
- refresh token endpoint to refresh JWTs /refresh
- logout: revoke the refresh token /api/logout
- **JWTS are short lived: 2mins**
