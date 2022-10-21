ES is a distributed, scalable, real-time search and analytics engine.

### RDBMS?
- slow for huge, distributed data.



**Built on top of Apache Lucene**, Lucene is very complex;

Elasticsearch uses Lucene internally for its indexing and searching, but it aims to make full-text search easy by hiding the complexities of Lucene behind a **RESTful API**

- enables you to search, analyze and explore your data
- full text search
- structured search
- real time analytics
- distributed
- document store where _every field_ is indexed and searchable
- capable of immense horizontal scale -> Petabytes of data.
- logging
- metrics
  - Gaming
  - mars rover

Usecases

- Wikipedia
  - full text search
  - search as you type
  - did you mean suggestions
- Github
  - full text search
  - To query 130 billion lines of code
- Stack overflow
  - full text search
  - More-like-this questions
- searching for drivers on Uber
- searching for products on e-commerce
- Tinder
  - finding related matches

# ELK

ElasticSearch - heart of ELK
"search experience"

- relevant results (handle typos)
- speed.

Data is stored as JSON objects (documents)
documents are logically grouped into _indexes_

every index has a lot of _shards_. Shard is where documents are stored.
You can add more shards on nodes as need arises. Sharding will **speed up your search requests**
You will need replica shards on other nodes.
Kibana

- web interface for elasticsearch
- dashboards

## How it works?

Data Ingestion --> Indexing..

Process by which raw data is parsed, normalized, enriched...before indexing inside ES.
- Raw data flows into ES from variety of sources [ logs, metrics, apps... ]

Once indexed in ES, users can run queries on Kibana.

## ES Nodes and ES Shards

Nodes serve ES API. Nodes contact shards for data. One or more shards make up the ES Index.

# Concepts

#### Cluster
Collection of N servers that together hold entire data, and give federated indexing and search capabilities across all N servers

#### Near-Real-Time (NRT)
Not really real time.. l o l

#### Index
Collection of documents

#### Node
Singe server.
- holds some data
- helps in indexing
- helps in Querying

#### Shard
Shard is a SUBSET of documents in an index.



# Problem
runnning 7.1 version, currently . upgrade to 7.9 7.10
-- then can move indexes to s3, and fetch if necessary
-- but we dont have snapshots available with us. Its only with AWS. -->avail only if cluster goes bad.
-- Manual snapshotting is tedious.
-- one index day per day... (elastic-logs-index-todaysdate) .... same index prod qa dev
------- project name env is tagged in terraform..AMI should read this and push logs accordingly.. (later)
------- Independant clusters (later)
-- default index

agents send to URL ES.

-- create a cluster 7.1
-- new random service send to 7.1
-- then manually upgrade 7.1 --> .2-->.3 ......10
-- make the application PRINT logs and send the logs...
-- 30% total costs. now. If upgrades done, 10 - 15%
-- /etc/docker/daemon.json file
-- one or two nodes per cluster.
-- prod , mumbai region.

