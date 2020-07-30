
add_subdirectory(fsa)
add_subdirectory(dlpack)


set(ABS_HEADERS_TO_BINDER ${ABS_FSA_HEADERS} ${ABS_DLPACK_HEADERS} PARENT_SCOPE)
get_filename_component(public_header_file interface.h ABSOLUTE)
set(public_header_file ${public_header_file} PARENT_SCOPE)

add_library(k2 INTERFACE)

set_target_properties(k2
                      PROPERTIES
                      PUBLIC_HEADER ${public_header_file})

target_include_directories(k2
                           INTERFACE
                           ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/cc
                           ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(k2 INTERFACE k2fsa k2dlpack)
