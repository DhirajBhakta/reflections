https://makefiletutorial.com/

A `Makefile` _feels_ like a "set of handy commands" for a given project, but . . .

#### Why was `make` and `Makefile` created?
> _which portions of the program needs to be built(compiled) again?_
> **Crux of make**:: Build your current target _again_ if any of the target's deps are "newer" than the target itself( filesystem timestamps ).

C build process is a pain. You need to detect which of your dependencies (c files, header files, object files) have changed and then _selectively_ build the things that _need to be built again_. GNU `make` was made just for that.

#### Alternatives
cmake, ninja, bazel : c and c++
maven , ant, gradle : java

#### Makefile Recipes
Recipes are the "set of handy commands" you bake into a Makefile.

Recipes are 
```Makefile
target: prerequisites
	command
	command
	command

target: prerequisites
	command
	command
	command
	
hello:
	echo "Hello, World"
	echo "This line will print if the file hello does not exist."
```
**Target**s are _usually_ file-name of the artifact produced by the commands in the recipe. The **command**s are run if the **Target** does NOT exist. The **prerequisites** are dependencies, . . . other files that must exist if this target has to be built. If you don't specify the dependency, then changes in the dependency is not detected and your target may not be built at all!
```makefile
blah:
	cc blah.c -o blah
```
^ here, when you run `make` , "blah" executable gets created. When you run it again, compilation is **skipped**, even if there are changes in `blah.c` ..because the target file `blah` already exists...so it skips the commands!
```makefile
blah: blah.c
	cc blah.c -o blah
```
^ Now, running `make` will run the commands IF `blah` doesn't exist OR, `blah.c` is newer than the target `blah`.


Running `make hello` will not print anything if there's already a file named `hello` in the directory.

#### Every line is executed in a new shell!
```makefile
all:
	echo `pwd`
	cd ..
	echo `pwd`
```
^ you see the same directory being printed, despite `cd..`

#### Shell variables use `$$` , make variables use `$()`
Shell variables and make variables are NOT the same
```Makefile
make_var = I am a make variable
all:
	# Same as running "sh_var='I am a shell variable'; echo $sh_var" in the shell
	sh_var='I am a shell variable'; echo $$sh_var

	# Same as running "echo I am a make variable" in the shell
	echo $(make_var)
```
Note: all shell variables(env vars) become available as make variables when `make` is run.

#### `all` target
```Makefile
all: one two three

one:
	touch one
two:
	touch two
three:
	touch three

clean:
	rm -f one two three
```
`all` target should be the FIRST target, so that when you run `make`, the `all` target is executed.
it would run all the specified targets `one`, `two` and `three`
#### Makefile example
```Makefile
blah: blah.o
	cc blah.o -o blah # Runs third

blah.o: blah.c
	cc -c blah.c -o blah.o # Runs second

blah.c:
	echo "int main() { return 0; }" > blah.c # Runs first

.PHONY: clean
clean:
	rm -rf blah.o
```


#### `.PHONY`
```makefile
.PHONY: clean
clean:
	rm -rf blah.o
```
Lets say you already had a file with filename "clean". Then this target would never run, `make clean` would never run!!!
That's why you use `.PHONY` to instruct the makefile that its a "phony(fraud) target", that it doesn't really produce an artifact with the same name...like all other regular targets do.

#### Single/Double quotes are meaningless in make
_But "quotes" are useful to Bash though: eg: `printf`_
```Makefile
a := one two   # "one two"
b := 'one two' # "'one two'" (so, pls dont use quotes. not recommended)
all:
	printf '$a'   # quotes are useful to bash though
	printf $b
```

#### Makefile for C compilation | Implicit rules
Makefile loves C compilation, makes a lot of things _implicit_.
Notice you didn't specify how the compilation needs to happen
```Makefile
CC = gcc # Flag for implicit rules
CFLAGS = -g # Flag for implicit rules. Turn on debug info

# Implicit rule #1: blah is built via the C linker implicit rule
# Implicit rule #2: blah.o is built via the C compilation implicit rule, because blah.c exists
blah: blah.o

blah.c:
	echo "int main() { return 0; }" > blah.c

clean:
	rm -f blah*
```
#### Gotchas
1. **First target is the default target**:  if you run just `make` without any **target**, it will run the very FIRST recipe! . Usually, `all` target is the very first **target**.
2. Every line in a recipe is executed in a **new shell**.
3. Shell variables `$$` are NOT treated same as make variables `$()`. Note that all env variables(shell variables) become available as make variables when running `make`.
4. **Single/Double quotes have no meaning in make**
5. without `.PHONY: clean`, your `make clean` command would never run IF there's a file named "clean" in your directory!
6. Built-in variables:
	1. `$(CC)` defaults to `cc` which is a symlink to `gcc` 
	2. `$(CXX)` defaults to `g++` 
	3. `$(CFLAGS)`: Extra flags to give to the C compiler
	5. `$(CPPFLAGS)`: Extra flags to give to the C preprocessor
	4. `$(CXXFLAGS)`: Extra flags to give to the C++ compiler

---

# Deconstructing Neovim Makefile
https://github.com/neovim/neovim/blob/master/Makefile

```Makefile
ifeq ($(OS),Windows_NT)
  SHELL := powershell.exe
  .SHELLFLAGS := -NoProfile -NoLogo
  MKDIR := @$$null = new-item -itemtype directory -force
  TOUCH := @$$null = new-item -force
  RM := remove-item -force
  CMAKE := cmake
  CMAKE_GENERATOR := Ninja
  define rmdir
    if (Test-Path $1) { remove-item -recurse $1 }
  endef
else
  MKDIR := mkdir -p
  TOUCH := touch
  RM := rm -rf
  CMAKE := $(shell (command -v cmake3 || command -v cmake || echo cmake))
  CMAKE_GENERATOR ?= "$(shell (command -v ninja > /dev/null 2>&1 && echo "Ninja") || echo "Unix Makefiles")"
  define rmdir
    rm -rf $1
  endef
endif

MAKEFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKEFILE_DIR  := $(dir $(MAKEFILE_PATH))

filter-false = $(strip $(filter-out 0 off OFF false FALSE,$1))
filter-true = $(strip $(filter-out 1 on ON true TRUE,$1))

# See contrib/local.mk.example
-include local.mk

all: nvim

CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)
# Extra CMake flags which extend the default set
CMAKE_EXTRA_FLAGS ?=
NVIM_PRG := $(MAKEFILE_DIR)/build/bin/nvim

# CMAKE_INSTALL_PREFIX
#   - May be passed directly or as part of CMAKE_EXTRA_FLAGS.
#   - `checkprefix` target checks that it matches the CMake-cached value. #9615
ifneq (,$(CMAKE_INSTALL_PREFIX)$(CMAKE_EXTRA_FLAGS))
CMAKE_INSTALL_PREFIX := $(shell echo $(CMAKE_EXTRA_FLAGS) | 2>/dev/null \
    grep -o 'CMAKE_INSTALL_PREFIX=[^ ]\+' | cut -d '=' -f2)
endif
ifneq (,$(CMAKE_INSTALL_PREFIX))
override CMAKE_EXTRA_FLAGS += -DCMAKE_INSTALL_PREFIX=$(CMAKE_INSTALL_PREFIX)

checkprefix:
	@if [ -f build/.ran-cmake ]; then \
	  cached_prefix=$(shell $(CMAKE) -L -N build | 2>/dev/null grep 'CMAKE_INSTALL_PREFIX' | cut -d '=' -f2); \
	  if ! [ "$(CMAKE_INSTALL_PREFIX)" = "$$cached_prefix" ]; then \
	    printf "Re-running CMake: CMAKE_INSTALL_PREFIX '$(CMAKE_INSTALL_PREFIX)' does not match cached value '%s'.\n" "$$cached_prefix"; \
	    $(RM) build/.ran-cmake; \
	  fi \
	fi
else
checkprefix: ;
endif

DEPS_BUILD_DIR ?= ".deps"
ifneq (1,$(words [$(DEPS_BUILD_DIR)]))
  $(error DEPS_BUILD_DIR must not contain whitespace)
endif

DEPS_CMAKE_FLAGS ?=
USE_BUNDLED ?=

ifneq (,$(USE_BUNDLED))
  BUNDLED_CMAKE_FLAG := -DUSE_BUNDLED=$(USE_BUNDLED)
endif

ifneq (,$(findstring functionaltest-lua,$(MAKECMDGOALS)))
  BUNDLED_LUA_CMAKE_FLAG := -DUSE_BUNDLED_LUA=ON
  $(shell [ -x $(DEPS_BUILD_DIR)/usr/bin/lua ] || $(RM) build/.ran-*)
endif

# For use where we want to make sure only a single job is run.  This does issue 
# a warning, but we need to keep SCRIPTS argument.
SINGLE_MAKE = export MAKEFLAGS= ; $(MAKE)

nvim: build/.ran-cmake deps
	$(CMAKE) --build build

libnvim: build/.ran-cmake deps
	$(CMAKE) --build build --target libnvim

cmake:
	$(TOUCH) CMakeLists.txt
	$(MAKE) build/.ran-cmake

build/.ran-cmake: | deps
	$(CMAKE) -B build -G $(CMAKE_GENERATOR) $(CMAKE_FLAGS) $(CMAKE_EXTRA_FLAGS) $(MAKEFILE_DIR)
	$(TOUCH) $@

deps: | build/.ran-deps-cmake
ifeq ($(call filter-true,$(USE_BUNDLED)),)
	$(CMAKE) --build $(DEPS_BUILD_DIR)
endif

ifeq ($(call filter-true,$(USE_BUNDLED)),)
$(DEPS_BUILD_DIR):
	$(MKDIR) $@
build/.ran-deps-cmake:: $(DEPS_BUILD_DIR)
	$(CMAKE) -S $(MAKEFILE_DIR)/cmake.deps -B $(DEPS_BUILD_DIR) -G $(CMAKE_GENERATOR) $(BUNDLED_CMAKE_FLAG) $(BUNDLED_LUA_CMAKE_FLAG) $(DEPS_CMAKE_FLAGS)
endif
build/.ran-deps-cmake::
	$(MKDIR) build
	$(TOUCH) "$@"

# TODO: cmake 3.2+ add_custom_target() has a USES_TERMINAL flag.
oldtest: | nvim
	$(SINGLE_MAKE) -C test/old/testdir clean
ifeq ($(strip $(TEST_FILE)),)
	$(SINGLE_MAKE) -C test/old/testdir NVIM_PRG=$(NVIM_PRG) $(MAKEOVERRIDES)
else
	@# Handle TEST_FILE=test_foo{,.res,.vim}.
	$(SINGLE_MAKE) -C test/old/testdir NVIM_PRG=$(NVIM_PRG) SCRIPTS= $(MAKEOVERRIDES) $(patsubst %.vim,%,$(patsubst %.res,%,$(TEST_FILE)))
endif
# Build oldtest by specifying the relative .vim filename.
.PHONY: phony_force
test/old/testdir/%.vim: phony_force nvim
	$(SINGLE_MAKE) -C test/old/testdir NVIM_PRG=$(NVIM_PRG) SCRIPTS= $(MAKEOVERRIDES) $(patsubst test/old/testdir/%.vim,%,$@)

functionaltest-lua: | nvim
	$(CMAKE) --build build --target functionaltest

FORMAT=formatc formatlua format
LINT=lintlua lintsh lintc clang-analyzer lintcommit lintdoc lint
TEST=functionaltest unittest
generated-sources benchmark $(FORMAT) $(LINT) $(TEST) doc: | build/.ran-cmake
	$(CMAKE) --build build --target $@

test: $(TEST)

iwyu: build/.ran-cmake
	$(CMAKE) --preset iwyu
	$(CMAKE) --build build > build/iwyu.log
	iwyu-fix-includes --only_re="src/nvim" --ignore_re="(src/nvim/eval/encode.c\
	|src/nvim/auto/\
	|src/nvim/os/lang.c\
	|src/nvim/map.c\
	)" --nosafe_headers < build/iwyu.log
	$(CMAKE) -B build -U ENABLE_IWYU
	$(CMAKE) --build build

clean:
ifneq ($(wildcard build),)
	$(CMAKE) --build build --target clean
endif
	$(MAKE) -C test/old/testdir clean
	$(MAKE) -C runtime/indent clean

distclean:
	$(call rmdir, $(DEPS_BUILD_DIR))
	$(call rmdir, build)
	$(MAKE) clean

install: checkprefix nvim
	$(CMAKE) --install build

appimage:
	bash scripts/genappimage.sh

# Build an appimage with embedded update information.
#   appimage-nightly: for nightly builds
#   appimage-latest: for a release
appimage-%:
	bash scripts/genappimage.sh $*

.PHONY: test clean distclean nvim libnvim cmake deps install appimage checkprefix benchmark $(FORMAT) $(LINT) $(TEST)
```

Upto first 50 lines or so, we're just setting up variables, paths to binaries like `cmake` , `ninja`, setting up CWD, path to this makefile in a variable etc . (first few lines populate the vars differently for Windows and Unix.)

#### What happens when you run `make` ?
Lets see what the build targets are:
```
1. all
2. nvim
3. libnvim
4. cmake
5. deps
6. build/.ran-cmake
7. build/.ran-deps-cmake::
8. oldtest
9. iwyu
10. checkprefix
11. appimage
12. clean
13. distclean
14. install
```

When you run `make`, the very first target `all` is run.
`all` has a dependency on `nvim`, hence `nvim` target is run
`nvim` depends on `build/.ran-cmake` and `deps` 
`build/.ran-cmake` depends on `deps` 
`deps` depends on `build/.ran-deps-cmake`
```Makefile
nvim: build/.ran-cmake deps
	$(CMAKE) --build build


​build/.ran-cmake: | deps
	$(CMAKE) -B build -G $(CMAKE_GENERATOR) $(CMAKE_FLAGS) $(CMAKE_EXTRA_FLAGS) $(MAKEFILE_DIR)
	$(TOUCH) $@

deps: | build/.ran-deps-cmake
​ifeq ($(call filter-true,$(USE_BUNDLED)),)
	$(CMAKE) --build $(DEPS_BUILD_DIR)
endif

ifeq ($(call filter-true,$(USE_BUNDLED)),)
$(DEPS_BUILD_DIR):
	$(MKDIR) $@
build/.ran-deps-cmake:: $(DEPS_BUILD_DIR)
	$(CMAKE) -S $(MAKEFILE_DIR)/cmake.deps -B $(DEPS_BUILD_DIR) -G $(CMAKE_GENERATOR) $(BUNDLED_CMAKE_FLAG) $(BUNDLED_LUA_CMAKE_FLAG) $(DEPS_CMAKE_FLAGS)
endif
build/.ran-deps-cmake::
	$(MKDIR) build
	$(TOUCH) "$@"
```
So the order is:
`build/.ran-deps-cmake` -> `deps` -> `build/.ran-cmake` -> `nvim` -> `all` 

#### But why is CMake being used here?
[[what is cmake]]
--> the Goal is to eventually compile the C source code. We could've used `make`(Makefile) to do that, but instead...`ninja-build` is used.  The input files to `ninja` are somewhat hard to write, which is why we use `cmake` to build the build files (for `ninja`) which will eventually be used to compile the C code (what the actual f***).
`Makefile -> CMake -> Ninja/Make -> Final Binary`

```
make <--Read Makefile
  |-- Evaluate variables
  |-- Identify default target (all)
  |-- Resolve dependencies (nvim)
  |-- Run commands (cmake --build build)
       |
       |-- Invoke CMake <-- CMakeLists.txt
       |-- Generate build system (Ninja)
           |
           |-- Run Ninja <-- Ninja build rules
           |-- Execute build commands
           |-- Compile C files
           |-- Link object files
           |-- Generate executables
```
