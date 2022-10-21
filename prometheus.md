# Why Prometheus

Prometheus was created for monitoring in  highly dynamic **container environments**
Can also be used in traditional, bare servers.

Modern devops is becoming more and more complex.
100s of containers with much more processes. How do you manage downtimes. How will you have insights on

- h/w level
- application level?

Any one microservice can crash and cause cascading failures. Debugging is hard. How do you know what went wrong?
How do you know the chain of events that caused the system failure?

Lot of things that can go wrong

- Response latency
- Application Errors
- Overload
- not enough resources...

What you need is

- constantly monitor all the services
- alert when crash
- identify problems before they occur
- check regularly the memory usage
- notify the administrator
- check regularly the storage usage and limits reached? Trigger alert at 50%!
- app becomes too slow and sends 100s of error messages which overloads the network bandwidth and fails other services

**You need automated monitoring and alerting**

Prometheus server PULLS metrics from targets. Targets are expected to expose `/metrics` endpoint which the server hits and collects metrics

Other monitoring tools like cloudwatch and newrelic expect targets to PUSH metrics to the central monitoring server. But what if all this causes high load of network traffic and monitoring system itself becomes your bottleneck?
You also need to install daemons to continuously push metrics

## Prometheus Architecture

![](https://training.promlabs.com/static/prometheus-architecture-81d1251aedaf0676f61ad31e4cf19363.svg)

### Prometheus Server

- does the actual monitoring work
- DATA RETRIEVAL WORKER - pulls metrics data
- STORAGE - stores metric data
- HTTP SERVER - accepts queries

"metrics" get saved in prometheus database.

- Prometheus pulls data from /metrics
- "Exporter" has /metrics
- client libraries has /metrics

# Prometheus Up and Running

Has a data model and a Query Language

#### History

- Nagios
- Graphite

They work by regularly executing scripts called checks. if a check fails, an alert is generated.

**Monitoring** is about **events**

- Receiving a HTTP request
- Sending a HTTP 400 response
- Entering a function
- Reaching the else of an if stmt
- Leaving a function
- A user logging in
- Writing data to disk
- Reading data from n/w
- Requesting more memory from kernel

**All events have context**. But this context can be very big to store

- Profiling
  - dumps a HUUGE context
  - meant for debugging
  - absolutely not meant for production as it eats away disk space
- Tracing
  - gives stack trace of a select few events,
  - tells how long each function took
  - you can tell which function is contributing to latency
- Logging
  - Transaction Logs
  - Request Logs
  - Application Logs
  - Debug Logs
- Metrics
  - metrics largely ignore context
  - at max one or two fields

## Prometheus Architecture

### Client Libraries

With two three lines of code, you can define a metric and add your desired instrumentation inline in the code you control. This is called **direct instrumentation**

### Exporters

Sometimes you cannot manipulate the code to define and send metrics as done using client libraries.

An Exporter is deployed beside the application you want to obtain metrics from.

- It takes in requests from Prometheus
- gathers required data from application
- transforms them into correct format
- returns them as a response to Prometheus

This approach is called **custom collectors** or **Const Metrics**

Specifically, **Node exporter** exposes kernel and machine level metrics on Unix systems,

- CPU
- memory
- disk space
- disk I/O
- network bandwidth
- average load
- motherboard temperature

### Service Discovery

finding applications that need to be monitored and to pull metrics from.
using "relabelling"

### Scraping

Sending a HTTP request called "Scrape" to pull in data.
Response to scrape is parsed and ingested into storage.
**Prometheus is a pull based system**

### Storage

Prometheus stores data locally in a custom DB. **This is not distributed.** It is a single server.

### Dashboards

Grafana

### Alert Manager

Alerts are sent to alert manager from Prometheus -> turned into notifications

Email, Slack, PagerDuty

### Long Term Storage

Someone else has to do it. LocalStorage is limited because Prometheus stores data only on the local machine. disk space is limited.

Someone else has to pull data from here and store in long term storage : Thanos!

# Instrumentation

### The Counter

Counters track either the number or size of events.
They track how often a particular code path is executed

- to track how many times errors or unexpected situations occur
- knowing how errors are trending over time is useful for debugging
- understand which are the most popular features and codepaths of your application, and optimise it after you know it.

### The Gauge

Gauges are a snapshot of some current state.

examples:

- number of items in a queue
- memory usage of a cache
- number of active threads
- the last time a record was processed
- avg requests per second in the last minute

### The Summary

to track latency, avg latency

### The Histogram

to get quantiles, percentile

if 0.95 quantile is 300ms => it means that 95% of requests took less than 300ms.

Quantiles are useful for reasoning about end user experience. If a user's browser makes 20 concurrent requests to your app, then it is the slowest of them that determines the user visible latency. The 95th percentile captures that latency.

##### What should I instrument?

Webservers and Databases

RED method (Requests, Errors, Duration) for online serving systems

- request rate
- error rate
- latency

USE method (Utilization, Saturation, Errors) for offline serving systems.

# Exposition

The process of making metrics available to Prometheus is called exposition.

- done over HTTP
- /metrics path
- needs to be configured once per application

### PushGateway

- for Batch jobs
- do some work and then exit
- Prometheus' "pull scraping" wont work
- we need to "push" to push gateway
- then Prometheus scrapes from push gateway

# Prometheus Talk

Potential problems you face

- Disk full -> no new data stored
- High temperature -> h/w failure
- n/w outage -> services cannot communcate
- Software bug -> request errors
- Low memory utilization -> money wasted

Need to observe your systems to get insights on

- Request/event rates
- Latency
- Errors
- Resource outage
- ...temperature, humidity
And then react to what went wrong.

#### Logs vs Metrics

- metrics are cheaper than logs (less detail for debugging)
- use ElasticSearch, Loki for logs

#### Tracing vs Metrics

- Logging on steroids
- trace the request throughout its journey in end to end in microservices
- use Jaeger, Zipkin for tracing

#### Old world 90's

- Nagios
- check based monitoring
- you have statically configured hosts
- and you run check scripts periodically to check health **right now**

#### Prometheus

Metrics based <u>monitoring and alerting</u> stack

- Instrumentation (NUMERIC time series data)
- Metrics collection(scraping) and storage
- Querying
- alerting
- dashboarding
- pull based monitoring systems

Does not

- logging or tracing
- Automatic anomaly detection
- Scalable or durable storage
- it is single node system

Successful for

- Dimensional data model
- Powerful Query language
- Simple and efficient SINGLE server
- Service Discovery integration

#### Prometheus Alternatives

- StasD
- OpenTSDB
- Ganglia
- InfluxDB
