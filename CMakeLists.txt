cmake_minimum_required(VERSION 3.25.0)
if (${BUILD_TARGET} MATCHES "MCU")
    # no need to cross compile for emulator target
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
    include(arduino)
endif()

project(embedded_proj LANGUAGES C CXX)
set(OUTPUT_TARGET "target")
set(FINAL_TRGT_DIR ${CMAKE_CURRENT_BINARY_DIR}/target)

# we need a dummy c file to link it to the library created from application
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/dummy.c "")
endif()

# create directory to put in the final target file
file(MAKE_DIRECTORY ${FINAL_TRGT_DIR})

function(build_libs)
    # trigger the memory map
    add_subdirectory(${CMAKE_SOURCE_DIR}/tools/emulator/memory)
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/registers)

    # trigger the compilation of the application and library
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/lib)
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/appl)
endfunction()

if (${BUILD_TARGET} MATCHES "EMULATOR")
    add_compile_definitions(EMU_TARGET) 
    add_library(${OUTPUT_TARGET} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/tools/emulator/board/board.c)
    build_libs()
    target_include_directories(${OUTPUT_TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
    target_include_directories(${OUTPUT_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tools/emulator/board)
    target_link_libraries(${OUTPUT_TARGET} PUBLIC APPL)
    target_link_libraries(${OUTPUT_TARGET} PUBLIC REGS)
    set(FINAL_TARGET_FILE ${CMAKE_CURRENT_BINARY_DIR}/Debug/${OUTPUT_TARGET}.dll)
    
    elseif(${BUILD_TARGET} MATCHES "MCU")
    add_compile_definitions(MCU_TARGET)
    # put the code to create .ihex file for flashing mcu
    set(FINAL_EXE_FILE ${CMAKE_CURRENT_BINARY_DIR}/final_exec.elf)
    set(FINAL_TARGET_FILE ${CMAKE_CURRENT_BINARY_DIR}/final_exec.hex)
    add_executable(${OUTPUT_TARGET} ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)
    build_libs()
    # Check https://stackoverflow.com/questions/21735624/c-application-linking-failing-with-undefined-reference-to-mulhi3
    # for the reason to add a new library path
    set_target_properties(${OUTPUT_TARGET} PROPERTIES
                            OUTPUT_NAME ${FINAL_EXE_FILE}
                            COMPILE_FLAGS "-mmcu=atmega328p -g"
                            LINK_FLAGS "-mmcu=atmega328p -L${LINKER_LIB_LOC}")       
    target_link_libraries(${OUTPUT_TARGET} PRIVATE APPL)

    # convert the final executable into binary for flashing
    add_custom_command(
        TARGET ${OUTPUT_TARGET}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex -j .text -j .data ${FINAL_EXE_FILE} ${FINAL_TARGET_FILE}
        COMMENT "Converting .elf file to .hex"
    )
    
    # finally copy the target file and put it into the target directory
    add_custom_command(
        TARGET ${OUTPUT_TARGET}
        POST_BUILD
        COMMAND mv ${FINAL_TARGET_FILE} ${FINAL_TRGT_DIR}
        COMMENT "We move the target file to a new directory for easy accessibility"
    )

else()
    # throw an error since the target specified is not valid anymore
    message(FATAL_ERROR "Cannot find the specified build target. Aborting the build.")
endif()

