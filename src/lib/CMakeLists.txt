cmake_minimum_required(VERSION 3.25.0)

message("Building the lib")
add_subdirectory(utils)
add_subdirectory(pins)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/lib/dummy_lib.c "")
add_library(LIB STATIC ${CMAKE_CURRENT_BINARY_DIR}/lib/dummy_lib.c)
target_link_libraries(LIB PINS UTILS)
