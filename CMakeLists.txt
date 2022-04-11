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
add_subdirectory(src)
add_subdirectory(docs)





