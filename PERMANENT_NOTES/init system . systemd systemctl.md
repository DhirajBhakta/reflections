Systemd is the default init system. `/sbin/init` runs as PID1, is the parent of all processes. 
Systemd is not limited to being PID1, systemd is a collection of tools. Systemd supersedes SysVinit or init.

It starts alll the startup services _parellely_  .

>**Note**
>`/sbin/init` is a symlink to `/usr/lib/systemd/systemd`

### List all the services
`systemctl` 

The service files (unit files) are located in `/usr/lib/systemd/system` and `/etc/systemd/system`.  The status command `systemctl status <servicename>` will show you where the unit file is. **The unit file contains the `ExecStart`, the command used to run the service. You get the startup args here**.

### Status of a service
`systemctl status <servicename>`

### Enable a service (to start at boot)
`systemctl enable <servicename>`

### Start a service (right away)
`systemctl start <servicename>`



a service file(unit file) looks like the following . Note `ExecStart`
```
[Unit]
Description=Docker Application Container Engine
Documentation=https://docs.docker.com
After=network-online.target docker.socket firewalld.service containerd.service time-set.target
Wants=network-online.target containerd.service
Requires=docker.socket

[Service]
Type=notify
# the default is not to use systemd for cgroups because the delegate issues still
# exists and systemd currently does not support the cgroup feature set required
# for containers run by docker
ExecStart=/usr/bin/dockerd -H fd:// --containerd=/run/containerd/containerd.sock
ExecReload=/bin/kill -s HUP $MAINPID
TimeoutStartSec=0
RestartSec=2
Restart=always

# Note that StartLimit* options were moved from "Service" to "Unit" in systemd 229.
# Both the old, and new location are accepted by systemd 229 and up, so using the old location
# to make them work for either version of systemd.
StartLimitBurst=3

# Note that StartLimitInterval was renamed to StartLimitIntervalSec in systemd 230.
# Both the old, and new name are accepted by systemd 230 and up, so using the old name to make
# this option work for either version of systemd.
StartLimitInterval=60s

# Having non-zero Limit*s causes performance problems due to accounting overhead
# in the kernel. We recommend using cgroups to do container-local accounting.
LimitNOFILE=infinity
LimitNPROC=infinity
LimitCORE=infinity

# Comment TasksMax if your systemd version does not support it.
# Only systemd 226 and above support this option.
TasksMax=infinity

# set delegate yes so that systemd does not reset the cgroups of docker containers
Delegate=yes

# kill only the docker process, not all processes in the cgroup
KillMode=process
OOMScoreAdjust=-500

[Install]
WantedBy=multi-user.target
```

