cmake_minimum_required(VERSION 3.25.0)

message("Building timer")
set(SOURCES timer.c)
set(HEADERS timer.h)
add_library(TIMER STATIC timer.c)
target_include_directories(TIMER PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
set_target_properties(TIMER PROPERTIES FOLDER "lib/timer")