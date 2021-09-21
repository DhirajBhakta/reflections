# Why Prometheus

Prometheus was created for monitoring in  highly dynamic **container environments**
Can also be used in traditional, bare servers.

Modern devops is becoming more and more complex.
100s of containers with much more processes. How do you manage downtimes. How will you have insights on h/w level or application level?

Lot of things that can go wrong

- Response latency
- Application Errors
- Overload
- not enough resources...

**You need automated monitoring and alerting**

Prometheus server PULLS metrics from targets. Targets are expected to expose `/metrics` endpoint which the server hits and collects metrics

Other monitoring tools like cloudwatch and newrelic expect targets to PUSH metrics to the central monitoring server. But what if all this causes high load of network traffic and monitoring system itself becomes your bottleneck?
You also need to install daemons to continuously push metrics
