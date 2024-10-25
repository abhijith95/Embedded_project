cmake_minimum_required(VERSION 3.25.0)

message("Building application")
if (${BUILD_TARGET} MATCHES "EMULATOR")
    add_library(APPL STATIC appl.c)
    target_link_libraries(APPL PRIVATE REGS)
elseif(${BUILD_TARGET} MATCHES "MCU")
    add_library(APPL STATIC main.c appl.c)
else()
    # throw an error since the target specified is not valid anymore
    message(FATAL_ERROR "Cannot find the specified build target. Aborting the build.")
endif()

target_include_directories(APPL PRIVATE ${CMAKE_SOURCE_DIR}/src/include)

# build the application based on the user input
string(TOLOWER ${APPL_TO_BUILD} DIR_NAME)
string(CONCAT APPL_MACRO "APPL_" ${APPL_TO_BUILD} "=1")

target_compile_definitions(APPL PRIVATE ${APPL_MACRO})
add_subdirectory(${DIR_NAME})
# enable main.c to call the correct application setup and appl main functions
target_link_libraries(APPL PUBLIC ${DIR_NAME})
target_link_libraries(APPL PRIVATE LIB)
set_target_properties(APPL PROPERTIES USE_FOLDERS OFF)
