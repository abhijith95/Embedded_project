#include "registers.h"

/* Define the global variables for the registers */
uint16_t eear        = (uint16_t)0;
uint8_t eedr         = (uint8_t)0;
uint8_t eecr         = (uint8_t)0;
uint8_t tifr0        = (uint8_t)0;
uint8_t tifr1        = (uint8_t)0;
uint8_t tifr2        = (uint8_t)0;
uint8_t admux        = (uint8_t)0;

timer_registers timer0   = { (uint8_t)0, /* tccra */
                                    (uint8_t)0, /* tccrb */ 
                                    (uint8_t)0, /* tccnt */ 
                                    (uint8_t)0, /* ocra */ 
                                    (uint8_t)0, /* ocrb */ 
                                };
timer_registers timer2   = { (uint8_t)0, /* tccra */
                                    (uint8_t)0, /* tccrb */ 
                                    (uint8_t)0, /* tccnt */ 
                                    (uint8_t)0, /* ocra */ 
                                    (uint8_t)0, /* ocrb */ 
                                };

gpio portb               = { (uint8_t)0, /* pin */
                                    (uint8_t)0, /* ddr */
                                    (uint8_t)0, /* port */
                                };
gpio portc               = { (uint8_t)0, /* pin */
                                    (uint8_t)0, /* ddr */
                                    (uint8_t)0, /* port */
                                };
gpio portd               = { (uint8_t)0, /* pin */
                                    (uint8_t)0, /* ddr */
                                    (uint8_t)0, /* port */
                                };
