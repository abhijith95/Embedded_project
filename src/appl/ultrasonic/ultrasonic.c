#include "ultrasonic.h"
#include "timer.h"
#include "pin.h"
#include "utils.h"

#define DIST_THRSH      (uint16_t)20
#define TRIG_DELAY_US   (uint32_t)12
#define TIME_NO_OBJ_US  (uint32_t)36000

typedef enum
{
    SEND_TRIG = 0,
    WAIT_FOR_ECHO,
    EVAL_ECHO
}ultrasonic_state;

void ultrasonic_setup()
{
    /* Configure pin PB5 to output to show sensor has detected something */
    Configure_pinPort(PORTB, (uint8_t)PINB5, OUTPUT);
    /* Configure PD2 as the trigger for the sensor */
    Configure_pinPort(PORTD, (uint8_t)PIND2, OUTPUT);
    /* Configure PB1 as the echo input from the sensor */
    Configure_pinPort(PORTB, (uint8_t)PINB0, INPUT);
}

void ultrasonic_main()
{
    static ultrasonic_state state = SEND_TRIG;
    static uint32_t time = 0U;
    switch(state)
    {
        case SEND_TRIG:
            Write_pin(PORTD, (uint8_t)PIND2, PIN_HIGH);
            Delay_us(TRIG_DELAY_US);
            Write_pin(PORTD, (uint8_t)PIND2, PIN_LOW);
            time = 0U;
            state = WAIT_FOR_ECHO;
            Reset_timer();
            break;
        
        case WAIT_FOR_ECHO:
            if(Read_pin(PORTB, (uint8_t)PINB0) == PIN_HIGH)
            {
                /* Signal detected from the sensor */
                Get_time_us(&time);
                state = SEND_TRIG;
                Reset_timer();
            }
            else
            {
                /* Keep ticking until the signal arrives */
            }
            break;
        
        case EVAL_ECHO:
            /* For now we will light up the B5 LED */
            if(time <= TIME_NO_OBJ_US)
            {
                /* We have detected something so light up the LED */
                Blink_onboard_led(1000U);
                
            }
            else
            {
                Write_pin(PORTB, (uint8_t)PINB5, PIN_LOW);
            }
            state = SEND_TRIG;
            Blink_onboard_led(200U);
            break;

        default:
            state = SEND_TRIG;
            break;
    }
}
