# cross-compile toolchain for cmake to build for arduino target

# toolchain binaries
set(CMAKE_C_COMPILER   "avr-gcc")
set(CMAKE_CXX_COMPILER "avr-g++")
set(CMAKE_AR "avr-ar")
set(CMAKE_ASM_COMPILER "avr-as")
set(CMAKE_RANLIB "avr-ranlib")
set(CMAKE_LINKER "avr-ld")
set(CMAKE_NM "avr-nm")
set(CMAKE_OBJCOPY "avr-objcopy")
set(CMAKE_SIZE "avr-size")
set(CMAKE_STRIP "avr-strip")
set(CMAKE_FIND_ROOT_PATH "C:\\Program Files (x86)\\WinAVR\\bin")

# target information
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR atmega328p)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM     NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY     ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE     ONLY)
