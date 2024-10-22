#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <stdint.h>

/***************************************/
/* EEPROM memory registers */
/***************************************/
#define EEAR    ((uint16_t*)0x41) /* Register containing the memory address to be read or write   */
#define EEDR    ((uint8_t*)0x40) /* Register containing the data to be read or written           */
#define EECR    ((uint8_t*)0x3F) /* Register to indicate reading or writing operation to eeprom  */

/***************************************/
/* Timer registers */
/***************************************/
#define FCPU_HZ (uint64_t)16000000
#define TIMER0  (timer_registers*)(0x44)
#define TIMER2  (timer_registers*)(0xB0)
#define TIFR0   (uint8_t*)(0x35)
#define TIFR1   (uint8_t*)(0x36)
#define TIFR2   (uint8_t*)(0x37)

/***************************************/
/* Defining registers for general purpose IO */
/***************************************/
#define PORTB (gpio*)(0x23)
#define PORTC (gpio*)(0x26)
#define PORTD (gpio*)(0x29)
#define ADMUX ((uint8_t*)0x7C)

/************************************************/
/* Data types */
/************************************************/
/* Data type representing the required registers to handle the port pins */
typedef struct 
{
    volatile uint8_t pin;
    volatile uint8_t ddr;
    volatile uint8_t port;
}gpio;

/*Datatype to hold the timer registers */
typedef struct 
{
    volatile uint8_t tccra;
    volatile uint8_t tccrb;
    volatile uint8_t tcnt;
    volatile uint8_t ocra;
    volatile uint8_t ocrb;
} timer_registers;

#endif
