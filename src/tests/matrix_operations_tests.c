#include "tests_matrix.h"

START_TEST(test_determinant_01) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(1, 1, &A);

    A.matrix[0][0] = 10.1234;
    
    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, OK);
    ck_assert_float_eq(det, 10.1234);
}
END_TEST

START_TEST(test_determinant_02) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(2, 2, &A);

    FILL_MATRIX(A, {1, 2, 
                    3, 4});
    
    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);
    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, OK);
    ck_assert_float_eq(det, -2);
}
END_TEST

START_TEST(test_determinant_03) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(4, 4, &A);

    FILL_MATRIX(A, {1, 2, 3, 4, 
                    4, 5 , 6, 7,
                    7, 55, 66, 8,
                    6, 8, 12, 15});
    
    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, OK);
    ck_assert_float_eq(det, -525);
}
END_TEST

START_TEST(test_determinant_04) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(4, 4, &A);

    FILL_MATRIX(A, {1.11, 2.32, 3.34, 4.01, 
                    4, 5.66 , 1.33, 7.77,
                    7.32, 55.1, 66.12, 8.75,
                    6.12, 8, 12, 15});
    
    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, OK);
    ck_assert_float_eq(det, -2763.454915);
}
END_TEST

START_TEST(test_determinant_05) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(4, 4, &A);

    FILL_MATRIX(A, {1.11, 2.32, 3.34, 4.01, 
                    4, 5 , 1, 7,
                    7, 55, 66, 8,
                    6, 8, 12, 15});
    
    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, OK);
    ck_assert_float_eq(det, -2419.77);
}
END_TEST

START_TEST(test_determinant_06) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(4, 4, &A);

    FILL_MATRIX(A, {111, 232, 334, 401, 
                    401, 566 , 133, 777,
                    732, 551, 661, 875,
                    612, 8, 12, 15});
    
    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, OK);
    ck_assert_float_eq(det, -3760377867); // -3760377867.000009
}
END_TEST

START_TEST(test_determinant_07) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(4, 4, &A);

    FILL_MATRIX(A, {1.001, 2.002, 3.003, 4.004, 
                    4.1, 5.2 , 1.1, 7.1,
                    7, 55, 66, 8,
                    6, 8, 12, 15});
    
    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, OK);
    ck_assert_float_eq(det, -2842.84);
}
END_TEST

START_TEST(test_determinant_08) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(4, 4, &A);

    FILL_MATRIX(A, {123, 456, 789, 123, 
                    456, 79 , 123, 456,
                    789, 13, 46, 789,
                    123, 46, 789, 13});
    
    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, OK);
    ck_assert_float_eq(det, 1051961460); // 1051961459.999996
}
END_TEST

START_TEST(test_determinant_09) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(1, 3, &A);

    FILL_MATRIX(A, {1, 2, 3});
    
    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, CALCULATION_ERROR);
}
END_TEST

START_TEST(test_determinant_10) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_determinant_11) {
    int res_create = 0;
    int res_determ = 0;
    double det = 0;
    matrix_t A = {0};

    res_create = s21_create_matrix(4, 4, &A);

    FILL_MATRIX(A, {0, 2, 3, 4, 
                    5, 6 , 7, 8,
                    9, 10, 11, 12,
                    13, 14, 15, 16});

    res_determ = s21_determinant(&A, &det);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_create, OK);
    ck_assert_int_eq(res_determ, OK);
    ck_assert_float_eq(det, 0);
}
END_TEST


//  ======================================================================== //



START_TEST(test_eq_matrix_01) {
    int res_func = 0;
    matrix_t A = {0};
    matrix_t B = {0};

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);

    FILL_MATRIX(A, {1.0000001, 2.0000001, 3.0000001, 4.0000001});
    FILL_MATRIX(B, {1.0000001, 2.0000001, 3.0000001, 4.0000001});
    
    res_func = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    ck_assert_int_eq(res_func, SUCCESS);
}
END_TEST

START_TEST(test_eq_matrix_02) {
    int res_func = 0;
    matrix_t A = {0};
    matrix_t B = {0};

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);

    FILL_MATRIX(A, {0.0000001, 0.0000001, 0.0000001, 0.0000001});
    FILL_MATRIX(B, {0.0000002, 0.0000002, 0.0000002, 0.0000002});
    
    res_func = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    ck_assert_int_eq(res_func, SUCCESS);
}
END_TEST

START_TEST(test_eq_matrix_03) {
    int res_func = 0;
    matrix_t A = {0};
    matrix_t B = {0};

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);

    FILL_MATRIX(A, {0.0000011, 0.0000001, 0.0000001, 0.0000001});
    FILL_MATRIX(B, {0.0000002, 0.0000002, 0.0000002, 0.0000002});
    
    res_func = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    ck_assert_int_eq(res_func, FAILURE);
}
END_TEST

START_TEST(test_eq_matrix_04) {
    int res_func = 0;
    matrix_t A = {0};
    matrix_t B = {0};

    s21_create_matrix(20, 20, &A);
    s21_create_matrix(20, 20, &B);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            A.matrix[i][j] = B.matrix[i][j] = get_rand(MIN_DOUBLE, MAX_DOUBLE);
        }
    }
    
    res_func = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    ck_assert_int_eq(res_func, SUCCESS);
}
END_TEST

START_TEST(test_eq_matrix_05) {
    int res_func = 0;
    matrix_t A = {0};
    matrix_t B = {0};

    s21_create_matrix(20, 20, &A);
    s21_create_matrix(20, 20, &B);
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            A.matrix[i][j] = B.matrix[i][j] = get_rand(MIN_DOUBLE, MAX_DOUBLE);
        }
    }
    B.matrix[19][10] += 0.000001;

    res_func = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    ck_assert_int_eq(res_func, FAILURE);
}
END_TEST

START_TEST(test_eq_matrix_06) {
    int res_func = 0;
    matrix_t A = {0};
    matrix_t B = {0};

    s21_create_matrix(2, 2, &A);
    s21_create_matrix(3, 2, &B);
     
    res_func = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);

    ck_assert_int_eq(res_func, FAILURE);
}
END_TEST

START_TEST(test_eq_matrix_07) {
    int res_func = 0;
    matrix_t A = {0};
    matrix_t B = {0};

    s21_create_matrix(2, 2, &A);
     
    res_func = s21_eq_matrix(&A, &B);
    s21_remove_matrix(&A);

    ck_assert_int_eq(res_func, FAILURE);
}
END_TEST

Suite *suite_determinant(void) {
    Suite *s = suite_create("suite_determinant");
    TCase *tc = tcase_create("case_determinant");

    tcase_add_test(tc, test_determinant_01);
    tcase_add_test(tc, test_determinant_02);
    tcase_add_test(tc, test_determinant_03);
    tcase_add_test(tc, test_determinant_04);
    tcase_add_test(tc, test_determinant_05);
    tcase_add_test(tc, test_determinant_06);
    tcase_add_test(tc, test_determinant_07);
    tcase_add_test(tc, test_determinant_08);
    tcase_add_test(tc, test_determinant_09);
    tcase_add_test(tc, test_determinant_10);
    tcase_add_test(tc, test_determinant_11);

    suite_add_tcase(s, tc);
    return s;
}

Suite *suite_eq_matrix(void) {
    Suite *s = suite_create("suite_eq_matrix");
    TCase *tc = tcase_create("case_eq_matrix");

    tcase_add_test(tc, test_eq_matrix_01);
    tcase_add_test(tc, test_eq_matrix_02);
    tcase_add_test(tc, test_eq_matrix_03);
    tcase_add_test(tc, test_eq_matrix_04);
    tcase_add_test(tc, test_eq_matrix_05);
    tcase_add_test(tc, test_eq_matrix_06);
    tcase_add_test(tc, test_eq_matrix_07);

    suite_add_tcase(s, tc);
    return s;
}