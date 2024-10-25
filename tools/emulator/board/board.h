#ifndef __MAIN_EMU_H__
#define __MAIN_EMU_H__

#include <stdint.h>
extern "C" {
    #include "registers.h"
}

#define FCPU_MHZ (FCPU_HZ/1000000)

class Arduino
{
    private:
    bool board_init;
    uint64_t time;

    protected:
    timer_registers* timer0_reg = &timer0;
    timer_registers* timer2_reg = &timer2;
    gpio* portb_reg = &portb;
    gpio* portc_reg = &portc;
    gpio* portd_reg = &portd;
    uint16_t* eear_reg  = &eear;
    uint8_t* eedr_reg   = &eedr;
    uint8_t* eecr_reg   = &eecr;
    uint8_t* tifr0_reg  = &tifr0;
    uint8_t* tifr1_reg  = &tifr1;
    uint8_t* tifr2_reg  = &tifr2;
    uint8_t* admux_reg  = &admux;

    public:
    Arduino(void); /* Class constructor */
    void Tick(uint32_t time_us);  /* Function that will run the board for a given time */

};

#endif
