cmake_minimum_required(VERSION 3.25.0)

message("Building EEPROM")
set(SOURCES eeprom.c)
set(HEADERS eeprom.h)
add_library(EEPROM STATIC eeprom.c)
set_target_properties(EEPROM PROPERTIES FOLDER "lib/eeprom")