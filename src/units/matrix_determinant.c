#include "../s21_matrix.h"

void matrix_swap_rows(matrix_t *A, int from, int to) {
    double *ptr;
    ptr = A->matrix[from];
    A->matrix[from] = A->matrix[to];
    A->matrix[to] = ptr;
}

// вычитание строки row1 из row2 c умножением первой строки на число.
void matrix_sub_rows_with_factor(matrix_t *A, int row1, int row2, double factor) {
    for (int i = 0; i < A->columns; i++)
        A->matrix[row2][i] -= A->matrix[row1][i] * factor;
}

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result) {
    if (incorrect_matrix(A))
        return INCORRECT_MATRIX;
    int result_code = (A->rows == A->columns) ? OK : CALCULATION_ERROR;

    matrix_t triangle = {0};
    if (result_code == OK) 
        result_code = s21_create_matrix(A->rows, A->columns, &triangle);   

    if (result_code == OK) 
        for(int i = 0; i < A->rows; i++)
            for(int j = 0; j < A->columns; j++)
                triangle.matrix[i][j] = A->matrix[i][j];

    *result = 1;
    //движемся по главной диагонали
    for (int i = 0; result_code == OK && i < triangle.columns - 1; i++) {
        for (int j = i + 1;  j < triangle.rows; j++) {
            if (is_zero(triangle.matrix[i][i]) && !is_zero(triangle.matrix[j][i])) {
                matrix_swap_rows(&triangle,i,j);
                *result = -(*result);
            } else if (!is_zero(triangle.matrix[j][i])) {
                matrix_sub_rows_with_factor(&triangle, i, j, triangle.matrix[j][i] / triangle.matrix[i][i]);                
            }
        }
    }

    for(int i = 0; i < triangle.columns; i++)
        (*result) *= triangle.matrix[i][i];

    s21_remove_matrix(&triangle);
    return result_code;
}