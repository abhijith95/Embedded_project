#include "utils.h"

void Delay(void)
{
    volatile uint32_t indx = (uint32_t)0;    
    for (; indx<DELAY_INDEX; indx++)
    {
        /* Do nothing, simply cause a delay*/
    }
}