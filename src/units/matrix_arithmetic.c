#include "../s21_matrix.h"

void sum_sub(matrix_t *A, matrix_t *B, matrix_t *result, int operation) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (operation)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      else
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
}

int simple_arithmetic(matrix_t *A, matrix_t *B, matrix_t *result,
                      int operation) {
  if (incorrect_matrix(A) || incorrect_matrix(B) || result == NULL)
    return INCORRECT_MATRIX;

  int result_code = OK;
  if (not_equal_size(A, B) || inf_or_nan(A) || inf_or_nan(B)) {
    result_code = CALCULATION_ERROR;
  } else {
    result_code = s21_create_matrix(A->rows, A->columns, result);
    if (result_code == OK) {
      sum_sub(A, B, result, operation);
    }
  }

  return result_code;
}

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return simple_arithmetic(A, B, result, 1);
}

// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return simple_arithmetic(A, B, result, 0);
}

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (incorrect_matrix(A) || result == NULL) return INCORRECT_MATRIX;

  int result_code = OK;
  if (inf_or_nan(A)) {
    result_code = CALCULATION_ERROR;
  } else {
    result_code = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && result_code == OK; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return result_code;
}

// Умножение матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (incorrect_matrix(A) || incorrect_matrix(B) || result == NULL)
    return INCORRECT_MATRIX;

  int result_code = OK;

  if (A->rows != B->columns || inf_or_nan(A) || inf_or_nan(B)) {
    result_code = CALCULATION_ERROR;
  } else {
    result_code = s21_create_matrix(A->rows, B->columns, result);
  }

  for (int i = 0; result_code == OK && i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < B->rows; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return result_code;
}