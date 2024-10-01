@echo off
SETLOCAL EnableDelayedExpansion

rmdir out\build /q /s
cmake -S %~dp0 -B %~dp0\out\build -D APPL_TO_BUILD=blinkLed
cmake --build %~dp0\out\build