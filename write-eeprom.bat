@echo off
SETLOCAL EnableDelayedExpansion
cls
@REM https://www.scadacore.com/tools/programming-calculators/online-checksum-calculator/
"C:\Program Files (x86)\WinAVR\bin\avrdude.exe" -C "C:\Program Files (x86)\WinAVR\bin\avrdude.conf" -v -p ATmega328P -P COM3 -c arduino -b 115200 -D -U eeprom:w:eeprom.hex:i