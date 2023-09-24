> Alternatively, `ps -ef` 

Lists all processes running on the system
- `a` : display all processes, incl those owned by other users
- `u` : display userID
- `x` : display background processes too, those not attached to a terminal


### To display Process Tree : `ps --forest`
Combine it with `ps aux --forest` 
You can also use `pstree` . `pstree -p <PID>` . The `-p` option is for displaying PIDs in the output.
### To display Threads : `ps -t <PID>`
