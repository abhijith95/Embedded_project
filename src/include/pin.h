#ifndef __PIN__
#define __PIN__

#include <stdint.h>
#include "registers.h"

/************************************************/
/* Data types */
/************************************************/

/* List of available pins on PORT B */
typedef enum
{
    PINB0 = 0,
    PINB1,
    PINB2,
    PINB3,
    PINB4,
    PINB5,
    PINB6,
    PINB7
} PINB;

/* List of available pins on PORT C */
typedef enum
{
    PINC0 = 0,
    PINC1,
    PINC2,
    PINC3,
    PINC4,
    PINC5,
    PINC6
} PINC;

/* List of available pins on PORT D */
typedef enum
{
    PIND0 = 0,
    PIND1,
    PIND2,
    PIND3,
    PIND4,
    PIND5,
    PIND6,
    PIND7
} PIND;

/* Enum describing the pin type */
typedef enum
{
    INPUT = 0,
    OUTPUT
}PIN_CONFIG;

/* Enum describing the digital pin value*/
typedef enum
{
    PIN_LOW = 0,
    PIN_HIGH
}PIN_VALUE;

/* Reference voltage source for analog pins */
typedef enum
{
    EXTERNAL_REF = 0,
    AVCC = 1,
    INTERNAL_11V = 3
}ANALOG_VREFS;

/* Function prototypes */

void Configure_pinPort(gpio *port, uint8_t pin, PIN_CONFIG pin_config);
PIN_VALUE Read_pin(gpio* port, uint8_t pin);
void Write_pin(gpio* port, uint8_t pin, PIN_VALUE value);
void Configure_analogPins(ANALOG_VREFS vref_source, PINC pin);

#endif
