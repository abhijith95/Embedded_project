cmake_minimum_required(VERSION 3.25.0)

message("Building application")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/dummy.c "")
add_library(APPL STATIC ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)

# conditionally add application to the library
if (${APPL_TO_BUILD} MATCHES "blinkLed")
add_subdirectory(blinkLed)
target_link_libraries(APPL PRIVATE blinkLed)
endif()
target_link_libraries(APPL PRIVATE LIB)
set_target_properties(APPL PROPERTIES USE_FOLDERS OFF)
