Components are the units of deployment. They are the smallest entitites that can be deployed as a part of a system.

- jar files
- gem files
- DLLs

Well designed components

- can be independently deployable, developable

# Component Cohesion

## REP &mdash; The Reuse/Release Equivalence Principle

_The granule of reuse is the granule of release_

Classes and modules that are grouped together into a component should be releasable together.

## CCP &mdash; The Common Closure Principle

_Gather into components those classes that change for the same reasons at the same times. Separate into different components those classes that change at different times for different reasons_

Just as SRP says that a calss should not contain multiple reasons to change, so the CCP says that a component should not have multiple reasons to change.

## CRP &mdash; The Common Reuse Principle

_Dont force users of a component to depend on things they don't need._

Classes that are not tightly bound to each other should not be in the same component
