---
tags: [prometheus, promql, grafana]
---

```promql
sum(scylla_manager_server_current_version{}) or on() vector(-1)
```
If there is no such metric found called `scylla_manager_server_current_version`, then "-1" would be returned. 

Another complex example would be...
```promql
(
    sum(scylla_manager_task_active_count{type=~"repair",cluster="setu-dev-playing-cluster"}) or 
    on() vector(0)
) + 
(
    sum(scylla_manager_task_active_count{type=~"backup",cluster="setu-dev-playing-cluster"})*2 or 
    on() vector(0)
) + 
(
    sum(scylla_manager_server_current_version{}) or 
    on() vector(-1)
)
```
In this complex example, we return the "status" of the Scylla Manager. It can either be "Online(0)", "Repair(1)", "Backup(2)" or "Offline(-1)".  

## [The `or` operator](https://prometheus.io/docs/prometheus/latest/querying/operators/#logical-set-binary-operators)
Basically OR is acting like the usual "default value provider" in programming
> Logical AND can be used as a circuit breaker, and Logical OR can be used to provide default values.

The binary `or` operator can work on two vectors : `<vector> or <vector>` 
And it returns the "union". i.e, all entries on the left vector and all entries in right vector which are not found in the left vectors. i.e removes duplicates from both the vectors.

### [The `on` keyword](https://prometheus.io/docs/prometheus/latest/querying/operators/#vector-matching)
`on(<labellist>)` helps you specify which "labels" to match the two vectors on.


---
```promql
 sum(scylla_manager_server_current_version{}) or on() vector(-1)
```
In this example, there are two vectors
- scylla_manager_server_current_version
- vector(-1)
`vector(-1)` is a time series with **no labels** and value=-1 at each timestamp. 

`on(<labellist>)` specifies which label to match on. 


