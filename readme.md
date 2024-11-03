# Introduction
Welcome to my repository of learning to bare metal code for microcontrollers. If you are like me, doing day job of coding on the application layer, blissfully unaware of the low level layers, how your piece of code interacts with the microcontroller, and want to learn more in depth then this place is for you. Here I try to setup my own layers in the pursuit of trying to understand it all. The required documentation of the board and the software tools can be found under [docs](./docs/). Read on to understand more on how the repository is setup and its capabilities
# Software prerequisites
Let us get clear of the important stuff, software tools that goes into working this repository:
    - [AVR-GCC compiler](https://winavr.sourceforge.net/): Cross-compiler that is used to compile code for arduino microcontroller
    - [Make for windows](https://gnuwin32.sourceforge.net/packages/make.htm): Since AVR-GCC is a GNU based compiler we need *make* build system in windows to build the final hex file
    - [AVRDude for windows](https://github.com/avrdudes/avrdude): Once the final hex file is built for arduino, we need to send the program to the board, which requires a special tool like avrdude.
# Hardware prerequsites
The microcontroller board used in this project is [Arduino Uno R3](https://docs.arduino.cc/hardware/uno-rev3/), which uses the [Atmega328p microcontroller](https://www.microchip.com/en-us/product/atmega328p). All the codes and compilation is done from a windows host machine, if you are using any other OS please get the corresponding software tools. Please keep in mind that the Cmake files need to be updated accordingly.
# Working principle
The repo contains the necessary code harness to build code to run on the board as well as code to run unit tests. It can be very helpful to understand each modules and how they work together.
## Application development guidelines
The base assumption with writing code to the arduino board is that only one application code is compiled and flashed to the board at a time. This is to ensure that we don't fill up on the flash memory with application code that is not set to active. The downside to this is that for unit tests to be run the code has to compiled with each application turned ON and the corresponding tests run. At the moment there is no automation code that will build and run unit tests for all the application, but it however is not very difficult to setup.
## Using delays
Since there is an emulator setup to perform unit testing, it is important to develop/write application code for the board in a certain way, especially delays. Traditionally the arduino IDE encourages the use of Delay function which suspends the code at a certain line until the time has elapsed. This works very well in the board, but with emulator this is hard because while the application is waiting on the line, the emulator cannot "tick time", unless multi-threading is implemented, which in this case is not. In order to just satisfy the emulator setup, we shall instead have an "idle" state in the application where it waits for the time delay to perform a certain action. All the while running the entire codebase. This will be easily understood by looking at the example applications.
## Emulator working principle
Since everything in microcontroller is done through registers, that is exactly what the emulator will try to emulate. The [lower layers](./src/lib/) of the application code directly write and read from the register memory address, which is defined by [registers.h](./src/include/registers.h). This file is created by the [CMakeList file](./tools/emulator/memory/CMakeLists.txt). Depending on the compile purpose, Cmake can either put in the actual register address as defined in the [datasheet](./docs/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf) or it assigns to globaly memory that is defined by [registers.c](./src/registers/registers.c) file. The [emulator](./tools/emulator/board/board.c) uses the external variables to interact with the application code. 
# Project setup
Before running the tests for the project, [CUnit library](./tools/cunit-master/) has to be compiled. The generated compiled file shall be put in a specific directory since the [test Cmake file](./test/blinkled/CMakeLists.txt) depends on it. Run the following command on the command prompt:
``` 
cd tools\cunit-master;
cmake -S . -B ..\..\out\cunit
cmake --build ..\..\out\cunit
``` 
# VS code setup
Here are some code snippets to use for building various targets and debugging the test code.
## Building emulator target
``` 
{
    "label": "BlinkLed build emulator target",
    "type": "shell",
    "command": "${workspaceFolder}/build.bat BLINKLED EMULATOR",
    "problemMatcher": []
}
```
## Building flash target
``` 
{
    "label": "BlinkLed build emulator target",
    "type": "shell",
    "command": "${workspaceFolder}/build.bat BLINKLED MCU",
    "problemMatcher": []
}
```
## Flashing arduino
```
{
    "label": "Flash arduino",
    "type": "shell",
    "command": "${workspaceFolder}/flash-arduino.bat",
    "problemMatcher": []
}
```
## Debugging the test code
```
"configurations": [
    {
        "name": "(gdb) Launch",
        "type": "cppvsdbg",
        "request": "launch",
        "program": "${workspaceFolder}\\blinkled\\out\\Debug\\blinkled_test.exe",  // Path to the executable
        "args": [],  // Optional: arguments to pass to your program
        "stopAtEntry": false,
        "cwd": "${workspaceFolder}", //\\blinkled\\out\\Debug",
        "environment": [],
        "externalConsole": true
    }
]
```
