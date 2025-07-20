
# tldr;
Branches
- A branch is just a file holding the shasum of the commit it points to. 
- Creating a branch is nothing more than just writing 40 characters to a file.
- "Switching" to a branch is nothing more than writing the path to the branch eg: `refs/heads/master` to the file named `HEAD` .
Commits
- Git does NOT store diffs, but stores entire content of the file when its first tracked, and everytime the file has changes. (Yes, seems bloaty..but zlib and pack files are too good.)

# How git stores and references our code
_The Git Object Database_

`.git` dir holds all the objects (branches, remotes, commits, blobs etc)
Its a **file based DB** 
```sh
tree .git
.git
├── HEAD
├── config
├── description
├── hooks/
│   ├── applypatch-msg.sample
|   └── # ... (other hooks)
├── info/
│   └── exclude
├── objects/
│   ├── info/
│   └── pack/
└── refs/
    ├── heads/
    └── tags/
```

`HEAD` -> pointer to the currently checked out object/ref.
`objects/` --> (immutable) all commits and blobs(files) and trees (dirs)
`refs/` --> (mutable) all branches, tags, remotes

### What happens when you run `git add <filename>` for the first time
(_...the file is NOT tracked yet,_)
`git add README.md`

```sh
tree -I "info|pack" .git/objects
.git/objects
└── 3b
    └── 18e512dba79e4c8300dd08aeb37f8e728b8dad
```
`3b18e512dba79e4c8300dd08aeb37f8e728b8dad` is the shasum (SHA-1)of the **contents of the file** (https://en.wikipedia.org/wiki/Content-addressable_storage) we just added (README.md), and has nothing to do with filename or metadata.... _just content._
(The filenames are stored in parent `tree` object)
> Notice  the first 2 chars are used to name the dir (performance optimisation)


To see the content of this file 
`git cat-file -p 3b18e512` outputs "hello world"

To check the _type_ of the object (blob/tree/commit)
`git cat-file -t 3b18e512` outputs "blob"

How was this sha generated? ...from the contents of the file.
`echo -e 'blob 12\0hello world' | shasum`

### What happens when you `git commit`?
2 new objects will be created
- tree (for current dir holding the `add`ed file)
- commit

 A "tree" in Git is an object (a file) which contains a list of pointers to blobs or other trees. Each line in the tree object's file contains a pointer (the object's hash) to one such object (tree or blob), while also providing the mode, object type, and a name for the file or directory.
```sh
git add readme.md
git commit -m 'Add readme'
tree -I "info|pack" .git/objects
.git/objects
├── 3b
│   └── 18e512dba79e4c8300dd08aeb37f8e728b8dad
├── 73
│   └── 94b8cc9ca916312a79ce8078c34b49b1617718
└── ef
    └── 34a153025fffb8a498fff540f7c93963937291

```

```sh
git cat-file -t ef34a15
tree

git cat-file -p ef34a15
100644 blob 3b18e512dba79e4c8300dd08aeb37f8e728b8dad    readme.md
```

Every commit object points at a tree.
There are too many objects now in `.git/objects`, so lets use `ls-tree` on the branch `master`. The branch points at a commit. The commit points at a tree, hence you shall see the contents of the tree object.
```sh
git ls-tree master
040000 tree 67b21f78a4548b2ba3eab318bb3628d039e851e6 app 
100644 blob 3b18e512dba79e4c8300dd08aeb37f8e728b8dad readme.md

git ls-tree 67b21f78a4548b2ba3eab318bb3628d039e851e6 
100644 blob e69de29bb2d1d6434b8b29ae775ad8c2e48c5391 script.rb
```

The commit object can be inspected too..
```sh
git cat-file -p f95b2fe 
tree 0cae7dc167b255c0123c7c396fc48ce40fc35cfa parent ef34a153025fffb8a498fff540f7c93963937291 author Chris Toomey <chris@ctoomey.com> 1441311544 -0400 committer Chris Toomey <chris@ctoomey.com> 1441311544 -0400 Another file in app dir
```
It contains
- hash of the current tree obj
- hash of prev commit 
- commit details (author, date, msg)
(Note: a "merge commit" has 2 parent commit hashes)

> **Note**: The commit DOES NOT STORE DIFFS !!
> Diffs are computed on demand.

# Git Object Model
Objects
- Blobs : store the contents of a  version of a file
- Trees  : store directory listing, holding pointers to blobs and other trees
- Commits : hold a pointer to a single Tree, a single parent commit, and commit info (author, timestamp, msg)
Refs
- Branches : store the commit sha
- Tags : store the commit sha
- Remote Branches : store the commit sha
Head: Singleton pointer to branch/commit
(Note: sometimes, tags can have extra metadata , "messages", or maybe digitally signed. In such cases, all these things are packaged into a immutable blob in objects/ dir and _ITS_ hash is stored in the tag, not the commit. One added level of indirection)

Blobs...
![[git-04.png]]

Trees..
![[git-05.png]]

![[git-03.png]]

### Refs
 _Ref = file whose contents are the hash of a single commit_
 **Branches & Tags are just pointers; nothing more!**
 (But Branches can change what they point at, ..everytime you commit, the branch pointer moves..everytime you merge/fastforward/rebase..the branch pointer moves..
 BUT
 tags cannot..tags are locked on to a single commit for their lifetime.)
```
$ tree .git/refs
.git/refs
├── heads/
|   └── master
└── tags/
    └── v0.1
```
`heads` hold the local branches
why "heads"? because branches are collection of things that `HEAD` can point at.
**`HEAD` is the ultimate ref, defining what we currently have checked out.**

A ref(branch/tag) is nothing but a file which contains the sha of the commit it points to 
```
$ cat .git/refs/heads/master
f95b2fe3b64c6351e7eec4011921b4469098b9ba

$ git cat-file -t f95b2fe3b64c6351e7eec4011921b4469098b9ba 
commit 

$ git cat-file -p f95b2fe3b64c6351e7eec4011921b4469098b9ba 
tree 0cae7dc167b255c0123c7c396fc48ce40fc35cfa 
parent ef34a153025fffb8a498fff540f7c93963937291 

author Chris Toomey <chris@ctoomey.com> 1441311544 -0400 
committer Chris Toomey <chris@ctoomey.com> 1441311544 -0400 

Another file in app dir

```

Same story with Tags...
```
$ cat .git/refs/tags/v0.1
f95b2fe3b64c6351e7eec4011921b4469098b9ba
```

Same story with Remote branches ...
(_Remotes are **pointers** to branches in some other guy's repo_)
```
$ tree .git/refs
.git/refs
├── heads/
|   ├── deck-last-attempt
|   ├── master
|   ├── ... (truncated)
|   └── welcome-trail
├── remotes/
│   ├── origin
│   │   ├── HEAD
│   │   ├── cjt-north-star-metric
│   │   ├── master
│   │   ├── mg-button-colors
│   │   └── ... (truncated)
│   ├── production
│   │   └── master
│   └── staging
│       ├── dashboard-staging
│       ├── ... (truncated)
│       └── master
└── tags/
	└── v0.1
```


```
$ cat .git/refs/origin/cjt-north-star-endpoint
3891a7bc21e5e0c69e71e8153bb8b4a67b80bff5

$ git cat-file -t 3891a7bc21e5e0c69e71e8153bb8b4a67b80bff5
commit

$ git cat-file -p 3891a7bc21e5e0c69e71e8153bb8b4a67b80bff5
tree 32022b6465ebf9f9e37b7e1caccb3c9e620dd465
parent 7262141ae317f56b567ed2f95505e6ca9bbe1605
author Chris Toomey <chris@ctoomey.com> 1433384047 -0400
committer Chris Toomey <chris@ctoomey.com> 1435239388 -0400

WIP analytics JSON endpoint
```


### `HEAD` object
It identifies the currently checked out object (typically, a branch..which in-turn points to a commit). 
**Its a singleton. only ONE `HEAD` can exist**

The `HEAD` object's contents ..
```
$ cat .git/HEAD
ref: refs/heads/master
```
Its possible though, to directly point at a commit (detached HEAD state)
```
$ git checkout 833c1ea

$ cat .git/HEAD
833c1ea55d76adcf48b5f7e933271fcc3e36f123
```

//TODO:summarize
When most SCMs store a new version of a project, they store the code delta or diff. When Git stores a new version of a project, it stores a new tree – a bunch of blobs of content and a collection of pointers that can be expanded back out into a full directory of files and subdirectories. If you want a diff between two versions, it doesn’t add up all the deltas, **it simply looks at the two trees and runs a new diff on them**.

This is what fundamentally allows the system to be easily distributed – it doesn’t have issues figuring out how to apply a complex series of deltas, it simply transfers all the directories and content that one user has and another does not have but is requesting. It is efficient about it – it only stores identical files and directories once and it can com- press and transfer its content using delta-compressed packfiles – but in concept, it is a very simple beast. Git is at it’s heart very stupid- simple.

//TODO:
But will this not bloat?
- delta compression is way too good. 13M for Git = 120M in Svn !!! (Svn stores diffs!!!)
- zLib ?


### `git show` |  `git ls-tree` | `git cat-file`
...any object or ref: commit/tree/blob  branch/tag
shows the objects contents in human readable format.
```sh
git show <sha>
```

```
$ git show master^
  commit 0c8a9ec46029a4e92a428cb98c9693f09f69a3ff
  Author: Scott Chacon <schacon@gmail.com>
  Date:   Mon Mar 17 21:52:11 2008 -0700

      changed the verison number

  diff --git a/Rakefile b/Rakefile
  index a874b73..8f94139 100644
  --- a/Rakefile
  +++ b/Rakefile

  @@ -5,7 +5,7 @@ require ‘rake/gempackagetask’
   spec = Gem::Specification.new do |s|

       s.platform  =   Gem::Platform::RUBY

       s.name      =  “simplegit”
  -    s.version   =  “0.1.0”
  +    s.version   =“0.1.1”

       s.author    =  “Scott Chacon”
       s.email     =  “schacon@gmail.com”
       s.summary   =“A simple gem for using Git in Ruby

code.”
```

For Tree objects, `git ls-tree <sha>` is more useful
```
$ git ls-tree master^{tree}
100644 blob 569b350811e7bfcb2cc781956641c3
100644 blob 8f94139338f9404f26296befa88755
040000 tree ae850bd698b2b5dfbac1ab5fd95a48

README
Rakefile
lib
```

Can run recursively from a given tree object too!!
```
$ git ls-tree -r -t master^{tree}

100644 blob 569b350811e7bfcb2cc781956641c
100644 blob 8f94139338f9404f26296befa8875
040000 tree ae850bd698b2b5dfbac1ab5fd95a4
100644 blob 7e92ed361869246dc76f0cd0e526e
rb

README
Rakefile
lib
lib/simplegit.
```

To inspect contents of blobs, `git cat-file -p <sha>` is more useful.
(-t is for type, -p is for contents)
```
git cat-file -t ae850bd698b2b5dfbac
  tree
  $ git cat-file -p ae850bd698b2b5dfbac

100644 blob 7e92ed361869246dc76
$ git cat-file -t 569b350811
blob
$ git cat-file -p 569b350811
SimpleGit Ruby Library
======================

simplegit.rb

  This library calls git commands and returns the output.
  It is an example for the Git Peepcode book.
  Author : Scott Chacon
```

### What happens when you create a new branch?
Checking out a new branch is just the act of creating a ref file, specifically a "head", and populating it with the relevant commit hash.
```
$ git checkout -b new-branch
```
First Git will follow from the `HEAD` to the current branch to determine what commit hash that branch points at. With that info, Git creates a new file in `.git/refs/heads`with our new branch name as the file name, and the commit hash as the contents. Lastly, it updates `HEAD` to point at this new ref.



### What happens when you checkout a tag?
_(applies to checking out a branch or a specific commit)_
![[git-07.png]]
Note that here the tag is not a mere ref, but a tag with more metadata (eg "messages", or digital signature), and hence is stored as an object in `objects/` dir..which eventually points to the commit. (one level of extra indirection). The tag ref in `refs/` dir just holds the shasum of the tag obj in `objects/` dir.

### Checking out a particular version of a file
```
$ git checkout master -- app/assets/javascripts/application.js
```
- Get the commit hash from ref's contents : `.git/refs/heads/master` will contain the commit id
- Get the Tree sha from the contents of the commit sha: `.git/objects/<2 letters of commit sha>/<rest of the commit sha>` will contain the tree object's sha
- walk down the Tree until you find the Tree object that contains the file "application.js" and get its blob sha
- the blob sha contains the contents of that file ! Git will restore that version of that file.

### What happens when you do a fast forward merge
```
$ git merge --ff-only feat/xxx
```
 
It creates no new objects...just updating the current branch to reference a different commit.(remember, the "branch" is a ref...just a file holding the commit sha it points to)
 
_why prefer the fast-forward only merges. we are just updating a pointer, but the code is not changed. In a traditional merge, Git does its best to bring together two different versions of the code, **creating a new commit and tree** that we have not interacted with._

### What happens when you merge
```
$ git merge feat/xxx
```
1.  Git creates a new tree for us from the two existing (diverging) trees.
2. Git will create a new commit that points at this new tree. 
3. The branch ref will be updated to point at this new commit.

> Note that traditionally you merge 2 branches, but you can merge N branches into a single merge commit!
### What happens when you rebase
```
$ git rebase master
```
Rebase can be performed when we have new commits on both our feature branch, and our "upstream" branch (typically `master`). We want to update the commits on our branch so they include the changes on `master`.

When we rebase, we essentially replay our work on the current version of the upstream branch. **Git does this by calculating each of the diffs for the commits unique to our branch, then applies them onto the upstream branch one by one. Each application of a diff creates a new commit, reusing the associated commit message and author details.**

Note that the old commits still exist, but they are now orphaned. No refs point to them any longer and so they are essentially unreachable (but you can, via reflog) 

Once all the new commits have been created, our branch is updated to point at the tip commit of our rebased group.

From here, we could now fast-forward merge the master branch into ours, as we are now in line with its history. The key difference between this and a traditional merge is that all of the commits here were created by us, and we get to interact with them and test them as needed before merging them into master.


### How does the commit history look like ?

![[git-08.png]]


### What happens when you clone a repo ?
TODO

### What happens when you `git fetch` ?
TODO
pulls all the refs and objects that you don’t already have from the remote repository


### What happens when you `git rm <filename>`?
TODO.
removed from the index(tree) in the next commit, as well as from the working dir.
BUT, its still present in the history !! cuz [[Git  history is never lost]] 

