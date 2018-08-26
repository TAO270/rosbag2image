cmake_minimum_required(VERSION 2.8.11)
project(rosbag2image)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CATKIN_GLOBAL_BIN_DESTINATION ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_BUILD_TYPE "Release")

set(cv_bridge_DIR /usr/local/share/cv_bridge/cmake )

find_package(OpenCV 3.0.0 REQUIRED)

find_package(catkin REQUIRED COMPONENTS 
image_transport 
cv_bridge
roscpp 
std_msgs 
sensor_msgs 
)
#catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES gstcamera
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
#)

include_directories(
  ${OpenCV_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS} 
  /opt/ros/include/
)
#imu2csv
add_executable(imu2csv src/imu2csv.cpp)
target_link_libraries(imu2csv ${catkin_LIBRARIES} )
#imWriteLeft
add_executable(imWriteLeft src/imWriteLeft.cpp)
target_link_libraries(imWriteLeft ${catkin_LIBRARIES} ${OpenCV_LIBS})
#imWriteRight
add_executable(imWriteRight src/imWriteRight.cpp)
target_link_libraries(imWriteRight  ${catkin_LIBRARIES} ${OpenCV_LIBS})
