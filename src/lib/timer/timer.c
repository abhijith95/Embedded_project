#include <stdint.h>
#include "timer.h"

#define TOTAL_REG_TICKS 255U

/************************************************/
/* Global variables */
/************************************************/
static timer time = {0U, 0U}; 
uint8_t timerPerCntrIncr_us = (uint8_t)0;
uint32_t overflow_ticks = (uint32_t)0;
timer_registers* timer0_reg = TIMER0;

/*
* Function to configure the timer register. Timer0 shall always be configured to 
* perform a general delay operation in the application.
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
    // timer_registers* timer0 = TIMER0;
    timer0_reg->tccrb = (uint8_t)prescale;
    timer0_reg->tccra = 0x0;

    switch(prescale)
    {
        case NO_PRESCALE:
            timerPerCntrIncr_us = (uint8_t)1;
            break;
        case PRESCALE_8:
            timerPerCntrIncr_us = (uint8_t)0.5;
            break;
        case PRESCALE_64:
            timerPerCntrIncr_us = (uint8_t)4;
            break;
        case PRESCALE_256:
            timerPerCntrIncr_us = (uint8_t)16;
            break;
        case PRESCALE_1024:
            timerPerCntrIncr_us = (uint8_t)64;
            break;
        case DISABLE_COUNT:
        default:
            timerPerCntrIncr_us = (uint8_t)1;
            break;
    }
}

/*
* Function to delay for a given microseconds.
*
* INPUT
* @param uint32_t delay_us - Delay value in microseconds
*
* OUTPUT
* @param None
*/
void Delay_us(uint32_t delay_us)
{
    /* Divide the delay into number of overflows and ticks*/
    uint32_t total_overflow = (uint32_t)((delay_us/timerPerCntrIncr_us)/TOTAL_REG_TICKS);
    uint8_t total_remainder_ticks = (uint8_t)((delay_us/timerPerCntrIncr_us)%TOTAL_REG_TICKS);
    /* Reset the register to start the delay */
    timer0_reg->tcnt = 0;
    overflow_ticks = (uint32_t)0;
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
    timer0_reg->tcnt = 0;
    while(timer0_reg->tcnt < total_remainder_ticks)
    {
        /* Wait for the timer to finish */
    }
    timer0_reg->tcnt = 0;
}

/*
* Function to delay for a given millisecond.
*
* INPUT
* @param uint32_t delay_ms - Delay value in millisecond
*
* OUTPUT
* @param None
*/
void Delay_ms(uint32_t delay_ms)
{
    Delay_us(delay_ms*1000U);
}

/*
* Function to rest the timer register and overflow counter to zero
*
* INPUT
* @param None
*
* OUTPUT
* @param None
*/
void Reset_timer()
{
    timer0_reg->tcnt = 0;
    overflow_ticks = (uint32_t)0;
    time.overflow_count = 0;
    time.total_ticks = 0;
}

/*
* Function that calculates time in us since last reset
*
* INPUT
* @param None
*
* OUTPUT
* @param uint32_t* time - Pointer to return the value
*/
void Get_time_us(uint32_t* time)
{
    *time = ((overflow_ticks*TOTAL_REG_TICKS) + (uint32_t)timer0_reg->tcnt)*timerPerCntrIncr_us;
}

uint8_t Time_elapsed(uint32_t time_us)
{
    /* Divide the delay into number of overflows and ticks*/
    uint8_t time_elapsed_B = (uint8_t)0;
    uint32_t total_overflow = (uint32_t)((time_us/timerPerCntrIncr_us)/TOTAL_REG_TICKS);
    uint8_t total_remainder_ticks = (uint8_t)((time_us/timerPerCntrIncr_us)%TOTAL_REG_TICKS);

    time.total_ticks = timer0_reg->tcnt;
    if(*TIFR0)
    {
        time.overflow_count+=(uint32_t)1;
        *TIFR0 |= (1 << 0);
    }
    else
    {
        /* Keep ticking */
    }

    if((time.overflow_count >= total_overflow) &&
        (time.total_ticks >= total_remainder_ticks))
    {
        time_elapsed_B = (uint8_t)1;
    }

    return time_elapsed_B;
}
