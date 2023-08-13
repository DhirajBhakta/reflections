You need a CA to sign certs. 

For self-signed certs, **you create your own CA**. a "CA" here would just be
- a private key (ca.key)
- a root CA certificate (ca.crt)
```bash
# create private key for CA
openssl genrsa -out ca.key 1024

# create a cert for the CA, signed by its own private key
openssl req -new -key ca.key -subj "/CN=LOCAL_CA" -out ca.csr
openssl x509 -req -in ca.csr -signkey ca.key -out ca.crt
```

> _You **could** now use this key+cert (ca.key+ca.crt) as server's key+cert, and add the cert(ca.crt) into browser/client's trust store to allow it to trust the server. But  you are not really creating a "CA" here, so lets not do that...

Now to create server certificate(using the CA above) and key 
```bash
# create private key for server
openssl genrsa -out server.key 1024

openssl req -new -key server.key -subj "/CN=my-server" -out server.csr
openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -out server.crt
```


If there was an mTLS setup, you would have to create cert+key for the client as well. 
```bash
#create private key for the client
openssl genrsa -out client.key 1024

openssl req -new -key client.key -subj "/CN=client-01" -out client.csr
openssl x509 -req -in client.csr -CA ca.crt -CAkey ca.key -out client.crt
```

> Here we used the same CA for signing the client cert, but the client **can** be signed with a different CA altogether. In such cases, the server needs to be made aware of such CAs by adding the CA's root/intermediate cert into the server's trust store. Usually passed as a startup argument to the server...

### Verfication on the client side
The "Issuer" is derived by inspecting the presented (server)certificate. The issuer's public key is looked up from the trust store of the client/ Host OS. The cert's signature is attempted to be decrypted by the the issuer's public key. If yes, the server cert is trusted by the client. Why? : If the cert was "signed" by CA, it means it was signed by the CA's private key. Now if you can decrypt it with CA's public key , it confirms the claim that the cert was indeed issued by the claimed CA. 

> the issuer's "public key" =  CA's intermediate certificate or rarely, CA's root certificate.


Check this output for an example server cert that was self signed using the short command. 
Note that the "Issuer" is same as "Subject". They have the same attributes. CN, C, ST..so on.
![[ssl-01.png]]




# Short command to generate self signed cert + key
```bash
openssl req -x509 -newkey rsa:2048 -keyout key.pem -out cert.pem -days 365
```
You can observe that there is **no CA involved here** , but why?

In this case, the generated key+cert are BOTH server key+cert AND CA key+cert. If these are supplied to a server as server key+cert, then a client, say a browser needs to "trust" it.. So you add the server cert in the browser's trust store / OS's trust store `/usr/local/share/ca-certificates` and run `sudo update-ca-certificates`. 

