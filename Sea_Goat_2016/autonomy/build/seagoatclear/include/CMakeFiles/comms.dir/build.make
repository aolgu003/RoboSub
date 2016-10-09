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
CMAKE_SOURCE_DIR = /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build

# Include any dependencies generated for this target.
include seagoat_vision/include/CMakeFiles/comms.dir/depend.make

# Include the progress variables for this target.
include seagoat_vision/include/CMakeFiles/comms.dir/progress.make

# Include the compile flags for this target's objects.
include seagoat_vision/include/CMakeFiles/comms.dir/flags.make

seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o: seagoat_vision/include/CMakeFiles/comms.dir/flags.make
seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o: ../seagoat_vision/include/comms.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/seagoat_vision/include && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/comms.dir/comms.cpp.o -c /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/seagoat_vision/include/comms.cpp

seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comms.dir/comms.cpp.i"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/seagoat_vision/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/seagoat_vision/include/comms.cpp > CMakeFiles/comms.dir/comms.cpp.i

seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comms.dir/comms.cpp.s"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/seagoat_vision/include && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/seagoat_vision/include/comms.cpp -o CMakeFiles/comms.dir/comms.cpp.s

seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o.requires:
.PHONY : seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o.requires

seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o.provides: seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o.requires
	$(MAKE) -f seagoat_vision/include/CMakeFiles/comms.dir/build.make seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o.provides.build
.PHONY : seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o.provides

seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o.provides.build: seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o

# Object files for target comms
comms_OBJECTS = \
"CMakeFiles/comms.dir/comms.cpp.o"

# External object files for target comms
comms_EXTERNAL_OBJECTS =

seagoat_vision/include/libcomms.so: seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o
seagoat_vision/include/libcomms.so: seagoat_vision/include/CMakeFiles/comms.dir/build.make
seagoat_vision/include/libcomms.so: seagoat_vision/include/CMakeFiles/comms.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libcomms.so"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/seagoat_vision/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/comms.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
seagoat_vision/include/CMakeFiles/comms.dir/build: seagoat_vision/include/libcomms.so
.PHONY : seagoat_vision/include/CMakeFiles/comms.dir/build

seagoat_vision/include/CMakeFiles/comms.dir/requires: seagoat_vision/include/CMakeFiles/comms.dir/comms.cpp.o.requires
.PHONY : seagoat_vision/include/CMakeFiles/comms.dir/requires

seagoat_vision/include/CMakeFiles/comms.dir/clean:
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/seagoat_vision/include && $(CMAKE_COMMAND) -P CMakeFiles/comms.dir/cmake_clean.cmake
.PHONY : seagoat_vision/include/CMakeFiles/comms.dir/clean

seagoat_vision/include/CMakeFiles/comms.dir/depend:
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/seagoat_vision/include /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/seagoat_vision/include /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/seagoat_vision/include/CMakeFiles/comms.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : seagoat_vision/include/CMakeFiles/comms.dir/depend
