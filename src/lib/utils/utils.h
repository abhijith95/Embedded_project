#ifndef __UTILS__
#define __UTILS__

#include <stdint.h>

#define CLK_FREQ_MHZ    (uint8_t)16
#define MAXTIME         (uint16_t)16
#define CLKSCALE        (uint16_t)1024

void Delay_ms(uint16_t delayTime_ms);

void ReadTime(uint8_t* current_time);

#endif