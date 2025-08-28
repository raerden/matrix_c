#include "../s21_matrix.h"

int incorrect_matrix(matrix_t *A) {
    int result_code = (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0);
    for (int i = 0; i < A->rows && result_code == 0; i++)
        if (A->matrix[i] == NULL)
            result_code = 1;
    return result_code;
}

int is_zero(double x) {
    return fabs(x) < EPSILON_5E_07;
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