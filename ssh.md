# Why SSH &mdash; Secure SHell
[blackmagicOfSSH](https://vimeo.com/54505525)

remote management of UNIX-like systems and many network devices

Secure shell (SSH) is a protocol for creating an **encrypted communications channel** between two networked hosts.

### what is "openSSH"
opensource implementation of SSH. lol

There's a team of BSD geeks (openBSD) which actively maintains a branch of _clean_ , _light_ openSSH which just works for BSD. another team works hard to maintain another branch which is portable across so many linux distros..while patching from the main branch


**replacement of**: telnet, RSH, rlogin, FTP

**foundation of** :SCP, SFTP

### SSH Server (sshd)
Listens on the network for incoming SSH requests

How to check if sshd is running (from outside)?
While the surest way is just logging into the server, a better way would be just check if the PORT 22 responds to a TCP request

`netcat -v 12.11.1.2 22` will print the SSH banner!

How to check if sshd is running (from inside)?

`ps ax | grep sshd`

If its not running, enable it using `systemctl restart sshd`

### SSH client (ssh)
User uses ssh client to connect to a remote machine. (remote machine runs the SSH server)

### SSH encryption of the communication channel
_**Cryptographic key exchange is the heart of SSH protocol**_

You know that the SSH server holds the public key

You know that the SSH client holds the private key

You also know Asymmetric encryption is very slow compared to symmetric.

So, SSH will use Asymmetric encryption 
 1. to negotiate & securely exchange a temporary key pair.
 2. Use this temporary key pair to derive a symmetric key.
 3. Use that symmetric key for <u>further communication using symmetric encryption</u>

If the connection runs for a long time, the connection will intermittently repeat the above process


## Configuration /etc/ssh

ssh (the client) has its config in `/etc/ssh/ssh_config`

sshd (the server) has its config in `/etc/ssh/sshd_config`

### Configuring sshd (server)
-> lets you restrict who can connect to this server, what actions they can take

While editing sshd_config, you can use the following debugging approaches
- Alternate config files & ports
- debug mode

Lets start by using an alternate config...cuz..who wants to mess with the original config file . right?
`/usr/sbin/sshd -f sshd_config.test`. Okay. this will error out. Because your original sshd is already running on port 22. So edit sshd_config.test file to bind to another port OR just `/usr/sbin/sshd -f sshd_config.test -p 2222`. 

#### Verify a config files (-t)
`sshd -t`

#### Running sshd in debug mode (-d)
Will be able to see in detail whats happening (during daemon startup, during client connection). BUT, only ONE client will be able to connect. Just one session. after that sshd will die. So use it just for debugging once. (Run this on alternate port -p 2222)

## SSH Tunnels &mdash; Local Port Forwarding
Access private resources on the cloud without exposing the port publicly
## SSH Tunnels &mdash; Remote Port Forwarding

# About telnet &mdash; granddaddy of ssh