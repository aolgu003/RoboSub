add_executable(test_mission main.cpp)
target_link_libraries(test_mission 
					${OpenCV_LIBS} 
					comms 
					seagoat_vision 
					segmentation  
					)
