# get headers for cppyy to parse
set(FSA_HEADERS
    arcsort.h
    array.h
    aux_labels.h
    connect.h
#    dense_fsa.h
    determinize.h
    determinize_impl.h
    fsa.h
    fsa_equivalent.h
    fsa_renderer.h
    fsa_util.h
    intersect.h
    properties.h
    rmepsilon.h
    topsort.h
    util.h
    weights.h)

# prepend absolute path to fsa/*.h
foreach (HEADER_FILE ${FSA_HEADERS})
  get_filename_component(absolute_header_file ${HEADER_FILE} ABSOLUTE)
  list(APPEND ABS_LIB_HEADERS ${absolute_header_file})
endforeach ()
set(ABS_FSA_HEADERS ${ABS_FSA_HEADERS} PARENT_SCOPE)

# please sort the source files alphabetically
add_library(k2fsa
            SHARED
            arcsort.cc
            aux_labels.cc
            connect.cc
            determinize.cc
            fsa.cc
            fsa_equivalent.cc
            fsa_renderer.cc
            fsa_util.cc
            intersect.cc
            properties.cc
            rmepsilon.cc
            topsort.cc
            util.cc
            weights.cc)

set_target_properties(k2fsa
                      PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION 1
                      LINKER_LANGUAGE CXX
                      PUBLIC_HEADER fsa.h)

target_include_directories(k2fsa
                           PUBLIC
                           ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}/cc
                           ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(k2fsa PUBLIC glog)

function(k2_add_fsa_test name)
  add_executable(${name} "${name}.cc")
  target_link_libraries(${name}
                        PRIVATE
                        k2fsa
                        gtest
                        gtest_main
                        )
  add_test(NAME "Test.${name}"
           COMMAND
           $<TARGET_FILE:${name}>
           )
endfunction()

# please sort the source files alphabetically
set(fsa_tests
    arcsort_test
    array_test
    aux_labels_test
    connect_test
    determinize_test
    fsa_equivalent_test
    fsa_renderer_test
    fsa_test
    fsa_util_test
    intersect_test
    properties_test
    rmepsilon_test
    topsort_test
    weights_test
    )

foreach (name IN LISTS fsa_tests)
  k2_add_fsa_test(${name})
endforeach ()
