cmake_minimum_required(VERSION 3.25.0)

message("Building timer")
set(SOURCES timer.c)
set(HEADERS timer.h)
add_library(TIMER STATIC timer.c)
set_target_properties(TIMER PROPERTIES FOLDER "lib/timer")