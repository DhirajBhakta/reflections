### Unstage a file
```sh
git reset filename
```
 Note: you might've been used to `git rm --cached` for the same, but that **removes** the file from index.

### Reverting to the last commit
...and throwing away all your uncommitted changes
```sh
git checkout .
```

### Undo the latest commit
```sh
git reset --soft HEAD^
```
`HEAD^`    : "parent" of HEAD. 
`--soft`  :  Leave the files in working dir untouched

### Undo a merge
You were doing a merge, and got lots of conflicts.. you want to abandon it all....
```sh
git reset --hard HEAD
```
> _`--hard` will reset BOTH index and working directory. 
 by default only index would have been reset, leaving the changes back in your working dir (--soft), but `--hard` is really "hard", brutal... will reset your working dir too._

But lets say you resolved ALL conflicts, and even committed..creating a merge commit..and now lots of tests fail!, you need to revert your merge commit!!
```sh
git reset --hard ORIG_HEAD
```
`ORIG_HEAD` is git saving your ass by keeping track of the `HEAD` _just before_ the previous merge/rebase/reset operation.
### Undo all commits
.. until its same as remote.
```sh
git reset --hard origin/master
```
All commits made on local `master` branch (above and beyond the remote) will be discarded.

