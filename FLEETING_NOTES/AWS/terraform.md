# Terraform

**IaC : Infrastructure as Code**

Declarative way of specififying the Infra.

Modifying anything is as easy as changing the declarative code and running `terraform plan` and `terraform apply` again. Everytime anything changes, the internal "terraform state" will refresh and change itself.

### Concepts

#### Workflow
1. `terraform init`
2. `terraform plan`
3. `terraform apply`
4. `terraform destroy`

Others
1. `terraform state`
2. `terraform state list`

#### `main.tf` : You can name it whatever you want though

#### `terraform.tfstate` : DONT DELETE THIS
The internal state file of current state in the cloud.

#### `providers` : AWS, Azure etc. To work with any platform, you need to download the respective `provider`.

You can setup the Provider at the top level in `main.tf`

```tf
provider "aws"{
	region = "ap-south-1"
	access_key = "................."
	secret_key = "................."
}
```

#### `resources`: Way to provision resources

```tf
resource "<provider>_<resource_type>" "name"{
    config options...
	key = "value"
	key2 = "value"
}
```

eg: How to provision an EC2 instance
```tf
resource "aws_instance" "web"{
	ami				= "ami-0859........"
	instance-type	= "t2-micro"
}
```

eg: How to provision a VPC and a subnet.
```tf
resource "aws_vpc" "first_vpc"{
	cidr_block = "10.0.0.0/16"
}

resource "aws_subnet" "subnet-1"{
	vpc_id	= aws_vpc.first_vpc.id    // this is how you reference other resources
	cidr_block = "10.0.1.0/24"
}
```

> Note on referencing: The order in which you place the code does not matter in terraform. Perfect declarative programming.


## Sample Project

1. Create VPC
2. Create IGW
3. Create Custom Route Table
4. Create a subnet
5. Associate subnet with Route Table
6. Create Security Group to allow port 22,80,443
7. Create a network interface with an IP in the subnet that was created in #4
8. Assign an elastic IP to the network interface created in #7
9. Create Ubuntu Server and install/enable apache2


First create a Key-Pair. PEM, download and store it safely.


### `main.tf`

```tf

provider "aws"{
	region = "ap-south-1"
	access_key = "................."
	secret_key = "................."
}

resource "aws_vpc" "prod-vpc"{
	cidr_block = "10.0.0.0/16"
	tags = {
		Name = "production"
	}
}

resource "aws_internet_gateway" "gw"{
	vpc_id	= aws_vpc.prod-vpc.id    // this is how you reference other resources
}

resource "aws_route_table" "prod-route-table"{
	vpc_id	= aws_vpc.prod-vpc.id    // this is how you reference other resources

	route {
		cidr_block = "0.0.0.0/0"
		gateway_id = aws_internet_gateway.gw.id
	}

	route {
		ipv6_cidr_block = "::/0"
		gateway_id = aws_internet_gateway.gw.id
	}
}

resource "aws_subnet" "subnet-1"{
	vpc_id	= aws_vpc.prod-vpc.id    // this is how you reference other resources
	cidr_block = "10.0.1.0/24"
	availability_zone = "ap-south-1"
}

resource "aws_route_table_association" "a"{
	subnet_id	= aws_subnet.subnet-1.id
	route_table_id	= aws_route_table.prod-route-table.id
}

resource "aws_security_group" "allow_web"{
	name = "allow_web_traffic"
	description = "Allow Web inbound traffic"
	vpc_id = aws_vpc.prod-vpc.id

	ingress {
		description = "HTTPS"
		from_port	= 443
		to_port		= 443
		protocol	= "tcp"
		cidr_blocks = ["0.0.0.0/0"] //anyone can access
	}
	ingress {
		description = "HTTP"
		from_port	= 80
		to_port		= 80
		protocol	= "tcp"
		cidr_blocks = ["0.0.0.0/0"] //anyone can access
	}
	ingress {
		description = "SSH"
		from_port	= 22
		to_port		= 22
		protocol	= "tcp"
		cidr_blocks = ["0.0.0.0/0"] //anyone can access
	}
	egress {
		from_port	= 0
		to_port		= 0
		protocol	= "-1"     // any protocol
		cidr_blocks	= ["0.0.0.0/0"] // to anyone
	}
}

resource "aws_network_interface" "web-server-nic" {
	subnet_id = aws_subnet.subnet-1.id
	private_ips = ["10.0.1.50"]
	security_groups = ["aws_security_group.allow_web.id]
}

resource "aws_eip" "one" {
	vpc			= true
	network_interface = aws_network_interface.web-server-nic.id
	associate_with_private_ip = "10.0.1.50"
	depends_on = [aws_internet_gateway.gw]  // eip needs a igw, else error
}

resource "aws_instance" "web-server-instance"{
	ami = "ami-1010033434...."
	instance_type = "t2.micro"
	availability_zone = "ap-south-1a"
	key_name = "main-key" // you created this at the very beginning

	network_interface {
		device_index = 0
		network_interface_id = aws_network_interface.web-server-nic.id
	}

	user_data = <<-EOF
		#!/bin/bash
		sudo apt update -y
		sudo apt install apache2 -y
		sudo systemctl start apache2
		sudo bash -c 'echo your first web server > /var/www/html/index.html'
		EOF
}
```
