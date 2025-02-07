#include "s21_matrix.h"
/*
Все операции (кроме сравнения матриц) должны возвращать результирующий код:
- 0 - OK
- 1 - Ошибка, некорректная матрица
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
нельзя провести вычисления и т.д.)
*/

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = 0;
  if (!result || (rows < 1 || columns < 1)) ret = 1;
  if (ret == 0) {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows && ret == 0; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          ret = 1;  // error
          for (int j = 0; j < i; j++) free(result->matrix[j]);
          free(result->matrix);
        }
      }
    } else
      ret = 1;  // error
  }
  return ret;
}

/*
дана матрица src и позиция ячейки для которой надо найти минор
1 3 5 4   1,1 - надо отпилить 1 строку и 1 столбец    3         1 5 4
3 5 6 6   и остатки записать в новую матрицу        3 5 6 6     2 4 5
2 3 4 5                                               3         7 7 8
7 6 7 8                                               6
*/
int s21_create_minor_matrix(int cellRow, int cellColumn, matrix_t src,
                            matrix_t *result) {
  int ret = 0;
  matrix_t mat = {0};
  if (src.rows == src.columns && src.rows > 1 && result &&
      s21_create_matrix(src.rows - 1, src.columns - 1, &mat) == 0) {
    for (int i = 0, mi = 0; mi < src.rows - 1 && i < src.rows && ret == 0;
         i++, mi++) {
      for (int j = 0, mj = 0;
           mj < src.columns - 1 && j < src.columns && ret == 0; mj++, j++) {
        // if curr row is one to avoid need ++i, so we copy cells from next row
        if (i == cellRow) {
          if (i == src.rows - 1)
            ret = 1;
          else
            ++i;
        }
        // if curr column is one to avoid
        if (j == cellColumn) {
          if (j == src.columns - 1)
            ret = 1;
          else
            ++j;
        }
        //если не вышли за границы матрицы то копируем значение
        if (ret == 0) mat.matrix[mi][mj] = src.matrix[i][j];
      }
    }
  } else
    ret = 1;
  if (ret == 0) *result = mat;
  return ret;
}

//определение детерминанта для матрицы
double s21_sumDetAllLevelMinors(matrix_t mat) {
  double ret = 0, sumComp = 0;
  int rows = mat.rows, columns = mat.columns, scale = rows;
  //находим детерминант по первой строке
  for (int i = 0; i < columns; i++) {
    scale = rows;
    matrix_t temp = mat, minor = {0};
    if (rows > 2) {
      s21_create_minor_matrix(0, i, temp, &minor);
      --scale;
      //рекурсивно находим минор младшего порядка для текущей ячейки
      if (scale > 2 && scale != rows) {
        sumComp =
            mat.matrix[0][i] * s21_sumDetAllLevelMinors(minor) * pow(-1, i);
        ret += sumComp;
      } else  //если текущая матрица 2х2
        ret += mat.matrix[0][i] * s21_twoDimMinor(minor) * pow(-1, i);
    } else  //если текущая матрица 2х2
      ret += mat.matrix[0][i] * s21_twoDimMinor(mat) * pow(-1, i);

    s21_remove_matrix(&minor);
  }
  return ret;
}

//определение детерминанта для 2х2 матрицы
double s21_twoDimMinor(matrix_t mat) {
  return (double)(mat.matrix[0][0] * mat.matrix[1][1] -
                  mat.matrix[0][1] * mat.matrix[1][0]);
}

// void printMatrix(matrix_t matrix) {
//   for (int i = 0; i < matrix.rows; i++) {
//     for (int j = 0; j < matrix.columns; j++)
//       // printf("%f ",*(*matrix.matrix + i*matrix.rows + j));
//       printf("%-10.5f ", matrix.matrix[i][j]);
//     printf("\n");
//   }
//   printf("\n");
// }

//заполнить матрицу рандомными числами
// void fillMatrix(matrix_t *matrix, double a, double b, double c) {
//   int m = matrix->rows, n = matrix->columns;
//   for (int i = 0; i < matrix->rows; i++) {
//     for (int j = 0; j < matrix->columns; j++) {
//       matrix->matrix[i][j] = 2 * i * a - pow(1, i + j) * b * j + c;
//     }
//   }
//   while (m > 1 && n > 2) {
//     matrix->matrix[m - 1][n - 1] += 1;
//     --m;
//     --n;
//   }
// }

void s21_remove_matrix(matrix_t *A) {
  //очистить память
  if (A && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
  }
}

// success = 1, failure = 0
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = (int)SUCCESS;
  if (A && A->matrix && B && B->matrix && A->columns == B->columns &&
      A->rows == B->rows) {
    int stop = 1;
    for (int i = 0; i < A->rows && stop; i++) {
      for (int j = 0; j < A->columns && stop; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
          stop = 0;
          ret = (int)FAILURE;
        }
      }
    }
  } else
    ret = (int)FAILURE;
  return ret;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (!(A && A->matrix && B && B->matrix && result))
    ret = 1;  // wrong inputs
  else if (ret == 0 && A->columns == B->columns && A->rows == B->rows) {
    int rows = A->rows, columns = A->columns;
    if (s21_create_matrix(rows, columns, result) == 0) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else
      ret = 1;  // cant allocate memory for new matrix
  } else
    ret = 2;  // wrong matrices
  return ret;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;
  if (!(A && A->matrix && B && B->matrix && result)) ret = 1;  // wrong inputs
  if (ret == 0 && A->columns == B->columns && A->rows == B->rows) {
    int rows = A->rows, columns = A->columns;
    // s21_remove_matrix(result);
    if (s21_create_matrix(rows, columns, result) == 0) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else
      ret = 1;  // cant allocate memory for new matrix
  } else if (ret != 1)
    ret = 2;  // wrong matrices
  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = 0;
  if (A && A->matrix && result) {
    int rows = A->rows, columns = A->columns;
    if (s21_create_matrix(rows, columns, result) == 0) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    } else
      ret = 1;  // cant allocate memory for new matrix
  } else
    ret = 1;  // wrong inputs
  return ret;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = 0;

  if (!(A && A->matrix && B && B->matrix && result)) ret = 1;  // wrong inputs
  if (ret == 0 && A->columns == B->rows)  // 2*3 x 3*4 = 2*4
  {
    int rows = A->rows, columns = B->columns;
    if (s21_create_matrix(rows, columns, result) == 0) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          //запишем в каждую ячейку новой матрицы значения
          for (int m = 0; m < A->columns; m++) {
            result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
          }
        }
      }
    } else
      ret = 1;  // cant allocate memory for new matrix
  } else if (ret != 1)
    ret = 2;  // wrong matrices
  return ret;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (A != NULL && A->matrix && result != NULL &&
      (s21_create_matrix(A->columns, A->rows, result) == 0)) {
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
    // printf("created\n");
  } else
    ret = 1;  // wrong inputs or cant allocate memory for new matrix
  return ret;
}

/*
Матрица алгебраических дополнений
Алгебраическим дополнением элемента матрицы является значение минора умноженное
на -1^(i+j). Минором M(i,j) называется определитель (n-1)-го порядка, полученный
вычёркиванием из матрицы A i-й строки и j-го столбца.
*/
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = 0;
  matrix_t complemMat = {0}, temp = {0};
  if (A && A->matrix && result)  // columns = rows >= 3!
  {
    if (A->columns == A->rows &&
        A->columns > 1)  // can calc complements if size of square matrix > 2!
    {
      ret = s21_create_matrix(A->rows, A->columns, &complemMat);
      double calcMinorDet = 0.0;
      //для каждой ячейки считаем детерминант и умножаем на знак
      for (int i = 0; i < A->columns; i++) {
        for (int j = 0; j < A->rows; j++) {
          s21_create_minor_matrix(i, j, *A,
                                  &temp);  // create minor for each cell
          s21_determinant(&temp,
                          &calcMinorDet);  // and calc determinant of each minor
          complemMat.matrix[i][j] = calcMinorDet * pow(-1, i + j);
          s21_remove_matrix(&temp);
        }
      }
      //копируем рассчитанные алгебр дополнения в result
      if (s21_create_matrix(A->rows, A->columns, result) == 0) {
        for (int i = 0; i < A->columns; i++) {
          for (int j = 0; j < A->rows; j++) {
            result->matrix[i][j] = complemMat.matrix[i][j];
          }
        }
      } else
        ret = 1;  // cant create result matrix memory error perhaps
      s21_remove_matrix(&complemMat);
    } else
      ret = 2;  //нельзя рассчитать для такой матрицы
  } else
    ret = 1;  //ошибка с матрицей
  return ret;
}

/*
Определитель матрицы равен сумме произведений элементов строки (столбца)
на соответствующие алгебраические дополнения.
*/
int s21_determinant(matrix_t *A, double *result) {
  int ret = 0;
  if (!(A && result)) ret = 1;
  if (ret == 0 && A->columns == A->rows) {
    double calcDet = 0.0;
    if (A->columns > 2)
      *result = s21_sumDetAllLevelMinors(*A);
    else if (A->columns == 2) {
      calcDet = s21_twoDimMinor(*A);
      *result = calcDet;
    } else
      *result = A->matrix[0][0];
  } else if (ret != 1)
    ret = 2;  // wrong matrix need square one
  return ret;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (A && A->matrix && result) {
    double det = 0;
    ret = s21_determinant(A, &det);
    // printf("det = %f\n", det);
    if (ret == 0 && det != 0 &&
        A->rows == A->columns)  // inverse matrix exists!
    {
      //если строк больше 1
      if (A->rows > 1) {
        matrix_t transposeMat = {0}, complMat = {0};
        if (s21_calc_complements(A, &complMat) == 0 &&
            s21_transpose(&complMat, &transposeMat) == 0) {
          double mult = 1.0 / det;
          ret = s21_mult_number(&transposeMat, mult, result);
        }
        s21_remove_matrix(&transposeMat);
        s21_remove_matrix(&complMat);

        // s21_remove_matrix(&inverseMat);
        //если 1 элемент в матрице то обратная матрица равна 1/элемент
      } else if (A->rows == 1) {
        if (s21_create_matrix(A->rows, A->columns, result) == 0) {
          result->matrix[0][0] = 1 / det;
          // printf("elem = %f\n", result->matrix[0][0]);
        }
      }
    } else if (ret == 0)
      ret = 2;  // if det == 0
  } else
    ret = 1;  // mem error
  return ret;
}