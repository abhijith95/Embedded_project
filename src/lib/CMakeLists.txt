cmake_minimum_required(VERSION 3.25.0)

message("Building the lib")
add_subdirectory(timer)
add_subdirectory(pins)
add_subdirectory(eeprom)
add_subdirectory(utils)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/lib/dummy_lib.c "")
add_library(LIB STATIC ${CMAKE_CURRENT_BINARY_DIR}/lib/dummy_lib.c)
target_link_libraries(LIB PRIVATE PINS UTILS TIMER EEPROM)
if (${BUILD_TARGET} MATCHES "EMULATOR")
    target_link_libraries(LIB PRIVATE REGS)
endif()
