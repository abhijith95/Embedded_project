#include "board.h"
#include "appl.h"
#include "timer.h"

Board arduino_board = {
                        (uint8_t)0,     /* boolean for board_init */
                        (uint64_t)0,    /* time */
                        (uint16_t)0,    /* Prescale */
                        &timer0,        /* timer0_reg */
                        &timer2,        /* timer2_reg */
                        &portb,         /* portb_reg */
                        &portc,         /* portc_reg */
                        &portd,         /* portd_reg */
                        &eear,          /* eear_reg */
                        &eedr,          /* eedr_reg */
                        &eecr,          /* eecr_reg */
                        &tifr0,         /* tifr0_reg */
                        &tifr1,         /* tifr1_reg */
                        &tifr2,         /* tifr2_reg */
                        &admux,         /* admux_reg */
};
/*
* Function to initialize the arduino board, but running the application setup
*
* INPUT
* @param Board* arduino_board - Pointer to the board object
*
* OUTPUT
* @param None
*/
void Board_init()
{
    arduino_board.board_init = (uint8_t)1;
    main_initBoard();
    Set_prescale();
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
void Tick(uint32_t time_us)
{
    /* Reset the local timer */
    arduino_board.time = 0;
    // arduino_board.timer0_reg->tcnt = 0;
    while(arduino_board.time <= (uint64_t)(time_us*FCPU_MHZ))
    {
        arduino_board.time += 1;
        if((arduino_board.time % arduino_board.prescale) == 0)
        {
            /* Update the register */
            arduino_board.timer0_reg->tcnt+=1;
        }
        else
        {
            /* Do nothing */
        }
        /* Clear the overflow counter if set by the software */
        if((*arduino_board.tifr0_reg>>0) & 1)
        {
            *arduino_board.tifr0_reg &= 0xFE;
        }
        else
        {
            /* Keep the counter as is */
        }
        if(arduino_board.timer0_reg->tcnt == 255)
        {
            /* Overflow the counter */
            *arduino_board.tifr0_reg |= (1<<0);
            arduino_board.timer0_reg->tcnt = 0;
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
void Set_prescale()
{
    switch(arduino_board.timer0_reg->tccrb)
    {
    case PRESCALE_8:
        arduino_board.prescale = (uint16_t) 8;
        break;
    case PRESCALE_64:
        arduino_board.prescale = (uint16_t) 64;
        break;
    case PRESCALE_256:
        arduino_board.prescale = (uint16_t) 256;
        break;
    case PRESCALE_1024:
        arduino_board.prescale = (uint16_t) 1024;
        break;
    case NO_PRESCALE:
    case DISABLE_COUNT:
    default:
        arduino_board.prescale = (uint16_t) 1;
        break;
    }
}

/*
* Function that ticks time until the condition passed is met or
* the timeout has elapsed
*
* INPUT
* @param uint32_t timeout_us - Timeout in microseconds
* @param uint8_t (*cond_check)(void) - Pointer to function that will
*                                       return 1 if condition is met
*
* OUTPUT
* @param uint64_t time_us  - Time in microseconds that was ticked
*/
uint64_t TickUntil(uint32_t timeout_us, uint8_t (*cond_check)(void))
{
    uint64_t time_count = (uint64_t)0;
    uint32_t temp = (uint32_t)(arduino_board.prescale/FCPU_MHZ);
    while ((cond_check() == 0) && (time_count <= (uint64_t)(timeout_us*FCPU_MHZ)))
    {
        /* We shall evaluate the condition every x microsecond determined by the prescaler config */
        Tick((uint32_t) temp);
        time_count += arduino_board.prescale;
    } 
    return((uint64_t)(time_count/FCPU_MHZ));
}

/*
* Function that ticks time until the condition passed is met or
* the timeout has elapsed
*
* INPUT
* @param uint32_t timeout_us - Timeout in microseconds
* @param uint8_t (*cond_check)(void) - Pointer to function that will
*                                       return 1 if condition is met
*
* OUTPUT
* @param uint64_t time_us  - Time in microseconds that was ticked
*/
uint64_t TickWhile(uint32_t timeout_us, uint8_t (*cond_check)(void))
{
    uint64_t time_count = (uint64_t)0;
    uint32_t temp = (uint32_t)(arduino_board.prescale/FCPU_MHZ);
    while ((cond_check() == 1) && (time_count <= (uint64_t)(timeout_us*FCPU_MHZ)))
    {
        /* We shall evaluate the condition every x microsecond determined by the prescaler config */
        Tick((uint32_t) temp);
        time_count += arduino_board.prescale;
    } 
    return((uint64_t)(time_count/FCPU_MHZ));
}
