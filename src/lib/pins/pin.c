#include <stdint.h>
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
* @param None
*/
void Configure_pinPort(gpio *port, uint8_t pin, PIN_CONFIG pin_config)
{
    if (pin_config == OUTPUT)
    {
        port->ddr |= (1 << pin);
    }
    else
    {
        port->ddr &= ~(1 << pin);
        /* This is to activate the pull-up resistor */
        port->port |= (((uint8_t) 1) << pin);
    }
}

/*
* Function to read the pin value 
*
* INPUT
* @param gpio *port     - pointer to a general purpose IO register
                            use macros PORTB/PORTC/PORTD
* @param uint8_t pin    - the pin number from the enum PINB/PINC/PIND
                            typecast to uint8_t
*
* OUTPUT
* @param PIN_VALUE      - Enum indicating the pin value
*/
PIN_VALUE Read_pin(gpio* port, uint8_t pin)
{
    uint8_t pin_value = (port->pin >> pin) & 1;
    return (PIN_VALUE) pin_value;
}

/*
* Function to read the pin value 
*
* INPUT
* @param gpio *port     - pointer to a general purpose IO register
                            use macros PORTB/PORTC/PORTD
* @param uint8_t pin    - the pin number from the enum PINB/PINC/PIND
                            typecast to uint8_t
* @param PIN_VALUE      - Enum indicating the pin value
* 
* OUTPUT
* @param None
*/
void Write_pin(gpio* port, uint8_t pin, PIN_VALUE value)
{
    if (value == PIN_HIGH)
    {
        port->pin |= (1 << pin);
        /* The port is also set to drive the pin to high, it is a digital pin concept */
        port->port |= (1 << pin);
    }
    else if (value == PIN_LOW)
    {
        port->pin &= ~(1 << pin);
        port->port &= ~(1 << pin);
    }
    else
    {
        /* Invalid pin value dont do anything */
    }
}

/*
* Function to configure the reference voltage source for analog pins
*
* INPUT
* @param ANALOG_VREFS vref_source   - reference voltage source
* @param PINC                       - pins to configure as analog input
* 
* OUTPUT
* @param None
*/
void Configure_analogPins(ANALOG_VREFS vref_source, PINC pin)
{
    *ADMUX |= ((uint8_t)vref_source << 6) | ((uint8_t)pin << 0);
}
