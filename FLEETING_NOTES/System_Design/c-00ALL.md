# All Concepts in one place

## 1. Networks and Protocols

### IP-Internet Protocol

- packets (2^16 bytes == 65536 bytes)
- each packet has a
  - Header
  - Data

## Horizontal v/s Vertical Scaling

### Horizontal

- Load Balancing required
- RESILIENT - not a single point of failure
- Network Calls(RPC) - slow
- Problem of Data inconsistency
- Scales well

### Vertical

- No Load Balancing required
- Single Point of Failure
- IPC for communication - fast
- Consistent. No problem of data inconsistency
- Hardware limit for scaling.

## Links

<https://www.freecodecamp.org/news/systems-design-for-interviews/>
