# Data models

## Relational  | document | graph

Historically, data started out being represented as one big tree &mdash; the Heirarchical Model, but that was not good for representing many-to-many relationships, so relational model was invented to solve the problem.

More recently, developers found some applications dont fit well in the relational model either. New non-relational "NoSQL" data stores came into picture
There are 2 variants of NoSQL

1. Document Databases
   - useful where data comes in self contained documents (JSON)
   - useful where relationships between one document and another are rare
   - they dont enforce a schema
2. Graph Databases
   - useful where anything is potentially related to everything
   - they dont enforce a schema

If schema is not enforced, then application is adaptible to changing requirements.

But the application still assumes data has a structure | its all about..

- schema is explicit (enforced on write) (schema-on-write)
- schema is implicit (handled on read) (schema-on-read)
