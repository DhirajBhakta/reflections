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
  



