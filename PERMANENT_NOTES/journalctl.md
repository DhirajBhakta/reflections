**view logs** of all the services running in the system, managed by systemd.

The logs are collected by `systemd-journald.service` (service collects logs of other services.)

#### `journalctl -u nginx.service` Show logs only for a particular unit. (-u stands for unit)

#### `journalctl -f -u nginx.service` to tail the logs...

