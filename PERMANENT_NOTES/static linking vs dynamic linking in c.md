
>**Info**
>Shared libraries (Shared object files) are found in `/usr/lib` and `/lib` . They contain both `*.a` (static object files, linked statically) and `*.so` (shared object files, linked dynamically) files .
## Linking
Helps you compile separate chunks separately and then link them together. If there's a change in one chunk, you compile just that chunk and re-link, avoiding the need to compile everything.
Linking can be done at
- compile time
- load time
- runtime

>**Info**
>Linkers enable "separate-compilation" of files in a large project. You can only recompile the changed files and re-link with other object files, without needing to recompile other source files.

![](../../assets/linux-00.svg)

Object files are of 4 types
- **Relocatable Object files**
	- object files which can be combined with other object files to make an executable object files. `gcc` takes in N relocatable object files and creates a single executable object file. 
	- object files made from source files NOT having a main method.
	- these cannot be simply loaded into memory and **cannot be directly executed**
	- have an extension of `*.o` eg: `hello.o`
- **Executable Object files**
	- can be simply loaded into memory and executed. 
	- dont have a extension eg :`hello`
- **Shared Object files**
	- "shared library" which can be dynamically linked, unlike **static library object files** which need to be included in the executable post compilation.
	- can be loaded into memory and **linked dynamically**, at load time or runtime.
	- analogous to DLLs in windows.
	- have an extension of `*.so`  eg: `libshadow.so`
- **Static library Object files**
	- These need to "copied over" into the final executable post compilation
	- opposites of "shared object files"
	- have an extension of `*.a`
### Static Linking
linker **copies** the dependencies into the final executable. Done during compilation.

Takes more disk space, more memory during load.
More portable because it doesn't require the presence of the library on the system where it runs.

#### static linking example (not static library)
The usual build step is generally done via static linking.. as follows
```c
// main.c
#include<add.h>
#include<stdio.h>

int main(){
	int x = add(10,20);
	return 0;
}
```
We have the header file 
```c
// add.h
int add(int, int);
```
And its corresponding definition file
```c
//add.c
int add(int a, int b){
	return a+b;
}
```

Compile main.c . (`-I` to look for header files in pwd, `-c` to create object file..without linking)
```shell
gcc -I . -c main.c
```
Compile add.c
```shell
gcc -c add.c
```
Link(static linking) main.o and add.o
```shell
gcc -o main main.o add.o
```

#### static library example
A library is a collection of N object files like `add.o` , `subtract.o` .... archived into one object file, a bundle of **relocatable object files**.
`ar` (GNU archive) command helps create the static library.
```shell
ar rs libmath.a add.o subtract.o multiply.o div.o
```
`libmath.a`  is the static library.
We link it with `main.o`
```shell
gcc -o main main.o libmath.a
```
OR
```shell
gcc -o main -L . main.o -lmath
```
>**Note**
> `-lmath` is `-l math` ==> "link the obj file lib{libname}.a"
> `gcc` assumes all libraries have the lib*.so "lib" prefix.
> `-L` specifies the dir to search for (libraries)obj files.

### Dynamic Linking
Libraries are NOT included in the executable, only the references are mentioned. Linked as and when required during **runtime**.

Helps reduce the executable size of the main program. Speeds up build time.

Less resource hungry, once the shared library is loaded, it would never be loaded again for 100 other programs using it, leaving a far smaller memory footprint.

#### shared library example
Compile the source file with `fpic` (position independent code) 
```shell
gcc -c -fpic add.c
gcc -c -fpic sub.c
gcc -c -fpic multiply.c
gcc -c -fpic div.c
```
Build the shared library
```shell
gcc -shared -o libmath.so add.o sub.o multiply.o div.o
```
To install this shared library, move it to standard dir containing libraries /usr/lib and run `ldconfig` 

Then you can link 
```shell
gcc -o main main.o libmath.so
```
OR
```shell
gcc -o main -L . main.o -lmath
```

This "linking" stores only the reference of the shared library in the executable. So you can edit the library, recompile it and then place it back in the LD_LIBRARY_PATH and next time the main program is run, it will pick it up just fine.

To find the list of shared libraries an executable is dependent on, use `ldd` command. `ldd <executable>`
