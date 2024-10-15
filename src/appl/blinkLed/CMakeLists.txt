cmake_minimum_required(VERSION 3.25.0)

message("Building blinkled")
set(SOURCES blinkled.c)
set(HEADERS blinkled.h)
add_library(blinkled blinkled.c)
set_target_properties(blinkled PROPERTIES FOLDER "appls/blinkled")
target_include_directories(blinkled PRIVATE 
                            ${CMAKE_SOURCE_DIR}/src/lib/timer
                            ${CMAKE_SOURCE_DIR}/src/lib/eeprom
                            ${CMAKE_SOURCE_DIR}/src/lib/pins)
