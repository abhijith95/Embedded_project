#include <stdint.h>
#include "utils.h"
#include "pin.h"

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
    Write_pin(PORTB, (uint8_t)PINB5, PIN_HIGH);
    Delay_ms(delay_ms);
    Write_pin(PORTB, (uint8_t)PINB5, PIN_LOW);
    Delay_ms(delay_ms);
}
