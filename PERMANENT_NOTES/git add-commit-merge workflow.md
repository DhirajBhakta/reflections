`git add .` is way too coarse. 
`git add <filename>` might _also_ be coarse.

What if you want to stage just a portion of changes in a given file and postpone other changes to next commit?

### Staging hunks piece by piece
review each group of changed lines and decide whether or not to stage a hunk.
```sh
git add --patch
```


### Rebase
You're on branch `feat` and you run 
```sh
git rebase master
```
You're **"rebasing"** your current branch onto the `master` branch.
i.e **shifting** the _base_ of your current branch (common ancestor with `master`) on to the HEAD of the `master` branch ...._Essentially giving you a linear history!_ 
![[git-00.svg]]

Same is the effect when you run `git pull origin master --rebase`

Note that internally, the diffs are taken and replayed, commit by commit, to **create brand new commits**, ...always remember [[Git  history is never lost]].

How is rebase different from a merge?
![[git-02.png]]

### What's a fast-forward merge?
  With fast-forward merges, **no new commits are created**, but instead the merging branch (typically master) is only moved to point at the commits on the target branch (typically our feature branch).
  Why? because there is nothing to merge! all commits that master has, feature branch also has it. the "merging" is then all about moving the master's HEAD pointer forward towards the HEAD of the feature branch...._fast forwarding_. 
  Creating a merge commit just for this is plain wasteful!
  
 `git pull origin master --ff-only`
 or 
 `git merge feat/xxx --ff-only`
 
  Tells Git to reject merges that are non-fastforward. 


### Squashing commits
...with _interactive rebase_ `git rebase -i `
```sh
git rebase -i HEAD~6
```
The listing you see is in **reverse chronological order** !!
`squash` on commits you want to squash on to the previous.
`pick` on the commit you want all the others to squash on to. (this will be the oldest compared to all other squashed commits)
```
pick abc123 Commit message 1
pick def456 Commit message 2
s ghi789 Commit message 3
s jkl012 Commit message 4
s mno345 Commit message 5
pick pqr678 Commit message 6
```



### Stashing your current changes...
..._because you're urgently required to halt your work on current branch , and do something important on another branch..._
```sh
git stash
```
...
then switch you branch, do the work, and come back..
```sh
 $ git stash list
  stash@{0}: WIP on experiment: 89e6d12... trying git archive
  stash@{1}: WIP on master: c110d7f... made the ls-tree function recursive
  stash@{2}: WIP on master: c110d7f... made the ls-tree function recursive

$ git stash show stash@{1}
   lib/simplegit.rb |    4 ++++
   1 files changed, 4 insertions(+), 0 deletions(-)

  $ git stash show stash@{2}
   lib/simplegit.rb |    8 ++++++++
   1 files changed, 8 insertions(+), 0 deletions(-)


$ git diff stash@{1}
  diff --git a/lib/simplegit.rb b/lib/simplegit.rb
  index e939f77..b03bc9c 100644
  --- a/lib/simplegit.rb
  +++ b/lib/simplegit.rb
  @@ -21,10 +21,6 @@ class SimpleGit

      command(“git ls-tree -r -t #{treeish}”)
    end

  -  def commit(message = ‘commit message’)
  -    command(“git commit -m #{message}”)
  -  end
  -

    private
      def command(git_cmd)
```

... and then finally apply the stash
```sh
git stash apply stash@{1}
```

> **Note**: usually you just apply the topmost stash  on the stack with `git stash pop`
