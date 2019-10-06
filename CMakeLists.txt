cmake_minimum_required(VERSION 3.1.0)
project(echo)

enable_language(C)
enable_language(CXX)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(APP_NAME echo_client)
set(APP_LIB_NAME echo_lib)

add_subdirectory(src)
add_subdirectory(tests)
