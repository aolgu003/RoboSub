cmake_minimum_required(VERSION 2.8)
project( seagoat_test )

include_directories ("${PROJECT_SOURCE_DIR}/seagoat_vision/include")
find_package( OpenCV REQUIRED )

add_subdirectory( seagoat_vision ./seagoat_vision)
add_subdirectory(mission ./mission)
#add_subdirectory(harness_tests ./harness_tests)
