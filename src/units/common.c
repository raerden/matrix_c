#include "../s21_matrix.h"
#include <string.h>

void print_matrix(matrix_t *A, int dec) {
    if (A == NULL || A->matrix == NULL) {
        printf("print_matrix: Matrix is NULL\n");
        return;
    }

    unsigned max_value_length = 0;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (max_value_length < A->matrix[i][j]) {
                if (dec)
                    max_value_length = (unsigned)snprintf(NULL, 0, "%.0lf", A->matrix[i][j]);
                else 
                    max_value_length = (unsigned)snprintf(NULL, 0, "%.7lf", A->matrix[i][j]);
            }
        }
    }

    printf("    Matrix (%d x %d):\n", A->rows, A->columns);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (dec)
                printf("%*.0lf ", max_value_length, A->matrix[i][j]);
            else
                printf("%*.7lf ", max_value_length + 1, A->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int incorrect_matrix(matrix_t *A) {
    int result_code = (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0);
    for (int i = 0; i < A->rows && result_code == 0; i++)
        if (A->matrix[i] == NULL)
            result_code = 1;
    return result_code;
}

int is_zero(double x) {
    return fabs(x) < 1e-6;
}

int not_equal_size(matrix_t *A, matrix_t *B) {
    return A->rows != B->rows || A->columns != B->columns;
}

int equal_to_6_decimal(double a, double b) {
    int res = trunc(a * SCALE_FACTOR_6B) == trunc(b * SCALE_FACTOR_6B);
    if (!res) {
        double diff = a - b;
        if (b > a) diff = b - a;
        res = diff <= EPSILON_5E_07 ? SUCCESS : FAILURE;
    }
    return res;
}

int inf_or_nan(matrix_t *A) {
    int result_code = 0;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
                result_code = 1;
                j = A->columns;
                i = A->rows;
            }
        }
    }
    return result_code;
}