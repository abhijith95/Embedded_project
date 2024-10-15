@echo off
SETLOCAL EnableDelayedExpansion
@REM Changing directory to easily reference the hex file
cd .\out\flash\target
@REM Flashing the arduino
"C:\Program Files (x86)\WinAVR\bin\avrdude.exe" -C "C:\Program Files (x86)\WinAVR\bin\avrdude.conf" -v -p ATmega328P -P COM3 -c arduino -b 115200 -D -U flash:w:final_exec.hex:i