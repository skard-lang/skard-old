cmake_minimum_required(VERSION 3.19)
project(cSkard C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCSKARD_DEBUG")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMOCKA_ROOT_DIR "${CMAKE_SOURCE_DIR}/lib/cmocka-1.0.0")

# skard-lib LIBRARY
add_library(skard-lib STATIC skard-lib/src/skard.h skard-lib/src/chunk.h skard-lib/src/chunk.c skard-lib/src/memory.c skard-lib/src/memory.h skard-lib/src/error.h skard-lib/src/error.c)

# cSkard EXECUTABLE
add_executable(cSkard skard-runtime/src/main.c)
target_include_directories(cSkard PRIVATE skard-lib/src)
target_link_libraries(cSkard skard-lib)

# skard-unittest EXECUTABLE
include(cmake/FetchCMocka.cmake)

enable_testing()

file(GLOB TESTS "tests/test_*.c")
foreach(TEST_FILE ${TESTS})
    string(REGEX MATCH "\\t\\e\\s\\t\\_[A-Za-z0-9_]+" TEST_NAME ${TEST_FILE})
    add_executable(${TEST_NAME} ${TEST_FILE} tests/unit_common.h)
    target_compile_features(${TEST_NAME} PRIVATE c_std_99)
    target_include_directories(${TEST_NAME} PRIVATE skard-lib/src)
    target_link_libraries(${TEST_NAME} skard-lib)
    target_link_libraries(${TEST_NAME} cmocka-static)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
