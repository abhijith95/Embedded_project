#include "board.h"
#include "appl.h"

void Board_init(Board* arduino_board)
{
    arduino_board->timer0_reg = &timer0;
    arduino_board->timer2_reg = &timer2;
    arduino_board->portb_reg = &portb;
    arduino_board->portc_reg = &portc;
    arduino_board->portd_reg = &portd;
    arduino_board->eear_reg  = &eear;
    arduino_board->eedr_reg   = &eedr;
    arduino_board->eecr_reg   = &eecr;
    arduino_board->tifr0_reg  = &tifr0;
    arduino_board->tifr1_reg  = &tifr1;
    arduino_board->tifr2_reg  = &tifr2;
    arduino_board->admux_reg  = &admux;
    main_initBoard();
    arduino_board->board_init = (uint8_t)1;
}

void Tick(uint32_t time_us, Board* arduino_board)
{
    /* Reset the local timer */
    arduino_board->time = 0;
    while(arduino_board->time < (uint64_t)(time_us*FCPU_MHZ))
    {
        main_runBoard();
        arduino_board->time += 1;
        if(arduino_board->time % 2 == 0)
        {
            /* Update the register */
            arduino_board->timer0_reg->tcnt+=1;
        }
        else
        {
            /* Do nothing */
        }
        if(arduino_board->timer0_reg->tcnt == 255)
        {
            /* Overflow the counter */
            *arduino_board->tifr0_reg |= (1<<0);
        }
        else
        {
            /* Do nothing */
        }
    }
}
