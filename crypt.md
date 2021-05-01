

# Ciphers
Ciphers are **algorithms** to perform encryption, decryption, digital signatures or hashing.
## Symmetric
_faster & older_

Blowfish, AES, DES, RC4, RC5 and RC6.

##### Most widely used
AES-128, AES-192, and AES-256.


## Asymmetric
_slower and newer_

RSA, DSA

# Public Key Infrastructure
_its not just publickey+privatekey_

PKI (Public Key Infrastructure) is a set of rules, procedures and policies that are needed to create, distribute, manage, store, use or revoke certificates and manage public-key encryption.

## Key components of PKI
- Certificate Policy
- Root CA
    - Main root of trust
    - accountable for identitiy authentication
- Intermediate CA
    - certified by a root CA
    - used to sign and issue digital certs
- Certificate DB
- Revocation Services
- Digital Certificates
    - Digital identity issued by intermediate CA

![](https://aboutssl.org/wp-content/uploads/2020/11/public-key-infrastructure-hierarchy.png)

The Root CA provides the rights to subordinateCA(intermediate CA) to sign digital certs for devices.

This heirarchy allows the rootCA to go offline ( good for security )

### Trust Hierarchy
How to trust a server? => through the SSL cert it gives<br>
How to trust the SSL cert? => through the CA that issued that cert<br>
How to trust the CA????

#### What is a CA?
They issue SSL certs<br>
They are a "trusted" 3rd party

#### What are root programs?
Root program runs some policies and validates requirements before adding a CA to the trusted root store.

Some globally known root programs 
- Apple Root Program
- Oracle Java Root Program
- Mozilla Root Program
- Microsoft Root Program

Also btw, the browser/OS comes with a set of already trusted CAs

#### Root Certificate
A public key cert which helps identify a root CA

They are self signed ( forming the basis of X.509 based PKI)

They are used to issue other certs

#### Intermediate Certificate
Provides security to the Root Certificate

Also works as a trusted root to issue certs

#### Leaf Certificate ( the final SSL cert)
A leaf certificate, also known as the end-entity certificate, is the last non-CA certificate of the chain which consists of a public key which is used by the users. These are the end-users’ SSL Certificates which is not directly issued by the Certificate Authorities from their roots, as those roots are much valuable and a lot of risks are involved around it.

#### Chain of trust
Security provided by SSL certificates is based on a Chain of Trust that originates from the Root Certificate of Certificate Authorities like Sectigo, DigiCert, GeoTrust, etc to the user’s certificate. And further, these SSL certificates are accepted by popular web browsers that contain the validated digital signature of the CA. Though the CA’s identity is built by adding the root certificates in the web browsers and without that, no browser would know whether to accept an SSL Certificate issued by a CA.

Furthermore, the Certificate Authorities are very strict with their guidelines and to guard their Root Certificates from getting compromised, they use an Intermediate Certificate which helps in issuing the user’s end-entity or leaf certificate.
![](assets/chainoftrust-02.png)

Moreover, Digital Certificates are verified via a chain of trust which is a list of certificates in an order. This contains End-Entity Certificate (Leaf Certificate), Intermediate Certificate and Root Certificate, where the root certificate authority (CA) is the trust anchor for the digital certificates.










