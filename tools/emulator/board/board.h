#ifndef __MAIN_EMU_H__
#define __MAIN_EMU_H__

#include <stdint.h>
#include "registers.h"
#include "dllExport.h"

#define FCPU_MHZ (FCPU_HZ/1000000)

/************************************************/
/* Data types */
/************************************************/
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
} DLLEXPORT Board;

/************************************************/
/* Global variables */
/************************************************/
extern DLLEXPORT Board arduino_board;

/************************************************/
/* Function prototypes */
/************************************************/
void Set_prescale();
DLLEXPORT void Board_init();
DLLEXPORT void Tick(uint32_t time_us);  /* Function that will run the board for a given time */
DLLEXPORT uint64_t TickUntil(uint32_t timeout_us, uint8_t (*cond_check)(void));
DLLEXPORT uint64_t TickWhile(uint32_t timeout_us, uint8_t (*cond_check)(void));
#endif
