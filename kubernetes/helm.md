Helm installs "charts" into Kubernetes, creating a new "release" for each _installation_.

## _Chart_
Is a helm package.

Contains definitions of all resources (in yaml files) needed to run the app in a kubernetes cluster

## _Release_
Is an instance of the chart running in a cluster.   

## Commands &mdash;
### `Helm install`
just creates the release of a chart with all defaults.

To override the values, provide a `values.yaml` file with -f , or just use `--set` during helm install



### helpful commands
1. `helm install`
2. `helm uninstall`
3. `helm list`
