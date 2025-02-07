#ifndef MATRIX
#define MATRIX

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0
/*
Все операции (кроме сравнения матриц) должны возвращать результирующий код:
- 0 - OK
- 1 - Ошибка, некорректная матрица
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
нельзя провести вычисления и т.д.)
*/

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// custom functions
int s21_create_minor_matrix(int rows, int columns, matrix_t src,
                            matrix_t *result);
double s21_twoDimMinor(matrix_t mat);
double s21_sumDetAllLevelMinors(matrix_t mat);  //вся подкапотная детерминанта

// trashy functions
void printMatrix(matrix_t matrix);
// void fillMatrix(matrix_t *matrix, double a, double b,
//                 double c);  // a*i + b*j + c;


#endif  // MATRIX