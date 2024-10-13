#include "blinkLed.h"
#include "timer.h"
#include "pin.h"
#include "eeprom.h"

#define LED_DELAY (uint32_t)1000

void blinkLed_setup()
{
    /* Configure pin PB5 to output*/
    Configure_pinPort(PORTB, (uint8_t)PINB5, OUTPUT);
}

void blinkLed_main()
{
    Write_pin(PORTB, (uint8_t)PINB5, PIN_HIGH);
    Delay_ms(LED_DELAY);
    Write_pin(PORTB, (uint8_t)PINB5, PIN_LOW);
    Delay_ms(LED_DELAY);
}