@echo off
SETLOCAL EnableDelayedExpansion
cls

SET CMAKE_ARGS=-S %~dp0

IF [%~2] == [] (
    goto :display_help
) ELSE IF "%~2" EQU "EMULATOR" (
    @REM Building for emulator, output will be a dll file
    SET BUILD_DIR=%~dp0/out/emulator
    SET CMAKE_ARGS=!CMAKE_ARGS! -B !BUILD_DIR!
    SET CMAKE_ARGS=!CMAKE_ARGS! -DBUILD_TARGET=EMULATOR -DAPPL_TO_BUILD

) ELSE IF "%~2" EQU "MCU" (
    @REM Building to flash the arduino, output will be .hex file
    @REM We need to have a different build generator when cross-compiling else the compiler settings
    @REM defaults to msvc. If this happens then we cannot build binary for arduino, this is why we use -G argument
    SET BUILD_DIR=%~dp0/out/flash
    SET CMAKE_ARGS=!CMAKE_ARGS! -B !BUILD_DIR!
    SET CMAKE_ARGS=!CMAKE_ARGS! -DBUILD_TARGET=MCU -G"MinGW Makefiles" -DAPPL_TO_BUILD
    
) ELSE (
    goto :display_help
)

@REM Get the application name to build
IF [%~1] == [] (
    goto :display_help
) ELSE (
    SET CMAKE_ARGS=!CMAKE_ARGS!=%~1
)

@REM Cleaning the out folder
IF EXIST "!BUILD_DIR!"  (
    echo Deleting the out folder for a clean build
    rmdir "!BUILD_DIR!" /q /s
)

:build_target
    echo Generating the build files !CMAKE_ARGS!
    cmake !CMAKE_ARGS!
    echo Building the target
    cmake --build !BUILD_DIR!
    goto :eof

:display_help
    echo Help for building MCU code
    echo The batch script takes two positional arguments. 
    echo The first argument will be the application that is being built. Give the folder name of the application
    echo The second argument shall be to specify the build target, EMULATOR or MCU. Use the exact same name as defined in the help
    goto :eof
    