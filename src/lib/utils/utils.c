#include "utils.h"
#include "memory_cal.h"

void Util_setup()
{
    /* Set the presclaer to 1024. This means for 16MHz the clock register will overflow
        after 16ms. See Timer0 control (Section 15) for 0x5U value */
    *((uint8_t*)TCCR0B) = 0x3U;
}
/*
* Function to cause intentional delay in the microcontroller
*
* INPUT
* @param uint16_t delayTime_ms  - Time in ms to delay
*
* OUTPUT
* @param None
*/
void Delay_ms(uint16_t delayTime_ms)
{
    uint16_t num_overflows = (uint16_t)0;
    uint8_t current_time = (uint8_t)0;
    uint8_t previous_time = (uint8_t)0;
    uint16_t elapsed_time = (uint16_t)0;

    while(elapsed_time < delayTime_ms)
    {
        /* Read the current time */
        ReadTime(&current_time);
        if(previous_time > current_time)
        {
            /* Register has overflown increase the overflow counter */
            num_overflows+=1;
        }
        else
        {
            /* Do nothing */
        }
        /* We will stay inside the function until the timer is reached*/
        elapsed_time = (TIME_1MS*num_overflows);
        previous_time = current_time;
    }
    /* Reset the overflow counter to start a new delay function */
}

/*
* Function that will read the register for the current time
*
* INPUT
* @param uint8_t *current_time  - Pointer to current time
*
* OUTPUT
* @param current_time           - The time will be written to the input parameter
*/
void ReadTime(uint8_t* current_time)
{
    *current_time = *((uint8_t*)TCNT0);
}
