find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_MVDR_TEST gnuradio-mvdr_test)

FIND_PATH(
    GR_MVDR_TEST_INCLUDE_DIRS
    NAMES gnuradio/mvdr_test/api.h
    HINTS $ENV{MVDR_TEST_DIR}/include
        ${PC_MVDR_TEST_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_MVDR_TEST_LIBRARIES
    NAMES gnuradio-mvdr_test
    HINTS $ENV{MVDR_TEST_DIR}/lib
        ${PC_MVDR_TEST_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-mvdr_testTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_MVDR_TEST DEFAULT_MSG GR_MVDR_TEST_LIBRARIES GR_MVDR_TEST_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_MVDR_TEST_LIBRARIES GR_MVDR_TEST_INCLUDE_DIRS)
