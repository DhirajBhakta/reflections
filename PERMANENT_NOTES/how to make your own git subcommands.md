
You can create your own subcommands like `git log` , `git grep` etc..
1. The script name must be prefixed with `git-`, e.g. `git-current-sha`.
2. The script file must be on your `$PATH`.
3. The script must be marked as executable. (it can be in any language: bash/python/ruby...)

```
#!/usr/bin/env ruby

current_sha = `git rev-parse HEAD`.chomp

puts "The current sha is: #{current_sha}"

```


```
# Create the ~/bin directory if it doesn't already exist
$ mkdir -p ~/bin

# Add the ~/bin directory to our path
$ echo 'export PATH="$HOME/bin:$PATH"' > ~/.zshenv

# Populate the script with code above
$ vim ~/bin/git-current-sha

# Mark it as executable
$ chmod +x ~/bin/git

# Run our fancy ruby script through Git!
$ git current-sha
The current sha is: 284aeca561c5be5ec7b81123ac625e02308d09e8
```

_Writing your own git subcommands are an alternative to creating your own Git aliases...because you can only write one or two shell commands in an alias_
(can you not call a python script from shell tho?)
