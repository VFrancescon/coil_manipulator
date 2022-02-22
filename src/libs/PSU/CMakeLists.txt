file(GLOB_RECURSE PSU_LIB_SRC
        "*.cpp")

file(GLOB_RECURSE PSU_LIB_HEADERS
        "${CMAKE_SOURCE_DIR}/include/*.h"
        "${CMAKE_SOURCE_DIR}/include/libs/PSU/*.h")

add_library(PSU_LIB ${PSU_LIB_SRC} ${PSU_LIB_HEADERS})

target_include_directories(PSU_LIB PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>"
                                                "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>")                                                  

target_link_libraries(PSU_LIB CppLinuxSerial)

# On Linux, "sudo make install" will typically copy the library
# into the folder /usr/local/bin
install(TARGETS PSU_LIB DESTINATION lib)

# On Linux, "sudo make install" will typically copy the
# folder into /usr/local/include
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/libs/PSU_LIB DESTINATION include)
install(DIRECTORY "/home/vittorio/coil_manipulator/include/libs/PSU" DESTINATION include)
