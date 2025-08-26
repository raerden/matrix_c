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

START_TEST(sub_matrix) {
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
        check.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
        }
    }

    matrix_t res = {0};
    ck_assert_int_eq(s21_sub_matrix(&A, &B, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(sum_matrix_error1) {
    matrix_t A = {0};
    matrix_t B = {0};
    s21_create_matrix(2, 2, &B);

    matrix_t res = {0};
    ck_assert_int_eq(s21_sum_matrix(&A, &B, &res), INCORRECT_MATRIX);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);

}
END_TEST

START_TEST(sum_matrix_error2) {
    matrix_t A = {0};
    s21_create_matrix(4, 4, &A);
    matrix_t B = {0};
    s21_create_matrix(2, 2, &B);

    matrix_t res = {0};
    ck_assert_int_eq(s21_sum_matrix(&A, &B, &res), CALCULATION_ERROR);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);

}
END_TEST

START_TEST(sum_matrix_inf) {
    matrix_t A = {0};
    matrix_t B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    FILL_MATRIX(A, {1, 2, 3, 4});
    FILL_MATRIX(B, {5, 6, 7, 8});
    B.matrix[1][1] = INFINITY;

    matrix_t res = {0};
    ck_assert_int_eq(s21_sum_matrix(&A, &B, &res), CALCULATION_ERROR);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);

}
END_TEST

START_TEST(mult_number_matrix) {
    int rows = rand() % 100 + 1;
    int cols = rand() % 100 + 1;
    matrix_t A = {0};
    s21_create_matrix(rows, cols, &A);
    matrix_t check = {0};
    s21_create_matrix(rows, cols, &check);
    double number = get_rand(MIN_DOUBLE, MAX_DOUBLE);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            A.matrix[i][j] = get_rand(MIN_DOUBLE, MAX_DOUBLE);
            check.matrix[i][j] = A.matrix[i][j] * number;
        }
    }

    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_number(&A, number, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_matrix_inf) {
    matrix_t A = {0};
    s21_create_matrix(2, 2, &A);
    FILL_MATRIX(A, {1, 2, 3, 4});

    A.matrix[1][1] = INFINITY;

    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_number(&A, 12.34, &res), CALCULATION_ERROR);

    s21_remove_matrix(&A);
    s21_remove_matrix(&res);

}
END_TEST

START_TEST(mult_matrix_error_not_created) {
    matrix_t A = {0};
    matrix_t B = {0};
    s21_create_matrix(2, 2, &A);
    FILL_MATRIX(A, {1, 2, 3, 4});

    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), INCORRECT_MATRIX);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);

}
END_TEST

START_TEST(mult_matrix_error_not_equal_size) {
    matrix_t A = {0};
    matrix_t B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(1, 3, &B);
    FILL_MATRIX(A, {1, 2, 3, 4});
    FILL_MATRIX(B, {5, 6, 7});

    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), CALCULATION_ERROR);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);

}
END_TEST

START_TEST(mult_matrix_error_infinity) {
    matrix_t A = {0};
    matrix_t B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    FILL_MATRIX(A, {1, 2, 3, 4});
    FILL_MATRIX(B, {5, 6, 7, 8});
    A.matrix[1][1] = INFINITY;

    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), CALCULATION_ERROR);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);

}
END_TEST

START_TEST(mult_matrix_ok) {
    matrix_t A = {0};
    s21_create_matrix(2, 2, &A);
    matrix_t B = {0};
    s21_create_matrix(2, 2, &B);
    matrix_t check = {0};
    s21_create_matrix(2, 2, &check);

    FILL_MATRIX(A, {1, 2, 3, 4});
    FILL_MATRIX(B, {1, 2, 3, 4});
    
    FILL_MATRIX(check, {7, 10, 15, 22});


    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix_ok2) {
    matrix_t A = {0};
    s21_create_matrix(3, 3, &A);
    matrix_t B = {0};
    s21_create_matrix(3, 3, &B);
    matrix_t check = {0};
    s21_create_matrix(3, 3, &check);

    FILL_MATRIX(A, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    FILL_MATRIX(B, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    
    FILL_MATRIX(check, {30, 36, 42, 66, 81, 96, 102, 126, 150});


    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), OK);
    ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&res);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix_ok3) {
    matrix_t A = {0};
    s21_create_matrix(3, 3, &A);
    matrix_t B = {0};
    s21_create_matrix(3, 3, &B);
    matrix_t check = {0};
    s21_create_matrix(3, 3, &check);

    FILL_MATRIX(A, {1.01, 2.31, 3.67, 4.04, 5.56, 6.66, 7.43, 8.12, 9.22});
    FILL_MATRIX(B, {9.22, 8.12, 7.43, 6.66, 5.56, 4.04, 3.67, 2.31, 1.01});
    
    FILL_MATRIX(check, {38.16, 29.52, 20.54, 98.72, 79.1, 59.2, 156.42, 126.77, 97.32});


    matrix_t res = {0};
    ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), OK);
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
    tcase_add_loop_test(tc, sub_matrix, 0, 10);
    tcase_add_test(tc, sum_matrix_error1);
    tcase_add_test(tc, sum_matrix_error2);
    tcase_add_test(tc, sum_matrix_inf);
    tcase_add_test(tc, mult_number_matrix);
    tcase_add_test(tc, mult_number_matrix_inf);
    tcase_add_test(tc, mult_matrix_error_not_created);
    tcase_add_test(tc, mult_matrix_error_not_equal_size);
    tcase_add_test(tc, mult_matrix_error_infinity);
    tcase_add_test(tc, mult_matrix_ok);
    tcase_add_test(tc, mult_matrix_ok2);
    tcase_add_test(tc, mult_matrix_ok3);


    suite_add_tcase(s, tc);
    return s;
}