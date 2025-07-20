_TLDR;  so you can separate declaration from the definition.
Why?=> sort of like why you use interfaces in OOP, there can be multiple definitions , and you can swap out any whenever you like..without affecting the caller_

---

Let's first try NOT using a header file.
There are two files `main.cpp` and `mathh.cpp`, the latter contains a function that `main.cpp` wants to use (or "import")
Notice that I did NOT explicitly `#include "math.cpp"`
```c++
//[dhirajbhakta@AMATERASU src]$ cat main.cpp
#include<iostream>

using namespace std;

int adder(int a, int b); // you NEED this declaration

int main(){
	cout<<adder(1,2);
	return 0;
}

//[dhirajbhakta@AMATERASU src]$ cat mathh.cpp

int adder(int a, int b){
	return a+b;
}
```

`g++ main.cpp` => does NOT work. missing definition of "adder".

 `g++ main.cpp mathh.cpp`  => it works, you get an executable!

> Note: g++ compiles both `main.cpp` and `math.cpp` into `main.o` and `mathh.o` and then the linker ... links them to give you the executable `a.out`.
> **_The default behavior of g++ is to compile all the files given to it , and then link them into the executable_**


...
But you had the hassle of  specifying the declaration of the function you used, `adder` in the main file. What if you had multiple such functions you used (want to import) from other files? --> _you put such declarations into a header file, and import just that header file_... The linker takes care of finding the definition from one of the compiled object files

```c++
//[dhirajbhakta@AMATERASU src]$ cat main.cpp
#include<iostream>
#include "mathh.h"

using namespace std;

int main(){
	cout<<adder(1,2);
	return 0;
}

//[dhirajbhakta@AMATERASU src]$ cat mathh.cpp
int adder(int a, int b){
	return a+b;
}

//[dhirajbhakta@AMATERASU src]$ cat mathh.h
#ifndef MATHH_H
#define MATHH_H

int adder(int a, int b);

#endif
```

`g++ main.cpp mathh.cpp` => it works, you get an executable

>Note: you didn't have to provide `mathh.h` to g++. You just imported it where you needed the declarations



