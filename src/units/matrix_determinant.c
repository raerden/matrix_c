#include "../s21_matrix.h"

// 1 если в матрице есть строка или столбец из нулей
int is_zero_row_or_col(matrix_t *A) {
    int res = 0;
    for (int i = 0; i < A->rows; i++) {
        double sum = 0;
        for (int j = 0; res == 0 && j < A->columns; j++)
            sum += A->matrix[i][j];
        if (sum == 0) res = 1;
    }
    for (int j = 0; res == 0 && j < A->columns; j++) {
        double sum = 0;
        for (int i = 0; res == 0 && i < A->rows; i++)
            sum += A->matrix[i][j];
        if (sum == 0) res = 1;
    }
    return res;
}

// 1 если матрица верхнетреугольная
int is_triangle_matrix(matrix_t *A) {
    int res = 1;
    for (int j = 0; j < A->columns && res == 1; j++) {
        int i = j + 1;
        while(i < A->rows && res == 1) {
            if (A->matrix[i][j] != 0) 
                res = 0;
            i++;
        }
    }
    return res;
}

void matrix_swap_rows(matrix_t *A, int from, int to) {
    double *ptr;
    ptr = A->matrix[from];
    A->matrix[from] = A->matrix[to];
    A->matrix[to] = ptr;
}

double matrix_prime_diag_mul(matrix_t *A) {
    double res = A->matrix[0][0];
    for (int i = 1; i < A->rows; i++)
        res *= A->matrix[i][i];
    return res;
}

void copy_matrix(matrix_t *A, matrix_t *B) {
    B->rows = A->rows;
    B->columns = A->columns;
    for (int i = 0; i < A->rows; i++) 
        for (int j = 0; j < A->columns; j++) 
            B->matrix[i][j] = A->matrix[i][j];
}

// найдет следующую строку ниже текущей с ненулевым элементов в указанном index столбце
int find_next_nonzero_row(matrix_t *A, int index) {
    int res = index;
    for (int i = index + 1; i < A->rows; i++) 
        if (A->matrix[i][index] != 0) {
            res = i;
            i = A->rows;
        }
    return res;
}

// вычитание строки row1 из row2 c умножением первой строки на число.
void matrix_sub_rows_with_factor(matrix_t *A, int row1, int row2, double factor) {
    for (int i = 0; i < A->columns; i++)
        A->matrix[row2][i] -= A->matrix[row1][i] * factor;
}

int calc_determ_by_matrixU(matrix_t *A, double *det) {
    matrix_t U = {0};
    int result_code = s21_create_matrix(A->rows, A->columns, &U);
    int sign = 1;
    *det = 1;
    if (result_code == OK) copy_matrix(A, &U);

    //движемся по главной диагонали
    for (int index = 0; result_code == OK && *det != 0 && index < U.columns - 1; index++) {
        int next_nonzero_row = find_next_nonzero_row(&U,index);

        // 0 - на главной диагонали! Найти ниже строку с не 0 эементом и поменять строки местами
        if (U.matrix[index][index] == 0) {
            if (index == next_nonzero_row) {
                *det = 0;
            } else {
                sign = -sign;
                matrix_swap_rows(&U, index, next_nonzero_row);
                next_nonzero_row = find_next_nonzero_row(&U,index);
            }
        }

        for (int row = index + 1; *det != 0 && row < U.rows; row++) {
            if (U.matrix[row][index] != 0) {
                //вычитаем строки с умножением
                matrix_sub_rows_with_factor(&U, index, row, U.matrix[row][index] / U.matrix[index][index]);
            }
        }
    }
    if (*det != 0)
        *det = matrix_prime_diag_mul(&U) * sign;
    s21_remove_matrix(&U);
    return result_code;
}

// Определитель для небольших матриц
double calc_determinant1_2_3(matrix_t *A) {
    double det;
    if (A->rows == 1) {
        det = A->matrix[0][0];
    }
    else if (A->rows == 2) {
        det = A->matrix[0][0] * A->matrix[1][1] - \
              A->matrix[0][1] * A->matrix[1][0];
    }
    else if (A->rows == 3) {
        // по правилу треугольника (Саррюса)
        det = (A->matrix[0][0] * A->matrix[1][1] * A->matrix[2][2] + \
               A->matrix[0][1] * A->matrix[1][2] * A->matrix[2][0] + \
               A->matrix[0][2] * A->matrix[1][0] * A->matrix[2][1])- \
              (A->matrix[0][2] * A->matrix[1][1] * A->matrix[2][0] + \
               A->matrix[0][0] * A->matrix[1][2] * A->matrix[2][1] + \
               A->matrix[0][1] * A->matrix[1][0] * A->matrix[2][2]);
    }
    return det;
}

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result) {
    if (incorrect_matrix(A))
        return INCORRECT_MATRIX;
    int result_code = (A->rows == A->columns) ? OK : CALCULATION_ERROR;

    // если хоть одна строка или столбец равны 0 то определитель равен 0
    int zerocol = 0;
    if (is_zero_row_or_col(A)) {
        *result = 0;
        zerocol = 1;
    }

    // Считаем определитель для небольших матриц до 3х3
    if (zerocol == 0 && A->rows < 4) {
        *result = calc_determinant1_2_3(A);
    } else if (zerocol == 0) {
        // Если матрица верхнетреугольная, то можно сразу посчитать определитель
        if (is_triangle_matrix(A))
            *result = matrix_prime_diag_mul(A);
        else {
            // Считаем определитель через формирование верхнетреугольной матрицы
            result_code = calc_determ_by_matrixU(A, result);
        }
    }
    return result_code;
}


/*
int calc_determ_by_matrixU(matrix_t *A, double *det) {
    matrix_t U = {0};
    int result_code = s21_create_matrix(A->rows, A->columns, &U);
    int sign = 1;
    *det = 1;
    if (result_code == OK) copy_matrix(A, &U);

    for (int index = 0; result_code == OK && *det != 0 && index < U.columns - 1; index++) {
        printf("-For index        ");
        printf("[%d][%d]= %.2f\n", index, index, U.matrix[index][index]);

        int next_nonzero_row = find_next_nonzero_row(&U,index);
        printf("next_nonzero_row");
        printf("[%d][%d]= %.2f\n", next_nonzero_row, index, U.matrix[next_nonzero_row][index]);

        // 0 - на главной диагонали. Найти ниже строку не 0 и поменять местами
        if (U.matrix[index][index] == 0) {
            printf("0 на главной диагонали\n");
            if (index == next_nonzero_row) {
                printf("все элементы в столбце, начиная с диагонального, равны 0\n");
                *det = 0;
            } else {
                printf("Переставим строки %d, %d\n", index, next_nonzero_row);
                sign = -sign;
                matrix_swap_rows(&U, index, next_nonzero_row);
                next_nonzero_row = find_next_nonzero_row(&U,index);
                print_matrix(&U,1);
                printf("next_nonzero_row");
                printf("[%d][%d]= %.2f\n", next_nonzero_row, index, U.matrix[next_nonzero_row][index]);
            }
        }

        // идем с нижней строки наверх. Вычитаем текущую строку от ненулевых
        printf("идем со следующей строки вниз\n");
        for (int row = index + 1; *det != 0 && row < U.rows; row++) {
            printf("[%d][%d] = %.2f", row, index, U.matrix[row][index]);
            if (U.matrix[row][index] != 0) {
                //вычитаем строки с умножением
                printf(" вычитаем строку %d из %d умножением на %.2f", index, row, U.matrix[row][index] / U.matrix[index][index]);
                matrix_sub_rows_with_factor(&U, index, row, U.matrix[row][index] / U.matrix[index][index]);
                print_matrix(&U,1);
            }
            printf("\n");
        }
    printf("\n");
    }
   
    printf("Верхнетреугольная матрица:\n");
    print_matrix(&U, 1);
    printf("определитель %d sign=%d\n", (int)matrix_prime_diag_mul(&U) * sign, sign);
    if (*det != 0)
        *det = matrix_prime_diag_mul(&U) * sign;
    s21_remove_matrix(&U);
    return result_code;
}
*/