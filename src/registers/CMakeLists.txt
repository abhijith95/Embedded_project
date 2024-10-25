cmake_minimum_required(VERSION 3.25.0)

if (${BUILD_TARGET} MATCHES "EMULATOR")
    add_library(REGS STATIC registers.c)
    target_include_directories(REGS PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
endif()
