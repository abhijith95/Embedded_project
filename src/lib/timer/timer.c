#include <stdint.h>
#include "timer.h"

uint8_t timerPerTick_us = (uint8_t)0;

/*
* Function to configure the timer register
*
* INPUT
* @param clock_prescale prescale - Reduce the timer frequency by the scale
*
* OUTPUT
* @param None
*/
void Configure_timers(clock_prescale prescale)
{
    *TIFR0 = 0;
    timer_registers* timer0 = TIMER0;
    timer0->tccrb = (uint8_t)prescale;
    timer0->tccra = 0x0;

    switch(prescale)
    {
        case NO_PRESCALE:
            timerPerTick_us = (uint8_t)1;
            break;
        case PRESCALE_8:
            timerPerTick_us = (uint8_t)0.5;
            break;
        case PRESCALE_64:
            timerPerTick_us = (uint8_t)4;
            break;
        case PRESCALE_256:
            timerPerTick_us = (uint8_t)16;
            break;
        case PRESCALE_1024:
            timerPerTick_us = (uint8_t)64;
            break;
        case DISABLE_COUNT:
        default:
            timerPerTick_us = (uint8_t)0;
            break;
    }
}

void Delay_us(uint32_t delay_us)
{
    timer_registers* timer0 = TIMER0;
    /* Divide the delay into number of overflows and ticks*/
    uint32_t total_overflow = (uint32_t)((delay_us/timerPerTick_us)/256);
    uint8_t total_remainder_ticks = (uint8_t)((delay_us/timerPerTick_us)%256);
    /* Reset the register to start the delay */
    timer0->tcnt = 0;
    uint32_t overflow_ticks = (uint32_t)0;
    while(overflow_ticks < total_overflow)
    {
        /* Increment overflow ticks */
        if(*TIFR0)
        {
            overflow_ticks+=(uint32_t)1;
            *TIFR0 |= (1 << 0);
        }
        else
        {
            /* Keep ticking */
        }
    }
    /* Tick rest of the remaining counters */
    timer0->tcnt = 0;
    while(timer0->tcnt < total_remainder_ticks)
    {
        /* Wait for the timer to finish */
    }
    timer0->tcnt = 0;
}