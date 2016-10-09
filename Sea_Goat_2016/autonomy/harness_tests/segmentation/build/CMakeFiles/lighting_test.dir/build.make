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
include CMakeFiles/lighting_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lighting_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lighting_test.dir/flags.make

CMakeFiles/lighting_test.dir/test_lighting.cpp.o: CMakeFiles/lighting_test.dir/flags.make
CMakeFiles/lighting_test.dir/test_lighting.cpp.o: ../test_lighting.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lighting_test.dir/test_lighting.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lighting_test.dir/test_lighting.cpp.o -c /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/test_lighting.cpp

CMakeFiles/lighting_test.dir/test_lighting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lighting_test.dir/test_lighting.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/test_lighting.cpp > CMakeFiles/lighting_test.dir/test_lighting.cpp.i

CMakeFiles/lighting_test.dir/test_lighting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lighting_test.dir/test_lighting.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/test_lighting.cpp -o CMakeFiles/lighting_test.dir/test_lighting.cpp.s

CMakeFiles/lighting_test.dir/test_lighting.cpp.o.requires:
.PHONY : CMakeFiles/lighting_test.dir/test_lighting.cpp.o.requires

CMakeFiles/lighting_test.dir/test_lighting.cpp.o.provides: CMakeFiles/lighting_test.dir/test_lighting.cpp.o.requires
	$(MAKE) -f CMakeFiles/lighting_test.dir/build.make CMakeFiles/lighting_test.dir/test_lighting.cpp.o.provides.build
.PHONY : CMakeFiles/lighting_test.dir/test_lighting.cpp.o.provides

CMakeFiles/lighting_test.dir/test_lighting.cpp.o.provides.build: CMakeFiles/lighting_test.dir/test_lighting.cpp.o

# Object files for target lighting_test
lighting_test_OBJECTS = \
"CMakeFiles/lighting_test.dir/test_lighting.cpp.o"

# External object files for target lighting_test
lighting_test_EXTERNAL_OBJECTS =

lighting_test: CMakeFiles/lighting_test.dir/test_lighting.cpp.o
lighting_test: CMakeFiles/lighting_test.dir/build.make
lighting_test: /usr/local/lib/libopencv_videostab.so.3.0.0
lighting_test: /usr/local/lib/libopencv_videoio.so.3.0.0
lighting_test: /usr/local/lib/libopencv_video.so.3.0.0
lighting_test: /usr/local/lib/libopencv_superres.so.3.0.0
lighting_test: /usr/local/lib/libopencv_stitching.so.3.0.0
lighting_test: /usr/local/lib/libopencv_shape.so.3.0.0
lighting_test: /usr/local/lib/libopencv_photo.so.3.0.0
lighting_test: /usr/local/lib/libopencv_objdetect.so.3.0.0
lighting_test: /usr/local/lib/libopencv_ml.so.3.0.0
lighting_test: /usr/local/lib/libopencv_imgproc.so.3.0.0
lighting_test: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
lighting_test: /usr/local/lib/libopencv_highgui.so.3.0.0
lighting_test: /usr/local/lib/libopencv_hal.a
lighting_test: /usr/local/lib/libopencv_flann.so.3.0.0
lighting_test: /usr/local/lib/libopencv_features2d.so.3.0.0
lighting_test: /usr/local/lib/libopencv_core.so.3.0.0
lighting_test: /usr/local/lib/libopencv_calib3d.so.3.0.0
lighting_test: include/libsegmentation.so
lighting_test: /usr/local/lib/libopencv_features2d.so.3.0.0
lighting_test: /usr/local/lib/libopencv_ml.so.3.0.0
lighting_test: /usr/local/lib/libopencv_highgui.so.3.0.0
lighting_test: /usr/local/lib/libopencv_videoio.so.3.0.0
lighting_test: /usr/local/lib/libopencv_imgcodecs.so.3.0.0
lighting_test: /usr/local/lib/libopencv_flann.so.3.0.0
lighting_test: /usr/local/lib/libopencv_video.so.3.0.0
lighting_test: /usr/local/lib/libopencv_imgproc.so.3.0.0
lighting_test: /usr/local/lib/libopencv_core.so.3.0.0
lighting_test: /usr/local/lib/libopencv_hal.a
lighting_test: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
lighting_test: CMakeFiles/lighting_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable lighting_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lighting_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lighting_test.dir/build: lighting_test
.PHONY : CMakeFiles/lighting_test.dir/build

CMakeFiles/lighting_test.dir/requires: CMakeFiles/lighting_test.dir/test_lighting.cpp.o.requires
.PHONY : CMakeFiles/lighting_test.dir/requires

CMakeFiles/lighting_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lighting_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lighting_test.dir/clean

CMakeFiles/lighting_test.dir/depend:
	cd /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build /home/andrew/Projects/RoboSub/Sea_Goat_2016/autonomy/vision/harness_tests/segmentation/build/CMakeFiles/lighting_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lighting_test.dir/depend
