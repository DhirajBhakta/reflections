# Why?
Traffic capture on your local machine/ remote machine.

## Basic CMD
- `tcpdump -w file` : write output to file
- `tcpdump -i eth0` : specify the interface
- `-v`: verbose option

## Basic filters
tcpdump filters are same as wireshark filters
### Host filter
- `host 192.168.1.1` : filter
- `host google.com` : filter
- `host bbc.com` : filter

### src | dst filter
- `dst 192.168.1.1` : filter
- `src google.com` : filter
- `host bbc.com` : filter

## Combining filters
### "and"
```
tcpdump -i wlan0 -v dst 192.168.107 and src 192.168.1.1
```
