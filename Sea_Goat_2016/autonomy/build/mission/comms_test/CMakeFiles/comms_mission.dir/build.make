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
include mission/comms_test/CMakeFiles/comms_mission.dir/depend.make

# Include the progress variables for this target.
include mission/comms_test/CMakeFiles/comms_mission.dir/progress.make

# Include the compile flags for this target's objects.
include mission/comms_test/CMakeFiles/comms_mission.dir/flags.make

mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o: mission/comms_test/CMakeFiles/comms_mission.dir/flags.make
mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o: ../mission/comms_test/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/mission/comms_test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/comms_mission.dir/main.cpp.o -c /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/mission/comms_test/main.cpp

mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/comms_mission.dir/main.cpp.i"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/mission/comms_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/mission/comms_test/main.cpp > CMakeFiles/comms_mission.dir/main.cpp.i

mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/comms_mission.dir/main.cpp.s"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/mission/comms_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/mission/comms_test/main.cpp -o CMakeFiles/comms_mission.dir/main.cpp.s

mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o.requires:
.PHONY : mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o.requires

mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o.provides: mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o.requires
	$(MAKE) -f mission/comms_test/CMakeFiles/comms_mission.dir/build.make mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o.provides.build
.PHONY : mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o.provides

mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o.provides.build: mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o

# Object files for target comms_mission
comms_mission_OBJECTS = \
"CMakeFiles/comms_mission.dir/main.cpp.o"

# External object files for target comms_mission
comms_mission_EXTERNAL_OBJECTS =

mission/comms_test/comms_mission: mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o
mission/comms_test/comms_mission: mission/comms_test/CMakeFiles/comms_mission.dir/build.make
mission/comms_test/comms_mission: /usr/local/lib/libopencv_videostab.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_videoio.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_video.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_superres.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_stitching.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_shape.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_photo.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_objdetect.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_ml.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_imgproc.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_highgui.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_hal.a
mission/comms_test/comms_mission: /usr/local/lib/libopencv_flann.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_features2d.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_core.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_calib3d.so.3.0.0
mission/comms_test/comms_mission: seagoat_vision/include/libcomms.so
mission/comms_test/comms_mission: seagoat_vision/include/libseagoat_vision.so
mission/comms_test/comms_mission: seagoat_vision/include/libsegmentation.so
mission/comms_test/comms_mission: /usr/local/lib/libopencv_features2d.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_ml.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_highgui.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_videoio.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_flann.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_video.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_imgproc.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_core.so.3.0.0
mission/comms_test/comms_mission: /usr/local/lib/libopencv_hal.a
mission/comms_test/comms_mission: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
mission/comms_test/comms_mission: mission/comms_test/CMakeFiles/comms_mission.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable comms_mission"
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/mission/comms_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/comms_mission.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mission/comms_test/CMakeFiles/comms_mission.dir/build: mission/comms_test/comms_mission
.PHONY : mission/comms_test/CMakeFiles/comms_mission.dir/build

mission/comms_test/CMakeFiles/comms_mission.dir/requires: mission/comms_test/CMakeFiles/comms_mission.dir/main.cpp.o.requires
.PHONY : mission/comms_test/CMakeFiles/comms_mission.dir/requires

mission/comms_test/CMakeFiles/comms_mission.dir/clean:
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/mission/comms_test && $(CMAKE_COMMAND) -P CMakeFiles/comms_mission.dir/cmake_clean.cmake
.PHONY : mission/comms_test/CMakeFiles/comms_mission.dir/clean

mission/comms_test/CMakeFiles/comms_mission.dir/depend:
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/mission/comms_test /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/mission/comms_test /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/build/mission/comms_test/CMakeFiles/comms_mission.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mission/comms_test/CMakeFiles/comms_mission.dir/depend

