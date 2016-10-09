cmake_minimum_required(VERSION 2.8)
project( grabcut )
find_package( OpenCV REQUIRED )
add_executable( grabcut grabcut.cpp )
target_link_libraries( grabcut ${OpenCV_LIBS} )

