## History

- 2002 launched internally
- 2003 first offering SQS
- 2006 SQS, S3, Ec3
- 2007 launched in Europe

## AWS Global Infrastructure

- AWS Regions
  - names : us-east-1, ap-south-1
  - a region is a cluster of datacenters
  - most AWS services are region scoped!
  - How to choose the region?
    - COMPLIANCE
      - Govt regulates that the data should be in same country
    - LATENCY
      - region close to your users
    - AVAILIBILITY of SERVICES
      - does my service exist in the desired region
    - PRICING
      - diff regions, diff pricing
- AWS Availability Zones
  - Each region has many AZs (~3)
    - ap-south-1a
    - ap-south-1b
    - ap-south-1c
  - each AZ is one or more datacenters with redundant power, networking, connectivity
  - theyre separate from each other, so that theyre isolated from disasters
  - AZs are connected with high b/w, ultra low latency networks
- AWS Datacenters
- AWS Edge Locations / Points of Presence
  - 216 points of presence
