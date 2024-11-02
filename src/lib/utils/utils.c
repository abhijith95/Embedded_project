#include <stdint.h>
#include "utils.h"
#include "pin.h"
#include "timer.h"

/*
* Function to blink the onboard LED. This function assumes that the pin PB5
* is set as output prior to the function call 
*
* INPUT
* @param None
*
* OUTPUT
* @param None
*/
void Blink_onboard_led(uint32_t delay_ms)
{
    static Blink_states state = INIT;
    switch (state)
    {
    case INIT:
        Write_pin(PORTB, (uint8_t)PINB5, PIN_LOW);
        state = LED_HIGH;
        Reset_timer();
        break;
    case LED_HIGH:
        Write_pin(PORTB, (uint8_t)PINB5, PIN_HIGH);
        if(Time_elapsed(delay_ms*1000U) == 1)
        {
            state = LED_LOW;
            Reset_timer();
        }
        else
        {
            /* Keep in the state */
        }
        break;
    case LED_LOW:
        Write_pin(PORTB, (uint8_t)PINB5, PIN_LOW);
        if(Time_elapsed(delay_ms*1000U) == 1)
        {
            state = INIT;
        }
        else
        {
            /* Keep in the state */
        }
        break;
    default:
        Write_pin(PORTB, (uint8_t)PINB5, PIN_LOW);
        state = INIT;
        break;
    }
}
