/*
*   File containing the address for registers and other related stuff
*
*/
#ifndef __MEMORYCAL__
#define __MEMORYCAL__
#include <stdint.h>

/* Defining registers for general purpose IO */
#define GPIOB (0x23U)
#define GPIOC (0x26U)
#define GPIOD (0x29U)

/* Timer registers */
#define TCCR0A  (0x44U)
#define TCCR0B  (0x45U)
#define TCNT0   (0x46U)

#endif