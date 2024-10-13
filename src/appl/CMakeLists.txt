cmake_minimum_required(VERSION 3.25.0)

message("Building application")
add_library(APPL STATIC main.c)
target_include_directories(APPL PRIVATE ${CMAKE_SOURCE_DIR}/src/lib/timer)

# conditionally add application to the library
if (${APPL_TO_BUILD} MATCHES "BLINKLED")
    add_subdirectory(blinkLed)
    target_include_directories(APPL PRIVATE ${CMAKE_SOURCE_DIR}/src/appl/blinkLed)
    # enable main.c to call the correct application setup and appl main functions
    target_link_libraries(APPL PUBLIC blinkLed)
    target_compile_definitions(APPL PRIVATE APPL_BLINKLED=1)
endif()
target_link_libraries(APPL PRIVATE LIB)
set_target_properties(APPL PROPERTIES USE_FOLDERS OFF)
