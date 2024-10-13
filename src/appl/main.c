#include "timer.h"
/* Conditionally include the applciation headers */
#ifdef APPL_BLINKLED
    #include "blinkLed.h"
#endif
#ifdef APPL_ULTRASONIC
    #include "ultrasonic.h"
#endif

int main()
{
    /* Perform all the setups here */
    Configure_timers(PRESCALE_64);
    /* Conditionally run all the application setup functions */
    #ifdef APPL_BLINKLED
        blinkLed_setup();
    #endif
    #ifdef APPL_ULTRASONIC
        ultrasonic_setup();
    #endif

    /* Start the main loop */
    while(1U)
    {
        #ifdef APPL_BLINKLED
            blinkLed_main();
        #endif
        #ifdef APPL_ULTRASONIC
            ultrasonic_main();
        #endif
    }
    return 1;
}