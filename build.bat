@echo off
SETLOCAL EnableDelayedExpansion
cls
IF EXIST ".\out\"  (
    echo Deleting the out folder for a clean build
    rmdir .\out /q /s
)

SET CMAKE_ARGS=-S %~dp0 -B %~dp0\out\build -DAPPL_TO_BUILD

@REM Get the application name to build
IF [%~1] == [] (
    goto display_help
) ELSE (
    SET CMAKE_ARGS=!CMAKE_ARGS!=%~1
)

IF [%~2] == [] (
    goto :display_help
) ELSE IF "%~2" EQU "EMULATOR" (
    @REM Building for emulator, output will be a dll file
    SET CMAKE_ARGS=!CMAKE_ARGS! -DBUILD_TARGET=EMULATOR
    goto :build_target

) ELSE IF "%~2" EQU "MCU" (
    @REM Building to flash the arduino, output will be .hex file
    @REM We need to have a different build generator when cross-compiling else the compiler settings
    @REM defaults to msvc. If this happens then we cannot build binary for arduino, this is why we use -G argument
    SET CMAKE_ARGS=!CMAKE_ARGS! -DBUILD_TARGET=MCU -G"MinGW Makefiles"
    goto :build_target
    
) ELSE (
    goto :display_help
)

:build_target
    echo Generating the build files
    cmake !CMAKE_ARGS!
    echo Building the target
    cmake --build %~dp0\out\build
    goto :eof

:display_help
    echo Help for building MCU code
    echo The batch script takes two positional arguments. 
    echo The first argument will be the application that is being built. Give the folder name of the application
    echo The second argument shall be to specify the build target, EMULATOR or MCU. Use the exact same name as defined in the help
    goto :eof