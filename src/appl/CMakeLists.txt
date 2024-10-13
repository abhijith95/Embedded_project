cmake_minimum_required(VERSION 3.25.0)

message("Building application")
add_library(APPL STATIC main.c)
target_include_directories(APPL PRIVATE ${CMAKE_SOURCE_DIR}/src/lib/timer)

# conditionally add application to the library
if (${APPL_TO_BUILD} MATCHES "BLINKLED")
    set(DIR_NAME blinkLed)
    set(APPL_MACRO APPL_BLINKLED=1)
elseif (${APPL_TO_BUILD} MATCHES "ULTRASONIC")
    set(DIR_NAME ultrasonic)
    set(APPL_MACRO APPL_ULTRASONIC=1)
endif()

add_subdirectory(${DIR_NAME})
target_include_directories(APPL PRIVATE ${CMAKE_SOURCE_DIR}/src/appl/${DIR_NAME})
# enable main.c to call the correct application setup and appl main functions
target_link_libraries(APPL PUBLIC ${DIR_NAME})
target_compile_definitions(APPL PRIVATE ${APPL_MACRO})
target_link_libraries(APPL PRIVATE LIB)
set_target_properties(APPL PROPERTIES USE_FOLDERS OFF)
