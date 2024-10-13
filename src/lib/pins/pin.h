#ifndef __PIN__
#define __PIN__

#include <stdint.h>

/* Defining registers for general purpose IO */
#define GPIOB (0x23U)
#define GPIOC (0x26U)
#define GPIOD (0x29U)

/* Data types */
typedef struct 
{
    volatile uint8_t pin;
    volatile uint8_t ddr;
    volatile uint8_t port;
}gpio;

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

typedef enum
{
    INPUT = 0,
    OUTPUT
}PIN_CONFIG;

typedef enum
{
    PIN_LOW = 0,
    PIN_HIGH
}PIN_VALUE;

/* Macros */
#define PORTB (gpio*)GPIOB
#define PORTC (gpio*)GPIOC
#define PORTD (gpio*)GPIOD

/* Function prototypes */

void Configure_pinPort(gpio *port, uint8_t pin, PIN_CONFIG pin_config);
PIN_VALUE Read_pin(gpio* port, uint8_t pin);
void Write_pin(gpio* port, uint8_t pin, PIN_VALUE value);

#endif