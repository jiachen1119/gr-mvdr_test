########################################################################

include(GrPlatform) #define LIB_SUFFIX

list(APPEND mvdr_test_sources
    mvdr_impl.cc
)

set(mvdr_test_sources "${mvdr_test_sources}" matlab/matlab.cpp matlab/matStruct.h)
if(NOT mvdr_test_sources)
    MESSAGE(STATUS "No C++ sources... skipping lib/")
    return()
endif(NOT mvdr_test_sources)

add_subdirectory(matlab)
add_library(gnuradio-mvdr_test SHARED ${mvdr_test_sources})

target_link_libraries(gnuradio-mvdr_test
        PUBLIC
        gnuradio::gnuradio-runtime
        $<BUILD_INTERFACE:matlab_lib>
        )
target_include_directories(gnuradio-mvdr_test
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    PUBLIC $<INSTALL_INTERFACE:include>
  )
set_target_properties(gnuradio-mvdr_test PROPERTIES DEFINE_SYMBOL "gnuradio_mvdr_test_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-mvdr_test PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-mvdr_test)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

# If your unit tests require special include paths, add them here
#include_directories()
# List all files that contain Boost.UTF unit tests here
list(APPEND test_mvdr_test_sources
qa_mvdr.cc
)
# Anything we need to link to for the unit tests go here
list(APPEND GR_TEST_TARGET_DEPS gnuradio-mvdr_test)

if(NOT test_mvdr_test_sources)
    MESSAGE(STATUS "No C++ unit tests... skipping")
    return()
endif(NOT test_mvdr_test_sources)

foreach(qa_file ${test_mvdr_test_sources})
    GR_ADD_CPP_TEST("mvdr_test_${qa_file}"
        ${CMAKE_CURRENT_SOURCE_DIR}/${qa_file}
    )
endforeach(qa_file)
