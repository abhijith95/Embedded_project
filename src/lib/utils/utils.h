#ifndef __UTILS__
#define __UTILS__

#include <stdint.h>

#define CLK_FREQ_MHZ    (uint64_t)16000000
#define CLKSCALE        (uint16_t)64
#define TIME_1MS        (uint16_t)1

void Delay_ms(uint16_t delayTime_ms);
void ReadTime(uint8_t* current_time);
void Util_setup();

#endif