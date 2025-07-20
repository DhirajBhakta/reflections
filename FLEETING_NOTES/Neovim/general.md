## Basics
- `vim` table
- `vim.api` table
- `vim.fn` table
- `vim.opt` table
- `vim.keymap` table

You can print each of the above to inspect them (in Ex mode `:lua =vim.api`)





#### To print lua table
In the command mode 
`:lua =vim` 
or
`:lua =require('codecompanion.config')`

This output will be VERY large, and will be rendered in `more` pager. 
To search through this output, you may want to _print the output to a file._

`:enew | put=execute('lua =require(\"codecompanion.config\")')`

