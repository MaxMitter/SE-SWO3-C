# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/swo3/Homework/Ue09/feedback/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/swo3/Homework/Ue09/feedback/src/build

# Include any dependencies generated for this target.
include CMakeFiles/deque.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/deque.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/deque.dir/flags.make

CMakeFiles/deque.dir/deque/main.cpp.o: CMakeFiles/deque.dir/flags.make
CMakeFiles/deque.dir/deque/main.cpp.o: ../deque/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/swo3/Homework/Ue09/feedback/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/deque.dir/deque/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/deque.dir/deque/main.cpp.o -c /home/swo3/Homework/Ue09/feedback/src/deque/main.cpp

CMakeFiles/deque.dir/deque/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/deque.dir/deque/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/swo3/Homework/Ue09/feedback/src/deque/main.cpp > CMakeFiles/deque.dir/deque/main.cpp.i

CMakeFiles/deque.dir/deque/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/deque.dir/deque/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/swo3/Homework/Ue09/feedback/src/deque/main.cpp -o CMakeFiles/deque.dir/deque/main.cpp.s

# Object files for target deque
deque_OBJECTS = \
"CMakeFiles/deque.dir/deque/main.cpp.o"

# External object files for target deque
deque_EXTERNAL_OBJECTS =

bin/deque: CMakeFiles/deque.dir/deque/main.cpp.o
bin/deque: CMakeFiles/deque.dir/build.make
bin/deque: CMakeFiles/deque.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/swo3/Homework/Ue09/feedback/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/deque"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/deque.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/deque.dir/build: bin/deque

.PHONY : CMakeFiles/deque.dir/build

CMakeFiles/deque.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/deque.dir/cmake_clean.cmake
.PHONY : CMakeFiles/deque.dir/clean

CMakeFiles/deque.dir/depend:
	cd /home/swo3/Homework/Ue09/feedback/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/swo3/Homework/Ue09/feedback/src /home/swo3/Homework/Ue09/feedback/src /home/swo3/Homework/Ue09/feedback/src/build /home/swo3/Homework/Ue09/feedback/src/build /home/swo3/Homework/Ue09/feedback/src/build/CMakeFiles/deque.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/deque.dir/depend
