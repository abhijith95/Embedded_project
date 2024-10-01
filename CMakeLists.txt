cmake_minimum_required(VERSION 3.25.0)
project(embedded_proj LANGUAGES C)

message("Building the target")
# we need a dummy c file to link it to the library created from application
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/dummy.c "")
endif()

# trigger the compilation of the application
add_subdirectory(${CMAKE_SOURCE_DIR}/src/lib)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/appl)


add_executable(final_exec ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)
target_link_libraries(final_exec PRIVATE APPL LIB)
