
# [12 factor App](https://12factor.net/)

## Codebase

## Dependencies

## Config

**Store Config in the environment (env variables)**

- strictly separate config from code
- Don't bake configs into your application, pull them out of it.
- **store config as environment variables**

<u>ConfigMaps and Secrets in Kubernetes</u>

## Backing Services

## Build-release-run

## Processes

## Port Binding

## Concurrency

## Disposability

## Dev&mdash;Prod Parity

## Logs

**Treat logs as event streams**

DONT COMPLICATE LOGS

Keep logs simple. Just write to stdout/stderr. Let other application take care of picking it up from stdout/sterr

## Admin Processes
