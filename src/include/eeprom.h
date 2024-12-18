#ifndef __EEPROM__
#define __EEPROM__

#include <stdint.h>
#include "registers.h"
#include "dllExport.h"

#define EEMPE   (uint8_t)2
#define EEPE    (uint8_t)1 
#define EERE    (uint8_t)0 

DLLEXPORT void ReadFromMemory(uint16_t memory_address, uint8_t* data_read);
DLLEXPORT void WriteToMemory(uint16_t memory_address, uint8_t data_toWrite);
static uint8_t GetEepeValue();

#endif