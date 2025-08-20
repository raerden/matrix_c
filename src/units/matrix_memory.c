#include "../s21_matrix.h"

// Создание матриц 
int s21_create_matrix(int rows, int columns, matrix_t *result) {
    if (rows <= 0 || columns <= 0 || result == NULL) {
        return INCORRECT_MATRIX;
    }

    int res = OK;
    result->matrix = (double **)calloc(rows, sizeof(double *));

    if (result->matrix == NULL) {
        res = INCORRECT_MATRIX;
    }

    int columns_allocated = 0;
    for (int i = 0; i < rows && res == OK; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
            res = INCORRECT_MATRIX;
        }
        columns_allocated++;
    }

    if (res != OK) {
        for (int i = 0; i < columns_allocated; i++) {
            if (result->matrix[i] != NULL) {
                free(result->matrix[i]);
                result->matrix[i] = NULL;
            }
        }
        free(result->matrix);
        result->matrix = NULL;
        result->rows = 0;
        result->columns = 0;
    } else {
        result->rows = rows;
        result->columns = columns;
    }

    return res;
}

// Очистка матрицы
void s21_remove_matrix(matrix_t *A) {
    if (A == NULL) {
        return;
    }

    if (A->matrix != NULL) {
        for (int i = 0; i < A->rows; i++) {
            if (A->matrix[i] != NULL) {
                free(A->matrix[i]);
                A->matrix[i] = NULL;
            }
        }
        free(A->matrix);
        A->matrix = NULL;
    }
    A->rows = 0;
    A->columns = 0;
}