
## What exactly should bash be used for?
The place where bash shines is NOT in complicated applications.

its for task automation, like making backups, 

Performance is one of the last priority when youre 


# Output Redirection '>' '>>'

`echo "lol" > lol.txt`
create the file if not exists, and overwrite if exists

`echo "lolol" >>lol.txt`
append

abuse this to clear files
` cat /dev/null > filetoclear.txt`

- Also btw, you can redirect ONLY STDOUT using > or 1>
- you can redirect ONLY STDERR using 2>

### what does ` ... > /dev/null 2>&1 ` mean then??
- it means send both STDOUT and STDERR to purgatory
#### Inference
Then it also means i can log both STDOUT and STDERR to single file using 
`.... > myfile 2>&1`

It also means i can log STDOUT and STDERR to separate files using
`... > outfile 2> errfile`


```
2>&1 redirects file descriptor 2 (stderr) to file descriptor 1 (stdout)
```

# Input Redirection '<'

`wc -l < testfile`

alternatively you could just pipe `cat testfile | wc -l`

# logical and (&&) logical or (||)
`( cat testfile | wc -l) && echo "Done"`
think short circuiting....wouldnt have printed if first part failed.

`ls dirThatDoesNotExist || echo "damn theres no file"`

How does it understand if someting failed? the 0,1 exit codes. But exit codes are for processes right? EXACTLY! the commands you run in a pipe are indeed processes

# Variables
`myvar="this is the value"`
Please dont put space around the '='

Otherwise if you put the space like `myvar = "some thing"` then it will look for a program named myvar and pass = as an argument, and the second part also as the argument


# Quoting.. ""  OR  ''

The basics of quoting is simple
- Use the single or double quotes when a value contains spaces
    ```
        a="hello world"
        b='hello world'
     ```
- We Quote to protect the special chars in a string from reinterpretation or expansion by the shell, to protect its LITERAL meaning.
- Single Quoting being the strictest -- absolutely no variable substitution or escaping of special chars  in the quoted string
- Double Quoting is lenient. Allows variable substitution and escaping of chars

```bash
a="hello \"there\" world"  # > hello "there" world
a='hello "there" world' # > hello "there" world
a='hello \"there\" world' # > hello \"there\" world
a='hello \'there\' world'  #ERROR
a="hello 'there' world" # > hello 'there' world
```

```bash
b="there"
a='hello \"$b\" world' # > hello \"$b\" world
a="hello \"$b\" world" # > hello "there" world
```
[Table of usages of single and double quotes](https://stackoverflow.com/a/42082956)
> Enclosing characters in single quotes (') preserves the literal value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash. 

> Enclosing characters in double quotes (") preserves the literal value of all characters within the quotes, with the exception of $, `, \ . The characters $ and ` retain their special meaning within double quotes (see Shell Expansions). The backslash retains its special meaning only when followed by one of the following characters: $, `, ", \, or newline. Within double quotes, backslashes that are followed by one of these characters are removed. Backslashes preceding characters without a special meaning are left unmodified. A double quote may be quoted within double quotes by preceding it with a backslash. 
The special parameters * and @ have special meaning when in double quotes.
- `echo "Do this ${N}th time"`
- `echo "There are X lines in the /etc/shadow file"`
- `echo "There are `wc -l < /etc/shadow` lines in the /etc/shadow file"`



# Shell Expansions
### brace expansion
### tilde expansion
### parameter and variable expansion

### command substitution

### word splitting

### filename expansion



# Exit codes

0 = Success<br>
1 = failed

`exit 0`

`exit $?`  Exit with the exit status of the last run command in the script

# Arguments
$# -- number of args that our script was run with <br>
$0 -- the filename of our script<br>
$1..$n -- script arguments

# if conditions & testing
[Read this first](https://unix.stackexchange.com/a/306115)
- [[ ]]  syntax is called `new test syntax`

- [ ] syntax is called `old test syntax`
```bash
if [[ condition ]]; then
    #statements
fi

if [ condition ]; then
    #statements
fi
```

```bash
NAME=$1
if [ "$NAME" = "Dhiraj" ]; then
    echo "Hi Dhiraj"
fi

```

# for loops
```bash
for arg in "$@"; do
    echo "$arg"
done
```
# Questions
1. what exactly is /dev/null
2. what exactly is a login shell?
3. What actually happens when your source?
4. what actually happens when you type a command in terminal?
5. what happens when i type bash in terminal?
6. [tty demystified ](http://www.linusakesson.net/programming/tty/)
7. grep tutorial one hour
8. bash tutorial of 3 hours
9 . [Read this first](https://unix.stackexchange.com/a/306115)