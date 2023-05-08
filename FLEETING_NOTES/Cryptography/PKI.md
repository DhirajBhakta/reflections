![[Pasted image 20230401231417.png]]
Asymmetric encryption provides a solid base for **security** and **authentication** ...and is a basis for 
- SSL/TLS
- SSH
- PGP
- RSA, ECC
https://www.golinuxcloud.com/openssl-create-client-server-certificate/

# Digital Certificate (Public key certificate)
- digitallly signed by the private key of the CA (Certificate Authority)
- issued **by** the CA **for** the owner.
- this CA is responsible for confirming the authenticity of this certificate's owner
- Contains the owner's public key and owner's details
- format=CRT (not PEM!!)
- When we request for a certificate from a CA, we get
	- digitally signed certificate
	- CA public key
- Note: we blindly trust the CA

![[Pasted image 20230402011422.png]]
1.  Create a **certificate signing request (CSR)** with a private key. A CSR contains details about location, organization, and FQDN (Fully Qualified Domain Name).
2.  Send the CSR to the trusted CA authority.
3.  The CA authority will send you the SSL certificate signed by their root certificate authority and private key.
4.  You can then validate and use the SSL certificate with your applications.

## Self signed certificates
https://devopscube.com/create-self-signed-certificates-openssl/
![[Pasted image 20230402011504.png]]
1.  Create our own root CA certificate & CA private key (We act as a CA on our own)
2.  Create a server private key to generate CSR
3.  Create an SSL certificate with CSR using our root CA and CA private key.
4.  Install the CA certificate in the browser or Operating system to avoid security warnings.


### Create self signed certificate with openssl (long way)
First create the "CA". We create CA's private key and CA's root certificate (root CA)
- CA private key
- root CA
```
openssl req -x509 \ 
            -sha256 -days 356 \ 
            -nodes \ 
            -newkey rsa:2048 \ 
            -subj "/CN=demo.mlopshub.com/C=US/L=San Fransisco" \ 
            -keyout rootCA.key -out rootCA.crt
```

Create the server's private key (owner private key)
```
openssl genrsa -out server.key 2048
```

Create CSR (Certificate signing request)
```cat > csr.conf <<EOF 
[ req ] 
default_bits = 2048 
prompt = no 
default_md = sha256 
req_extensions = req_ext 
distinguished_name = dn 

[ dn ] 
C = US 
ST = California 
L = San Fransisco 
O = MLopsHub 
OU = MlopsHub Dev 
CN = demo.mlopshub.com 

[ req_ext ] 
subjectAltName = @alt_names 

[ alt_names ] 
DNS.1 = demo.mlopshub.com 
DNS.2 = www.demo.mlopshub.com 
IP.1 = 192.168.1.5 
IP.2 = 192.168.1.6 EOF
```

```
openssl req -new -key server.key -out server.csr -config csr.conf
```


Create the certficate 
```
cat > cert.conf <<EOF

authorityKeyIdentifier=keyid,issuer
basicConstraints=CA:FALSE
keyUsage = digitalSignature, nonRepudiation, keyEncipherment, dataEncipherment
subjectAltName = @alt_names

[alt_names]
DNS.1 = demo.mlopshub.com

EOF
```

```
openssl x509 -req \ 
             -in server.csr \ 
             -CA rootCA.crt -CAkey rootCA.key \ 
             -CAcreateserial -out server.crt \ 
             -days 365 \ 
             -sha256 -extfile cert.conf
```

server.crt is the certificate to be used by the server.
server.key is the private key of the server

### Create self signed certificate with openssl (short way)
```
openssl req -x509 -sha256 -nodes -days 365 -newkey rsa:2048 -keyout privateKey.key -out certificate.crt
```

Note that the short way DOES NOT output the rootCA and CA's private key. Probably using a default. Unless you have the rootCA, you cannot get browsers to trust this digital certificate...which kinda makes this approach useless. Just go for the long approach.


### what is the problem with self signed certificate?


## What is x.509?
Its a standard format for certificates.



# openssl commands

### Create a private key
```
openssl genrsa -out server.key 2048
```

### Generate public Key (derive) from a private key
```
openssl rsa -in mykey.pem -pubout > mykey.pub
```
Why does this work? public key is (n,e) and private key is (n,d, p, q)... e is modulus multiplicative inverse of `totient(n)`. and `totient(n) = (p-1)(q-1)`


### Get the details of a private key
```
openssl rsa -text -in mykey.pem
```



### Other random commands...
```
openssl genrsa -out private.pem 1024   #generate private key file
openssl rsa -in private.pem -text      #view info in the private key file
openssl rsa -in private.pem -pubout -out public.pem  #extract public key to file
openssl rsa -in public.pem -pubin -text  #view info in the public key file
```

# Questions
- what is x509 ?
- what is root CA and intermediate CA?
- what is CSR ? what does it contain?
- how to generate client certificate and server certificate?



# References
- https://www.golinuxcloud.com/tutorial-pki-certificates-authority-ocsp/ 