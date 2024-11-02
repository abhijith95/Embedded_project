#ifndef __UTILS__
#define __UTILS__
#include <stdint.h>
#include "dllExport.h"

/************************************************/
/* Data types */
/************************************************/
typedef enum
{
    INIT = 0,
    LED_HIGH,
    LED_LOW
} Blink_states;

/************************************************/
/* Function prototypes */
/************************************************/
DLLEXPORT void Blink_onboard_led(uint32_t delay_ms);

#endif