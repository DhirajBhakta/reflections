## Why tmux?
- in a regular terminal .. kill the terminal -> processes get killed. How do  we avoid killing the terminal?
- "detach" from your session, and continue right back where you left off... EVEN if your SSH connection to the remote machine breaks!

## Tmux is client-server
The client sends "commands" to the server.
The commands can be sent in 3 ways
- via kb shortcuts : `PREFIX %` splits the pane
- via command mode : `: split-pane`  splits the pane
- via cmd line : `tmux split-pane` 

## Tmux primitives
sessions, windows and panes
![](https://miro.medium.com/max/598/1*wDlRZIj8fTwxxghD0XRDbA.png)
![[tmux.png]]


### The Command Prefix
`< C - b >`

### Pane Management
##### Split Horizontally
`PREFIX "`

##### Split Vertically
`PREFIX %`

##### Cycle through panes
`PREFIX Spacebar`

##### killing a pane
`PREFIX x`

##### Resize all panes
`:select-layout tiled`
`:select-layout even-horizontal`
`:select-layout even-vertical`
`:select-layout main-horizontal`
`:select-layout main-vertical`

##### Zoom into a pane 
`PREFIX z`

##### Send keys to all the panes in a window
Write once to the pane you want to send keys to and then write the keys you want to send to all the other panes in that window.
`:setw synchronize-panes on`
..later,
`:setw synchronize-panes off`

=======
## Sessions

| shortcut   | :command | shell                         | description               |
| ---------- | -------- | ----------------------------- | ------------------------- |
|            |          | `tmux new-session -s [name]`  | create a named session    |
|            |          | `tmux attach -t [name]`       | attach to a named session |
|            |          | `tmux attach`                 | attach to default session |
| `PREFIX d` |          |                               | detach from session       |
|            |          | `tmux kill-session -t [name]` | kill a session            |
|            |          | `tmux list-sessions`          | list all sessions         |

## Windows
| shortcut                 | :command | shell | description        |
| ------------------------ | -------- | ----- | ------------------ |
|                          |          |       | new window         |
| `PREFIX n` \| `Prefix p` |          |       | cycle windows      |
| `PREFIX [num]`           |          |       | goto window number |


## Panes

| shortcut             | :command | shell | description                      |
| -------------------- | -------- | ----- | -------------------------------- |
| `PREFIX %`           |          |       | split vertically                 |
| `PREFIX "`           |          |       | split horizontally               |
| `PREFIX [arrowkeys]` |          |       | move between panes               |
| `PREFIX o`           |          |       | cycle panes                      |
| `PREFIX space`       |          |       | try out different window layouts |
| `PREFIX !`           |          |       | promote pane to its own window   |


# Advanced

### Scrolling in "copy mode"
`PREFIX [` enters copy mode, and you can use arrow keys to scroll.
You can enable vi mode in copy mode 
```sh
set-window-option -g mode-keys vi
bind-key -T copy-mode-vi v send -X begin-selection
bind-key -T copy-mode-vi V send -X select-line
bind-key -T copy-mode-vi y send -X copy-pipe-and-cancel 'xclip -in -selection clip clipboard'
# for macOS
bind-key -T copy-mode-vi y send -X copy-pipe-and-cancel 'pbcopy'
>>>>>>> 16607dc (random push [2025] : git,cas)
```

### 256-color $TERM
add to `~/.tmux.conf`
```sh
set-option -g default-terminal "screen-256color"
```

### Take your bindings on trial mode
```
tmux bind-key u split-window
```
OR... via tmux command prompt
```sh
:bind-key u split-window
```
then you can try `PREFIX u` to check if the new binding works without polluting your `~/.tmux.conf`

### `~/.tmux.conf` 
adding the following will reload the tmux conf with `PREFIX r` 
```
bind-key r source-file ~/.tmux.conf \; display-message "~/.tmux.conf reloaded"
```
Note: `\;` helps write multiple commands in one line

Same could've been done by `:source ~/.tmux.conf` in tmux command prompt 
OR..
`tmux source ~/.tmux.conf` in the terminal


...
adding the following helps create new rebindings for switching between panes instead of `PREFIX [arrowkeys]`
```sh
bind-key -n C-h select-pane -L
bind-key -n C-j select-pane -D
bind-key -n C-k select-pane -U
bind-key -n C-l select-pane -R
```
Note: `-n` flag is to avoid needing `PREFIX` . so i can directly hit `CTRL-h` and left pane would get selected.


...
adding the following helps quickly opening frequently used commands like `htop` upon splitting a window
```sh
bind-key h split-window -h "htop"
bind-key t split-window -h -c ~/ "vim todo.md"
# or just
bind-key t split-window -h "vim ~/todo.md"
```
