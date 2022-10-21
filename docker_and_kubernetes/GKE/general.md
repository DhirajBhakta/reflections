# cloud computing definition

- On demand self service - automated interface - no human intervention for provisioning resources
- access resources over the n/w
- Resource sharing. The cloud provider buys resources in bulk - economies of scale
- Elastic resources. grow/shrink based on usage/time period
- Pay for what you use/reserve.

# Regions and Zones

- One region (eg: europe-west2) can have multiple Zones(europe-west2-a, europe-west2-b, europe-west2-c)
- fault-tolerant apps => deploy across multiple zones
- GCP resources/services can be
  - Zonal (eg: compute engine)
  - Regional (redundancy within a region, HA)
  - Multi-Regional

# enable containers API

gcloud services enable container.googleapis.com

# create cluster

gcloud container clusters create fancy-cluster --num-nodes 3

## GCP "Project" ?

- organizing entity which contains all the resources and services
- All GCP services you use are associated with a project
- You can have more than one project. Each team in a company can have one project
- Projects are billed separately

## GCP "Folder"?

- GCP Projects can be grouped into Folders
- Many Folders can be grouped within another Folder
- To use Folders, you need an OrganizationNode at the top of the hierarchy

### IAM

WHO CAN DO WHAT ON WHICH RESOURCE

WHO

- google account
- service account
- google group

CAN DO WHAT

- role ( group of permissions)
  - primitive roles ( Owner, Editor, Viewer, BillingAdmin) "Who can do what on all resources"
  - predefined roles
  - custom roles

## VPC Networks

- A project can have upto 5 VPCs
- A VPC in one project can be shared/peered with another VPC in another project
- A VPC has no IP address range
- A VPC is global and spans all available regions
- A VPC contains subnetworks
- every Project comes with a default VPC with one subnet per region with default firewall rules
