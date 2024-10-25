#include "board.h"
extern "C" {
    #include "appl.h"
}

Arduino::Arduino()
{
    board_init = false;
    time = 0.0;
}

void Arduino::Tick(uint32_t time_us)
{
    /* Reset the local timer */
    time = 0.0;
    if(board_init == false)
    {
        board_init = true;
        main_initBoard();
    }
    else
    {
        /* Do nothing continue on to ticking */
    }
    while(time < (uint64_t)(time_us*FCPU_MHZ))
    {
        main_runBoard();
        time += 1;
        if(time % 2 == 0)
        {
            /* Update the register */
            timer0_reg->tcnt+=1;
        }
        else
        {
            /* Do nothing */
        }
        if(timer0_reg->tcnt == 255)
        {
            /* Overflow the counter */
            *tifr0_reg |= (1<<0);
        }
        else
        {
            /* Do nothing */
        }
    }
}
