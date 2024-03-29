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
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(include)
include_directories(submodules)
include_directories("submodules")
link_directories(submodules)
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Pylon_INCLUDE_DIRS} )

add_executable( camera_test "src/opencv/camera_test.cpp" )
add_executable( middleware_test "src/middleware_test.cpp")
add_executable( tip_tracking "src/opencv/tip_tracking.cpp")
# add_executable( skeleton "src/opencv/skeleton_method.cpp")
add_executable( thcal "src/opencv/thresholds_cal.cpp")
add_executable( run_camera "src/opencv/run_camera.cpp")
add_executable( field3d "src/set3DField.cpp")
add_executable( precomps "src/precomputation.cpp" )
add_executable( introducer "src/introducer.cpp")
add_executable( psus "src/psu_test.cpp")
add_executable( pylonSave "src/opencv/pylonSave.cpp")
add_executable( debugPolarity "src/debugPolarity.cpp")
add_executable( waterfall "src/waterfall.cpp")
add_executable( biterror "src/biterrordebug.cpp")

# add_executable( PsuLibTest "src/PSULib_test.cpp")
# add_executable( initial_test "src/initial_serial_comm.cpp")
# add_executable( teslameter_test "src/TeslameterTest.cpp")

target_include_directories(precomps PUBLIC "submodules")

target_link_libraries( camera_test ${OpenCV_LIBS} ${Pylon_LIBRARIES} )
target_link_libraries( tip_tracking ${OpenCV_LIBS} ${Pylon_LIBRARIES})
# target_link_libraries( skeleton ${OpenCV_LIBS} a-star)
target_link_libraries( thcal ${OpenCV_LIBS} ${Pylon_LIBRARIES})
target_link_libraries( run_camera ${OpenCV_LIBS} ${Pylon_LIBRARIES})
target_link_libraries( introducer LINK_PUBLIC LinActuatorLib)
target_link_libraries( middleware_test LINK_PUBLIC HCoilMiddlewareLib )
target_link_libraries( field3d LINK_PUBLIC HCoilMiddlewareLib)
target_link_libraries( precomps Eigen3::Eigen)
target_link_libraries( psus LINK_PUBLIC DxkdpLib)
target_link_libraries( pylonSave ${Pylon_LIBRARIES} ${OpenCV_LIBS})
target_link_libraries( debugPolarity LINK_PUBLIC CppLinuxSerial)
#link libs Dxkdp, cpplinuxserial to waterfall target
target_link_libraries( waterfall LINK_PUBLIC DxkdpLib CppLinuxSerial)
target_link_libraries( biterror LINK_PUBLIC DxkdpLib CppLinuxSerial)

# target_link_libraries( PsuLibTest LINK_PUBLIC DxkdpLib )
# target_link_libraries( initial_test LINK_PUBLIC CppLinuxSerial )
# target_link_libraries( teslameter_test LINK_PUBLIC LakeshoreF71Lib )


## Two lines below allow libraries to be built.
include_directories(libs/include)
add_subdirectory(libs/src)
# add_subdirectory(submodules/a-star)
# add_subdirectory(src)
add_subdirectory(docsBuild)





