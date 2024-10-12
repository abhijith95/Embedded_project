#include "utils.h"
/* Conditionally include the applciation headers */
#ifdef APPL_BLINKLED
    #include "blinkLed.h"
#endif

int main()
{
    /* Perform all the setups here */
    Util_setup();
    /* Conditionally run all the application setup functions */
    #ifdef APPL_BLINKLED
        blinkLed_setup();
    #endif

    /* Start the main loop */
    while(1U)
    {
        #ifdef APPL_BLINKLED
            blinkLed_main();
        #endif
    }
    return 1;
}