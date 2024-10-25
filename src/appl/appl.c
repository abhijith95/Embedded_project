#include "timer.h"
#include "appl.h"
/* Conditionally include the applciation headers */
#ifdef APPL_BLINKLED
    #include "blinkLed.h"
#endif
#ifdef APPL_ULTRASONIC
    #include "ultrasonic.h"
#endif
#ifdef APPL_JOYSTICK
    #include "joystick.h"
#endif

/*
* Function to initialize the arduino board with the necessary things
* like configuring the input/output pins, clock prescaler, etc.
*
* INPUT
* @param None
* 
* OUTPUT
* @param None
*
*/
void main_initBoard(void)
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
    #ifdef APPL_JOYSTICK
        joystick_setup();
    #endif
}

/*
* Function that runs the code for the main while loop
*
* INPUT
* @param None
* 
* OUTPUT
* @param None
*
*/
void main_runBoard(void)
{
    #ifdef APPL_BLINKLED
        blinkLed_main();
    #endif
    #ifdef APPL_ULTRASONIC
        ultrasonic_main();
    #endif
    #ifdef APPL_JOYSTICK
        joystick_main();
    #endif
}
