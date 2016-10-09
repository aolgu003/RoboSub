cmake_minimum_required(VERSION 2.8)
project( saliencySeg )

find_package( OpenCV REQUIRED )
include_directories ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory (include) 

add_executable( lighting_test test_lighting.cpp )
target_link_libraries( lighting_test ${OpenCV_LIBS} )
target_link_libraries( lighting_test segmentation)

add_executable(competition_test test_competition.cpp)
target_link_libraries( competition_test ${OpenCV_LIBS} )
target_link_libraries( competition_test segmentation)
