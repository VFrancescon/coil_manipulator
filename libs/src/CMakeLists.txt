# STEP 1: Include cpp files

file(GLOB_RECURSE PSU_LIB_SRC
        "DxkdpLib.cpp")

file(GLOB_RECURSE LIN_ACT_LIB_SRC
        "LinActuatorLib.cpp")

# STEP 2: Include headers

file(GLOB_RECURSE PSU_LIB_HEADERS
        "${CMAKE_SOURCE_DIR}/include/libs/DxkdpLib/DxkdpLib.hpp")

file(GLOB_RECURSE LIN_ACT_LIB_HEADERS
        "${CMAKE_SOURCE_DIR}/include/libs/LinActuatorLib/LinActuatorLib.hpp")


# STEP 3: Create Library
add_library(DxkdpLib ${PSU_LIB_SRC} ${PSU_LIB_HEADERS})
add_library(LinActuatorLib ${LIN_ACT_LIB_SRC} ${LIN_ACT_LIB_HEADERS})

# STEP 4: Link the include directories

target_include_directories(DxkdpLib PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
                                                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>")                                                  

target_include_directories(LinActuatorLib PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
                                                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>")   

# STEP 5: Link external libraries

target_link_libraries(DxkdpLib CppLinuxSerial)
target_link_libraries(LinActuatorLib CppLinuxSerial)

#STEP 6: Install bin

# On Linux, "sudo make install" will typically copy the library
# into the folder /usr/local/bin
install(TARGETS DxkdpLib DESTINATION lib)
install(TARGETS LinActuatorLib DESTINATION lib)

#Step 7: Install local

# On Linux, "sudo make install" will typically copy the
# folder into /usr/local/include
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/libs/PSU_LIB DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/DxkdpLib DESTINATION include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/LinActuatorLib DESTINATION include)