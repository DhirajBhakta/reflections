### Split architecture related changes from main feature development
Oftentimes when you start working on a feature, you realise the arch is a mess, you refactor a lot, and then add your feature and ship them all in the **same PR**. DONT do this!
- separate PR for arch changes.
- separate PR for feature development.


### Raise PRs very early
Helps you and your team get a broad overview of what's to be done, specially when you **include a task list** in the PR description.

### Descriptive PR description
- context.
- why is this change needed?
- what business problem does it solve?
- other approaches considered, and why they were dropped?
- assumptions made.
- include screenshots/screen recordings
- include a task list with `[x] [ ] ...`

### Squash commits into single commit prior to merge
... via [[git add-commit-merge workflow#Squashing commits|Interactive Rebase]]
But most git hosting services do this automatically. Github actions/ Gitlab prior to merging PR, you can "squash commits and discard branch".

### Use a Linear git history...allow for fast-forward merges
...Prefer `rebase` over `merge` to keep the history linear.
rebase your feature branch on to master ...... do this often.
(_your commits on feat branch should always be ahead of the latest master_)

Note: you'll need to **force push** your feat branch if you embrace rebasing (because commit hashes change everytime you rebase). 
However, **Never rebase public branches!!** , **Never force push public branches** 

When the PR is "merged", it shall just be a fast forward merge   `git checkout master && git pull && git merge feat --ff-only` . i.e,  a brand new "merge" commit will NOT be created and the HEAD just fast forwards to the tip of feat branch. 
Your history will be clean from noise (merge commits).

^ This would be harder to enforce since most git hosting platforms allow merge commits to be the default during PR merges. 




