#include "../s21_matrix.h"

// Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    if (incorrect_matrix(A) || incorrect_matrix(B) || not_equal_size(A, B)) {
        return FAILURE;
    }
    int result_code = SUCCESS;
    for (int i = 0; i < A->rows && result_code == SUCCESS; i++) {
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
    if (incorrect_matrix(A) || result == NULL) 
        return INCORRECT_MATRIX;

    int result_code = OK;
    result_code = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; result_code == OK && i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[j][i] = A->matrix[i][j];
    return result_code;
}

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);