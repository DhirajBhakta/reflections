
## Server side functionality?

WebRTC enables p2p communication. But it still needs servers

WebRTC needs server side functionality for

- User discovery
- Signaling
- NAT traversal, Firewall traversal
- Relay servers (TURN) in case p2p fails

---> ICE framework tries to connect peers directly with lowest possible latency through UDP. STUN job: to enable a peer behind NAT to find out its public address and port

---> If UDP fails, ICE tries TCP

---> If direct connection fails, ICE uses intermediary relay TURN server

![](https://www.html5rocks.com/en/tutorials/webrtc/basics/dataPathways.png)

STUN+TURN are used by ICE framework to enable RTCPeerConnection to cope with NAT traversal.

## Signaling?

_process of coordinating communication_.

_exchanging metadata to establish connection_.

Signaling is not implemented by webrtc. You gotta do it yourself.

![](https://www.html5rocks.com/en/tutorials/webrtc/infrastructure/jsep.png)

JSEP requires exchange of _offer_ and _answer_ between the peers. Offer and Answer are communicated in SDP (Session Description Protocol)

## SDP

Session Description Protocol

The protocol used to encode the **offer** and **answer**.

(check JSEP: Javascript Session Establishment Protocol)

WebRTC clients(peers) need to ascertain and exchange local and remote capability information by exchanging **offer** and an **answer** using SDP

Streaming is the job of RTCPeerConnection

## Alice trying to call Eve

1. Alice creates `RTCPeerConnection`
2. Alice creates `offer` (an SDP)
    - `RTCPeerConnection.createOffer()`
3. Alice calls `setLocalDescription()` with her `offer`
4. Alice stringifies the offer and **uses a signaling mechanism** to send it to Eve.

---

5. Eve calls `setRemoteDescription()` with Alice's offer, so that her `RTCPeerConnection` knows about Alice's setup
6. Eve creates `answer`(an SDP)
    - `RTCPeerConnection.createAnswer()`
7. Eve sets her answer as the local description by calling `setLocalDescription()`
8. Eve then **uses the signaling mechanism** to send her stringified answer to Alice
9. Alice calls `setRemoteDescription()` on Eve's answer.

## Finding Candidates

Process of finding the IP+PORT using the ICE Framework

1. Alice creates an `RTCPeerConnection` with an `onicecandidate` handler
2. The handler is called when the n/w candidates become available
3. In the handler, Alice sends stringified candidate data to Eve through their signaling channel
4. When Eve gets a candidate message from Alice, she calls `addIceCandidate()` to add the candidate to the remote peer description

## ICE Candidate Trickling

## Build your own Signaling Server

Push messages from the server to the client!?? HOW??

EventSource API. SSE. Server Sent Events.
Server-->Browser. But EventSource is one way. So you need some hacks :/ . XHR to rescue lol!. Signaling service passes message from the caller to the server via XHR, which is pushed to callee through EventSource.

Websocket is more natural solution. Full Duplex.

Mindless Polling. Also works *cough*. The WebRTC clients poll the signaling server repeatedly.
Note that is indeed needed even after session establishment. ..To poll for signaling messages in case of session termination by other peers.

_How to scale a signaling server though_?

- XMPP
- ZeroMQ and OpenMQ
- Commercial cloud messaging platforms that use websockets
  - Pusher, Kaazing, PubNub
- Commercial webrtc platforms
  - vline

_Fuck Scaling. How to make a simple signaling server?_

- NodeJS with socket.io and node-static

_Fuck writing my own. Anything readymade?_

There are many webrtc signaling servers which are integrated with webrtc client js libraries

- webRTC.io
- Signalmaster with SimpleWebRTC
- (commercial) vLine, OpenTok, Asterisk

## After Signaling: NAT hellhole

use ICE
![](https://www.html5rocks.com/en/tutorials/webrtc/infrastructure/p2p.png)
^ a world without NATs and firewalls...everyone has a unique address yay!!

![](https://www.html5rocks.com/en/tutorials/webrtc/infrastructure/nat.png)
^ Sad sad reality :lolcry:

ICE solves this. Provide ICE server URLs to `RTCPeerConnection`

ICE tries to find the best path to connect peers.It tries all possibilities in parallel and chooses the most efficient option

- ICE first tries to make a connection using the host address obtained from the device's OS and NIC.
- If that fails(due to NAT), ICE obtains its external address using a STUN server
- If that fails, traffic is routed through a TURN relay server
![](https://www.html5rocks.com/en/tutorials/webrtc/infrastructure/stun.png)
![](https://www.html5rocks.com/en/tutorials/webrtc/infrastructure/turn.png)

---
**STUN** server is used to get an external n/w address

**TURN** servers are used to relay traffic if p2p connection fails

**ICE** = STUN+TURN

(PS: every TURN server is a STUN server with additional built-in relaying functionality)

(PS: TURN servers are expensive to run, gotta pay lol)

---

# WebRTC

- MediaStream (getUserMedia API)
- RTCPeerConnection
- RTCDataChannel

## methods and objects

- RTCPeerConnection
  - createOffer -> RTCSessionDescription
  - createAnswer
  - setLocalDescription
  - setRemoteDescription
  - createDataChannel
  - ondatachannel

- RTCDataChannel

# Resources

- <https://www.html5rocks.com/en/tutorials/webrtc/basics/>
- <https://www.html5rocks.com/en/tutorials/webrtc/infrastructure/>
- <https://www.html5rocks.com/en/tutorials/websockets/basics/>
- vercel/pkg for turning node apps into executables
