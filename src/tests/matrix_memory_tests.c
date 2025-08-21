#include <check.h>
#include "tests_matrix.h"

START_TEST(create_matrix_01) {
    int res = 0;
    matrix_t A = {0};

    res = s21_create_matrix(1, 1, &A);
    ck_assert_int_eq(res, OK);
    s21_remove_matrix(&A);
}
END_TEST

Suite *suite_create_matrix(void) {
    Suite *s = suite_create("suite_create_matrix");
    TCase *tc = tcase_create("case_create_matrix");

    tcase_add_test(tc, create_matrix_01);
    // tcase_add_test(tc, create_2);
    // tcase_add_test(tc, create_3);

    suite_add_tcase(s, tc);
    return s;
}