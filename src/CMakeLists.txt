target_link_libraries(VideoPlayer ${OpenCV_LIBS} )
cmake_minimum_required(VERSION 3.17)
project( VideoPlayer )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(SOURCES
  Delivery3_7.cpp
)
add_executable( ${PROJECT_NAME} ${SOURCES})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )