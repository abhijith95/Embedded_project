#ifndef __MAIN_EMU_H__
#define __MAIN_EMU_H__

#include <stdint.h>
#include "registers.h"

#define FCPU_MHZ (FCPU_HZ/1000000)

typedef struct
{
    uint8_t board_init;
    uint64_t time;
    uint16_t prescale;
    timer_registers* timer0_reg;
    timer_registers* timer2_reg;
    gpio* portb_reg;
    gpio* portc_reg;
    gpio* portd_reg;
    uint16_t* eear_reg;
    uint8_t* eedr_reg ;
    uint8_t* eecr_reg ;
    uint8_t* tifr0_reg;
    uint8_t* tifr1_reg;
    uint8_t* tifr2_reg;
    uint8_t* admux_reg;
} __declspec(dllexport) Board;

void Set_prescale(Board *arduino_board);
__declspec(dllexport) void Board_init(Board* arduino_board);
__declspec(dllexport) void Tick(uint32_t time_us, Board* arduino_board);  /* Function that will run the board for a given time */
#endif
