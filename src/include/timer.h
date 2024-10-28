#ifndef __TIMER__
#define __TIMER__
#include <stdint.h>
#include "registers.h"
#include "dllExport.h"

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
} DLLEXPORT clock_prescale;

DLLEXPORT void Configure_timers(clock_prescale prescale);
DLLEXPORT void Delay_us(uint32_t delay_us);
DLLEXPORT void Delay_ms(uint32_t delay_ms);
DLLEXPORT void Reset_timer(void);
DLLEXPORT void Get_time_us(uint32_t* time);

#endif