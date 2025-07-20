- Normal Mode
- Insert Mode
- Visual Mode
- Visual Block Mode
-  
Spend most of your time in **Normal Mode** and least in **Insert Mode**.
**Visual Mode** is _okay_ but catch yourself when using it, and translate it to **Normal mode** keystrokes.

### Navigation
| ...                  | description                                             |
| -------------------- | ------------------------------------------------------- |
| `gg` and `G`         | jump to "top" and "bottom" of the file                  |
| `<C-u>` and `<C-d>`  | scroll "up" and "down" (half) a page                    |
| `H`  `M`  `L`        | High Middle Low of the viewport                         |
| `zz`  (`zt` \| `zb`) | center(or top\|bottom) the current line within viewport |
|                      |                                                         |

### Motion 
##### Motion within a line

| ...         | description                                                                                    |
| ----------- | ---------------------------------------------------------------------------------------------- |
| `w` and `b` | move "word" by word forward and backward                                                       |
| `f`         | "find" and jump to the first occurrence                                                        |
| `t`         | jump "till" the first occurrence of the character<br>(just like `f` but stops ONE char before) |
| `F`         | just like `f` but backwards                                                                    |
| `T`         | just like `t` but backwards                                                                    |
| `;` and `,` | repeat `f` or `t` (forwards`;`) OR repeat `F` or `T` (backwards`,`)                            |

### Commands (Normal Mode)
vim accepts commands which look like sentences : (verb)(adjective)(noun) eg: "delete" a "word"  . . . `adjective is optional!` 
Note: `noun` is "text objects"
so, when you hit `d` (delete), vim is waiting for the noun, eg: `dw` for "delete word" or `daw` for "delete a word". and if you don't provide any noun, and provide the verb again, it will  apply the command(verb) on the entire line : eg: `dd` , `cc`, `yy`

| mapping | operation(verb)                           |
| ------- | ----------------------------------------- |
| d       | delete                                    |
| y       | yank                                      |
| v       | visually select                           |
| > <     | indent, deindent                          |
| =       | reformat(reindent, break long lines, etc) |

Vim  has understanding of a lot of "text objects" other than words, paragraphs....like paranethesis, square brackets, double quotes, single quotes,< >, \` \`,  html or xml tags....essentially anything that has a **natural grouping**

| ...   | description                 |
| ----- | --------------------------- |
| `daw` | delete a word               |
| `ciw` | change inner word           |
| `dip` | delete inner paragraph      |
| `>ip` | indent inner paragraph      |
| `=ip` | reformat  inner paragraph   |
| `ci(` | change inside parenthesis   |
| `ci"` | change inside double quotes |
| `cit` | change inner tag            |
| `dat` | delete the tag              |
 
#### Repeat commands with `.` 
`.` helps you repeat your last command. (say `ciw`)

#### Other useful builtin aliases
since `$` stands for "end of the line" and `0` is "beginning of line",
- `d$` deletes from current position to the end of the line.
- `y$` yanks from current position to the end of the line.
- `c$` changes from current position to the end of the line.
(Remember: `d` `y` `c` are the big 3 verbs/commands)

However, vim gives aliases for the above in **capital letters**

| alias | ...  |
| ----- | ---- |
| `D`   | `d$` |
| `Y`   | `y$` |
| `C`   | `c$` |
test test 

### Tabs | Windows
PREFIX = `<C-w>`

| ...           | description          |
| ------------- | -------------------- |
| `PREFIX hjkl` | move between windows |
| `PREFIX HJKL` | shift window         |
| `PREFIX ><-+` | resize window        |
| `PREFIX =`    | reorganize windows   |

Tab Navigation...

| ...           | description        |
| ------------- | ------------------ |
| `gt` and `gT` | cycle between tabs |


### Registers
| ...       | description                |
| --------- | -------------------------- |
| ""        | default (unnamed) register |
| "a to "z  | named registers            |
| "0 to  "9 | history registers          |
| "-        | blackhole register         |
|           |                            |

### Configuration `~/.vimrc` or `~/.config/nvim/init.vim`
How to remap?
```sh
nmap 0 ^
```
This remaps "0" to "^" _only in normal mode_

Most characters are already taken, so its hard to create mappings of your own. This is why **Leader** exists, to help create your own _namespace_.
Note: Leader is `\` by default.
```sh
nmap <leader>so :source ~/.vimrc<cr>
```

...
How to set options?
```sh
set number
```

...
---->**(advanced)**<----
responding to _events_
```vimrc
autocmd Filetype help nmap q :q
```

...
---->**(advanced)**<----
How to create new commands?
You do this with `command!`
```sh
command! ShowConfig :e ~/.vimrc
```


### Random Tricks

#### Surround a word with double quotes `ciw"< C-R >""`
>>>>>>> 16607dc (random push [2025] : git,cas)
```
ciw    : change inner word, will delete it and place in default register (")
"      : will just type " because.... youre still in insert mode.
<C-R>" : will paste the contents of the default register (")
"      : will just type " because.... youre still in insert mode.
```
 - ##### Surround 3 words with double quotes `c3w"< C-R >""`
 - ##### Surround 3 words with backticks  `c3w`< C-R >"`
 - ##### Surround 3 words with double quotes `c3w"< C-R >""`


---
### Folding: `zf` and `zo`
`:set foldmethod=indent`
kkkkkkkkkkkkkkkk
# How to search the manual
