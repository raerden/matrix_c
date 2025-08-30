#ifndef SRC_TESTS_MATRIX_H_
#define SRC_TESTS_MATRIX_H_

#include <check.h>
#include <time.h>

#include "../s21_matrix.h"
// #include <unistd.h>

// для заполнения матриц значениями.
#define FILL_MATRIX(mat, ...)                         \
  do {                                                \
    double temp[] = __VA_ARGS__;                      \
    long unsigned index = 0;                          \
    for (int x = 0; x < (mat).rows; x++) {            \
      for (int y = 0; y < (mat).columns; y++) {       \
        if (index < sizeof(temp) / sizeof(temp[0])) { \
          (mat).matrix[x][y] = temp[index++];         \
        }                                             \
      }                                               \
    }                                                 \
  } while (0)

#define MAX_DOUBLE 1.79769e+6
#define MIN_DOUBLE 2.22507e-6

Suite *suite_create_matrix(void);
Suite *suite_transpose_matrix(void);
Suite *suite_eq_matrix(void);
Suite *suite_arithmetic_matrix(void);
Suite *suite_calc_complements(void);
Suite *suite_determinant(void);
Suite *suite_inverse_matrix(void);

void testcases(Suite *testcase);
double get_rand(double min, double max);

#endif