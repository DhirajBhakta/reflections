
### Objects are Immutable
All objects in Git are **Immutable**. 
Git never alters the contents of a commit. 
- Even if you `--amend` a commit ... 
- Even if you `cherry-pick` a commit onto another branch ...
a brand new commit is created with a new hash, the old one is untouched. You can restore them if you need to.

### Reflog
Every action is tracked in `git reflog`. 
Even a destructive action like _rebasing_ can be recovered since commits are immutable.

Every commit, branch, checkout, rebase, reset, etc. all are tracked, and from this history we can restore any version of the code.

Try `git reflog`
```sh
$ git reflog 3001aaf HEAD@{0}: pull: Fast-forward 1576f8b HEAD@{1}: pull: Fast-forward 7caa99e HEAD@{2}: merge update-rss-summaries: Fast-forward 1a8a17d HEAD@{3}: checkout: moving from update-rss-summaries to master 7caa99e HEAD@{4}: checkout: moving from master to update-rss-summaries 1a8a17d HEAD@{5}: checkout: moving from update-rss-summaries to master 7caa99e HEAD@{6}: rebase -i (finish): returning to refs/heads/update-rss-summaries # ...
```

For a specific branch
```sh
git reflog show <branch>
```