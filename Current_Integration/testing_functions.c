#include "MadLab_header.h"

int initialise_CUnit(CU_pSuite *pSuite, char *suite_name)
{
   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   *pSuite = CU_add_suite(suite_name, NULL, NULL);
   if (NULL == *pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   return 0;
}

int close_CUnit(void)
{
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

void set_up_test(char *suite_name, char *test_name, CU_TestFunc function)
{
   CU_pSuite pSuite = NULL;

   initialise_CUnit(&pSuite, suite_name);

   if ((NULL == CU_add_test(pSuite, test_name, function))){
      CU_cleanup_registry();
      CU_get_error();
    }

   close_CUnit();
}

void test_makeRoom(void)
{
   
}