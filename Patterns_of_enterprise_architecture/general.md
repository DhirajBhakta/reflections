
**Architecture** is about how you decompose an enterprise application into layers and how these layers work together.

**Enterprise Applications**
payroll, patient records, shipping tracking, cost analysis, credit scoring, insurance, supply chain, accounting, customer service, forex trading...so on

- Involve _persistent data_
- Involve _lots of data_
- Involve _lots of UI screens_
- They integrate with other enterprise aplications
- Many people _access the data concurrently_. Millions...

Challenges

- deal with complex data
- deal with complex business logics which can change over time.
- deal with conceptual disagreement about "data" across different teams

**Performance**
DO NOT worry about performance until youve instrumented, measured it. Dont prematurely optimise.

Performance is either Throughput or Response time.

## Key metrics

**Response time**

**Responsiveness**

**Latency**

- As a developer, you can do nothing to improve latency, so...
- minimize network calls

**Throughput**
_How much stuff you can do in a given amount of time_

- transactions per second (tps)
- bytes per second (bps)

**Load**
_How much stress a system is under_

- how many users are concurrently connected

**Load Sensitivity**
_How response time varies with the load_

**Efficiency**
_performance divided by resources_

- A system that gives 30tps on two CPUs is more efficient that one that gets 40tps on 4 CPUs

**Capacity**
capacity of the system is an indication of maximum effective throughput or load.
This may be the absolute max or a point at which performance dips below an acceptable threshold.

**Scaling**
Measure of how adding resources(h/w) affects performance.

## Patterns

**Patterns** are common solutions to recurring problems.

- patterns are half baked, you need to fill in the blanks in context of your own system.
- patterns are a starting point, not a destination.
- Patterns create "Vocabulary" about design. Naming them is very useful.

<hr/>
# Chapter 1: Layering

Layering is commonly used to **break apart** complicated s/w system.

OS

- programming languages
- OS system calls
- device drivers
- CPU instruction sets
- logic gates inside chips

Networking

- FTP
- TCP
- IP
- ethernet

 _a layer uses various services defined by the lower layer, but the lower layer is unaware of the higher layer_

_each layer hides the layers below it_
