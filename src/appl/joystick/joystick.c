#include "joystick.h"
#include "timer.h"
#include "pin.h"
#include "utils.h"

void joystick_setup()
{
    /* Configure pin PB5 to output to show sensor has detected something */
    Configure_pinPort(PORTB, (uint8_t)PINB5, OUTPUT);
    /* Configure PD2 as the trigger for the sensor */
    Configure_pinPort(PORTD, (uint8_t)PIND2, INPUT);
}
void joystick_main()
{
    if(Read_pin(PORTD, (uint8_t)PIND2) == PIN_LOW)
    {
        /* The push button is high by default */
        Blink_onboard_led(1000U);
    }
    else
    {
        Write_pin(PORTB, (uint8_t)PINB5, PIN_LOW);
    }
}