#include "tests_matrix.h"

double get_rand(double min, double max) {
    double rnd = (double)rand() / RAND_MAX;
    return min + rnd * (max - min);
}

void testcases(Suite *testcase) {
    static int counter_testcase = 1;

    if (counter_testcase > 0) putchar('\n');
    counter_testcase++;
    SRunner *sr = srunner_create(testcase);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    srunner_free(sr);
}

int main(void) {
    srand(time(NULL));
    // Suite *list_cases[] = {suite_create_matrix(),    
    //                        suite_sub_matrix(),       suite_sum_matrix(),
    //                        suite_mult_matrix(),      suite_mult_number_matrix(),
    //                        suite_transpose_matrix(), suite_calc_complements(),
    //                        suite_determinant(),      suite_inverse_matrix(),
    //                        suite_matrix_gather(),    NULL};
    Suite *list_cases[] = {suite_create_matrix(), suite_sum_matrix(), 
                           suite_eq_matrix(), suite_transpose_matrix(),
                        suite_determinant(),
                        NULL,
    };
    for (Suite **current_testcase = list_cases; *current_testcase != NULL;
        current_testcase++) {
        testcases(*current_testcase);
    }
    return 0;
}