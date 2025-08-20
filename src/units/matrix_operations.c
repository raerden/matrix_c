#include "../s21_matrix.h"

// Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    if (incorrect_matrix(A) || incorrect_matrix(B) || not_equal_size(A, B)) {
        return FAILURE;
    }
    int res = SUCCESS;
    for (int i = 0; i < A->rows && res == SUCCESS; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (!(equal_to_6_decimal(A->matrix[i][j], B->matrix[i][j]))) {
                res = FAILURE;
                j = A->columns;
                i = A->rows;
            }
        }
    }
    return res;
}

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);