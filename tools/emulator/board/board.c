#include "board.h"
#include "appl.h"
#include "timer.h"

/*
* Function to initialize the arduino board, but running the application setup
*
* INPUT
* @param Board* arduino_board - Pointer to the board object
*
* OUTPUT
* @param None
*/
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
    Set_prescale(arduino_board);
}

/*
* Function to tick time and call the main function of the arduino board
*
* INPUT
* @param uint32_t time_us       - Time in microseconds to tick
* @param Board* arduino_board   - Pointer to the board object
*
* OUTPUT
* @param None
*/
void Tick(uint32_t time_us, Board* arduino_board)
{
    /* Reset the local timer */
    arduino_board->time = 0;
    arduino_board->timer0_reg->tcnt = 0;
    while(arduino_board->time <= (uint64_t)(time_us*FCPU_MHZ))
    {
        arduino_board->time += 1;
        if((arduino_board->time % arduino_board->prescale) == 0)
        {
            /* Update the register */
            arduino_board->timer0_reg->tcnt+=1;
        }
        else
        {
            /* Do nothing */
        }
        /* Clear the overflow counter if set by the software */
        if((*arduino_board->tifr0_reg>>0) & 1)
        {
            *arduino_board->tifr0_reg &= 0xFE;
        }
        else
        {
            /* Keep the counter as is */
        }
        if(arduino_board->timer0_reg->tcnt == 255)
        {
            /* Overflow the counter */
            *arduino_board->tifr0_reg |= (1<<0);
            arduino_board->timer0_reg->tcnt = 0;
        }
        else
        {
            /* Do nothing */
        }
        main_runBoard();
    }
}

/*
* Function to setup the prescale value on timer0 register
*
* INPUT
* @param Board* arduino_board - Pointer to the board object
*
* OUTPUT
* @param None
*/
void Set_prescale(Board* arduino_board)
{
    switch(arduino_board->timer0_reg->tccrb)
    {
    case PRESCALE_8:
        arduino_board->prescale = (uint16_t) 8;
        break;
    case PRESCALE_64:
        arduino_board->prescale = (uint16_t) 64;
        break;
    case PRESCALE_256:
        arduino_board->prescale = (uint16_t) 256;
        break;
    case PRESCALE_1024:
        arduino_board->prescale = (uint16_t) 1024;
        break;
    case NO_PRESCALE:
    case DISABLE_COUNT:
    default:
        arduino_board->prescale = (uint16_t) 1;
        break;
    }
}
