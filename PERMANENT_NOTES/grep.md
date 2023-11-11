
# g/re/p

global<br>
regular expression<br>
print


# Tips
- Always Quote what you search for (single quote) so that **nothing is expanded by the shell**
- Case insensitive,--> `-i` option
- Multiple patterns to search, --> `-e` option
- Match whole words, and ignore substring matches, --> `-w` option
- Print 5 lines AFTER match --> `-A5`
- Print 5 lines BEFORE match --> `-B5`
- Print 5 lines around match(context) --> `-C5`
- Print line number of each match --> `-n`
- ...
- Count number of matches (count lines) --> `-c`
- Show file names only --> `-l`
- 


# Grep variants

#### egrep = enhanced grep  `grep -E`
more meta characters that you can use

```bash
$ cat /usr/bin/egrep

# you will see that its just invoking `grep -E` lol
```

#### fgrep = fixed grep `grep -F`
patterns are treated as strings, not regular expressions
```bash
$ cat /usr/bin/fgrep

# you will see that its just invoking `grep -F` lol
```

#### `grep -v` inverted search
show everything that did not match the pattern
Typically used as a filter
```sh
grep -i password * | grep -v junk
```
I want to search for "every", but not "everyone", "everybody", "everywhere"
```sh
grep every * | grep -v everyone | grep -v everybody | grep -v everywhere
#OR
grep every * | grep -Ev '(everybody|everyone|everywhere)'
```

#### Search across multiple files
`grep -i run-parts /etc/cron.d/*`

 you can also just write all the filenames at the end separated by space

#### Search within a directory 
`grep -R pattern dir`

#### Show only the matched string `-o`
Useful when
- you want to count the total occurrences of a word (there may be more than 1 match on single line, simple grep will count the matches as 1)
```sh
grep every * | grep -Ev '(everybody|everyone|everywhere)' | grep -o every | wc -l
```
- you want to see what the matches are
```sh
grep -o "is.*line" testfile
> is line is the 1st lower case line
> is line
> is is the last line
```


# Regexp

### `.` 
Match a single character....any character

### `?` 
Match preceding item ZERO or ONE time

### `+` 
Match preceding item ONE or MORE times

### `*` 
Match preceding item ZERO or MORE times

### `{2}` 
Match preceding item 2 times

### `{3,}` 
Match preceding item 3 or MORE times

### `{,4}` 
Match preceding item ATMOST 4 times

### `{1,5}` 
Match preceding item ATLEAST once, but no more than 5 times

### `[A,B]` 
Match 'A' or 'B'

### `[3-9]`
Match all digits 3 to 9

### `[^A-Z]`
DOESNT include any caps alpha characters.

### `^` and `$`
`^` is start of the line, and end of the line is marked by `$`

## Examples

1. `grep -c "^$" messages.log python.log`  
	 count empty lines in both these files.
2. `grep -w .... messages.log`
	match all 4 letter words i.
3. `grep 127.0.0.1 /etc/hosts`
     the "dot" stands for any character
     So it will not work as intended. Use `grep "127\.0\.0\.1 /etc/hosts"` to escape dot.
    just try `grep 127...... /etc/hosts` and you'll see the same output

4. `grep -F 127.0.0.1 /etc/hosts`
    then this will ignore meta characters. "dot" will not have any meaning. does exact string match . patterns are 

4. `grep -v '^#' /etc/services | head`
    to not see any comments

    `grep -ve '^#' -ve '^$' /etc/services`
    to skip comments and skip empty lines

    you can do the same with **Enhanced grep** `grep -Ev '^(#|$)' /etc/services | head`

    Quite useful in say checking the configs of say sshd_config 
    ` grep -Ev '^(#|$)' /etc/ssh/sshd_config ` where i dont want to see disabled lines and empty lines

5. ```bash
    echo "color" > file
    echo "colour" >> file
	grep -E 'colou?r' file1`

6. `grep -i 'permitroot' -C5 /etc/ssh/sshd_config `
    Show me 5 lines before and after (the context) of matches with "permitroot" case insensitive

6. List TCP port of single digit
   ` grep -E '\s[0-9]{1}/tcp' /etc/services`

7. `grep -E '\s*#' file` 
Match all lines containing comments
. Match any number of whitespaces at the beginning

8. `grep -iE '^a.*ss$' /usr/share/dict/words`
Show all the words which start with "a" and end with "ss"

9. m_d___e
    `grep -E '^m.d...e$' /usr/share/dict/words`

10. `grep '^[A,E].*o' file` Match all strings starting with A or E and ending with o.
11. `grep -i "^[^aeiou]" /usr/share/dict/linux.words` Match all lines NOT starting with a vowel.




# Questions
1. what do we mean by "not expanded by the shell" why should the shell expand?
learn shell expansion/
2. Understand grep -E. what exactly is extended. which should i be using often
4. globbing? file globbing? metacharacters?