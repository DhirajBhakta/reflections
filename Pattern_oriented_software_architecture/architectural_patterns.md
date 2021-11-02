# Architectural patterns

highest level patterns.
Fundamental structure of an application.

- Layers
- Pipes and Filters
- Blackboard
- Broker
- Model-View-Controller
- Presentation-Abstraction-Control
- Microkernel
- Reflection

## From Mud to Structure

How to probide high-level system subdivisions

- Layers pattern
  - decomposed into groups of tasks
  - each group at a particular layer of abstraction
- Pipes and Filters pattern
  - for processing streams of data
  - each processing step is encapsulated in a filter component
  - data is passed through pipes b/w adjacent filters.
- Blackboard pattern
  - when you have patchy knowledge about the system.
  - requirements are not yet clear.

# Layers

Networking protocols : best example

- each layer uses the services of the next lower layer

You need to balance the following forces

- code changes should not ripple through the system. They should be confined to one component and not affect others.
- Interfaces should be stable

-
