#include "eeprom.h"

void ReadFromMemory(uint16_t memory_address, uint8_t* data_read)
{
    /* Make sure there are no current writing operations going on */
    while (GetEepeValue() == (uint8_t)1)
    {
        /* Wait for eepe value to go to zero */
    }
    *EEAR = memory_address;
    *(EECR) |= (1<<EERE);
    *data_read = *EEDR;
}

void WriteToMemory(uint16_t memory_address, uint8_t data_toWrite)
{
    
    /* Make sure there are no current writing operations going on */
    while (GetEepeValue() == (uint8_t)1)
    {
        /* Wait for eepe value to go to zero */
    }

    /* Write the address and data to the appropriate registers */
    *EEAR = memory_address;
    *EEDR = data_toWrite;

    /* Set value to the control register. Maintain this order! */
    *(EECR) |= (1<<EEMPE);
    *(EECR) |= (1<<EEPE);

    while (GetEepeValue() == (uint8_t)1)
    {
        /* Wait for eepe value to go to zero */
    }
}

static uint8_t GetEepeValue()
{
    uint8_t eepe_mask = ((uint8_t) 1 << EEPE);
    uint8_t eepe_value = (*(EECR) & eepe_mask) >> EEPE;
    return eepe_value;
}