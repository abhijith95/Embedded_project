#include "board.h"
#include "pin.h"
#include <stdio.h>
#include "CUnit/Basic.h"

Board arduino_board;

void test_led_blink()
{
    /* Tick for little bit to get the LED high in the beginning */
    Tick((uint32_t)4, &arduino_board);
    CU_ASSERT(Read_pin(arduino_board.portb_reg, PINB5) == PIN_HIGH);
    Tick((uint32_t)1000000, &arduino_board);
    CU_ASSERT(Read_pin(arduino_board.portb_reg, PINB5) == PIN_LOW);
}

int init_suite(void) 
{ 
    Board_init(&arduino_board);
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