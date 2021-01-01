#
#  Copyright 2019 - 2021 The XOrange Studio. All rights reserved.
#  Use of this source code is governed by a BSD-style license that can be
#  found in the LICENSE.md file.
#

#  Test case.
add_executable(
    io-unittest
    io.unittest.cc
    ${CMAKE_BINARY_DIR}/src/io.cc
    ${CMAKE_BINARY_DIR}/src/error.cc
)
target_include_directories(
    io-unittest
    PRIVATE 
    ${CMAKE_BINARY_DIR}/include
)

add_test(
    NAME                xaptest-io
    COMMAND             ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/io-unittest
    WORKING_DIRECTORY   ${CMAKE_BINARY_DIR}
)

set_tests_properties(xaptest-io PROPERTIES TIMEOUT 1)