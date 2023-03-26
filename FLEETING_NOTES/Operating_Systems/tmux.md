https://danielmiessler.com/study/tmux/


One of tmux’s biggest advantages is that we can fire it up, start up programs or processes inside the tmux environment, and then leave it running in the background by “detaching” from the session.If we close a regular terminal session, all the programs we have running inthat session are killed off. But when we detach from a tmux session, we’renot actually closing tmux. Any programs we started up in that session willstay running. We can then “attach” to the session and pick up where we leftoff.


sessions, windows and panes
![](https://miro.medium.com/max/598/1*wDlRZIj8fTwxxghD0XRDbA.png)

# The Command Prefix
< C - b >

# Session Management

### Creating a named session
`tmux new-session -s [name]`

### Attach to a named session
`tmux attach -t [name]`

### Detach from a session
`PREFIX d`

### Kill a session
`tmux kill-session -t [name]`

### List all sessions 
`tmux ls`

# Window Management

### Create a new window
`PREFIX c`

### Renaming a window
`PREFIX ,`

### Cycling between windows
`PREFIX n` or `PREFIX p`   [ next and previous]

`PREFIX w` is also great (ncurses)

### Killing a window
`PREFIX &`



# Pane Management
### Split Horizontally
`PREFIX "`

### Split Vertically
`PREFIX %`

### Cycle through panes
`PREFIX Spacebar`

### killing a pane
`PREFIX x`

```
Ctrl-b q Show pane numbers (used to switch between panes)
Ctrl-b o Switch to the next pane
Ctrl-b ? List all keybindings
```
# moving between windows
Ctrl-b n (Move to the next window)
Ctrl-b p (Move to the previous window)
Ctrl-b l (Move to the previously selected window)
Ctrl-b w (List all windows / window numbers)
Ctrl-b window number (Move to the specified window number, the
default bindings are from 0 -- 9)

# Tiling commands
Ctrl-b % (Split the window vertically)
CTRL-b " (Split window horizontally)
Ctrl-b o (Goto next pane)
Ctrl-b q (Show pane numbers, when the numbers show up type the key to go to that pane)
Ctrl-b { (Move the current pane left)
Ctrl-b } (Move the current pane right)

# Make a pane its own window
Ctrl-b : "break-pane"

# add to ~/.tmux.conf
bind | split-window -h
bind - split-window -v