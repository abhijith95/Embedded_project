cmake_minimum_required(VERSION 3.25.0)
project(blinkled_test LANGUAGES C CXX)

set(BOARD_DLL "${CMAKE_SOURCE_DIR}/../../out/emulator/Debug/target.dll")
set(FINAL_BOARD_DLL "${CMAKE_BINARY_DIR}/Debug/target.dll")

find_library(BOARD NAMES target 
            PATHS "${CMAKE_SOURCE_DIR}/../../out/emulator/Debug" NO_DEFAULT_PATH)
find_library(CUNIT NAMES cunit 
            PATHS "${CMAKE_SOURCE_DIR}/../../out/cunit/CUnit/Debug" NO_DEFAULT_PATH)

add_executable(blinkled_test test_blinkled.c)
target_include_directories(blinkled_test PRIVATE "${CMAKE_SOURCE_DIR}/../../src/include")
target_include_directories(blinkled_test PRIVATE "${CMAKE_SOURCE_DIR}/../../tools/emulator/board")
target_include_directories(blinkled_test PRIVATE "${CMAKE_SOURCE_DIR}/../../tools/cunit-master/CUnit/CUnit")
target_include_directories(blinkled_test PRIVATE "${CMAKE_SOURCE_DIR}/../../tools/cunit-master/CUnit")
target_include_directories(blinkled_test PRIVATE "${CMAKE_SOURCE_DIR}/../../tools/cunit-master")
target_link_libraries(blinkled_test PRIVATE ${BOARD})
target_link_libraries(blinkled_test PRIVATE ${CUNIT})

add_custom_command(
        TARGET blinkled_test
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${BOARD_DLL} ${FINAL_BOARD_DLL}
        COMMENT "Moving the target dll to the same place as the test executable"
)
