#include "../s21_matrix.h"
#include <string.h>

void print_matrix(matrix_t *A) {
    if (A == NULL || A->matrix == NULL) {
        printf("print_matrix: Matrix is NULL\n");
        return;
    }

    unsigned max_value_length = 0;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (max_value_length < A->matrix[i][j])
                max_value_length = (unsigned)snprintf(NULL, 0, "%lf", A->matrix[i][j]);
        }
    }

    printf("Matrix (%d x %d):\n", A->rows, A->columns);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            printf("%*lf ", max_value_length, A->matrix[i][j]);
        }
        printf("\n");
    }
}

int not_equal_size(matrix_t *A, matrix_t *B) {
    return A->rows != B->rows || A->columns != B->columns;
}

int incorrect_matrix(matrix_t *A) {
    return A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0;
}

int equal_to_6_decimal(double a, double b) {
    return trunc(a * 1e6) == trunc(b * 1e6);
}

int inf_or_nan(matrix_t *A) {
    int res = 0;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
                res = 1;
                j = A->columns;
                i = A->rows;
            }
        }
    }
    return res;
}