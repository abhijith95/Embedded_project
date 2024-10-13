cmake_minimum_required(VERSION 3.25.0)

message("Building application")
add_library(APPL STATIC main.c)
target_include_directories(APPL PRIVATE ${CMAKE_SOURCE_DIR}/src/lib/timer)

# build the application based on the user input
string(TOLOWER ${APPL_TO_BUILD} DIR_NAME)
string(CONCAT APPL_MACRO "APPL_" ${APPL_TO_BUILD} "=1")

add_subdirectory(${DIR_NAME})
target_include_directories(APPL PRIVATE ${CMAKE_SOURCE_DIR}/src/appl/${DIR_NAME})
# enable main.c to call the correct application setup and appl main functions
target_link_libraries(APPL PUBLIC ${DIR_NAME})
target_compile_definitions(APPL PRIVATE ${APPL_MACRO})
target_link_libraries(APPL PRIVATE LIB)
set_target_properties(APPL PROPERTIES USE_FOLDERS OFF)
