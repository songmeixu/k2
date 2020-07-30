# get headers for cppyy to parse
set(DLPACK_HEADERS
    dlpack.h
    array.h
    tensor.h
    fsa_dlpack.h)

# prepend absolute path to fsa/*.h
foreach (HEADER_FILE ${DLPACK_HEADERS})
  get_filename_component(absolute_header_file ${HEADER_FILE} ABSOLUTE)
  list(APPEND ABS_DLPACK_HEADERS ${absolute_header_file})
endforeach ()
set(ABS_DLPACK_HEADERS ${ABS_DLPACK_HEADERS} PARENT_SCOPE)

# please sort the source files alphabetically
add_library(k2dlpack
            SHARED
            tensor.cc)

set_target_properties(k2dlpack
                      PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION 1
                      LINKER_LANGUAGE CXX
                      PUBLIC_HEADER fsa_dlpack.h)

target_include_directories(k2dlpack
                           PUBLIC
                           ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/cc
                           ${CMAKE_CURRENT_LIST_DIR}
                           ${PYBIND11_INCLUDE_DIR})

target_link_libraries(k2dlpack PUBLIC glog pybind11::module)
