cmake_minimum_required(VERSION 3.25.0)

message("Building EEPROM")
set(SOURCES eeprom.c)
set(HEADERS eeprom.h)
add_library(EEPROM STATIC eeprom.c)
target_include_directories(EEPROM PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
set_target_properties(EEPROM PROPERTIES FOLDER "lib/eeprom")