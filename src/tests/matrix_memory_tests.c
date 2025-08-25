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

START_TEST(create_matrix_02) {
    int res = 0;
    matrix_t A = {0};

    res = s21_create_matrix(0, 1, &A);
    ck_assert_int_eq(res, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_03) {
    int res = 0;
    matrix_t A = {0};

    res = s21_create_matrix(-1, 1, &A);
    ck_assert_int_eq(res, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_04) {
    int res = 0;
    matrix_t A = {0};

    s21_remove_matrix(&A);
    res = s21_create_matrix(1, 1, &A);
    ck_assert_int_eq(res, OK);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_remove_matrix_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(res, OK);
}
END_TEST



Suite *suite_create_matrix(void) {
    Suite *s = suite_create("suite_create_matrix");
    TCase *tc = tcase_create("case_create_matrix");

    tcase_add_test(tc, create_matrix_01);
    tcase_add_test(tc, create_matrix_02);
    tcase_add_test(tc, create_matrix_03);
    tcase_add_test(tc, create_matrix_04);
    tcase_add_test(tc, s21_remove_matrix_01);

    suite_add_tcase(s, tc);
    return s;
}