# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT mvdr_test_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT mvdr_test_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND mvdr_test_python_files
    mvdr_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(mvdr_test
   ../../..
   gr::mvdr_test
   "${mvdr_test_python_files}")

# copy in bindings .so file for use in QA test module
add_custom_target(
  copy_bindings_for_tests ALL
  COMMAND
    ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/*.so"
    ${CMAKE_BINARY_DIR}/test_modules/gnuradio/mvdr_test/
  DEPENDS mvdr_test_python)

install(TARGETS mvdr_test_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/mvdr_test COMPONENT pythonapi)
