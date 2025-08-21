#include <check.h>
#include "tests_matrix.h"

START_TEST(sum_matrix) {
    int rows = rand() % 100 + 1;
    int cols = rand() % 100 + 1;
    matrix_t A = {0};
    s21_create_matrix(rows, cols, &A);
    matrix_t B = {0};
    s21_create_matrix(rows, cols, &B);
    matrix_t check = {0};
    s21_create_matrix(rows, cols, &check);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        A.matrix[i][j] = get_rand(MIN_DOUBLE, MAX_DOUBLE);
        B.matrix[i][j] = get_rand(MIN_DOUBLE, MAX_DOUBLE);
        check.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
        }
    }

    matrix_t res = {0};
    ck_assert_int_eq(s21_sum_matrix(&A, &B, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

Suite *suite_sum_matrix(void) {
    Suite *s = suite_create("suite_sum_matrix");
    TCase *tc = tcase_create("case_sum_matrix");

    tcase_add_loop_test(tc, sum_matrix, 0, 10);
    // tcase_add_loop_test(tc, sum_matrix1, 0, 100);
    // tcase_add_loop_test(tc, sum_matrix2, 0, 100);

    suite_add_tcase(s, tc);
    return s;
}