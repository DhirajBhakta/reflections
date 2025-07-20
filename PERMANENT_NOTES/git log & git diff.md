
### Formatting git log
```sh
git log --pretty=format:'%h - %an [%ar] %s'
```
`%ar` : "3 days ago" relative date
`%h`   : commit hash
`%an` : author name

...with colors
```sh
git log --pretty=format:'%C(yellow)%h%C(reset) - %an [%C(green)%ar%C(reset)] %s'
```

another example
```sh
git log -n 30 --since=”1 month ago” --until=yesterday --author=”dhiraj”
```

# Searching
### Searching through commit messages
... search for all commit messages with word "cache" or "caching"
```
$ git log --grep -E -i 'cach(e|ing)'
```

### Searching through code changes
...search for all commits which added/removed/updated a given string "useEffect"
```
$ git log -S useEffect
```

### List commits affecting a given file 
...show all commits which made changes to a given file
```sh
git log --oneline -- requirements.txt
```

## Search history without a checkout : `git grep`
```sh
git grep <pattern> sha sha sha sha ...
```
provide the sha of trees, instead of files.

---
# Diff
Show all commits that are in branch2, but not in branch1
```sh
git log branch1..branch2
git log origin/master..master
# show commits in master but not in origin/master
```

### `git diff` outputs a valid "patchfile"...
... pipe it to a "patchfile", and this patchfile can be _applied_ by anyone !
```sh
git diff master..experiment > experiment.patch
```
then later..
```sh
git apply experiment.patch
```
or...
```sh
patch -p1 < experiment.patch
```
### succinct `git diff --stats`
```sh
$ git diff --stat 0576fac35..
   README           |    4 +++-
   Rakefile         |    2 +-
   lib/simplegit.rb |    4 ++++
   3 files changed, 8 insertions(+), 2 deletions(-)

 $ git diff --stat master feat/xxx
   README          |    4 ++--
   lib/simplegit.rb |    4 ++++
   2 files changed, 6 insertions(+), 2 deletions(-)
```

and then later, if you want to see what exactly changed in a specific file..
...

### what exactly changed in a specific file between commits ?
use the `--` separator and then specify filename.
```sh
$ git diff a11bef06a3f65..cf25cc3bfb0 -- Rakefile
  diff --git a/Rakefile b/Rakefile
  index a874b73..8f94139 100644
  --- a/Rakefile

  +++ b/Rakefile
  @@ -5,7 +5,7 @@ require ‘rake/gempackagetask’

   spec = Gem::Specification.new do |s|
       s.platform  =   Gem::Platform::RUBY
       s.name      =“simplegit”

  -    s.version   =  “0.1.0”
  +    s.version   =“0.1.1”

       s.author    =  “Scott Chacon”
       s.email     =  “schacon@gmail.com”
       s.summary   =“A simple gem for using Git in Ruby

code.”
```