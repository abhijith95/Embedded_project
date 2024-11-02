#include "board.h"
#include "pin.h"
#include "timer.h"
#include <math.h>
#include <stdio.h>
#include "CUnit/Basic.h"

#define LED_DELAY_US (uint32_t)1000000

uint8_t check_pin_high(void)
{
    return((uint8_t) (Read_pin(arduino_board.portb_reg, PINB5) == PIN_HIGH));
}

uint8_t check_pin_low(void)
{
    return((uint8_t) (Read_pin(arduino_board.portb_reg, PINB5) == PIN_LOW));
}

void test_led_blink()
{
    uint64_t time = 0;
    /* Tick for little bit to get the LED high in the beginning */
    (void)TickUntil(100, check_pin_high);
    CU_ASSERT(Read_pin(arduino_board.portb_reg, PINB5) == PIN_HIGH);
    Reset_timer();
    uint64_t t2 = TickWhile((LED_DELAY_US - 500000), check_pin_high);
    time = TickUntil(600000, check_pin_low);
    CU_ASSERT_DOUBLE_EQUAL((time + t2), LED_DELAY_US, 1000);
    CU_ASSERT(Read_pin(arduino_board.portb_reg, PINB5) == PIN_LOW);
    Reset_timer();
    t2 = TickWhile((LED_DELAY_US - 500000), check_pin_low);
    time = TickUntil(LED_DELAY_US, check_pin_high);
    CU_ASSERT_DOUBLE_EQUAL((time + t2), LED_DELAY_US, 1000);
}

int init_suite(void) 
{ 
    Board_init();
    return 0; 
}
int clean_suite(void) { return 0; }

int main()
{
    CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if ( CUE_SUCCESS != CU_initialize_registry() )
    {
        return CU_get_error();
    }
    /* add a suite to the registry */
   pSuite = CU_add_suite("led_blink_test_suite", init_suite, clean_suite);
   if ( NULL == pSuite ) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }
   /* Add test to the suite */
   if(NULL == CU_add_test(pSuite, "test1", test_led_blink))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
