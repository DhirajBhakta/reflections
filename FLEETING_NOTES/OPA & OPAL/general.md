![[opa-00.jpeg]]
![[opa-00.png]]
# OPA
_General purpose POLICY ENGINE_ **policy evaluation / enforcement engine**
--->_Glorified memcache_<---

- Decouple policy from code
- policy written in rego (logical language like prolog)
- many data sources (DB / Salesforce / S3 ...)
- many models (RBAC/ABAC,ReBAC)
- complex rules
- REST API


---
# OPAL
_Open Policy Administration Layer_

![[opa-01.png]]
Application interfaces with OPA only. But OPA needs to have **up-to-date data and policies**
- propagate data+policy updates quickly to OPA
- REST API
- pull and push supported: pull from data source via polling | push via webhooks

OPAL is stateless, it just forwards data to OPA
- websocket pub-sub
- "topics" : for data and policies
	- multitenancy, separation of services 

#### OPAL and Kafka
master layer (list of OPAL servers), if needs HA, can all be connected by a Kafka backbone
(note: this is NOT the client connection of websockets)