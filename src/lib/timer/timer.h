#ifndef __TIMER__
#define __TIMER__
#include <stdint.h>
#include "../memory/registers.h"

/************************************************/
/* Data types */
/************************************************/
typedef enum
{
    DISABLE_COUNT = 0,
    NO_PRESCALE,
    PRESCALE_8,
    PRESCALE_64,
    PRESCALE_256,
    PRESCALE_1024
}clock_prescale;

void Configure_timers(clock_prescale prescale);
void Delay_us(uint32_t delay_us);
void Delay_ms(uint32_t delay_ms);
void Reset_timer(void);
void Get_time_us(uint32_t* time);

#endif