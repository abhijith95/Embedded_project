cmake_minimum_required(VERSION 3.25.0)

message("Building PINS")
set(SOURCES pin.c)
set(HEADERS pin.h)
add_library(PINS STATIC pin.c)
set_target_properties(PINS PROPERTIES FOLDER "lib/pins")
