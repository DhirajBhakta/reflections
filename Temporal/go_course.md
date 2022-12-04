# Temporal 101 with Go

```sh
git clone https://github.com/temporalio/edu-101-go-code;
cd edu-101-go-code/temporal-server;
docker compose up;
```

### To learn
- **Workflows and Activities** | Describe and implement a basic business process
    - Write a workflow definition
    - pass params into workflow
    - access the result of a workflow
    - pass params into activity
    - get result of an activity from inside a workflow
    - interface with an external service from an activity
- Deploy development temporal cluster locally
- Temporal Go SDK
- How temporal helps recover from failures
- Understand temporal's execution model
    - Relationship b/w **worker and temporal server**
    - connectivity requirement for an application
    - deployment requirement for an application
    - locate & interpret event history(input/output values) of a workflow execution
    - Execute a workflow from code. (although it can be triggered from tctl)
    - Make minor changes to application code
    - Restart worker process after deployment of new code.
- Temporal **WebUI**
    - View current status of workflow
    - View history of past workflows
- Temporal **Command line tool (tctl)**
    - View history of past workflows
    - Execute a workflow
- Different options for running Temporal in Production



