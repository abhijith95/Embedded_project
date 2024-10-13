#ifndef __TIMER__
#define __TIMER__
#include <stdint.h>

/* Timer constants */
#define FCPU_HZ  (uint64_t)16000000

/* Timer registers */
#define TIMER0  (timer_registers*)(0x44)
#define TIMER1  (timer_registers*)(0x80)
#define TIMER2  (timer_registers*)(0xB0)
/* Timer interrupt registers */
#define TIFR0 (uint8_t*)0x35

/*Datatype to hold the timer registers */
typedef struct 
{
    volatile uint8_t tccra;
    volatile uint8_t tccrb;
    volatile uint8_t tcnt;
    volatile uint8_t ocra;
    volatile uint8_t ocrb;
} timer_registers;

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

#endif