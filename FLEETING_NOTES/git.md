### Misc

Learn fugitive!!!
- 3way diff?
- diffget
- Gread
- Gremove
-
git show
git reset <filename>    `removes the file from staging area, but keeps it in working dir`
git reset `removes ALL files from staging area into working dir`
git reset --soft HEAD^ `what is --soft and HEAD^ what is ^`
exit vim with `:cquit` to exit with nonzero exit code...(error) to prevent committing once you enter vim with git commit. 
git add --patch (whats a hunk?)
git diff origin/master..master
git cherry-pick origin/master..master
git checkout master && git reset --hard origin/master (what is --hard)
git full-commit
"git object model"...
tree -C .git
tree -C -I "info|pack" .git/objects
git cat-file -p 3b18e5 (holds blobs. what are blobs? contents of a file.)
https://www.jonathancreamer.com/how-we-shrunk-our-git-repo-size-by-94-percent/
echo -e 'blob 12\0hello world' | shasum
git cat-file -t    AND   git cat-file -p.          on any hash gives type and content respy.
git cat-file -t 3b18e5 (gives the type `blob`)
blob = file contents. not the name, not anything. just contents.
git objects = (blob, tree , commit)
git ls-tree (is better than git cat-file)
git doesnt store the diffs in commits...whaaattt? it stores the entire file as it looked at that point in time.
objects vs refs
refs  = (tags, branches, remotes)
checking out a particular version of a file : git checkout master -- app/application.js
git grep ??
git merge - (what ?)
git stash list 
how to pop a particular stash?
how to see the entire history of a given file or a given line?
lets say i MOVED a func from one file to another, gblame would show my name. how do i check its commit, and then checkout its parent commit and then traverse history for that func to find out who wrote that line originally (not my refactor of file movement!)

Fugitive
- :Gstatus 
    - hit`ENTER` to view the file.
        - then `:Gdiff` to compare with index.
    - hit `-` minus key on files to move it to/from index/workingdir
    - hit `p` to trigger `git add --patch` to stage hunks little by little on a large file with changes.
    - hit `C` to `git commit`
- :Gwrite = git add current file
- :Gread = loads last commit's version of the file. you lose changes!
    - same as :Git checkout %
- :Gremove = git rm 
- :Gmove = git mv
- what is git diff --patch ? what is hunks?
    - git diff --cached ?
- :Gdiff = compare working copy with index (git diff)
    - left is index; right is working copy
    - :Gwrite on index is same as :Gread on working copy.
    - :Gwrite on working copy is same as :Gread on index.
    - dont get confused by above
        - always run :Gwrite :Gread on the working copy (right side!)
    - [vimbuiltin] :diffget and :diffput for hunks...
        - :diffupdate for repaint diff highlighting
    - [merge conflicts]
    - running :Gdiff on a conflicted file shows 3waydiffsplit
        - :diffget 2 
        - :diffget 3 
        - `[c` and `]c` helps move around conflicts in file.
        - After all conflicts are resolved, run :only in middle buffer to get rid of left and right

- git show <sha>  ::: for details on any git object: blob,tree,commit,tag
- git ls-tree <sha> | git cat-file -p <sha> | git cat-file -t <sha>
- :Gedit = open a file in another branch
    :Gedit branchname:path/to/file
- :Glog and :Ggrep = git log and git grep are best tools to dig up the history 
    - :Glog         = loads all previous versions of current file in quickfixlist
    - :Glog --      = loads all commits into quickfixlist
    - :Glog -- %    = loads all commits which touch the current file into quickfixlist
- Digging up history
    - search working copy 
        - git grep ::::: or :Ggrep --> copen
        - :Ggrep 'find me' demo  (demo branch) 
    - search commit messsages
        - git log --grep=str
    - ***search diffs for words added/removed.*** !!!
        - git log -S word ::: :Glog -Sword -- 



Vim:
- <C-n> = native autocomplete
- hlsearch option to highlight all words without going to them explicitly with `*`
- `*` -> `cw` -> `*` then keep using `.` to change all occurrences one by one.
- `qa` for recording macro ->`q` to stop recording. `@a` to replay the recording.
- learn autocmd

Nvim:
- learn autocmd in nvim and vim
- treesitter ??
- vim options via `vim.opt` helps set good defaults, "configurable"
- `:lua vim.diagnostic.goto_next` 
    - vim.diagnostic.goto_prev
    - vim.diagnostic.open_float
    - learn to set keymaps for the above!!
- autocommmands( registering to events )
    - vim.api.nvim_create_autocmd
    - vim.api.nvim_create_augroup







## Bad commit messages

1. You find a bug that is down to a rather obscure line of code
2. You use your version control system to find out who put in that line of code and when.3. That  person  is  off  on  holiday  or  has  gone  home  for  the  night,  and  left  a commit message that said “fixed obscure bug.”
4. You change the obscure line of code to fix the bug.
5. Something else breaks.
6. You spend hours trying to get the application working again.