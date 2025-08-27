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
        
    int result_code = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; result_code == OK && i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[j][i] = A->matrix[i][j];
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
    if (incorrect_matrix(A) || result == NULL) 
        return INCORRECT_MATRIX;
    int result_code = OK;
    if ((A->rows != A->columns) || inf_or_nan(A))
        result_code = CALCULATION_ERROR;
    
    
    matrix_t minor = {0};
    if (result_code == OK)
        result_code = s21_create_matrix(A->rows, A->columns, result);
    
    if (result_code == OK && A->rows == 1) {
        result->matrix[0][0] = A->matrix[0][0];
    } else if (result_code == OK) {
        result_code = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

        for (int i = 0; result_code == OK && i < A->rows; i++)
            for (int j = 0; j < A->columns; j++) {
                create_matrix_minor(A, i, j, &minor);
                s21_determinant(&minor, &result->matrix[i][j]);
                result->matrix[i][j] *= ((i + j) % 2) ? -1.0 : 1.0;
            }

        s21_remove_matrix(&minor);
    }
    if (result_code != OK)
        s21_remove_matrix(result);

    return result_code;
}

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);