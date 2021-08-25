<h2 style="color:white;background-color:#777; padding:2em; border-radius:4px; box-shadow:0 0 4px black; border:none">
    Do you want this client to do what its asking to do?
    <button style="color:white; background-color:green">Yes</button>
    <button style="color:white; background-color:red">No</button>
</h2>

### The Goal
![](https://learning.oreilly.com/api/v2/epubs/urn:orm:book:9781617293276/files/OEBPS/Images/01fig02.jpg)

#### Approach 1: replay the user password
#### Approach 2: developer key
This has the benefit of not exposing the user’s credentials to the client, but at the cost of the client requiring a highly powerful credential. Our printing service could print any photos that it wanted to at any time, for any user, since the client effectively has free rein over the data on the protected resource.
#### Approach 3: service specific password that limits access




#### LDAP
a client application collects credentials directly from the user and then replays these credentials to the LDAP server to see whether they’re valid. The client system must have access to the plaintext password of the user during the transaction; otherwise, it has no way of verifying it with the LDAP server. In a very real sense, this method is a form of man-in-the-middle attack on the user, although one that’s generally benevolent in nature.

To continue to act as the user, the client has to store the user’s password in a replayable fashion (often in plaintext or a reversible encryption mechanism) for later use at the protected resource.


the client application is impersonating the resource owner, and the protected resource has no way of distinguishing a call directly from the resource owner from a call being directed through a client. 

What if you wanted to limit the access to the client?
What if you wanted to turn off the access anytime?
# Oauth
- security protocol to protect web APIs
- Oauth is about 
    - how to get a token and 
    - how to use a token
- Oauth IS NOT an authentication protocol
# Oauth2.0
RFC definition ---
>The OAuth 2.0 authorization framework enables a third-party application to obtain limited access to an HTTP service, either on behalf of a resource owner by orchestrating an approval interaction between the resource owner and the HTTP service, or by allowing the third-party application to obtain access on its own behalf.

**A client application** wants to gain access to a **protected resource** on behalf of a **resource owner** (usually an end user)
- **resource owner**
    - has access to an API 
    - _delegates_ access via confirmation on browser
- **protected resource**
    - the API
- **Client application**
    -  ノಠ_ಠノ

<hr style="background:black; border-radius:50%"/>



- a delegation protocol
> letting someone who controls a resource allow a software application to access that resource on their behalf without impersonating them

>it provides a means by which a client can request that a user delegate some of their authority to it. The user can then approve this request, and the client can then act on it with the results of that approval.
- The application (who wants the resource) requests authorization from the owner of the resource
- The application recieves tokens to access the resource.
    - token = `delegated` right of access
    - token = `valet key`
    - OAuth tokens can limit the client’s access to only the actions that the resource owner has delegated.
    > The valet key of a car allows the owner of the car to give limited access to someone, the valet, without handing over full control in the form of the owner’s key. max distance, limited access inside the car..automatic shutoff etc.


#### Authorization Server (AS)
The authorization server (AS) is trusted by the protected resource to issue special-purpose security credentials—called OAuth access tokens—to clients.
>To acquire a token, the client first sends the resource owner to the authorization server in order to request that the resource owner authorize this client. The resource owner authenticates to the authorization server and is generally presented with a choice of whether to authorize the client making the request. The client is able to ask for a subset of functionality, or scopes, which the resource owner may be able to further diminish. Once the authorization grant has been made, the client can then request an access token from the authorization server. This access token can be used at the protected resource to access the API, as granted by the resource owner
![](https://learning.oreilly.com/api/v2/epubs/urn:orm:book:9781617293276/files/OEBPS/Images/01fig08_alt.jpg)


This is a general overview of how the OAuth protocol works, but in fact there are several ways to get an access token using OAuth. We’ll discuss the details of this process in chapter 2 by looking in more detail at the authorization code grant type of OAuth 2.0. 





## Oauth 1.0
a client application is authorized by a user and receives a token that can then be used to access a remote API. These tokens were all issued with a public and private portion, and this protocol used a novel (if in retrospect fragile) cryptographic signing mechanism so that it could be used over non-TLS HTTP connections. 

 OAuth 1.0 was a monolithic protocol designed to provide one mechanism to solve all use cases, and it was venturing into uncomfortable territory.

 ## Oauth 2.0
 - modular. While Oauth1.0 was monolithic
 The modularity in OAuth 2.0 allowed it to be a framework that could be deployed and used in all of the ways that OAuth 1.0 had been in practice, but without twisting core aspects of the protocol. OAuth 2.0 essentially provided recipes.

 - RFC 6749 details how to get a token
    - Furthermore, the core of RFC6749 details multiple ways to get a token and provides an extension mechanism
 - RFC 6750 details how to use a particular type of token (the Bearer token) at a protected resource. 
 
 Instead of defining one complex method to fit different deployment models, OAuth 2.0 defines four different grant types, each suited to a different application type.



# Chapter 2
2 Major steps in an Oauth transaction
1. Issuing a token
2. Using that token

#### Oauth Steps
1. The Resource Owner indicates to the Client that they would like the Client to act on their behalf (for example, “Go load my photos from that service so I can print them”).
2. The Client requests authorization from the Resource Owner at the Authorization Server.
3. The Resource Owner grants authorization to the Client.
4. The Client receives a Token from the Authorization Server.
5. The Client presents the Token to the Protected Resource.

## Types of Authorization grants (flows)
- authorization code  grant
- client credentials grant
- custom delegation grant
- resource owner password grant
- implicit grant type
### Authorization Code grant type
The authorization code grant uses a temporary credential, the authorization code, to represent the resource owner’s delegation to the client
![](https://learning.oreilly.com/api/v2/epubs/urn:orm:book:9781617293276/files/OEBPS/Images/02fig01_alt.jpg)

##### Scenario
The user clicks on a photo and requests a third party service to print it. Behind the scenes an API call happens.
- This API can understand that the user ABC wants to print XYZ image
- This API knows that it needs Oauth carry out the printing request (to access user's XYZ image)

**How to find the authorization server?**
- not specified in the Oauth spec. so its left to the implementation :/
- openID connect solves this problem

Lets assume that the client is statically configured to know how to talk to the **authorization server** and even the **protected resource**.

**Step 1: Client sends the resource owner to the authorization server**

..._via a HTTP redirect_
![](https://learning.oreilly.com/api/v2/epubs/urn:orm:book:9781617293276/files/OEBPS/Images/02fig02.jpg)

The browser automatically parses the "location" attribute of the redirect response from the client and navigates to it ( which turns out to be the URL of the authorization server with. This URL contains certain stuff encoded by the client, like info to identify the client, requested scopes etc )

_Note how the client isnt making the request directly and it doing things via HTTP redirect_


**Step 2: User authenticates himself**
- Oauth doesnt dictate the authentication strategy

**Step 3: User authorizes the client application**
![](https://learning.oreilly.com/api/v2/epubs/urn:orm:book:9781617293276/files/OEBPS/Images/02fig04.jpg)
- The resource owner chooses to _delegate_ some portion of his authority to the client application.
- The client's request already contains the scopes its trying to get authority over (embedded in the redirect URL), and the resource owner can deny some of them, allow some of them or accept all



**Step 3: Authorization Server redirects the user back to the client application**

This redirect URL sent by the AS contains the authorization code as `code` URL query parameter, and the browser immediately navigates to this URL,,,which turns out to be an API of the client application. 

_Bingo! the client got the authorization code, without ever talking directly to the authorization server_












<hr style="background:black; border-radius:50%"/>
<hr style="background:black; border-radius:50%"/>

# Scenario
You have access token to access one API. How will that API communicate with the next API .(relaying)

### Approach 1: Poor man's delegation
.....reuse the same token.
![](https://www.scottbrady91.com/img/oauth/poor-mans-delegation.png)
This gives the attacker the potential to bypass API gateway and use the compromised token to directly hit API2 (which was supposed to be behind the API gateway)

This isnt delegation. This is **impersonation**


### Approach 2: Client Credentials Grant type
Machine to machine delegation with client credentials
![](https://www.scottbrady91.com/img/oauth/client-creds-delegation.png)
Once we have the new access token AP2, we lose the information carried by the first access token meant for API1. scopes, audience and all that

### Approach 3: Custom Delegation Grant type
exchange access tokens used to access API1 for a token to access API2, while still acting on the user’s behalf. 
![](https://www.scottbrady91.com/img/oauth/full-delegation.png)









## Note
- OpenIDConnect is built on top of Oauth2.0


# Questions
- HTTP basic auth?
- HTTP digest auth?
- realm?
- cookies?
- federated login?