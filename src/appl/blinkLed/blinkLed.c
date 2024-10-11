#include "utils.h"
#include "pin.h"
#include "eeprom.h"

#define LED_DELAY (uint16_t)300
#define DELAY_TIMER (uint8_t)10
#define DELAY_ADDRESS (uint16_t)0x5FU

int main()
{
    /* Configure pin PB5 to output*/
    Configure_pinPort(PORTB, (uint8_t)PINB5, OUTPUT);
    uint8_t delay_timer = (uint8_t)30;

    /* The main loop for the application */
    while(1)
    {
        Write_pin(PORTB, (uint8_t)PINB5, PIN_HIGH);
        Delay_ms((uint16_t)(delay_timer * 10U));
        Write_pin(PORTB, (uint8_t)PINB5, PIN_LOW);
        Delay_ms((uint16_t)(delay_timer * 10U));
    }
    return 0;
}