




- data stored in the form of  `DOCUMENTS` (JSON objects)
- A `DOCUMENT` HAS LIST OF `FIELDS`

## Querying Elasticsearch
- RESTful APIs
- Queries are also JSON objects

## Handling Scale
- Since Elasticsearch is distributed by nature, it scales very well in terms of increasing data volumes and query throughput. Hence, even you have loads of data, the search is still going to be super fast. As a matter of fact, Elasticsearch is written in Java and is built on the top of Apache Lucene.

# KIBANA
- USES the RESTful APIs of Elasticsearch
- dashboard for Elasticsearch
- visualizations
- Web interface to the data stored in ElasticSearch
- `One thing worth mentioning here is, when you start up the Kibana first time on your machine, it actually creates an index into the elasticsearch cluster just to store various information related to itself`


# LOGSTASH
- Earler, used as a tool to process logs from application and send them to Elasticsearch
- Now it has EVOLVED to do much more than that (General purpose tool), it has become a `data processing pipeline`
- The data that Logstash receives could be 
    - log file entries, 
    - e-commerce orders, 
    - customers, 
    - chat messages, etc. 
    
    These events are then processed by Logstash and shipped off to one or more destinations. A couple of examples could be 
    - Elasticsearch, 
    - a Kafka queue, 
    - an e-mail message, 
    - or to an HTTP endpoint.