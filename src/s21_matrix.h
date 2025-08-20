#ifndef S21_MATRIX_H
#define S21_MATRIX_H
// This project made by woodsjul

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

typedef enum {
  OK = 0,
  INCORRECT_MATRIX = 1, // Ошибка, некорректная матрица;
  CALCULATION_ERROR = 2    // Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т. д.).
} res_code;

// Создание матриц 
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Очистка матрицы
void s21_remove_matrix(matrix_t *A);

// Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Вычитание матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// Умножение матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Вспомогательные функции
void print_matrix(matrix_t *A);
int incorrect_matrix(matrix_t *A);
int not_equal_size(matrix_t *A, matrix_t *B);
int equal_to_6_decimal(double a, double b);
int inf_or_nan(matrix_t *A);

#endif