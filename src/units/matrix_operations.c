#include "../s21_matrix.h"

// Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (incorrect_matrix(A) || incorrect_matrix(B)) {
    return FAILURE;
  }
  int result_code = not_equal_size(A, B) ? FAILURE : SUCCESS;
  for (int i = 0; result_code == SUCCESS && i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (!(equal_to_6_decimal(A->matrix[i][j], B->matrix[i][j]))) {
        result_code = FAILURE;
        j = A->columns;
        i = A->rows;
      }
    }
  }
  return result_code;
}

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (incorrect_matrix(A) || result == NULL) return INCORRECT_MATRIX;

  int result_code = s21_create_matrix(A->columns, A->rows, result);
  for (int i = 0; result_code == OK && i < A->rows; i++)
    for (int j = 0; j < A->columns; j++) result->matrix[j][i] = A->matrix[i][j];
  return result_code;
}

void matrix_swap_rows(matrix_t *A, int from, int to) {
  double *ptr;
  ptr = A->matrix[from];
  A->matrix[from] = A->matrix[to];
  A->matrix[to] = ptr;
}

// вычитание строки row1 из row2 c умножением первой строки на число.
void matrix_sub_rows_with_factor(matrix_t *A, int row1, int row2,
                                 double factor) {
  for (int i = 0; i < A->columns; i++)
    A->matrix[row2][i] -= A->matrix[row1][i] * factor;
}

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result) {
  if (incorrect_matrix(A)) return INCORRECT_MATRIX;
  int result_code = (A->rows == A->columns) ? OK : CALCULATION_ERROR;

  matrix_t triangle = {0};
  if (result_code == OK)
    result_code = s21_create_matrix(A->rows, A->columns, &triangle);

  if (result_code == OK)
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        triangle.matrix[i][j] = A->matrix[i][j];

  *result = 1;
  // движемся по главной диагонали
  for (int i = 0; result_code == OK && i < triangle.columns - 1; i++) {
    for (int j = i + 1; j < triangle.rows; j++) {
      if (is_zero(triangle.matrix[i][i]) && !is_zero(triangle.matrix[j][i])) {
        matrix_swap_rows(&triangle, i, j);
        *result = -(*result);
      } else if (!is_zero(triangle.matrix[j][i])) {
        matrix_sub_rows_with_factor(
            &triangle, i, j, triangle.matrix[j][i] / triangle.matrix[i][i]);
      }
    }
  }

  for (int i = 0; i < triangle.columns; i++) (*result) *= triangle.matrix[i][i];

  s21_remove_matrix(&triangle);
  return result_code;
}

// копируем в матрицу M ячейки из A без указанной row и column
void create_matrix_minor(matrix_t *A, int iR, int jR, matrix_t *M) {
  int iM = 0;
  for (int i = 0; i < A->rows; i++) {
    int jM = 0;
    for (int j = 0; j < A->columns && i != iR; j++) {
      if (j != jR) {
        M->matrix[iM][jM] = A->matrix[i][j];
        jM++;
      }
    }
    if (i != iR) iM++;
  }
}

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (incorrect_matrix(A) || result == NULL) return INCORRECT_MATRIX;
  int result_code = OK;
  if ((A->rows != A->columns) || inf_or_nan(A)) result_code = CALCULATION_ERROR;

  matrix_t minor = {0};
  if (result_code == OK)
    result_code = s21_create_matrix(A->rows, A->columns, result);

  if (result_code == OK && A->rows == 1) {
    result->matrix[0][0] = 1.0;
  } else if (result_code == OK) {
    result_code = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

    for (int i = 0; result_code == OK && i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        create_matrix_minor(A, i, j, &minor);
        result_code = s21_determinant(&minor, &result->matrix[i][j]);
        result->matrix[i][j] *= ((i + j) % 2) ? -1.0 : 1.0;
      }

    s21_remove_matrix(&minor);
  }
  if (result_code != OK) s21_remove_matrix(result);

  return result_code;
}

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (incorrect_matrix(A) || result == NULL) return INCORRECT_MATRIX;
  int result_code = (A->rows == A->columns) ? OK : CALCULATION_ERROR;
  double det = 0;
  if (result_code == OK) result_code = s21_determinant(A, &det);
  if (result_code != OK || is_zero(det)) result_code = CALCULATION_ERROR;
  if (result_code == OK) {
    matrix_t complements = {0};
    matrix_t complements_t = {0};
    result_code = s21_calc_complements(A, &complements);
    if (result_code == OK)
      result_code = s21_transpose(&complements, &complements_t);
    if (result_code == OK)
      result_code = s21_mult_number(&complements_t, 1.0 / det, result);
    s21_remove_matrix(&complements);
    s21_remove_matrix(&complements_t);
  }
  return result_code;
}