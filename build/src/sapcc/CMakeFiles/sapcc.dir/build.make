# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chuck/Src/sapcc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chuck/Src/sapcc/build

# Include any dependencies generated for this target.
include src/sapcc/CMakeFiles/sapcc.dir/depend.make

# Include the progress variables for this target.
include src/sapcc/CMakeFiles/sapcc.dir/progress.make

# Include the compile flags for this target's objects.
include src/sapcc/CMakeFiles/sapcc.dir/flags.make

src/sapcc/CMakeFiles/sapcc.dir/utils.c.o: src/sapcc/CMakeFiles/sapcc.dir/flags.make
src/sapcc/CMakeFiles/sapcc.dir/utils.c.o: ../src/sapcc/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chuck/Src/sapcc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/sapcc/CMakeFiles/sapcc.dir/utils.c.o"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sapcc.dir/utils.c.o -c /home/chuck/Src/sapcc/src/sapcc/utils.c

src/sapcc/CMakeFiles/sapcc.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sapcc.dir/utils.c.i"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chuck/Src/sapcc/src/sapcc/utils.c > CMakeFiles/sapcc.dir/utils.c.i

src/sapcc/CMakeFiles/sapcc.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sapcc.dir/utils.c.s"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chuck/Src/sapcc/src/sapcc/utils.c -o CMakeFiles/sapcc.dir/utils.c.s

src/sapcc/CMakeFiles/sapcc.dir/scanner.c.o: src/sapcc/CMakeFiles/sapcc.dir/flags.make
src/sapcc/CMakeFiles/sapcc.dir/scanner.c.o: ../src/sapcc/scanner.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chuck/Src/sapcc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/sapcc/CMakeFiles/sapcc.dir/scanner.c.o"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sapcc.dir/scanner.c.o -c /home/chuck/Src/sapcc/src/sapcc/scanner.c

src/sapcc/CMakeFiles/sapcc.dir/scanner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sapcc.dir/scanner.c.i"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chuck/Src/sapcc/src/sapcc/scanner.c > CMakeFiles/sapcc.dir/scanner.c.i

src/sapcc/CMakeFiles/sapcc.dir/scanner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sapcc.dir/scanner.c.s"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chuck/Src/sapcc/src/sapcc/scanner.c -o CMakeFiles/sapcc.dir/scanner.c.s

src/sapcc/CMakeFiles/sapcc.dir/parser.c.o: src/sapcc/CMakeFiles/sapcc.dir/flags.make
src/sapcc/CMakeFiles/sapcc.dir/parser.c.o: ../src/sapcc/parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chuck/Src/sapcc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/sapcc/CMakeFiles/sapcc.dir/parser.c.o"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sapcc.dir/parser.c.o -c /home/chuck/Src/sapcc/src/sapcc/parser.c

src/sapcc/CMakeFiles/sapcc.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sapcc.dir/parser.c.i"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chuck/Src/sapcc/src/sapcc/parser.c > CMakeFiles/sapcc.dir/parser.c.i

src/sapcc/CMakeFiles/sapcc.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sapcc.dir/parser.c.s"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chuck/Src/sapcc/src/sapcc/parser.c -o CMakeFiles/sapcc.dir/parser.c.s

src/sapcc/CMakeFiles/sapcc.dir/main.c.o: src/sapcc/CMakeFiles/sapcc.dir/flags.make
src/sapcc/CMakeFiles/sapcc.dir/main.c.o: ../src/sapcc/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chuck/Src/sapcc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/sapcc/CMakeFiles/sapcc.dir/main.c.o"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/sapcc.dir/main.c.o -c /home/chuck/Src/sapcc/src/sapcc/main.c

src/sapcc/CMakeFiles/sapcc.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sapcc.dir/main.c.i"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chuck/Src/sapcc/src/sapcc/main.c > CMakeFiles/sapcc.dir/main.c.i

src/sapcc/CMakeFiles/sapcc.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sapcc.dir/main.c.s"
	cd /home/chuck/Src/sapcc/build/src/sapcc && /usr/bin/clang $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chuck/Src/sapcc/src/sapcc/main.c -o CMakeFiles/sapcc.dir/main.c.s

# Object files for target sapcc
sapcc_OBJECTS = \
"CMakeFiles/sapcc.dir/utils.c.o" \
"CMakeFiles/sapcc.dir/scanner.c.o" \
"CMakeFiles/sapcc.dir/parser.c.o" \
"CMakeFiles/sapcc.dir/main.c.o"

# External object files for target sapcc
sapcc_EXTERNAL_OBJECTS =

../bin/sapcc: src/sapcc/CMakeFiles/sapcc.dir/utils.c.o
../bin/sapcc: src/sapcc/CMakeFiles/sapcc.dir/scanner.c.o
../bin/sapcc: src/sapcc/CMakeFiles/sapcc.dir/parser.c.o
../bin/sapcc: src/sapcc/CMakeFiles/sapcc.dir/main.c.o
../bin/sapcc: src/sapcc/CMakeFiles/sapcc.dir/build.make
../bin/sapcc: ../bin/libcommon.a
../bin/sapcc: src/sapcc/CMakeFiles/sapcc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chuck/Src/sapcc/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable ../../../bin/sapcc"
	cd /home/chuck/Src/sapcc/build/src/sapcc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sapcc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/sapcc/CMakeFiles/sapcc.dir/build: ../bin/sapcc

.PHONY : src/sapcc/CMakeFiles/sapcc.dir/build

src/sapcc/CMakeFiles/sapcc.dir/clean:
	cd /home/chuck/Src/sapcc/build/src/sapcc && $(CMAKE_COMMAND) -P CMakeFiles/sapcc.dir/cmake_clean.cmake
.PHONY : src/sapcc/CMakeFiles/sapcc.dir/clean

src/sapcc/CMakeFiles/sapcc.dir/depend:
	cd /home/chuck/Src/sapcc/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chuck/Src/sapcc /home/chuck/Src/sapcc/src/sapcc /home/chuck/Src/sapcc/build /home/chuck/Src/sapcc/build/src/sapcc /home/chuck/Src/sapcc/build/src/sapcc/CMakeFiles/sapcc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/sapcc/CMakeFiles/sapcc.dir/depend

