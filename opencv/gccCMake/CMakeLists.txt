cmake_minimum_required(VERSION 2.8)
project( DisplayImage )

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

set(OpenCV_DIR /usr/sup/opencv-3.0.0/share/OpenCV) 
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /h/mvanweli/workspace/opencv)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( /usr/sup/opencv-3.0.0/include )
add_executable( DisplayImage DisplayImage.cpp )
target_link_libraries( DisplayImage ${OpenCV_LIBS} )
message("LIBS TO COME")
message(${OpenCV_LIBS})
