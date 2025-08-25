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
                    max_value_length = (unsigned)snprintf(NULL, 0, "%lf", A->matrix[i][j]);
            }
        }
    }

    printf("    Matrix (%d i %d):\n", A->rows, A->columns);
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (dec)
                printf("%*.0lf ", max_value_length, A->matrix[i][j]);
            else
                printf("%*lf ", max_value_length, A->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int not_equal_size(matrix_t *A, matrix_t *B) {
    return A->rows != B->rows || A->columns != B->columns;
}

int incorrect_matrix(matrix_t *A) {
    int result_code = (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0);
    for (int i = 0; i < A->rows && result_code == 0; i++)
        if (A->matrix[i] == NULL)
            result_code = 1;
    return result_code;
}

double trunc_to_6(double a) {
    return trunc(fabs(a) * SCALE_FACTOR_6 + ROUNDING_CORRECTION);
}

int equal_to_6_decimal(double a, double b) {
    return trunc_to_6(a) == trunc_to_6(b);
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

// Создает новую матрицу n-1. Вырезаем из исходной указанный row, column
int remove_row_column(matrix_t *A, int i, int j, matrix_t *M) {
    int result_code = OK;
    result_code = s21_create_matrix(A->rows - 1, A->rows - 1, M);
    int iM = 0;
    for (int x = 0; result_code == OK && x < A->rows; x++) {
        int jM = 0;
        for (int y = 0; y < A->columns && x != i; y++) {
            if (y != j) {
                M->matrix[iM][jM] = A->matrix[x][y];
                jM++;
            }
        }
        if (x != i) iM++;
    }
    return result_code;
}