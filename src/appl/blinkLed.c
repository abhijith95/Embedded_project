#include "utils.h"
#include "pin.h"

void main()
{
    /* Configure pin PB5 to output*/
    Configure_pinPort(PORTB, (uint8_t)PINB5, OUTPUT);

    /* The main loop for the application */
    while(1)
    {
        Write_pin(PORTB, (uint8_t)PINB5, PIN_HIGH);
        Delay();
        Write_pin(PORTB, (uint8_t)PINB5, PIN_LOW);
    }
}