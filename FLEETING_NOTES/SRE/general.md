Application is "Stabilized" after go live? No!

## History
Historically, companies have employed SYSADMINS to run complex computing systems.
- assemble existing s/w components and deploy them to work together to produce a service
- run the service
- respond to events and updates as they occur.
- As system grows in complexity and traffic volume
    - frequency of events and updates increase
    - sysadmin team grows

_Because the sysadmin role requires a markedly different skillset that that required of a product's developers, developers and sysadmins are divided into discrete teams: "development" and "operations" or "ops"_

### Disadvantages of dev|ops split &mdash; The Conflict
- costs increase with scale, size of the team grows
- Both team will find it little difficult to communicate..diff in lingo
- devs want to release features quickly and push to PROD
- ops want to keep things working and resist changes. "if it works, dont change it"

## SRE 
_SRE is fundamentally doing work that has historically been done by the operations(sysadmins) team, but using engineers with s/w expertise, and banking on the fact that these engineers have the ability to design and implement automation with s/w to replace human labor_

- SRE teams SHOULD be focussed on engineering. Without constant engg, operations load increases and teams will need more people just to keep pace with the workload.
- they quickly become bored by performing tasks by hand
- they have skill set necessary to write s/w to replace their previously manual work, even when the solution is complicated.

# Responsibilities
- availability
- latency
- performance
- efficiency
- change management
- monitoring
- emergency response
- capacity planning of services






