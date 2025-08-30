#ifndef S21_MATRIX_H
#define S21_MATRIX_H
// This project made by woodsjul

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCALE_FACTOR_6B 1E+06
#define EPSILON_5E_07 5E-07
#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef enum { OK = 0, INCORRECT_MATRIX = 1, CALCULATION_ERROR = 2 } res_code;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Вспомогательные функции
int incorrect_matrix(matrix_t *A);
int is_zero(double x);
int not_equal_size(matrix_t *A, matrix_t *B);
int equal_to_6_decimal(double a, double b);
int inf_or_nan(matrix_t *A);

// This project made by woodsjul
#endif