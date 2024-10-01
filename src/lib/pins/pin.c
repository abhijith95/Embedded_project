#include <stdint.h>
#include "memory_cal.h"
#include "pin.h"

/*
* Function to configure ports for read or write
*
* INPUT
* @param gpio *port            - pointer to a general purpose IO register
                                    use macros PORTB/PORTC/PORTD
* @param uint8_t pin           - the pin number from the enum PINB/PINC/PIND
                                    typecast to uint8_t
* @param PIN_CONFIG pin_config - Pin configuration INPUT/OUTPUT
*
* OUTPUT
* None
*/
void Configure_pinPort(gpio *port, uint8_t pin, PIN_CONFIG pin_config)
{
    port->ddr |= (((uint8_t) pin_config) << pin);
    if(pin_config == INPUT)
    {
        /* This is to activate the pull-up resistor */
        port->port |= (((uint8_t) 1) << pin);
    }
    else
    {
        /* do nothing */
    }
}

PIN_VALUE Read_pin(gpio* port, uint8_t pin)
{
    uint8_t mask = ((uint8_t) 1 << pin);
    uint8_t pin_value = (port->pin & mask) >> pin;
    return (PIN_VALUE) pin_value;
}

void Write_pin(gpio* port, uint8_t pin, PIN_VALUE value)
{
    port->pin |= (((uint8_t) value) << pin);
}
