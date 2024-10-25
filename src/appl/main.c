#include "appl.h"

int main()
{
    main_initBoard();
    /* Start the main loop */
    while(1U)
    {
        main_runBoard();
    }
    return 1;
}