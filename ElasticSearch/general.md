ES is a distributed, scalable, real-time search and analytics engine.

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
