#ifndef __EEPROM__
#define __EEPROM__

#include <stdint.h>

#define EEAR    ((uint16_t*)0x41U)  /* Register containing the memory address to be read or write   */
#define EEDR    ((uint8_t*)0x40U)   /* Register containing the data to be read or written           */
#define EECR    ((uint8_t*)0x3FU)   /* Register to indicate reading or writing operation to eeprom  */
#define EEMPE   (uint8_t)2
#define EEPE    (uint8_t)1 
#define EERE    (uint8_t)0 

void ReadFromMemory(uint16_t memory_address, uint8_t* data_read);
void WriteToMemory(uint16_t memory_address, uint8_t data_toWrite);
static uint8_t GetEepeValue();

#endif