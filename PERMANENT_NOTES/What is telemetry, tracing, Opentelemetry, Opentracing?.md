
> "Instrumentation" is code's ability to emit **logs**, **metrics** and **traces**. 
> Instrumentation _enables_ Telemetry

> "Telemetry" is collecting measurements at a remote location/device and sending them to a central place(exporting). 
> Telemetry _enables_ Observability.
> telemetry data = "logs, traces, metrics"

> "Observability" is being able to know the system's internal state via external outputs.
> external outputs = telemetry data = "logs, traces, metrics"


## The Problem
You want to capture the entire "request response lifecycle" **across** all the microservices the request goes through, time taken at each step, errors or bottlenecks(⬆️ latency) encountered along the way.

![[tracing-01.png]]

The Request arrives here at component/microservice A and response leaves through A, but would have traveled through many other services. Each service generates its own **span**. These spans are linked via a unique ID(TraceID) and this "linked list" of spans is called a **trace**. The trace aggregates the data across the spans
Here 
- A is parent span of B and E
- B is parent span of C and D
_Helps you understand(or spot) how and why latency is high in entire request lifecycle_
_Helps you understand(or spot) how and why errors occur in entire request lifecycle_


#### Why isn't Logs enough?
Let's say you got an alert for "ServiceA being unable to write to DB". ServiceB and ServiceC call ServiceA. Which of these triggered this error? Logs wont help you answer that unless you have a way to correlate logs of all the services with a unique ID.

#### Logs vs Metrics vs Traces - Three pillars of Observability

![[tracing-08.png]]
People usually incorporate logging first, metrics next, and finally (if interested) tracing.

- Logs - the application story
- Metrics - Numbers telling stats about the system, aggregatable **numbers**.
- Traces - Context of why things are happening the way they are. Request scoped.
Trace can have logs inside it. Logs can point to the trace. Metrics can be correlated via time to both trace and logs. Usefulness can be seen only when all three are collaborative, not when you deploy these three systems individuallUsefulness can be seen only when all three are collaborative, not when you deploy these three systems individuall. **Usefulness can be seen only when all three are collaborative, NOT when you deploy these three systems individually**

Each "Span" in a trace looks like a "structured log". Spans can be called "structured logs" with context, correlation, hierarchy and more baked in. These "structured logs" can come from different processes, services, VMS, datacenters...
A sample span looks like 
```json
{
  "name": "/v1/sys/health",
  "context": {
    "trace_id": "7bba9f33312b3dbb8b2c2c62bb7abe2d",
    "span_id": "086e83747d0e381e"
  },
  "parent_id": "",
  "start_time": "2021-10-22 16:04:01.209458162 +0000 UTC",
  "end_time": "2021-10-22 16:04:01.209514132 +0000 UTC",
  "status_code": "STATUS_CODE_OK",
  "status_message": "",
  "attributes": {
    "net.transport": "IP.TCP",
    "net.peer.ip": "172.17.0.1",
    "net.peer.port": "51820",
    "net.host.ip": "10.177.2.152",
    "net.host.port": "26040",
    "http.method": "GET",
    "http.target": "/v1/sys/health",
    "http.server_name": "mortar-gateway",
    "http.route": "/v1/sys/health",
    "http.user_agent": "Consul Health Check",
    "http.scheme": "http",
    "http.host": "10.177.2.152:26040",
    "http.flavor": "1.1"
  },
  "events": [
    {
      "name": "",
      "message": "OK",
      "timestamp": "2021-10-22 16:04:01.209512872 +0000 UTC"
    }
  ]
}

```


Logging is historically the first centralized debugging system.


## Solutions
2010: Google's paper on their in-house tracing system : Dapper
2012: Twitter's Zipkin(opensourced)
2015: Uber's Jaegar (opensourced)


(Fullfledged Propreitery APM tools like Datadog, Splunk, Dynatrace are now putting efforts to migrate to opentelemetry)

Everybody(see solutions above) did their own thing to achieve the same thing. Different ways to describe, store and visualize trace data....until there were attempts at standardization.

### Standardization

#### OpenTracing (2015)
Dealt with just "distributed tracing". Now Deprecated, use OpenTelemetry instead.
Why deprecated?
- deals with just traces
- does not care about standardizing exporters to allow for traces to flow into any pluggable sink. cares only about devX and how to collect/instrument. 
**Has the goal of a standardized developer API for tracing**

#### OpenCensus (2018)
**Allowed for pluggable backends**. Had support for both metrics and traces.
Primarily has auto-instrumentation agents, and no devX (no APIs) to control the tracing via code.

#### OpenTelemetry (2019)
Is a merger of OpenTracing and OpenCensus.
You get standardized developer API for trace collection + pluggable backends.

- Provides a standard for 
	- instrumentation (at the point of measurement)
	- collection of instrumentation data
	- Provides a way to send/export these data
- Deals with logs, traces, metrics. all
- Is Vendor Agnostic. **Independent** of the tools where logs, metrics, traces are collected and stored.

**Aims to provide a single set of APIs, libraries, agents and collection services for capturing metrics and traces. Aims to support existing tools and allow for pluggable backends. eg: sending metrics to Prometheus or Grafana, Sending logs to elasticsearch, sending traces to Jaegar or Zipkin**

**Aims to be the glue, To collect metrics, logs, traces together under one unified SDK**.

Collect + Process + Export. Not store , Not visualize.


---

## OpenTelemetry

![[tracing-02.png]]
![[tracing-00.webp]]

### OpenTelemetry client side SDK
#### Purpose
- **collect** data about the application
- Propagate context b/w services
- Ship it somewhere

Developers should be involved as little as possible in instrumenting their code. They need not know where the telemetry data eventually resides.

> **Note**
> OTel is only meant for Collect+Process+Export of Signals(logs,metrics,traces). Does not deal with storage and visualization.

> **Note** on Logging side of Opentelemetry: 
> Although is spec is elaborate for Traces and Metrics, Otel doesnt care  about logs, and only acts to create a bridge between uncontrolled logs and controlled traces and metrics. The API for logs is called "Logs Bridge API" for the same reason.
> ^ Just stay away from this. Not yet implemented on golang, and Experimental on python.

>**Note** On Baggage side of Opentelemetry:
>In addition to logs , metrics , and traces.... theres "baggage"
>baggage is a k-v store of a trace, available to any span in the trace.
>Say you want UserID attribute on all spans, but only one service knows about UserID...then adding it to baggage can help;
>baggage is NOT a subset of span attributes.
>#TODO : this might alleviate monstrous logging problem in BOU COU. 
### Terminology

> * TracerProvider, MeterProvider, LoggerProvider
> * Tracer, Meter, Logger
> * TraceExporter, MetricExporter, LogRecordExporter 

- **OTel API**
	- Used to define how telemetry data is generated for a given Signal	(Traces/metrics/logs)
	- Used primarily by library authors, and NOT by developers who consume libs in their services (they use SDK)
- **OTel SDK**
	- #TODO
- **Instrumentation**
	- **Automatic Instrumentation**
		- Some libs are **natively instrumented**, their native code itself emits traces, logs, metrics as per otel format. 
		- If not natively instrumented, you have **instrumentation libs** for specific libs , which attaches to an existing library, you don't have to touch your code. Libs specifically made for integrating with popular libs like DB libs, HTTP libs, REST libs, frameworks so that they can abstract away instrumentation from the developer. They use either library hooks or just monkey-patch the lib code to inject instrumentation code(or bytecode injection). You include the libs and those other libs are already instrumented.
		- Having all popular libs to be natively instrumented, so that additional instrumentation libs with monkey patching is not required...is a long term goal.
		- all automatic instrumentation libraries: https://opentelemetry.io/ecosystem/registry/?component=instrumentation&language=go
	- **Manual Instrumentation**
		- developer writes dedicated code to export data from wherever(any part of the code) he wants.
		- developer explicitly adds and ends spans. ... adds attrs and events to the spans
		- You just need to use Otel SDK (which internally uses Otel API)
		- Library authors use Otel APIs
			- If youre making a importable library, you'd use just Otel API.
			- If youre making a standalone process, you'd use both Otel API and Otel SDK. Why? You need the SDK to wire up all the dependencies required to emit out the signals. When youre making a library, you dont care about this since you dont know who imports the library, and you leave it up to the consumer. When you make a service out of your code, its a live running system and now youre responsible to configure the wiring, which is why you need the SDK. **Unless you import OpenTelemetry SDK,  the API import is pointless, your instrumentation code does nothing,  and wont add overhead to performance** . OpenTelemetry is no-op and very performant when there is no SDK in the application. When SDK is imported and configured, it consumes bound resources https://opentelemetry.io/docs/specs/otel/performance/
- **Resource**
	- **Resource** is the entity that produces telemetry data. eg: your microservice / your DB lib / redis lib
	- A **Resource** is identified for resource attributes, which can be one or more of the following
		- process name
		- k8s pod name
		- k8s namespace
		- k8s deployment name
		- Host
		- Operating System
		- Container name
		- CloudProvider specific attributes...
		- Note that all the above K8s/cloud values can be automatically obtained via **Resource Detectors** .
	- The resource attributes help investigate  better on the observability backend.
- **Collector**
	- Its a proxy
	- Made up of a **Reciever**(s), (Optional)**Processor**(s) and **Exporter**(s)
	- **Reciever** can accept signals in multiple formats
		- OTLP
		- Jaegar format
		- Prometheus format
		- ... commercial/proprietary tools formats
	- (Optional)**Processors** can do filtering and batching and transformations on signals.
	- **Exporter**(s) can send to multiple backends(incl other collector(s))
	- **Collector** can be deployed in two modes
		- As **Collector Agent**
		- As **Collector Gateway** 
- **`TracerProvider`** and **`MeterProvider`** and **`LoggerProvider`**
	- Initialized ONCE per microservice. Includes **`Resource`** Initialization and **`Exporter`** Initialization. Good to make a singleton global for this.
	- Is a factory for **`Tracer`**  and **`Meter`** and **`Logger`**
-  **`Tracer`**  and **`Meter`** and **`Logger`**
	- **`Tracer`**
		- Creates **Spans** 
	- **`Meter`**
		- Emits metrics via MetricInstruments
		- MetricInstruments
			- Counter
			- Asynchronous Counter
			- UpDownCounter : ex, for Queue len
			- Asynchronous UpDownCounter
			- Gauge
			- Histogram
	- **`Logger`**
		- Creates **LogRecords**
		- Note that **`LoggerProvider`** and **`Logger`** are created by logging lib authors and are abstracted away from you.  These metaphors are part of LogsBridgeAPI
		- Devs are required only to configure a logging lib to use a **`LogAppender`**(log bridge). You can do this via the OTel SDK.
		- **`LogAppender`** (Bridge)
			- Emits logs to **`LogRecordExporter`** 
- **`TraceExporter`** and **`MetricExporter`** and **`LogsRecordExporter`**
	- These send trace, metrics, logs respectively to a "consumer".
	- These are "translation" libraries which translate in-memory OTel **Span** or **Metric** objects into 
		- **appropriate format** expected by the final destination, the telemetry analysis tool (Jaegar, Prometheus, ElasticSearch)
		- OR **OTLP format** expected by OTel **Collectors**
	- Exporters can be push or pull based.
	- "consumer" can be stdout during debugging (`ConsoleExporter`)
	- "consumer" can be the final destination, the telemetry analysis tool: Jaegar, Prometheus, ElasticSearch..
	- "consumer" is usually the **Collector**.
- **Signal**
	- Logs, Metrics, Traces, Baggage.
	- **Trace**
		- A Trace is a collection(Tree) of **Spans**, rooted at a **Root Span**
			- The root **Span** represents a request from start to finish.
		- All these spans are correlated with a TraceID.
		- **Span**
			- A Span represents a transaction/operation/bunch of operations/ developer defined "group" of "operations".
			- Spans are immutable.
			- Building blocks of Traces
			- In json format, a span is essentially a "structured log"
			- Has a **Context** object (Sub-object in the span object json)
				- Contains Trace ID
				- Contains Span ID
				- A **Propagator** is responsible for serializing deserializing this context object when it passes through service interfaces. (travels between services).
					- You can write your own custom **Propagator**
						- #TODO why would you even want to do this??
			- Has a ParentID (root span does not have one)
			- Has name of the service.
			- Has startTime, endTime.
			- Contains **events** and **attributes** which capture more info about the operations associated with that **span**
				- Can include userID, cartID, ... businessEntityID associated with the request here.
				- If you microservice doesnt have logging setup, use **span events** and append logs here.
			- Contains **Span Links** (optional)
				- links other spans(in ANOTHER trace), created in async fashion...like jobs. _This request caused a task to be added to a queue. And that task has its own span_ 
			- Every Span has a "status" \[ Unset, Error , OK ]
				- `Unset`: default. "span has no errors"
				- `OK`: explicitly marked "error free" by the developer. not really required to mark spans as `OK` . `Unset` suffices. 
				- `Error`: Error occurred during the span. Even stuff like 500 can be tracked here.
			- Every Span has a "kind". \[ Client, Server, Internal, Producer, Consumer ]
				- Parent of `Server` span is a remote `Client` span
				- Parent of a `Consumer` span is a `Producer` span.
				- If not specified, the kind = `Internal`
				- **Internal Spans** 
					- Spans which dont cross service boundaries. Useful for instrumenting a function
				- **Server Span**
					- Incoming HTTP request at a microservice for ex.
				- **Client Span** 
					- Outgoing HTTP request from a microservice for ex.
				- **Consumer Span**
					- Similar to Server span, but the "job" might have been created long ago, unlike requests which are real time.
				- **Producer Span**
					- Similar to Client span, they create "jobs".. jobs into job queue OR local jobs for an event listener.
	- **Metrics**
	- **Logs**
	- **Baggage**

### Steps to emit Signals (Traces, Metrics, Logs)
#TODO add steps here after otel demo. Also, question the significance of every line of code in  this verbosity hell.

The Goal is to create **Spans** , emit **metrics** and write **logs** ..and for that you need to call functions on **`Tracer`** , **`Meter`** and **`Logger`** objects.

**`Tracer`** , **`Meter`** and **`Logger`** objects are created via global Singleton objects **`TracerProvider`**  **`MeterProvider`** and **`LoggerProvider`** . When you create these singletons, provide the service name(+version), which will be included in all spans created in this service.

You need to uniquely identify your microservice/library thats emitting these signals. You do this via resource attributes by creating a **`Resource`** Object and associating it to the TracerProvider. Once you do this, all spans created by the `Tracer` object will have the resource attributes attached to it.

Now you need a destination to emit these signals.
- stdout
- directly to final destination (telemetry analysis backend like Jaegar, Prometheus, ElasticSearch)
- OTel Collectors, which will later send it to final destination.
Each of these destinations expect the signals in very specific formats, which is why you need **Exporters** . **`TraceExporter`** **`MetricExporter`** and **`LogRecordExporter`** objects exist for this very reason, hence you need to create them too.

in Brief, steps include
1. Initialize "Provider", "Exporter", "Resource". (see the definition of Resource in Terminology section above).
2. Create Meter/Tracer/Logger objects
4. Emit the signals using the Meter/Tracer/Logger objects

### Collector
(Read the terminology section first)
Collector can be deployed as 
- Collector-agent
- Collector-gateway
_"Collector" usually means "Collector-gateway" ( and not the collector-agent that runs alongside the application, although both are run from the same binary)_ 
![[tracing-01.webp]]
##### Whats the point of collector-agent or collector-gateway?
Claim: Performance benefits
On top of it, Collectors contain receivers+processors+exporters which can help accept signals in any format and transform/filter it in any way.
But can't the SDK itself do it? SDK already can choose from a list of Exporters and export directly to the backend.
The Benefit lies in the fact that the stuff done by collector
- encryption
- compression
- batching
- filtering
- retry
..**are CPU intensive** to a degree and is best kept decoupled away from main process which emits signals.
>**Note**
>Collector to Collector communication (Incl collector-agent to collector-gateway) is via grpc by default, not http

#### Collector Deployment patterns
https://github.com/jpkrohling/opentelemetry-collector-deployment-patterns
1. App --->  Collector-agent --->  Backend
2. App ---> Collector-agent---> Central Collector-Gateway ---> Backend
	- Benefits: **Enforce** policies batching/retry/encryption/compression/authentication/Sampling/metadata-enrichment/Scaling..
3. On Kubernetes
	1. App--> Collector-agent (DaemonSet)-->Central Collector-Gateway --> Backend
4. With Load Balancing: TraceID based load balancing to decide which collector the signal goes to.

> Why not send signals directly to backend from the SDK in the application?
> - This is possible. 
> - You'll have less control over data that flows to the backend
> - You cant enforce policy from a "central" place as described above
> - Migration from one backend to a different backend later would be difficult, you cant do this without bothering the associated dev team which built the application.



## Managing Scale
(
sdk --> load balancer --> collector load balancer --> collectors --> kafka/kinesis --> backend/database
)


You can put a load balancer infront of multiple otel collectors
![[tracing-11.png]]

### Sampling
![[tracing-07.png]]
Tracing is expensive
- Collection (CPU, Mem)
- Export (data transfer cost)
- Storage (+compute)

How much traces to collect?
- "I want to debug any request/issue" - requires 100% of traffic
- "I want to debug system wide issue" - 20-50%
- "I want to know application baseline" - 5-10%
- "I want to understand system architecture" - 5%
Sampling reduces traffic on exporters, by sending only a small percentage(sample) of the traces, and ignoring the rest, **and reduces ingestion costs**
- Head Sampling 
	- Make the sampling decision when the req arrives (as early as possible), Inexpensive.
- Tail Sampling
	- Sampling decision done when all spans of the trace are done (as late as possible)
	- Sampling decision taken after reviewing every span in the trace
		- "Always sample traces that contain error"
		- "Always sample  traces which have overall latency > Threshold"
		- "Always sample traces with one or more spans having attrs attrX=Y"
	- Costly to implement


## OpenTelemetry on Kubernetes
>**Info**
>With your application running on K8s, seems that you dont have to write any code. The OTel K8s operator can frikkin inject code to make basic things happen!
## Extending OTel
The spec is designed to be extensible
- **Add a receiver** to the collector to accept data from a custom source.
	- Why would you want to add a reciever?
- **Add custom instrumentation lib into SDK** 
	- Why would you want to add custom instrumentation lib into SDK ?
- **Create a new Exporter** (to a backend that doesnt support OTLP)
	- Why would you want to create a new exporter?
- **Create a custom propagator** 
	-  Why Would you want to create a custom Propagator?
	- You shall use *PropagationAPIs* for this.
	- otel already maintains several "official" propagators
	- default propagator uses the headers spec'ed by W3C TraceContext spec.
	-
- **Create Distributions** https://opentelemetry.io/docs/concepts/distributions/ 
	- Why Would you want to create a distribution?
	- TODO
--- 

- A collector can exist as a library imported in main service OR can be a standalone service. Is this statement true? Why does collector have two modes : collector-agent and collector-gateway? is there any benefit to collector-agent? Whats the drawback of bypassing the collector-agent and sending signals directly? If its for performance, how exactly is it improving performance?
- Exporters can be push or pull based? which one should i choose? why?
- can logs in ES, metrics in Thanos, and traces in Jaegar can all be correlated on grafana!? is it even possible? or should they be duplicated into one data source? `TracerProvider` and `MeterProvider` in code?
- Why do we have the damn heirarchy or TracerProvider, Tracer and why are they objects? why wouldnt i just do something like `otel.createTrace()` ??
- Difference between actual logs and "span events", since span events are treated as structured logs "within" a span.
	- Seems that you can "stamp" the trace/span context onto the standalone logs so that you can correlate them later.
	- Use standalone logs for verbose logs and avoid span events if theyre verbose as hell.
- When to add to events of existing span? When to create a new span?
- How to efficiently query via grafana for a group of microservices? How to debug?
- the "Trace Exporter" or "MetricExporter" or "LogRecordExporter" or "Exporter" in general ..within the SDK, which sends traces out.. **does it have a shared component from within a collector**? because collectors too have "exporter"s. 
- Read more on Baggage. Possible benefits for BOU COU to replace monstrous logging.
- Read more on OTLP, whats the point of it? dont existing formats suffice?
- Spans are immutable? then wtf are Processors for?
- When to use OpenTelemetry API and when to use OpenTelemetry SDK ? https://opentelemetry.io/docs/concepts/instrumentation/manual/
- How important are "Context Extraction/Injection" ? Say one microservice is called from another, does the second one need to extract context for any reason?
	- https://opentelemetry.io/docs/concepts/instrumentation/libraries/
- Tracing on async based microservices is not straight forward. Ones which add tasks to queues.
- Make a list of "When and how should i trace" best practises
	- Thin clients?
	- outgoing n/w calls?
- Read up K8s Otel Operator. and related helm charts.
-  On K8s why does Jaegar need a Jaegar K8s operator when OTel already has its own OTel K8s operator? https://medium.com/@magstherdev/opentelemetry-on-kubernetes-c167f024b35f How was OTel collector pod created here without having added the OTel operator first? Can it run without the operator? Or is Jaegar operator helping in some way?
- Figure out an apt combo of head sampling and tail sampling for cost optimization. Check if something can be done at runtime to switch on/off
- Read Propagators 
- Why batching (processors inside collectors) can help save costs. Diff kinds of batching. Can batching be done on the SDK itself, bypassing collectors?
- YAML format for Collectors seems pretty IMP. document it. Check if the YAML provided to SDK also has similar format, which will prove that the SDK itself is a collector variant.
- Collector Deployment patterns : https://www.youtube.com/watch?v=WhRrwSHDBFs https://github.com/jpkrohling/opentelemetry-collector-deployment-patterns
- Collector Load Balancing Patterns
- How to choose a Backend? newrelic, tempo , lightstep, honeycomb, jaegar https://faun.pub/opentelemetry-backends-240acbd8dcac https://signoz.io/blog/opentelemetry-backend/
	- Tempo seems to be better for cost, and integrates with Loki.
- Go through full list of Recievers
- Go through full list of Processors
- How to think about Monitoring for complete OTel stack? what if collector(s) go down , low on resources, data loss (loss of traces..) Build grafana dashboards for OTel collectors specifically .. https://github.com/open-telemetry/opentelemetry-collector/blob/main/docs/monitoring.md
- All Signals in one place https://grafana.com/blog/2020/03/31/how-to-successfully-correlate-metrics-logs-and-traces-in-grafana/ Signals Correlation, is it possible in ES+prometheus+Jaegar combo?

TODO
- otel demo repo
- Bare minimum setup from ops perspective? no scale
- Bare minimum effort from dev to integrate? What needs to be configured?

---

```
Goals
- Manage high volumes with kafka as a buffer.
- Make sure its queryable/visualizable on grafana. If not supported, write plugins. https://grafana.com/blog/2020/03/31/how-to-successfully-correlate-metrics-logs-and-traces-in-grafana/
- Use dynatrace approach of tracing 3rd party calls, to check if 3rd party is the reason for bottleneck or not. (not just internal spans).
```
