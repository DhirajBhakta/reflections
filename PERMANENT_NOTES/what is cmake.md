_**CMake makes your Makefile**_

https://youtu.be/DDHCEE_PHOU
https://github.com/pyk/cmake-tutorial

`cmake` is NOT a build tool, its a "meta-build tool".
_It generates build files for OTHER build tools like => `make` , `ninja` 

Just like how `make` depends on a top level file called `Makefile`,
`cmake` depends on a top level file called `CMakeLists.txt`

`CMakeLists` --> cmake ---> generate build files for specific environments
eg: Makefiles for unix, or input files for `ninja-build`

#### Why CMake?
_**CMake makes your Makefile**_

#### Example
https://github.com/pyk/cmake-tutorial
Let's first not use any build system, and rely just on `g++` compiler to compile it all. See [[why do you need a header file?]]
`g++ main.cpp mathh.cpp`

Now lets use a `Makefile` to do that for us
```Makefile
all:
	g++ main.cpp mathh.cpp
```
you just need to run `make` to get an executable, no longer need to remember g++ specifics.

Now lets use CMake, we write a `CMakeLists.txt`
```CMakeLists.txt
cmake_minimum_required (VERSION 3.10)

# Define the project
project(cmake-tutorial)

# Add definition for math library
add_library(math mathh.cpp)

# Add definition for the  main binary
add_executable(cmake-tutorial main.cpp)
target_link_libraries(cmake-tutorial math)
```
run `cmake .` and you get a `Makefile`!, now run `make` and you get an executable.





