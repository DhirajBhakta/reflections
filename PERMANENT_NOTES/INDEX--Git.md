TODO move important commands to  ** cheatsheet ** !
> *“In many ways you can just see git as a **filesystem — it’s content-addressable**, and it has a notion of versioning, but I really really designed it coming at the problem from the viewpoint of a filesystem person (hey, kernels is what I do), and I actually have absolutely zero interest in creating a traditional SCM system.”* 
> – Linus Torvalds
> See [[content addressable storage]]

> Git does NOT store diffs. It stores entire contents of a file as-is...as **blobs**. and stores the **snapshot** of the entire tree (repo). [[git internals|Git calculates the diff **ondemand**]]
> 

[[git design goals]] TODO
- how is git "efficient"" . deep dive into delta compression and pack files TODO
- what makes git a "distributed" VCS ? how exactly is it distributed?
[[Git  history is never lost]]
[[git best practises]]

### Alias
[[git alias]]

### Stashing
[[git stash]]
### Staging & Committing
[[git add-commit-merge workflow#Staging hunks piece by piece|Staging hunks piece by piece]]
Abort a commit (within vim) with `:cquit`

> _In Git, the opposite of `git push` is not `git pull`, but `git fetch`. A ‘pull’ is a ‘fetch’ and then a ‘merge’._

### Diff
`oldbranch..newbranch`
[[git log & git diff#Diff|Show new commits in newbranch]]
[[git diff#Diff between 2 branches|Show new changes in newbranch]]

### Cherry-picking
[[git diff#cherry-pick all commits between 2 branches|cherry-pick all commits between 2 branches]]

### Log
[[git log & git diff#List commits affecting a given file|Listing commits affecting the **given file**]]

### History
[[git log & git diff#Formatting git log|Formatting git log output]]

[[git log & git diff#Searching|Searching]]
- [[git log & git diff#Searching through commit messages|Searching through **commit messages**]]
- [[git log & git diff#Searching through code changes|Searching through **code changes**]]
- [[git log & git diff#List commits affecting a given file|Listing commits affecting the **given file**]]

_TODO: How to dig history to pinpoint the commit which introduced the func and walk forward until current state (even if the func was moved across files)...do the same for any given line too.._
### Undoing 
[[git reset#Unstage a file|Unstage a file]]
[[git reset#Reverting to the last commit|Discarding all changes in your working dir]]
[[git reset#Undo the latest commit|Undo the latest commit]] 
[[git reset#Undo a merge|Undo a merge]]

- TODO diff b/w --soft and --hard reset?
- TODO reverting to Nth commit before current?
- TODO how to do a hard reset on the branch, making it in sync with upstream remote branch?

### Internals
[[git internals]]
- `git show <sha>` sha can be commit,tree,blob

### Maintenance 
[[git garbage collection]]
### Misc
[[how to make your own git subcommands]]
[[lesser known git commands]] TODO
[[non SCM uses of Git]]


---
# Vim - Fugitive

`:GStatus`




