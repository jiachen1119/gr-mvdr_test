# CMake generated Testfile for 
# Source directory: /home/tang/CLionProjects/OOT_test/gr-mvdr_test/python/mvdr_test
# Build directory: /home/tang/CLionProjects/OOT_test/gr-mvdr_test/build/python/mvdr_test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(qa_mvdr "/usr/bin/sh" "qa_mvdr_test.sh")
set_tests_properties(qa_mvdr PROPERTIES  _BACKTRACE_TRIPLES "/usr/lib/x86_64-linux-gnu/cmake/gnuradio/GrTest.cmake;116;add_test;/home/tang/CLionProjects/OOT_test/gr-mvdr_test/python/mvdr_test/CMakeLists.txt;42;GR_ADD_TEST;/home/tang/CLionProjects/OOT_test/gr-mvdr_test/python/mvdr_test/CMakeLists.txt;0;")
subdirs("bindings")
