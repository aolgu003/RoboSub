# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build

# Include any dependencies generated for this target.
include include/CMakeFiles/segmentation.dir/depend.make

# Include the progress variables for this target.
include include/CMakeFiles/segmentation.dir/progress.make

# Include the compile flags for this target's objects.
include include/CMakeFiles/segmentation.dir/flags.make

include/CMakeFiles/segmentation.dir/segmentation.cpp.o: include/CMakeFiles/segmentation.dir/flags.make
include/CMakeFiles/segmentation.dir/segmentation.cpp.o: ../include/segmentation.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object include/CMakeFiles/segmentation.dir/segmentation.cpp.o"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/include && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/segmentation.dir/segmentation.cpp.o -c /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/include/segmentation.cpp

include/CMakeFiles/segmentation.dir/segmentation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/segmentation.dir/segmentation.cpp.i"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/include/segmentation.cpp > CMakeFiles/segmentation.dir/segmentation.cpp.i

include/CMakeFiles/segmentation.dir/segmentation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/segmentation.dir/segmentation.cpp.s"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/include/segmentation.cpp -o CMakeFiles/segmentation.dir/segmentation.cpp.s

include/CMakeFiles/segmentation.dir/segmentation.cpp.o.requires:
.PHONY : include/CMakeFiles/segmentation.dir/segmentation.cpp.o.requires

include/CMakeFiles/segmentation.dir/segmentation.cpp.o.provides: include/CMakeFiles/segmentation.dir/segmentation.cpp.o.requires
	$(MAKE) -f include/CMakeFiles/segmentation.dir/build.make include/CMakeFiles/segmentation.dir/segmentation.cpp.o.provides.build
.PHONY : include/CMakeFiles/segmentation.dir/segmentation.cpp.o.provides

include/CMakeFiles/segmentation.dir/segmentation.cpp.o.provides.build: include/CMakeFiles/segmentation.dir/segmentation.cpp.o

# Object files for target segmentation
segmentation_OBJECTS = \
"CMakeFiles/segmentation.dir/segmentation.cpp.o"

# External object files for target segmentation
segmentation_EXTERNAL_OBJECTS =

include/libsegmentation.so: include/CMakeFiles/segmentation.dir/segmentation.cpp.o
include/libsegmentation.so: include/CMakeFiles/segmentation.dir/build.make
include/libsegmentation.so: include/CMakeFiles/segmentation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libsegmentation.so"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/segmentation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/CMakeFiles/segmentation.dir/build: include/libsegmentation.so
.PHONY : include/CMakeFiles/segmentation.dir/build

include/CMakeFiles/segmentation.dir/requires: include/CMakeFiles/segmentation.dir/segmentation.cpp.o.requires
.PHONY : include/CMakeFiles/segmentation.dir/requires

include/CMakeFiles/segmentation.dir/clean:
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/include && $(CMAKE_COMMAND) -P CMakeFiles/segmentation.dir/cmake_clean.cmake
.PHONY : include/CMakeFiles/segmentation.dir/clean

include/CMakeFiles/segmentation.dir/depend:
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/include /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/include /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/include/CMakeFiles/segmentation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/CMakeFiles/segmentation.dir/depend
