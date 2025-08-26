#include "../s21_matrix.h"

// Создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result) {
    if (rows <= 0 || columns <= 0 || result == NULL) {
        return INCORRECT_MATRIX;
    }

    int result_code = OK;
#ifdef TEST_MEMORY_FAILURE
    if (rows == 666)
        result->matrix = NULL;
    else
        result->matrix = (double **)calloc(rows, sizeof(double *));
#else
    result->matrix = (double **)calloc(rows, sizeof(double *));
#endif
    if (result->matrix == NULL) {
        result_code = INCORRECT_MATRIX;
    }

    int columns_allocated = 0;
    for (int i = 0; i < rows && result_code == OK; i++) {
#ifdef TEST_MEMORY_FAILURE
    if (rows == 777 && i > 0) 
        result->matrix[i] = NULL;
    else 
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
#else
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
#endif
        if (result->matrix[i] == NULL) {
            result_code = INCORRECT_MATRIX;
        }
        columns_allocated++;
    }

    if (result_code != OK) {
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

    return result_code;
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