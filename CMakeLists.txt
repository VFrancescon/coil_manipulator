cmake_minimum_required(VERSION 3.1.0)
project(coil_manipulator)

add_definitions(-std=c++14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(HOME_DIR, "/home/stormlab/Nikita/coil_manipulator/build")
# set(Matlab_ROOT_DIR, "/home/stormlab/MATLAB/")
set(CMAKE_CXX_EXTENSIONS OFF)
# Nikita: for using thread.h
set(CMAKE_CXX_FLAGS -pthread)


find_package( OpenCV REQUIRED )
find_package(Pylon QUIET)
if (NOT ${Pylon_FOUND})
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindPylon.cmake")
endif()
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(include/)
link_directories(include/)
include_directories(submodules)
include_directories("submodules")
link_directories(submodules)
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${Pylon_INCLUDE_DIRS} )
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../MATLAB/extern/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../MATLAB/extern/bin/glnax64")

add_executable( camera_test "src/opencv/camera_test.cpp" )
add_executable( middleware_test "src/middleware_test.cpp")
add_executable( tip_tracking "src/opencv/tip_tracking.cpp")
add_executable( skeleton "src/opencv/skeleton_method.cpp")
add_executable( thcal "src/opencv/thresholds_cal.cpp")
add_executable( run_camera "src/opencv/run_camera.cpp")
add_executable( field3d "src/set3DField.cpp")
add_executable( precomps "src/precomputation.cpp" )
add_executable( introducer "src/introducer.cpp")
add_executable( nikita_cl "src/nikita_cl.cpp"
                        "dynamic_lungs_embed/4_DynamicLungs_working/dynamic_lungs_embed_ert_rtw/dynamic_lungs_embed_data.cpp"
                        "dynamic_lungs_embed/4_DynamicLungs_working/dynamic_lungs_embed_ert_rtw/dynamic_lungs_embed.cpp"
                        "dynamic_lungs_embed/MATLAB/rtw/c/src/rt_logging.c"
                        "${CMAKE_CURRENT_SOURCE_DIR}/../../MATLAB/extern/include/MatlabEngine.hpp"
                        "${CMAKE_CURRENT_SOURCE_DIR}/../../MATLAB/extern/include/MatlabDataArray.hpp")
# add_executable( PsuLibTest "src/PSULib_test.cpp")
# add_executable( initial_test "src/initial_serial_comm.cpp")
# add_executable( teslameter_test "src/TeslameterTest.cpp")

target_include_directories(precomps PUBLIC "submodules")
target_include_directories(nikita_cl PUBLIC submodules include)
target_include_directories(nikita_cl PUBLIC "dynamic_lungs_embed/4_DynamicLungs_working/dynamic_lungs_embed_ert_rtw")
target_include_directories(nikita_cl PUBLIC "dynamic_lungs_embed/MATLAB/rtw/c/src")
target_include_directories(nikita_cl PUBLIC "dynamic_lungs_embed/MATLAB/simulink/include")
target_include_directories(nikita_cl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../MATLAB/extern/include")

target_link_libraries( camera_test ${OpenCV_LIBS} ${Pylon_LIBRARIES} )
target_link_libraries( tip_tracking ${OpenCV_LIBS} ${Pylon_LIBRARIES} a-star)
target_link_libraries( skeleton ${OpenCV_LIBS} a-star)
target_link_libraries( thcal ${OpenCV_LIBS} ${Pylon_LIBRARIES})
target_link_libraries( run_camera ${OpenCV_LIBS} ${Pylon_LIBRARIES})
target_link_libraries( introducer LINK_PUBLIC LinActuatorLib)
target_link_libraries( middleware_test LINK_PUBLIC HCoilMiddlewareLib )
target_link_libraries( field3d LINK_PUBLIC HCoilMiddlewareLib)
target_link_libraries( precomps Eigen3::Eigen)
target_link_libraries( nikita_cl ${OpenCV_LIBS} ${Pylon_LIBRARIES} Eigen3::Eigen)
target_link_libraries( nikita_cl ${CMAKE_CURRENT_SOURCE_DIR}/../../MATLAB/extern/bin/glnxa64/libMatlabEngine.so)
target_link_libraries( nikita_cl ${CMAKE_CURRENT_SOURCE_DIR}/../../MATLAB/extern/bin/glnxa64/libMatlabDataArray.so)

# link_directories(nikit_cl "/home/stormlab/MATLAB/extern/bin/glnax64")
# target_link_libraries( PsuLibTest LINK_PUBLIC DxkdpLib )
# target_link_libraries( initial_test LINK_PUBLIC CppLinuxSerial )
# target_link_libraries( teslameter_test LINK_PUBLIC LakeshoreF71Lib )

## Two lines below allow libraries to be built.
include_directories(libs/include)
add_subdirectory(libs/src)
add_subdirectory(submodules/a-star)
add_subdirectory(docsBuild)





