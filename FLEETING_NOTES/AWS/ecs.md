## Terms
- ECS Cluster
- CAS
- ASG
- task
- instance




## ECS Auto Scaling...

CAS (Cluster Auto Scaling Groups) is a ECS capability to manage scaling of ASG. CAS ensures "right" number of instances are running in an ASG

CAS relies on ECS Capacity Providers.

ECS cluster <-- ECS Capacity Provider --> ASG 
						(1)	------------- (1)
	(1)-----------------(N)


### Design Goals
1. CAS should scale the ASG out whenever there is not enough capacity to run tasks.
2. CAS should scale the ASG in without disruption.
3. customer has full control of their ASGs.

### Theory...

M: #tasks that need to run
N: #instances currently running
CapcityProviderReservation = (M/N)*100

if N==M, scaling out is not required. Scaling in is not possible.

if N<M, scale out is required; atleast one task in provisioning state.

if N>M, scale in is possible(but not required); atleast one instance is not running any tasks

How to calculate required "M"?
- group all provisioning tasks by resource requirements 
- fetch resource stats of the ASG
- for each group, calculate the number of instances reqd. M = maximum value across all task groups
- require that
	N + minimumScalingStepSize <= M <= N + maximumScalingStepSize








