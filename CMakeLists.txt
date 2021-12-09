cmake_minimum_required(VERSION 3.1.0)
project(coil_manipulator)

add_definitions(-std=c++14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)
add_subdirectory(src/CppLinuxSerial)

add_executable(initial_test "${CMAKE_SOURCE_DIR}/src/initial_serial_comm.cpp")

target_link_libraries(initial_test PUBLIC CppLinuxSerial)

target_include_directories(initial_test PUBLIC
                          "${CMAKE_SOURCE_DIR}"
                          "${CMAKE_SOURCE_DIR}/src/CppLinuxSerial"
                          )