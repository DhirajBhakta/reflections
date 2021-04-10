## Something to digest early
Our industry is a young one. 

> This is something we seem to forget, and yet we have
only been creating programs that run on what we recognize as computers for around
70 years. Therefore, we are constantly looking to other professions in an attempt to
explain what we do. We aren’t medical doctors or engineers, but nor are we plumbers
or electricians. Instead, we fall into some middle ground, which makes it hard for
society to understand us, or for us to understand where we fit.
So we borrow from other professions. We call ourselves software “engineers,” or
“architects.” But we aren’t, are we? Architects and engineers have a rigor and disci
pline we could only dream of, and their importance in society is well understood. I
remember talking to a friend of mine, the day before he became a qualified architect.
“Tomorrow,” he said, “if I give you advice down at the pub about how to build some‐
thing and it’s wrong, I get held to account. I could get sued, as in the eyes of the law I
am now a qualified architect and I should be held responsible if I get it wrong.” The
importance of these jobs to society means that there are required qualifications peo‐
ple have to meet. In the UK, for example, a minimum of seven years study is required
before you can be called an architect. But these jobs are also based on a body of
knowledge going back thousands of years. And us? Not quite. Which is also why I
view most forms of IT certification as worthless, as we know so little about what good
looks like. <br/>
 &mdash; _Sam Newman, Building Microservices_

 - We create stuff thats designed to flex, adapt and evolve to user's changing requirements and as our understanding of the domain deepen, _unlike engineers and architects who already have a knowledge base of 1000+ years and create something static_
 - Pointless for the "architect" to create diagram after diagrams, pages and pages of documentation envisioning to create the __perfect__ system without taking into account the fundamentally unknowable future.
 - Our requirements shift faster than for engineers and architects. Event the tools and approaches shift faster
 - Our products are NOT never-changing-artifacts

## Role of the Architect
 - An architect cannot and should not _overspecify_ things to the last detail. Rather make the framework where changes can smoothly happen.
 - A software architect should be more like a town planner than an actual architect. 
 - sets only the direction, and direct involvement is minimal. But like the town-planner, if the sewage plant is being developed in the residential area, then he needs to step in to shut it down.
 - Make the environment _habitable_ for developers
 - Should know how to _Zone_. And worry less about what happens inside the zones, and worry more about what happens between the zones.
    - Worry how services across the zones talk to each other.
    - How to monitor the health of each of the services in each of the zones
    - If teams use microservices, architect trusts the team to make the right local decisions.
    - _Be worried about what happens between the boxes, than what happens inside_ : If one team uses REST over HTTP, another uses Java RMI, gRPC, protocol buffers...communication becomes nightmare! standardize this!
    - Its one thing to give the teams the freedom to choose the stack for their microservice and another to make teams so varied that moving developers across becomes impossible, and we dont have grasp of a particular technology as a company. We also wont be able to build solutions spanning all the teams ( eg: logging, monitoring) 
    Netflix, for example, has mostly standardized on Cassandra as a data-store technology. Although it may not be the best fit for all of its cases, Netflix feels that the value gained by building tooling and expertise around Cassandra is more important than having to support and operate at scale multiple other platforms that may be a better fit for certain tasks . See?
- How to monitor the overall health of the system
    - System-wide view, not a service-specific view
    - All services should emit health and general monitoring related metrics in a same standard way
    - **Push mechanism** Where every service _pushes_ data to central location.
- Define integration styles
    - REST over HTTP? standardize it across all services.
    - define the concepts of noun, verb for REST endpoints
    - define to how handle pagination of resources in REST terms
    - Define how the downstream services will interpret your service's output. HTTP status codes 2XX 4XX 5XX to be defined perfectly || proper standardized messages within the output
    - Knowing the difference between a request that was OK and processed correctly, a request that was bad and thus prevented the service from doing anything with it, and a request that
    might be OK but we can’t tell because the server was down is key to ensuring we can fail fast and track down issues. If our services play fast and loose with these rules, we end up with a more vulnerable system.
    - Refrain from making microservice interfaces being too chatty --> will lead to performance issues.

- sit with the team regularly and pair program to get a sense of how the team works ( effective than having a call or reviewing code)
- Understand Company's **Strategies**
    - Eg: goal is to decrease time to market on new features.
- Define **Principles**
    - note that principles are different from constraints
    - They try to achieve the company strategies
    - Eg: to decrease time to market, the principle is that delivery teams have full control over the lifecycle of of their s/w to ship whenever they are ready, not blocked by any other team.
- Define **Practises** that adhere to the principles
    - Eg: All logging should happen centrally
    - Eg: REST/HTTP is the standard integration style
    - Due to their technical nature, practises tend to change more than principles
- After defining the standards, principles and practises, make it easy for the developers to follow them.. dont make it a burden.
    - Write a real-world _exemplar_ service (which is actually running in PROD in the company) which follows all the principles, practises. New devs love imitation.
    - You can write the _boilerplate_ for each microservice, or something that generates the boilerplate. Eg; `arc-react-tools`, `arc-react-boilerplate`, `phoenix` as tomcat wrapper, `arda` as flask boilerplate
        - Common stuff like health checking, exposing metrics exposing HTTP endpoints etc can be inside this boilerplate
        - If you write the boilerplate and make it mandatory, you also need to worry about how to _upgrade_ this boilerplate in already running microservices !
- If you are working in an organization that places lots of restrictions on how developers can
do their work, then microservices may not be for you.



## When selecting a new Tech, 
 ### Measure the **Technical Fit**
 [RAD-Cert Philosophy](https://rad-cert.com/Home/Philosophy)
 - Does this help with the problem?
 - Is there something that will help us more?
 - How does it compare against competitors?
 - Is this the simplest thing we can do?
 - Does it bring unnecessary costs?
 - Is there extra maintenance?
 - Does it have good documentation?
 - Does it have good developer community acceptance?


# My Learnings
## For a greenfield project 
- Get [The walking skeleton](https://www.oreilly.com/library/view/97-things-every/9780596800611/ch60.html) up and ready as the first priority
- DONT aim to make the perfect architecture in first shot.
- Write basic tests and automate the process of running those tests locally.
- Automate the deployment process (but with ability to be triggered manually)
- Setup CICD ASAP



## Continuous Delivery
- Every _check-in_ is a release candidate.
  
## Hexagonal Architecture 
pass

## Onion Architecture
Has a lot of layers, and makes you cry when you try to cut through it.