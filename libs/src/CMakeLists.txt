find_package(Threads REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# STEP 1: Include cpp files

file(GLOB_RECURSE PSU_LIB_SRC
        "DxkdpLib.cpp")

file(GLOB_RECURSE LIN_ACT_LIB_SRC
        "LinActuatorLib.cpp")

file(GLOB_RECURSE F71_LIB_SRC
        "LakeshoreF71Lib.cpp")

file(GLOB_RECURSE MDLWR_LIB_SRC
        "HCoilMiddlewareLib.cpp")

# STEP 2: Include headers

file(GLOB_RECURSE PSU_LIB_HEADERS
        "${CMAKE_SOURCE_DIR}/include/libs/DxkdpLib/*.hpp")

file(GLOB_RECURSE LIN_ACT_LIB_HEADERS
        "${CMAKE_SOURCE_DIR}/include/libs/LinActuatorLib/LinActuatorLib.hpp")

file(GLOB_RECURSE F71_LIB_HEADERS
        "${CMAKE_SOURCE_DIR}/include/libs/LakeshoreF71Lib/LakeshoreF71Lib.hpp")

file(GLOB_RECURSE MDLWR_LIB_HEADERS
        "${CMAKE_SOURCE_DIR}/include/libs/HCoilMiddlewareLib/HCoilMiddlewareLib.hpp")

# STEP 3: Create Library
add_library(DxkdpLib ${PSU_LIB_SRC} ${PSU_LIB_HEADERS})
add_library(LinActuatorLib ${LIN_ACT_LIB_SRC} ${LIN_ACT_LIB_HEADERS})
add_library(LakeshoreF71Lib ${F71_LIB_SRC} ${F71_LIB_HEADERS})
add_library(HCoilMiddlewareLib ${MDLWR_LIB_SRC} ${MDLWR_LIB_HEADERS})

# STEP 4: Link the include directories

target_include_directories(DxkdpLib PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
                                                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>")                                                  

target_include_directories(LinActuatorLib PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
                                                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>")   

target_include_directories(LakeshoreF71Lib PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
                                                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>")   
target_include_directories(HCoilMiddlewareLib PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
                                                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>")   
# STEP 5: Link external libraries

target_link_libraries(DxkdpLib CppLinuxSerial)
target_link_libraries(LinActuatorLib CppLinuxSerial)
target_link_libraries(LakeshoreF71Lib CppLinuxSerial)
target_link_libraries(HCoilMiddlewareLib DxkdpLib LinActuatorLib LakeshoreF71Lib Threads::Threads Eigen3::Eigen)

#STEP 6: Install bin

# On Linux, "sudo make install" will typically copy the library
# into the folder /usr/local/bin
install(TARGETS DxkdpLib DESTINATION lib)
install(TARGETS LinActuatorLib DESTINATION lib)
install(TARGETS LakeshoreF71Lib DESTINATION lib)
install(TARGETS HCoilMiddlewareLib DESTINATION lib)

#Step 7: Install local

# On Linux, "sudo make install" will typically copy the
# folder into /usr/local/include
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/libs/PSU_LIB DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/DxkdpLib DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/LinActuatorLib DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/LakeshoreF71Lib DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/HCoilMiddlewareLib DESTINATION include)