# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.30.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.30.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/allantoledo/CLionProjects/compiladorMiniJava

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/allantoledo/CLionProjects/compiladorMiniJava

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.30.2/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.30.2/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/allantoledo/CLionProjects/compiladorMiniJava/CMakeFiles /Users/allantoledo/CLionProjects/compiladorMiniJava//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/allantoledo/CLionProjects/compiladorMiniJava/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named compiler

# Build rule for target.
compiler: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 compiler
.PHONY : compiler

# fast build rule for target.
compiler/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/build
.PHONY : compiler/fast

#=============================================================================
# Target rules for targets named interpreter

# Build rule for target.
interpreter: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 interpreter
.PHONY : interpreter

# fast build rule for target.
interpreter/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/build
.PHONY : interpreter/fast

src/compiler.o: src/compiler.cpp.o
.PHONY : src/compiler.o

# target to build an object file
src/compiler.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/compiler.cpp.o
.PHONY : src/compiler.cpp.o

src/compiler.i: src/compiler.cpp.i
.PHONY : src/compiler.i

# target to preprocess a source file
src/compiler.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/compiler.cpp.i
.PHONY : src/compiler.cpp.i

src/compiler.s: src/compiler.cpp.s
.PHONY : src/compiler.s

# target to generate assembly for a file
src/compiler.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/compiler.cpp.s
.PHONY : src/compiler.cpp.s

src/interpreter.o: src/interpreter.cpp.o
.PHONY : src/interpreter.o

# target to build an object file
src/interpreter.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/interpreter.cpp.o
.PHONY : src/interpreter.cpp.o

src/interpreter.i: src/interpreter.cpp.i
.PHONY : src/interpreter.i

# target to preprocess a source file
src/interpreter.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/interpreter.cpp.i
.PHONY : src/interpreter.cpp.i

src/interpreter.s: src/interpreter.cpp.s
.PHONY : src/interpreter.s

# target to generate assembly for a file
src/interpreter.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/interpreter.cpp.s
.PHONY : src/interpreter.cpp.s

src/ist/ist.o: src/ist/ist.cpp.o
.PHONY : src/ist/ist.o

# target to build an object file
src/ist/ist.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/ist/ist.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/ist/ist.cpp.o
.PHONY : src/ist/ist.cpp.o

src/ist/ist.i: src/ist/ist.cpp.i
.PHONY : src/ist/ist.i

# target to preprocess a source file
src/ist/ist.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/ist/ist.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/ist/ist.cpp.i
.PHONY : src/ist/ist.cpp.i

src/ist/ist.s: src/ist/ist.cpp.s
.PHONY : src/ist/ist.s

# target to generate assembly for a file
src/ist/ist.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/ist/ist.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/ist/ist.cpp.s
.PHONY : src/ist/ist.cpp.s

src/lex/lex.o: src/lex/lex.cpp.o
.PHONY : src/lex/lex.o

# target to build an object file
src/lex/lex.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/lex/lex.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/lex/lex.cpp.o
.PHONY : src/lex/lex.cpp.o

src/lex/lex.i: src/lex/lex.cpp.i
.PHONY : src/lex/lex.i

# target to preprocess a source file
src/lex/lex.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/lex/lex.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/lex/lex.cpp.i
.PHONY : src/lex/lex.cpp.i

src/lex/lex.s: src/lex/lex.cpp.s
.PHONY : src/lex/lex.s

# target to generate assembly for a file
src/lex/lex.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/lex/lex.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/lex/lex.cpp.s
.PHONY : src/lex/lex.cpp.s

src/sin/sin.o: src/sin/sin.cpp.o
.PHONY : src/sin/sin.o

# target to build an object file
src/sin/sin.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/sin/sin.cpp.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/sin/sin.cpp.o
.PHONY : src/sin/sin.cpp.o

src/sin/sin.i: src/sin/sin.cpp.i
.PHONY : src/sin/sin.i

# target to preprocess a source file
src/sin/sin.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/sin/sin.cpp.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/sin/sin.cpp.i
.PHONY : src/sin/sin.cpp.i

src/sin/sin.s: src/sin/sin.cpp.s
.PHONY : src/sin/sin.s

# target to generate assembly for a file
src/sin/sin.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/compiler.dir/build.make CMakeFiles/compiler.dir/src/sin/sin.cpp.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/interpreter.dir/build.make CMakeFiles/interpreter.dir/src/sin/sin.cpp.s
.PHONY : src/sin/sin.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... compiler"
	@echo "... interpreter"
	@echo "... src/compiler.o"
	@echo "... src/compiler.i"
	@echo "... src/compiler.s"
	@echo "... src/interpreter.o"
	@echo "... src/interpreter.i"
	@echo "... src/interpreter.s"
	@echo "... src/ist/ist.o"
	@echo "... src/ist/ist.i"
	@echo "... src/ist/ist.s"
	@echo "... src/lex/lex.o"
	@echo "... src/lex/lex.i"
	@echo "... src/lex/lex.s"
	@echo "... src/sin/sin.o"
	@echo "... src/sin/sin.i"
	@echo "... src/sin/sin.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

