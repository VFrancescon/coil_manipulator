find_package(Doxygen REQUIRED)

get_target_property(DXKDP_H_DIR DxkdpLib INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE DXKDP_H ${DXKDP_H_DIR}/*.hpp)

get_target_property(HCOILMID_H_DIR HCoilMiddlewareLib INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE HCOILMID_H ${HCOILMID_H_DIR}/*.hpp)

get_target_property(LSF71_H_DIR LakeshoreF71Lib INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE LSF71_H ${LSF71_H_DIR}/*.hpp)

get_target_property(LINACT_H_DIR LinActuatorLib INTERFACE_INCLUDE_DIRECTORIES)
file(GLOB_RECURSE LINACT_H ${LINACT_H_DIR}/*.hpp)

#This will be the main output of our command
set(DOXYGEN_INDEX_FILE ${CMAKE_CURRENT_SOURCE_DIR}/html/index.html)

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/libs)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us

add_custom_command( OUTPUT ${DOXYGEN_INDEX_FILE}
                    DEPENDS ${DXKDP_H} ${LINACT_H} ${LSF71_H} ${HCOILMID_H}
                    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                    MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                    WORKING_DIRECTORY ${CMAKE_INCLUDE_CURRENT_DIR}
                    MAIN_DEPENDENCY Doxyfile
                    COMMENT "Generating Docs"
                    VERBATIM)   

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})