# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/pi/Mouse-glove/tst

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Mouse-glove/tst

# Include any dependencies generated for this target.
include CMakeFiles/Test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Test.dir/flags.make

CMakeFiles/Test.dir/Filt_tst.cpp.o: CMakeFiles/Test.dir/flags.make
CMakeFiles/Test.dir/Filt_tst.cpp.o: Filt_tst.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Mouse-glove/tst/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Test.dir/Filt_tst.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Test.dir/Filt_tst.cpp.o -c /home/pi/Mouse-glove/tst/Filt_tst.cpp

CMakeFiles/Test.dir/Filt_tst.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test.dir/Filt_tst.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Mouse-glove/tst/Filt_tst.cpp > CMakeFiles/Test.dir/Filt_tst.cpp.i

CMakeFiles/Test.dir/Filt_tst.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test.dir/Filt_tst.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Mouse-glove/tst/Filt_tst.cpp -o CMakeFiles/Test.dir/Filt_tst.cpp.s

# Object files for target Test
Test_OBJECTS = \
"CMakeFiles/Test.dir/Filt_tst.cpp.o"

# External object files for target Test
Test_EXTERNAL_OBJECTS =

bin/Test: CMakeFiles/Test.dir/Filt_tst.cpp.o
bin/Test: CMakeFiles/Test.dir/build.make
bin/Test: /usr/lib/libboost_filesystem.so
bin/Test: /usr/lib/libboost_system.so
bin/Test: /usr/lib/libboost_unit_test_framework.so
bin/Test: CMakeFiles/Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Mouse-glove/tst/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/Test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Test.dir/build: bin/Test

.PHONY : CMakeFiles/Test.dir/build

CMakeFiles/Test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Test.dir/clean

CMakeFiles/Test.dir/depend:
	cd /home/pi/Mouse-glove/tst && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Mouse-glove/tst /home/pi/Mouse-glove/tst /home/pi/Mouse-glove/tst /home/pi/Mouse-glove/tst /home/pi/Mouse-glove/tst/CMakeFiles/Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Test.dir/depend

