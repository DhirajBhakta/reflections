1. Preprocessor
2. Compilation
3. Assembler
4. Linking
5. Loading

"build" = "compilation" + "linking" = creating object files + linking object files




![](https://www.cs.nmsu.edu/~jcook/images/compiling.png)
> **Info**
> C was developed by Dennis Ritchie solely for the purpose of developing UNIX. 
> people later started using it for their own programs, & system-level programming.


You have `helloworld.c` , --> you need --> `helloworld`  executable(object code) which contains machine instructions. On UNIX, **an executable file has no extension**.
```shell
gcc helloworld.c -o helloworld
```

> **Warning**
> If you just `gcc helloworld.c`  you shall get `a.out` executable.


## Preprocessor
- macro expansion
- headfile contents inserted into the main program

`cpp` (Preprocessor) is a separate program, but its invoked indirectly via `gcc` compiler.

All `#include<...>` and `#define..` are parsed, the respective file contents are inserted directly into the program text.

The resultant file is `helloworld.i` (not persisted to disk unless specified)
```shell
cpp helloworld.c > helloworld.i
```
You could also use
```shell
gcc -E helloworld.c
```

## Compilation
converting the source file to **assembly code** (helloworld.s)
```shell
gcc -S helloworld.i
```

`-S` tells gcc to convert to assembly code _without_ creating the object file(machine instructions).

>**Info**
>Compilation happens **one file at a time**.

Compilation does NOT complain about undefined functions, it just assumes those functions will be obtained later from other linked object files. The Linker does complain about undefined functions if they're not found in any object files.

## Assembler
Assembly code to machine instructions (object file)
```shell
as helloworld.s -o helloworld.o
```


## Linking
The Linker(`ld`) links object files(dependencies) to give the final executable. `gcc` internally invokes the `ld` command to save you the trouble of writing ...
```shell
ld -dynamic-linker \
	/lib64/ld-linux-x86-64.so.2 \
	/usr/lib64/crt1.o \
	/usr/lib64/crti.o \
	/usr/lib64/crtn.o \
	 helloworld.o \
	/usr/lib/gcc/x86_64-redhat-linux/4.1.2/crtbegin.o \
	-L /usr/lib/gcc/x86_64-redhat-linux/4.1.2/ \
	-lgcc -lgcc_eh -lc -lgcc -lgcc_eh /usr/lib/gcc/x86_64-redhat-linux/4.1.2/crtend.o \
	-o helloworld
```

This long command is internally handled by gcc, which you can use instead
```shell
gcc helloworld.c -o helloworld
```
We can also give `gcc` the list of object code files instead of source code files, and it skips compilation and just does the linking.


> **Note**
> We haven't talked about shared libraries (end with `*.a`) and shared libraries (end with `*.so`). We haven't talked about "libraries" at all. We just dealt with linking N files to produce an executable without needing to create a library out of N-1 dependencies.


With this approach to _chunkified_ compiling, if there's any change in any file, ONLY that file needs to be re-compiled and the resultant object code of that file can be re-linked to the final executable, saving you from recompiling the entire large codebase. **_Compile only what you change, everything else is re-linked_**


## Loading
Happens when you **run** the executable.
Program is scanned for references to shared libraries(if any), and they are mapped into your program.

