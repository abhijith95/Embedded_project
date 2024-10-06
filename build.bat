@echo off
SETLOCAL EnableDelayedExpansion

cls
rmdir .\out /q /s
@REM We need to have a different build generator when cross-compiling else the compiler settings
@REM defaults to msvc. If this happens then we cannot build binary for
cmake -S %~dp0 -B %~dp0\out\build -G"MinGW Makefiles" -DAPPL_TO_BUILD=blinkLed -DBUILD_TARGET=MCU
make --directory=%~dp0\out\build
@REM cmake --build %~dp0\out\build --target clean