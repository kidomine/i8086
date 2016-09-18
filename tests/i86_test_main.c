/*
 * i8086/i86_test_main.c
 *
 *   Created on: Aug 27, 2016 3:11:43 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#include "CUnit/Basic.h"

int init_suite(void) { return 0; }
int clean_suite(void) {return 0; }

void
i86_test_000(void)
{
        //FT_Library ft_library = NULL;
        //ft_library = ftcore_CreateFtLibrary();

        //CU_ASSERT_NOT_EQUAL(ft_library, NULL);

        //ftcore_DestroyFtLibrary(&ft_library);
        //CU_ASSERT_EQUAL(ft_library, NULL);
}

int
register_tests(CU_pSuite pcu_suite)
{
        if(NULL == CU_add_test(pcu_suite, "i86_test_000", i86_test_000))
        {
                return -1;
        }

        return 0;
}

int main(int argc, char *argv[])
{
    CU_pSuite pcu_suite = NULL;

    if(CUE_SUCCESS != CU_initialize_registry())
    {
            return CU_get_error();
    }

    pcu_suite = (CU_add_suite("i8086 test suite", init_suite, clean_suite));
    if(NULL == pcu_suite)
    {
            CU_cleanup_registry();
            return CU_get_error();
    }

    if(register_tests(pcu_suite) != 0)
    {
            CU_cleanup_registry();
            return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);

    CU_basic_run_tests();
    printf("\n");

    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    // Run all tests using the automated interface
    CU_automated_run_tests();
    CU_list_tests_to_file();

    // Run all tests using the console interface
    //CU_console_run_tests();

    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
