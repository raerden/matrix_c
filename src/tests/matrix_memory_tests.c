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

#ifdef TEST_MEMORY_FAILURE
START_TEST(create_matrix_05) {
    int res = 0;
    matrix_t A = {0};
    res = s21_create_matrix(666, 1, &A);
    ck_assert_int_eq(res, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_matrix_06) {
    int res = 0;
    matrix_t A = {0};
    res = s21_create_matrix(777, 1, &A);
    ck_assert_int_eq(res, INCORRECT_MATRIX);
    s21_remove_matrix(&A);
}
END_TEST
#endif



START_TEST(s21_remove_matrix_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_matrix_02) {
  s21_remove_matrix(NULL);
}
END_TEST



Suite *suite_create_matrix(void) {
    Suite *s = suite_create("suite_create_matrix");
    TCase *tc = tcase_create("case_create_matrix");

    tcase_add_test(tc, create_matrix_01);
    tcase_add_test(tc, create_matrix_02);
    tcase_add_test(tc, create_matrix_03);
    tcase_add_test(tc, create_matrix_04);
#ifdef TEST_MEMORY_FAILURE
    tcase_add_test(tc, create_matrix_05);
    tcase_add_test(tc, create_matrix_06);
#endif
    tcase_add_test(tc, s21_remove_matrix_01);
    tcase_add_test(tc, s21_remove_matrix_02);

    suite_add_tcase(s, tc);
    return s;
}