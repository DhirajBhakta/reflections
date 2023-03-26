# Feature Management
![](https://launchdarkly.com/static/FF-dashboard-small-8bd4a32da4606857213654d0fd103eb6.png)
 Product teams  use  feature  management  to  
 - progressively  deliver  new features to end users
 - run experiments and A/B tests
 - helps avoid long lived branches

 all while the application is running and without the need to deploy new code.

 Wrapping each change in a feature flag 

 ## Feature Flag 
 How to decouple the act of deploying from the act of releasing?
 - feature flags

![](https://reflectoring.io/assets/img/posts/feature-flag-tools/percentage-rollout.png)
 
In the early days feature flags were passed in compile/build time. (not dynamic)
- env variables
- configs

New way
```js
if(enableFeature(one.click.checkout, {...})){
    /*show the one-click checkout feature */
}else {
    /* show the old feature*/
}

/**
* second param is context
* The function call is made to the central feature management platform
*/
```

We ask the **feature management platform**
- here's the context
- can I enable the feature?

![](https://23o0161033pm1289qo1hzrwi-wpengine.netdna-ssl.com/wp-content/uploads/2021/02/Pipeline-After-Adding-Feature-Flags-1024x576.png)

### Testing in Production!
Production environment, whose access is restricted to certain people .. is the best way to test stuff as PROD cannot be really completely mimicked in test environment ( even if you try to, its going to be costly)
##### Percentage Deployment | Ring Deployment
Make a slow rollout, enable your feature managment platform to _enable the feature first for internal developers_, then a smaller group, then a wider group.

Deployment Model should be 
1. First to internal users
2. Next to canary users
3. Next to beta testers | early adopters
4. Full rollout 

![](https://docs.microsoft.com/en-us/azure/devops/migrate/media/phase-rollout-with-rings/phase-rollout-with-rings-pipeline.png?view=azure-devops)

### Safety Valves | Circuit Breakers = Permanent feature flags

### Should you test all combinations of feature flags ?
You'd have exponential test cases if you'd do that

- test each flag in isolation
- make sure a flag doesnt affect another (seems  tough :/)

### How to unit test?
- mock out the feature mangement service

### Manage tech debt | remove old flags often
- Organize your flags into buckets (by projects/microservice etc)
- name the flags well (fflag_ prefix)

## Blue Green Deployment V/S feature flags
- Granularity
    - **Feature  flags  work  at  the  code  level**,  and  flags  can  protect extremely fine-grained changes, down to individual code paths.
    -  In   contrast, **blue/green   deploys   work   by   routing   traffic   to entirely  different  versions  of  a  service.**
- Users
    - to which user? can be controlled via feature flags because they operate at the code level, and user details can be obtained in that environment
    - BG deployment, routers handle it...they have no info about the users attributes
- lifetime
    - BG is usually shortlived
    - feature flags can be lifetime

## Get started with feature managemnt 
1. config file
    - cant be changed dynamically
    - no context; user specific - NO
2. DB
    - values can be changed dynamically
    - no context; user specific - NO
3. DB with context
    - context - YES
4. Feature Managment as a service

### Polling vs Streaming
clients can either poll for flags

clients can also keep a long running connection with the feature managmeent server and recieve events...











