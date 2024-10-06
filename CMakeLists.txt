cmake_minimum_required(VERSION 3.25.0)
if (${BUILD_TARGET} MATCHES "MCU")
    # no need to cross compile for emulator target
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
    include(arduino)
endif()

project(embedded_proj LANGUAGES C)
set(OUTPUT_TARGET "target")

# we need a dummy c file to link it to the library created from application
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/dummy.c "")
endif()

# trigger the compilation of the application
add_subdirectory(${CMAKE_SOURCE_DIR}/src/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/appl)

if (${BUILD_TARGET} MATCHES "EMULATOR")
    add_library(${OUTPUT_TARGET} SHARED ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)
    target_link_libraries(${OUTPUT_TARGET} PRIVATE APPL)
elseif(${BUILD_TARGET} MATCHES "MCU")
    # put the code to create .ihex file for flashing mcu
    set(FINAL_EXE_FILE ${CMAKE_CURRENT_BINARY_DIR}/final_exec.elf)
    set(FINAL_HEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/final_exec.hex)
    add_executable(${OUTPUT_TARGET} ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)
    set_target_properties(${OUTPUT_TARGET} PROPERTIES
                            OUTPUT_NAME ${FINAL_EXE_FILE}
                            COMPILE_FLAGS "-mmcu=atmega328p -g"
                            LINK_FLAGS "-mmcu=atmega328p")       
    target_link_libraries(${OUTPUT_TARGET} PRIVATE APPL)

    # convert the final executable into binary for flashing
    add_custom_command(
        TARGET ${OUTPUT_TARGET}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex -j .text -j .data ${FINAL_EXE_FILE} ${FINAL_HEX_FILE}
        COMMENT "Converting .elf file to .hex"
    )

else()
    # throw an error since the target specified is not valid anymore
    message(FATAL_ERROR "Cannot find the specified build target. Aborting the build.")
endif()