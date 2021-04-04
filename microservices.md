<style>
 mark{
   color: green;
   background-color:black;
   padding:4px;
   border-radius: 3px;
   font-weight: bolder;
 }
 </style>



## Monolith
Everything put together in one process

Monoliths give you &mdash; consistency;
Microservices give you &mdash; Availability

Microservices lose consistency in favor of Availability<mark>CAP Theorem</mark>; so they embrace Eventual Consistency

## Lets have lots of "smart endpoints" and "dumb pipes"
Inspiration for this is the internet itself, works really well innit?


## One Process vs A network of communicating processes
- Independantly replaceable
- Independatly upgradable

## Library vs Service (-> Componentization via services)
_Both Libraries and Services act as "Components" to the host system_

- Library will use the same process as the Host which uses the library
- Service is another process running in its own right, communicating with Host using IPC
  
  _Which is better_ ? :
  Upgradeablilty of Libraries is a Pain ( this shit works only on Java8 etc) whereas services can be independantly upgraded as you wish

## Its Fuzzy when you talk about how "big" a microservice should be
- People say one microservice per responsibility
- But define responsibility?
- How "big" a microservice should be?
- Isnt HTTP too slow at scale when you define too many microservices (?) Alternatives (?) gRPC (?)
  - Netflix has 1000 Microservices [check](https://medium.com/refraction-tech-everything/how-netflix-works-the-hugely-simplified-complex-stuff-that-happens-every-time-you-hit-play-3a40c9be254b)
  - Gilt has 250+ Microservices



## Questions
- SRP on steroids will give birth to too many microservices(?) will this cause harm? will it slow down stuff?
- How is Microservices different from SOA ?

# Service Oriented Architecture
- Multiple Services collaborate to provide some set of capabilities.
- `Service` means completely separate OS process.
- Communications between `Services` occur via network calls.
- Emerged to combat drawbacks of large monoliths
- Aims to `reuse` the same service by two or more applications.

# Decompositional Techniques
1. ### Microservices
2. ### Shared Libraries:
 - Lost heterogenity
    - The code in library has to be in the same language as the host (Java8 example) or at least run in the same platform.

3. Modules

# Building Microservices - Book Notes
  _Designing Fine Grained Systems_

<Mark> Primary Goal = decoupling</Mark>
Model the services right, and get the APIs right.<br>

<Mark>Golden Rule: Can you make a change to the service and deploy it without having to change anything else?</Mark> If no, just dont use microservices.

<Mark> 2 week rule:</Mark> You should be able to write a microservice in 2 weeks; it should be THAT small

  
  Definition: Small autonomous services that work together. Small, focussed on doing one thing well. 
All communication between the services themselves are via network calls, to enforce
separation between the services and avoid the perils of tight coupling.

#### What let do the birth of Microservices
 - Domain-driven design. 
 - Continuous delivery. 
 - On-demand virtualization. 
 - Infrastructure automation. 
 - Small autonomous teams. 
 - Systems at scale. 

## Benefits of Microservices
- Technological Heterogenity
  - Hard to add new/cutting-edge tech to monoliths. But you can do so for a single Microservice
  - Can use the best language/tool/framework/library for a given microservice without worrying about the whole (You wont break anything like in monoliths)
- Resilience
  - In monoliths, if one service fails, everything stops working. So we tend to run multiple instances of the entire monolith on multiple machines to handle failure.
  - But lol, new kinds of failure can happen! network failures &#128163;
- Scaling
  - With smaller services, we can scale only the services you need.
  - With giant monoliths, we have to scale everything as a single piece.
- Ease of Deployment 
  - 1 line change to a huge monolith requires a complete build+redeploy (High-impact High-risk deployment). --> Fear --> Less frequent deployments --> batched changes deployed at once (once in three months and shit) --> changes built up between releases --> Huge delta between releases --> More risk of fucking up 
  - with Microservices, you can shit new features fast. Because they affect smaller units, and can always be rolled back

- Organizational Alignment
  - Microservices allow us to better align our architecture to our organization.
  - Minimize the number of people working on any given codebase.
  - Smaller teams working on smaller codebases tend to be more productive.
- Composability & reusability
  - One microservice designed for one application could potentially be reused or composed to increase its functionality for use by other applications.
- Optimizing for Replaceability
  - freedom to Kill the service and upgrade/replace it when its stack is outdated.
  - When the Microservice codebase is small (2 weeks to develop) lesser the attachment and fear to upgrade/replace it

### Questions you need to answer while architecting Microservices
- How many different Technologies we should use?
- Should we let different teams use different programming idioms?
- Should we split or merge a service?




### What went wrong with Monoliths?
<mark>Though we try to maintain _modularity_ in Monolith codebases; its difficult</mark>
- arbitrary in-process boundaries break down
- Code related to similar functions starts to become spread all over.<br>
  Eventually making fixing bugs, adding features more and more difficult


### On "smallness" of microservices
As you get smaller
- Benefits around interdependence increase &#128077;
- Complexity around more and more moving parts increase &#128078;
  
 As you get better at handling this complexity, you can strive for smaller and smaller services.

 ### Ideal Microservices
 - Should Avoid Breaking Changes (Consumers should not be impacted)
    - Pick a integration technology which helps you avoid this. If a microservice adds a new field to a piece of data it sends out, existing consumers should not be impacted
 - APIs should be techonology agnostic
    - Being microservices, they should have the freedom to change the tech inside their bounded context as they wish, without affecting the boundaries. So dont choose a integration technology that dictates the tech used inside the bounded context


 ## Loose Coupling & High Cohesion ... ( in microservice context)
 1. A loosely coupled service knows very little about the service it communicates with
 2. A loosely coupled service can be independantly upgraded/replaced & redeployed without causing any change in other services
 3. A highly cohesive service has a lot of related concepts/sub-services together in one place.
 4. A highly cohesive service helps you avoid doing N number of releases just to push related changes ( because theyre spread across multiple microservice, though being closely related )

 ## The Bounded Context
  <mark>_specific responsibility enforced by explicit boundaries_</mark>

  If you want information from a `Bounded Context` or want to make requests of functionality within a `Bounded Context`, you communicate with its explicit `Interface` using `Models`
  ### &rarr; One Microservice per Bounded Context &larr;
![](https://learning.oreilly.com/library/view/domain-driven-design-distilled/9780134434964/graphics/04fig02.jpg)

 Any given domain consists of multiple bounded contexts, and residing within each are _models_ that do not need to be communicated outside as well as _models_ that
are shared externally with other bounded contexts. 

Each bounded context has an
explicit interface, where it decides what models to share with other contexts. 

How to avoid tight coupling?
- Define clearly what `model`s should be shared across boundaries
- Define what `model`s are best kept internal to the `Bounded Context`

When you start thinking about `Bounded Contexts`, Focus on what the context's role is.. this should shape how its endpoints (interfaces, boundaries) look like. Dont focus on the _data_. Doing the latter makes your microservice expose plain CRUD endpoints.
- What does this context do? [ answer this first ]
- What data does it need to achieve that? [ think about this later ]

###  Ubiquitous Language
Also remember to use the _standard_ terminologies used by the business in the code for microservices. ** Refreain from using Synonyms **  ( remember how much pain "withdrawal" and "redemption" caused in FD)

The same terms and ideas that are shared between parts of your organization should be reflected in your interfaces. It can be useful to think of forms being sent between these microservices, much as forms are sent around an organization.


## Premature Decomposition ( into microservices)
If you are new to the domain, keep it monolithic. Because you are not yet familiar with the `Bounded Context`s in the domain. In many ways, monolithic --> split into --> microservices is much easier than trying to go to microservices from the beginning.

## Integration ( the boundary layer of a bounded context )
<mark>SOAP? XML? RPC? Protocol buffers? REST/HTTP?</mark>
>Getting integration right is the single most important aspect of the technology associated with microservices in my opinion.

### - Changes in your microservice should not affect your consumers.( data formats, schema changes etc)
### - your APIs should be tech agnostic
### - your APIs should be easy to use
### - Hide internal implementation detail

### Database integrations 
- Make sure NONE of the internal schemas are exposed. Consumers of the service should have absolutely no clue over the DB side of things. DONT make the APIs look like plain CRUD analogues of the DB table names. If you decide to restructure the DB tables / heavily normalize / denormalize / or entirely change the DB to NoSQL or something, you'll get fucked so bad.
- Imagine for a second that 10 services directly query YOUR DB. 
    - If you change the implementation, theyre fucked ( bye bye loose coupling)
    - If a change in logic has to happen to one concept, and if all those 10 services share this logic, they all should make code change ( bye bye high cohesion)


### Synchronous v/s Asynchronous Integrations? (request/response  OR  event based)
-->Whats your APIs gonna be?<--
- Request/Response
  - Client initiates request and waits for response.(Synchronous)
  - Client initiates request and registers a callback, asking the server to let the client know. (Asychronous). 
    - Lol! looks like request/reponse model can do async stuff too! i n t e r e s t i n g 
  - Ex: RPC , REST/HTTP
- Event Based
  - Client wont "request for anything"
  - Client just "Says" that "this thing happened" and expects all other parties to understand what it means and do the job (trigger).
  - Asynchronous.
  - Highly decoupled. The client that emits an event doesn’t have any way of knowing who or
what will react to it, which also means that you can add new subscribers to these
events without the client ever needing to know.

### Orchestration v/s Choreography
- Orchestration
  - Central Brain, drives all the flows.
- Choreography
  - We let the subsystems know of thier role, and they do their stuff 

#### Example
![](assets/00.png)

With Orchestration
* Customer Service would act like the central brain
* It talks to all the services in a series of Request/Response
* "The Brain" can track where the customer is in the process.
* Using synchronous request/response, the brain could know if each phase has worked or not.

Downsides of Orchestration
- Customer service can become too much of a central governing authority. 
- Too much logic in one place. 
- "_I have seen this approach result in a small number of smart “god” services telling anemic CRUD-based services what to
do_".
- Extremely Brittle, higher cost of change.
![](assets/01.png)

With Choreography
- Customer Service `emits an event` in an asynchronous manner, saying Customer created.
- Other Services `subscribe` to these events and react accordingly.
- SIGNIFICANTLY decoupled.
- More amenable to change.

Downsides of Choreography
- More effort needed to monitor and track that right thing is happening.
- More effort needed to monitor and track the processess across service boundaries.
![](assets/02.png)

> ** Synchronous calls are simpler, and we get to know if things worked straightaway. If we like the semantics of request/response but are dealing with longer-lived processes, we could just initiate asynchronous requests and wait for callbacks. 
<br>
** On the other hand, asynchronous event collaboration helps us adopt a choreographed approach, which can yield significantly more decoupled services—something we want to strive for to ensure our services are independently releasable.

### RPC
- Remote Procedure Calls
- " Make the process of executing code on a remote machine as simple and straight-forward as calling a local function. "
> RPCs are based on the observation that procedure calls are a well known and well understood mechanism for transfer of control and data within a program running on a single computer. Therefore, it is proposed that this same mechanism be extended to provide for transfer of control and data across a communication network.

![](https://prakhar.me/images/rpcs.jpg)









