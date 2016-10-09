add_executable(comms_mission main.cpp)

target_link_libraries(comms_mission 
					${OpenCV_LIBS} 
					comms 
					seagoat_vision 
					segmentation  
					)
