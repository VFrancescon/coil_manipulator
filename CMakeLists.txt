cmake_minimum_required(VERSION 3.1.0)
project(coil_manipulator)

add_definitions(-std=c++14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package( OpenCV REQUIRED )
find_package(Pylon QUIET)
if (NOT ${Pylon_FOUND})
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindPylon.cmake")
endif()

include_directories(include)
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Pylon_INCLUDE_DIRS} )

## Two lines below allow libraries to be built.
include_directories(libs/include)
add_subdirectory(libs/src)

add_executable( PsuLibTest "${CMAKE_SOURCE_DIR}/src/PSULib_test.cpp")
add_executable( initial_test "${CMAKE_SOURCE_DIR}/src/initial_serial_comm.cpp")
add_executable( camera_test "${CMAKE_SOURCE_DIR}/src/opencv/camera_test.cpp" )
add_executable( teslameter_test "${CMAKE_SOURCE_DIR}/src/TeslameterTest.cpp")

target_link_libraries( PsuLibTest LINK_PUBLIC DxkdpLib)
target_link_libraries( initial_test LINK_PUBLIC CppLinuxSerial)
target_link_libraries( camera_test ${OpenCV_LIBS} ${Pylon_LIBRARIES} )
target_link_libraries( teslameter_test LINK_PUBLIC LakeshoreF71Lib)
# target_include_directories(initial_test PUBLIC
#                           "${CMAKE_SOURCE_DIR}"
#                           "${CMAKE_SOURCE_DIR}/src/CppLinuxSerial"
#                           )


