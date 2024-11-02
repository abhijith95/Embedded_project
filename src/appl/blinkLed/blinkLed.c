#include "blinkLed.h"
#include "pin.h"
#include "utils.h"

#define LED_DELAY (uint32_t)1000

void blinkLed_setup()
{
    /* Configure pin PB5 to output*/
    Configure_pinPort(PORTB, (uint8_t)PINB5, OUTPUT);
}

void blinkLed_main()
{
    Blink_onboard_led(LED_DELAY);
}