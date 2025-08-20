#include "../s21_matrix.h"

void sum_sub(matrix_t *A, matrix_t *B, matrix_t *result, int operation) {
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (operation == 0)
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            else
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
    }
}

int simple_arithmetic(matrix_t *A, matrix_t *B, matrix_t *result, int operation) {
    if (incorrect_matrix(A) || incorrect_matrix(B)) return INCORRECT_MATRIX;
    
    int res = OK;
    if (not_equal_size(A, B) || inf_or_nan(A) || inf_or_nan(B)) {
        res = CALCULATION_ERROR;
    } else {
        res = s21_create_matrix(A->rows, A->columns, result);
        if (res == OK) {
            sum_sub(A, B, result, operation);
        }
    }
    
    return res;
}

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    return simple_arithmetic(A, B, result, 0);
}

// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result){
    return simple_arithmetic(A, B, result, 1);
}

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    if (incorrect_matrix(A)) return INCORRECT_MATRIX;
    
    int res = OK;
    if (inf_or_nan(A)) {
        res = CALCULATION_ERROR;
    } else {
        res = s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows && res == OK; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    }
    
    return res;
}

// Умножение матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);