cmake_minimum_required(VERSION 3.25.0)

message("Building blinkLed")
set(SOURCES blinkLed.c)
add_library(blinkLed blinkLed.c)
set_target_properties(blinkLed PROPERTIES FOLDER "appls/blinkLed")
target_include_directories(blinkLed PRIVATE 
                            ${CMAKE_SOURCE_DIR}/src/lib/utils
                            ${CMAKE_SOURCE_DIR}/src/lib/pins)
