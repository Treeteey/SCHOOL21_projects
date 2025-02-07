#include "s21_tests_matrix.h"

int NOCORRECT = 1, NORMAL = 0, NOCALC = 2;
double EPS = 1e-6;
/*
Все операции (кроме сравнения матриц) должны возвращать результирующий код:
- 0 - OK
- 1 - Ошибка, некорректная матрица
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
нельзя провести вычисления и т.д.)
*/
//**********************************************************************************
//                      ТЕСТЫ НА СОЗДАНИЕ МАТРИЦЫ
//**********************************************************************************

START_TEST(s21_create_matrix_1) {
  matrix_t mat;
  int result = s21_create_matrix(1, 1, &mat);
  ck_assert_int_eq(NORMAL, result);
  s21_remove_matrix(&mat);
  // printf("FOWK11\n");
}
END_TEST

START_TEST(s21_create_matrix_2) {
  matrix_t mat;
  int result = s21_create_matrix(0, 0, &mat);
  if (result == NORMAL) s21_remove_matrix(&mat);
  // printf("fowk12\n");
  ck_assert_int_eq(NOCORRECT, result);
}
END_TEST

START_TEST(s21_create_matrix_3) {
  matrix_t mat;
  int result = s21_create_matrix(2, 0, &mat);
  ck_assert_int_eq(NOCORRECT, result);
  if (result == 0) s21_remove_matrix(&mat);
  // printf("FOWK13\n");
}
END_TEST

START_TEST(s21_create_matrix_4) {
  matrix_t mat;
  int result = s21_create_matrix(3, 5, &mat);
  ck_assert_int_eq(NORMAL, result);
  if (result == 0) s21_remove_matrix(&mat);
  // printf("FOWK14\n");
}
END_TEST

START_TEST(s21_create_matrix_5) {
  matrix_t mat;
  int result = s21_create_matrix(-1, 5, &mat);
  ck_assert_int_eq(NOCORRECT, result);
  if (result == 0) s21_remove_matrix(&mat);
  // printf("FOWK15\n");
}
END_TEST

//**********************************************************************************
//                      ТЕСТЫ НА УДАЛЕНИЕ МАТРИЦЫ
//**********************************************************************************

START_TEST(s21_remove_matrix_1) {
  matrix_t mat;
  int result = 1;
  if (s21_create_matrix(1, 1, &mat) == 0) {
    s21_remove_matrix(&mat);
    if (mat.matrix == NULL)
      result = 0;
    else
      result = 1;
    ck_assert_int_eq(NORMAL, result);
    // printf("FOWK21\n");
  }
}
END_TEST

START_TEST(s21_remove_matrix_2) {
  matrix_t mat;
  int result = 1;
  if (s21_create_matrix(3, 5, &mat) == 0) {
    s21_remove_matrix(&mat);
    if (mat.matrix == NULL)
      result = 0;
    else
      result = 1;
    ck_assert_int_eq(NORMAL, result);
    // printf("FOWK22\n");
  }
}
END_TEST

//**********************************************************************************
//                      ТЕСТЫ НА СРАВНЕНИЕ МАТРИЦ
//**********************************************************************************

START_TEST(s21_eq_matrix_1) {
  matrix_t mat1, mat2;
  s21_create_matrix(1, 3, &mat1);
  s21_create_matrix(1, 3, &mat2);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = -1;
  mat1.matrix[0][2] = 3;

  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = -1;
  mat2.matrix[0][2] = 3;

  int result = s21_eq_matrix(&mat1, &mat2);

  ck_assert_int_eq(SUCCESS, result);
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  // printf("FOWK31\n");
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  matrix_t mat1, mat2;
  s21_create_matrix(1, 3, &mat1);
  s21_create_matrix(1, 3, &mat2);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = -1;
  mat1.matrix[0][2] = 3;

  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 443;
  mat2.matrix[0][2] = 3;

  int result = s21_eq_matrix(&mat1, &mat2);  // different element

  ck_assert_int_eq(FAILURE, result);
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  // printf("FOWK32\n");
}
END_TEST

START_TEST(s21_eq_matrix_3) {
  matrix_t mat1, mat2;
  s21_create_matrix(1, 3, &mat1);
  s21_create_matrix(1, 3, &mat2);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = -1;
  mat1.matrix[0][2] = 3;

  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 443;
  mat2.matrix[0][2] = 3;

  int result = s21_eq_matrix(&mat1, NULL);  // wrong argument

  ck_assert_int_eq(FAILURE, result);
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  // printf("FOWK33\n");
}
END_TEST

START_TEST(s21_eq_matrix_4) {
  matrix_t mat1, mat2;
  s21_create_matrix(1, 3, &mat1);
  s21_create_matrix(3, 1, &mat2);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = -1;
  mat1.matrix[0][2] = 3;

  mat2.matrix[0][0] = 1;
  mat2.matrix[1][0] = -1;
  mat2.matrix[2][0] = 3;

  int result = s21_eq_matrix(&mat1, &mat2);  // diff matrices

  ck_assert_int_eq(FAILURE, result);
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  // printf("FOWK34\n");
}
END_TEST

// //**********************************************************************************
// //                      ТЕСТЫ НА суммирование МАТРИЦ
// //**********************************************************************************

START_TEST(s21_sum_matrix_1) {
  int err = 0;
  matrix_t mat1;
  matrix_t mat2;
  matrix_t result;
  matrix_t sum;
  s21_create_matrix(2, 3, &mat1);
  s21_create_matrix(2, 3, &mat2);
  s21_create_matrix(2, 3, &result);

  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = -1;
  mat1.matrix[0][2] = 3;
  mat1.matrix[1][0] = 1;
  mat1.matrix[1][1] = -1;
  mat1.matrix[1][2] = 3;

  mat2.matrix[0][0] = 3;
  mat2.matrix[0][1] = 5;
  mat2.matrix[0][2] = 2;
  mat2.matrix[1][0] = 0;
  mat2.matrix[1][1] = -54;
  mat2.matrix[1][2] = 100;

  result.matrix[0][0] = 4;
  result.matrix[0][1] = 4;
  result.matrix[0][2] = 5;
  result.matrix[1][0] = 1;
  result.matrix[1][1] = -55;
  result.matrix[1][2] = 103;

  err = s21_sum_matrix(&mat1, &mat2, &sum);

  ck_assert_int_eq(NORMAL, err);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&sum);
  // printf("FOWK41\n");
}

START_TEST(s21_sum_matrix_2) {
  int err = 0;
  matrix_t matrix_1;
  matrix_t matrix_2;
  matrix_t result;

  s21_create_matrix(2, 2, &matrix_1);
  s21_create_matrix(2, 2, &matrix_2);

  err = s21_sum_matrix(&matrix_1, &matrix_2, NULL);
  ck_assert_int_eq(NOCORRECT, err);
  if (err == 0) s21_remove_matrix(&result);

  err = s21_sum_matrix(&matrix_1, NULL, &result);
  ck_assert_int_eq(NOCORRECT, err);
  if (err == 0) s21_remove_matrix(&result);

  err = s21_sum_matrix(NULL, &matrix_2, &result);
  ck_assert_int_eq(NOCORRECT, err);
  if (err == 0) s21_remove_matrix(&result);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  // printf("FOWK42\n");
}
END_TEST

START_TEST(s21_sum_matrix_3) {
  int err = 0;
  matrix_t mat1;
  matrix_t mat2;
  matrix_t sum;
  err += s21_create_matrix(2, 2, &mat1);
  err += s21_create_matrix(2, 2, &mat2);

  // s21_create_matrix(2, 2, &sum);
  if (err == 0) {
    mat1.matrix[0][0] = 1;
    mat1.matrix[0][1] = -1;
    mat1.matrix[1][0] = 1;
    mat1.matrix[1][1] = -1;

    mat2.matrix[0][0] = 3;
    mat2.matrix[0][1] = 5;
    mat2.matrix[1][0] = 0;
    mat2.matrix[1][1] = -54;

    mat1.columns = 5;  // change columns number not matrix
    err = s21_sum_matrix(&mat1, &mat2, &sum);
    // printf("err43 = %d\n", err);

    ck_assert_int_eq(NOCALC, err);
    if (err == 0) {
      s21_remove_matrix(&sum);
    }
    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }
  // printf("FOWK43\n");
}

//**********************************************************************************
//                      ТЕСТЫ НА вычитание МАТРИЦ
//**********************************************************************************

START_TEST(s21_sub_matrix_1) {
  matrix_t mat1;
  matrix_t mat2;
  matrix_t result;
  matrix_t sub;
  s21_create_matrix(2, 3, &mat1);
  s21_create_matrix(2, 3, &mat2);
  s21_create_matrix(2, 3, &result);

  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = -1;
  mat1.matrix[0][2] = 3;
  mat1.matrix[1][0] = 1;
  mat1.matrix[1][1] = -1;
  mat1.matrix[1][2] = 3;

  mat2.matrix[0][0] = 3;
  mat2.matrix[0][1] = 5;
  mat2.matrix[0][2] = 2;
  mat2.matrix[1][0] = 0;
  mat2.matrix[1][1] = -54;
  mat2.matrix[1][2] = 100;

  result.matrix[0][0] = -2;
  result.matrix[0][1] = -6;
  result.matrix[0][2] = 1;
  result.matrix[1][0] = 1;
  result.matrix[1][1] = 53;
  result.matrix[1][2] = -97;
  if (s21_sub_matrix(&mat1, &mat2, &sub) == 0) {
    ck_assert_int_eq(SUCCESS, s21_eq_matrix(&sub, &result));
    s21_remove_matrix(&sub);
  }
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
  // printf("FOWK51\n");
}

START_TEST(s21_sub_matrix_2) {
  int err = 0;
  matrix_t mat1;
  matrix_t mat2;
  matrix_t result;
  matrix_t sum;

  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &sum);
  s21_create_matrix(2, 2, &result);

  err = s21_sub_matrix(&mat1, &mat2, NULL);
  ck_assert_int_eq(1, err);

  err = s21_sub_matrix(&mat1, NULL, &sum);
  ck_assert_int_eq(1, err);

  err = s21_sub_matrix(NULL, &mat2, &sum);
  ck_assert_int_eq(1, err);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&sum);
  // printf("FOWK52\n");
}
END_TEST

START_TEST(s21_sub_matrix_3) {
  int err = 0;
  matrix_t mat1;
  matrix_t mat2;
  matrix_t result;
  matrix_t sub;
  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &result);
  // s21_create_matrix(2, 2, &sub);

  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = -1;
  mat1.matrix[1][0] = 1;
  mat1.matrix[1][1] = -1;

  mat2.matrix[0][0] = 3;
  mat2.matrix[0][1] = 5;
  mat2.matrix[1][0] = 0;
  mat2.matrix[1][1] = -54;

  result.matrix[0][0] = -2;
  result.matrix[0][1] = -6;
  result.matrix[1][0] = 1;
  result.matrix[1][1] = -55;
  // printf("%p %p\n", &sub, &sub.matrix);
  mat1.columns = 5;  // change columns number not matrix
  err = s21_sub_matrix(&mat1, &mat2, &sub);
  // printf("%p %p\n", &sub, &sub.matrix);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&mat1);
  s21_create_matrix(2, 8, &mat1);
  err = s21_sum_matrix(&mat1, &mat2, &sub);

  ck_assert_int_eq(NOCALC, err);
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
  if (err == 0) s21_remove_matrix(&sub);
  // printf("FOWK53\n");
}

//**********************************************************************************
//                      ТЕСТЫ НА умножение МАТРИЦ
//**********************************************************************************

START_TEST(s21_mult_matrix_1) {
  int err = 0;
  matrix_t mat1;
  matrix_t mat2;
  matrix_t result;
  matrix_t mult;

  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &result);
  // s21_create_matrix(2, 2, &mult);

  mat1.matrix[0][0] = 5;
  mat1.matrix[0][1] = -1;
  mat1.matrix[1][0] = 0;
  mat1.matrix[1][1] = -1;

  mat2.matrix[0][0] = 3;
  mat2.matrix[0][1] = 5;
  mat2.matrix[1][0] = 0;
  mat2.matrix[1][1] = -54;

  result.matrix[0][0] = 15;
  result.matrix[0][1] = 79;
  result.matrix[1][0] = 0;
  result.matrix[1][1] = 54;

  if (s21_mult_matrix(&mat1, &mat2, &mult) == 0) {
    err = s21_eq_matrix(&result, &mult);
    ck_assert_int_eq(SUCCESS, err);
    s21_remove_matrix(&mult);
  }

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);

  // printf("FOWK61\n");
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  int err = 0;
  matrix_t mat1;
  matrix_t mat2;
  matrix_t result;
  matrix_t mult;

  s21_create_matrix(1, 2, &mat1);
  s21_create_matrix(2, 1, &mat2);
  s21_create_matrix(1, 1, &result);
  // s21_create_matrix(2, 2, &mult);

  mat1.matrix[0][0] = 0;
  mat1.matrix[0][1] = -2;

  mat2.matrix[0][0] = 1;
  mat2.matrix[1][0] = 5;

  result.matrix[0][0] = -10;

  if (s21_mult_matrix(&mat1, &mat2, &mult) == 0) {
    err = s21_eq_matrix(&result, &mult);
    ck_assert_int_eq(SUCCESS, err);
  }

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&mult);
  // printf("FOWK62\n");
}
END_TEST

START_TEST(s21_mult_matrix_3) {
  int err = 0;
  matrix_t mat1;
  matrix_t mat2;
  matrix_t result;
  matrix_t mult;

  s21_create_matrix(2, 1, &mat1);
  s21_create_matrix(1, 2, &mat2);
  s21_create_matrix(2, 2, &result);

  mat1.matrix[0][0] = 0;
  mat1.matrix[1][0] = -2;

  mat2.matrix[0][0] = 1;
  mat2.matrix[0][1] = 5;

  result.matrix[0][0] = 0;
  result.matrix[0][1] = 0;
  result.matrix[1][0] = -2;
  result.matrix[1][1] = -10;

  if (s21_mult_matrix(&mat1, &mat2, &mult) == 0) {
    err = s21_eq_matrix(&result, &mult);
    ck_assert_int_eq(SUCCESS, err);
  }

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&mult);
  // printf("FOWK63\n");
}
END_TEST

//проверка на невозможность расчета
//количество столбцов 1 матрицы не равно количеству строк 2 матрицы
START_TEST(s21_mult_matrix_4) {  // cant calc matrices
  int err = 0;
  matrix_t mat1;
  matrix_t mat2;
  matrix_t result;
  matrix_t mult;
  s21_create_matrix(2, 1, &mat1);
  s21_create_matrix(2, 1, &mat2);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &mult);

  mat1.matrix[0][0] = 0;
  mat1.matrix[1][0] = -2;

  mat2.matrix[0][0] = 1;
  mat2.matrix[1][0] = 5;

  result.matrix[0][0] = -10;

  err = s21_mult_matrix(&mat1, &mat2, &mult);
  ck_assert_int_eq(2, err);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&mult);
  // printf("FOWK64\n");
}
END_TEST

//проверка на некорректные матрицы
START_TEST(s21_mult_matrix_5) {
  int err = 0;
  matrix_t mat1;
  matrix_t mat2;
  matrix_t result;
  matrix_t mult;

  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &mat2);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &mult);

  err = s21_mult_matrix(NULL, &mat2, &result);
  ck_assert_int_eq(1, err);

  err = s21_mult_matrix(&mat1, NULL, &result);
  ck_assert_int_eq(1, err);

  err = s21_mult_matrix(&mat1, &mat2, NULL);
  ck_assert_int_eq(1, err);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&mult);
  // printf("FOWK65\n");
}
END_TEST

//**********************************************************************************
//                      ТЕСТЫ НА умножение на число МАТРИЦ
//**********************************************************************************

START_TEST(s21_mult_number_1) {
  int err = 0, number = 0;
  matrix_t mat1;
  matrix_t result;
  matrix_t mult;

  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &result);

  mat1.matrix[0][0] = 5;
  mat1.matrix[0][1] = -1;
  mat1.matrix[1][0] = 0;
  mat1.matrix[1][1] = -1;

  result.matrix[0][0] = 0;
  result.matrix[0][1] = 0;
  result.matrix[1][0] = 0;
  result.matrix[1][1] = 0;

  if (s21_mult_number(&mat1, number, &mult) == 0) {
    err = s21_eq_matrix(&result, &mult);
    ck_assert_int_eq(SUCCESS, err);
  }

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&mult);
}
END_TEST

// coca cola NORMAL
START_TEST(s21_mult_number_2) {
  int err = 0, number = 3;
  matrix_t mat1;
  matrix_t result;
  matrix_t mult;

  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &result);

  mat1.matrix[0][0] = 5;
  mat1.matrix[0][1] = -1;
  mat1.matrix[1][0] = 0;
  mat1.matrix[1][1] = 22;

  result.matrix[0][0] = 15;
  result.matrix[0][1] = -3;
  result.matrix[1][0] = 0;
  result.matrix[1][1] = 66;

  if (s21_mult_number(&mat1, number, &mult) == 0) {
    err = s21_eq_matrix(&result, &mult);
    ck_assert_int_eq(SUCCESS, err);
    s21_remove_matrix(&mult);
  }

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&result);

  // printf("FOWK72\n");
}
END_TEST

//проверка на некорректные матрицы
START_TEST(s21_mult_number_3) {
  int err = 0, number = 2;
  matrix_t mat1;
  matrix_t result;

  s21_create_matrix(2, 2, &mat1);
  s21_create_matrix(2, 2, &result);

  err = s21_mult_number(NULL, number, &result);
  ck_assert_int_eq(1, err);

  err = s21_mult_number(&mat1, number, NULL);
  ck_assert_int_eq(1, err);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&result);
}
END_TEST

//**********************************************************************************
//                      ТЕСТЫ НА транспонирование МАТРИЦ
//**********************************************************************************

START_TEST(s21_transpose_1) {
  matrix_t mat1;
  matrix_t result;
  matrix_t tran;

  s21_create_matrix(2, 3, &mat1);
  s21_create_matrix(3, 2, &result);

  mat1.matrix[0][0] = 5;
  mat1.matrix[0][1] = 3;
  mat1.matrix[0][2] = 1;
  mat1.matrix[1][0] = 7;
  mat1.matrix[1][1] = 5;
  mat1.matrix[1][2] = 4;

  result.matrix[0][0] = 5;
  result.matrix[0][1] = 7;
  result.matrix[1][0] = 3;
  result.matrix[1][1] = 5;
  result.matrix[2][0] = 1;
  result.matrix[2][1] = 4;

  if (s21_transpose(&mat1, &tran) == 0) {
    ck_assert_int_eq(SUCCESS, s21_eq_matrix(&result, &tran));
    s21_remove_matrix(&tran);
  }

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&result);

  // printf("FOWK81\n");
}
END_TEST

START_TEST(s21_transpose_2) {
  int err = 0;
  matrix_t mat1;
  matrix_t result;
  matrix_t tran;

  s21_create_matrix(1, 3, &mat1);
  s21_create_matrix(3, 1, &result);

  mat1.matrix[0][0] = 5;
  mat1.matrix[0][1] = 3;
  mat1.matrix[0][2] = 1;

  result.matrix[0][0] = 5;
  result.matrix[1][0] = 3;
  result.matrix[2][0] = 1;
  err = s21_transpose(&mat1, &tran);
  if (err == 0) {
    err = s21_eq_matrix(&result, &tran);
    ck_assert_int_eq(SUCCESS, err);
    s21_remove_matrix(&tran);
  }

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&result);
}
END_TEST

// проверка на некорректные матрицы
START_TEST(s21_transpose_3) {
  int err = 0;
  matrix_t mat1;
  matrix_t result;

  s21_create_matrix(2, 2, &mat1);

  // printf("aa\n");
  err = s21_transpose(NULL, &result);
  ck_assert_int_eq(NOCORRECT, err);
  // printf("a1\n");

  err = s21_transpose(&mat1, NULL);
  ck_assert_int_eq(NOCORRECT, err);
  // printf("a2\n");

  s21_remove_matrix(&mat1);
}
END_TEST

//**********************************************************************************
//                      ТЕСТЫ НА расчет детерминанта
//**********************************************************************************

START_TEST(s21_determinant_1) {
  matrix_t mat1;
  double result = 46716379880, determ = 0;

  s21_create_matrix(8, 8, &mat1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 3;
  mat1.matrix[0][2] = 451;
  mat1.matrix[0][3] = 2;
  mat1.matrix[0][4] = 3;
  mat1.matrix[0][5] = 12;
  mat1.matrix[0][6] = 34;
  mat1.matrix[0][7] = 2;

  mat1.matrix[1][0] = 2;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 3;
  mat1.matrix[1][3] = 1;
  mat1.matrix[1][4] = 43;
  mat1.matrix[1][5] = 14;
  mat1.matrix[1][6] = 5;
  mat1.matrix[1][7] = 1;

  mat1.matrix[2][0] = 12;
  mat1.matrix[2][1] = 414;
  mat1.matrix[2][2] = 5;
  mat1.matrix[2][3] = 6;
  mat1.matrix[2][4] = 7;
  mat1.matrix[2][5] = 2;
  mat1.matrix[2][6] = 1;
  mat1.matrix[2][7] = 3;

  mat1.matrix[3][0] = 1;
  mat1.matrix[3][1] = 4;
  mat1.matrix[3][2] = 4;
  mat1.matrix[3][3] = 2;
  mat1.matrix[3][4] = 4;
  mat1.matrix[3][5] = 6;
  mat1.matrix[3][6] = 54;
  mat1.matrix[3][7] = 4;
  // {4,2,2,3,3,1,1,2},{2,14,4,1,2,3,2,4},
  // {8,7,8,7,8,7,6,6},{5,4,7,8,3,2,2,2}}
  mat1.matrix[4][0] = 4;
  mat1.matrix[4][1] = 2;
  mat1.matrix[4][2] = 2;
  mat1.matrix[4][3] = 3;
  mat1.matrix[4][4] = 3;
  mat1.matrix[4][5] = 1;
  mat1.matrix[4][6] = 1;
  mat1.matrix[4][7] = 2;

  mat1.matrix[5][0] = 2;
  mat1.matrix[5][1] = 14;
  mat1.matrix[5][2] = 4;
  mat1.matrix[5][3] = 1;
  mat1.matrix[5][4] = 2;
  mat1.matrix[5][5] = 3;
  mat1.matrix[5][6] = 2;
  mat1.matrix[5][7] = 4;

  mat1.matrix[6][0] = 8;
  mat1.matrix[6][1] = 7;
  mat1.matrix[6][2] = 8;
  mat1.matrix[6][3] = 7;
  mat1.matrix[6][4] = 8;
  mat1.matrix[6][5] = 7;
  mat1.matrix[6][6] = 6;
  mat1.matrix[6][7] = 6;

  mat1.matrix[7][0] = 5;
  mat1.matrix[7][1] = 4;
  mat1.matrix[7][2] = 7;
  mat1.matrix[7][3] = 8;
  mat1.matrix[7][4] = 3;
  mat1.matrix[7][5] = 2;
  mat1.matrix[7][6] = 2;
  mat1.matrix[7][7] = 2;
  if (s21_determinant(&mat1, &determ) == 0) {
    ck_assert_double_eq(result, determ);
    s21_remove_matrix(&mat1);
  }
}
END_TEST

START_TEST(s21_determinant_2) {
  matrix_t mat1;
  double result = 530997, determ = 0;
  s21_create_matrix(4, 4, &mat1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 3;
  mat1.matrix[0][2] = 451;
  mat1.matrix[0][3] = 2;

  mat1.matrix[1][0] = 2;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 3;
  mat1.matrix[1][3] = 1;

  mat1.matrix[2][0] = 12;
  mat1.matrix[2][1] = 414;
  mat1.matrix[2][2] = 5;
  mat1.matrix[2][3] = 6;

  mat1.matrix[3][0] = 1;
  mat1.matrix[3][1] = 4;
  mat1.matrix[3][2] = 4;
  mat1.matrix[3][3] = 2;
  if (s21_determinant(&mat1, &determ) == 0) {
    ck_assert_double_eq(result, determ);
    s21_remove_matrix(&mat1);
  }
}
END_TEST

//проверка на некорректные матрицы
START_TEST(s21_determinant_3) {
  int err = 0;
  matrix_t mat1;
  double result = 0;
  s21_create_matrix(2, 3, &mat1);

  err = s21_determinant(NULL, &result);
  ck_assert_int_eq(1, err);

  err = s21_determinant(&mat1, NULL);
  ck_assert_int_eq(1, err);

  s21_remove_matrix(&mat1);
}
END_TEST

//проверка на невозможность расчета: только у квадратных
//матриц можно рассчитать детерминант
START_TEST(s21_determinant_4) {
  int err = 0;
  matrix_t mat1;
  double determ = 0;
  s21_create_matrix(2, 4, &mat1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 3;
  mat1.matrix[0][2] = 451;
  mat1.matrix[0][3] = 2;

  mat1.matrix[1][0] = 2;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 3;
  mat1.matrix[1][3] = 1;

  err = s21_determinant(&mat1, &determ);
  ck_assert_int_eq(2, err);
  s21_remove_matrix(&mat1);
}
END_TEST

//**********************************************************************************
//                      ТЕСТЫ НА расчет алгебраические дополнения
//**********************************************************************************

START_TEST(s21_calc_complements_1) {
  matrix_t mat1;
  matrix_t result;
  matrix_t calc;

  s21_create_matrix(4, 4, &result);
  s21_create_matrix(4, 4, &mat1);

  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 3;
  mat1.matrix[0][2] = 4;
  mat1.matrix[0][3] = 2;

  mat1.matrix[1][0] = 2;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 3;
  mat1.matrix[1][3] = 1;

  mat1.matrix[2][0] = 12;
  mat1.matrix[2][1] = 9;
  mat1.matrix[2][2] = 5;
  mat1.matrix[2][3] = -6;

  mat1.matrix[3][0] = -1;
  mat1.matrix[3][1] = 4;
  mat1.matrix[3][2] = 4;
  mat1.matrix[3][3] = 2;

  result.matrix[0][0] = -8;
  result.matrix[0][1] = -67;
  result.matrix[0][2] = 87;
  result.matrix[0][3] = -44;

  result.matrix[1][0] = 34;
  result.matrix[1][1] = 68;
  result.matrix[1][2] = -102;
  result.matrix[1][3] = 85;

  result.matrix[2][0] = -2;
  result.matrix[2][1] = -4;
  result.matrix[2][2] = 9;
  result.matrix[2][3] = -11;

  result.matrix[3][0] = -15;
  result.matrix[3][1] = 21;
  result.matrix[3][2] = -9;
  result.matrix[3][3] = -6;

  if (s21_calc_complements(&mat1, &calc) == 0) {
    ck_assert_double_eq(SUCCESS, s21_eq_matrix(&calc, &result));
  }
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&calc);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t mat1;
  matrix_t result;
  matrix_t calc;

  s21_create_matrix(3, 3, &result);
  s21_create_matrix(3, 3, &mat1);

  mat1.matrix[0][0] = 2;
  mat1.matrix[0][1] = 2;
  mat1.matrix[0][2] = 2;

  mat1.matrix[1][0] = 2;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 3;

  mat1.matrix[2][0] = 12;
  mat1.matrix[2][1] = 3;
  mat1.matrix[2][2] = 5;

  result.matrix[0][0] = 6;
  result.matrix[0][1] = 26;
  result.matrix[0][2] = -30;

  result.matrix[1][0] = -4;
  result.matrix[1][1] = -14;
  result.matrix[1][2] = 18;

  result.matrix[2][0] = 0;
  result.matrix[2][1] = -2;
  result.matrix[2][2] = 2;

  if (s21_calc_complements(&mat1, &calc) == 0) {
    ck_assert_double_eq(SUCCESS, s21_eq_matrix(&calc, &result));
  }
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&calc);
}
END_TEST

//проверка на некорректные адреса матрицы
START_TEST(s21_calc_complements_3) {
  int err = 0;
  matrix_t mat1;
  matrix_t calc;
  s21_create_matrix(3, 3, &mat1);

  err = s21_calc_complements(NULL, &calc);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_calc_complements(&mat1, NULL);
  ck_assert_int_eq(NOCORRECT, err);

  s21_remove_matrix(&mat1);
}
END_TEST

//проверка на невозможность расчета: только у квадратных
//матриц можно рассчитать алгебраические дополнения
START_TEST(s21_calc_complements_4) {
  int err = 0;
  matrix_t mat1;
  matrix_t calc;
  s21_create_matrix(2, 4, &mat1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 3;
  mat1.matrix[0][2] = 451;
  mat1.matrix[0][3] = 2;

  mat1.matrix[1][0] = 2;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 3;
  mat1.matrix[1][3] = 1;

  err = s21_calc_complements(&mat1, &calc);
  // printf("104 err = %d\n", err);

  ck_assert_int_eq(NOCALC, err);
  s21_remove_matrix(&mat1);
}
END_TEST

//**********************************************************************************
//                      ТЕСТЫ НА расчет обратной матрицы
//**********************************************************************************

START_TEST(s21_inverse_matrix_1) {
  int err = 0;
  matrix_t mat1;
  matrix_t result;
  matrix_t calc;

  s21_create_matrix(4, 4, &result);
  s21_create_matrix(4, 4, &mat1);

  mat1.matrix[0][0] = 4;
  mat1.matrix[0][1] = 3;
  mat1.matrix[0][2] = 4;
  mat1.matrix[0][3] = 2;

  mat1.matrix[1][0] = 2;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 3;
  mat1.matrix[1][3] = 1;

  mat1.matrix[2][0] = 1;
  mat1.matrix[2][1] = 0;
  mat1.matrix[2][2] = 5;
  mat1.matrix[2][3] = -6;

  mat1.matrix[3][0] = -1;
  mat1.matrix[3][1] = 4;
  mat1.matrix[3][2] = 4;
  mat1.matrix[3][3] = 2;

  result.matrix[0][0] = 0.071942;
  result.matrix[0][1] = 0.244604;
  result.matrix[0][2] = -0.014388;
  result.matrix[0][3] = -0.237410;

  result.matrix[1][0] = -0.640288;
  result.matrix[1][1] = 1.223022;
  result.matrix[1][2] = -0.071942;
  result.matrix[1][3] = -0.187050;

  result.matrix[2][0] = 0.460432;
  result.matrix[2][1] = -0.834532;
  result.matrix[2][2] = 0.107914;
  result.matrix[2][3] = 0.280576;

  result.matrix[3][0] = 0.395683;
  result.matrix[3][1] = -0.654676;
  result.matrix[3][2] = -0.079137;
  result.matrix[3][3] = 0.194245;

  if (s21_inverse_matrix(&mat1, &calc) == 0) {
    err = s21_eq_matrix(&calc, &result);
    ck_assert_double_eq(SUCCESS, err);
    s21_remove_matrix(&calc);
  }
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  matrix_t mat1;
  matrix_t result;
  matrix_t calc;

  s21_create_matrix(3, 3, &result);
  s21_create_matrix(3, 3, &mat1);

  mat1.matrix[0][0] = 2;
  mat1.matrix[0][1] = 5;
  mat1.matrix[0][2] = 7;

  mat1.matrix[1][0] = 6;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 4;

  mat1.matrix[2][0] = 5;
  mat1.matrix[2][1] = -2;
  mat1.matrix[2][2] = -3;

  result.matrix[0][0] = 1;
  result.matrix[0][1] = -1;
  result.matrix[0][2] = 1;

  result.matrix[1][0] = -38;
  result.matrix[1][1] = 41;
  result.matrix[1][2] = -34;

  result.matrix[2][0] = 27;
  result.matrix[2][1] = -29;
  result.matrix[2][2] = 24;

  if (s21_inverse_matrix(&mat1, &calc) == 0) {
    ck_assert_double_eq(SUCCESS, s21_eq_matrix(&calc, &result));
    s21_remove_matrix(&calc);
  }
  s21_remove_matrix(&mat1);
  s21_remove_matrix(&result);
}
END_TEST

//проверка на некорректные адреса матрицы
START_TEST(s21_inverse_matrix_3) {
  int err = 0;
  matrix_t mat1;
  matrix_t calc;
  s21_create_matrix(3, 3, &mat1);

  err = s21_inverse_matrix(NULL, &calc);
  ck_assert_int_eq(1, err);

  err = s21_inverse_matrix(&mat1, NULL);
  ck_assert_int_eq(1, err);

  s21_remove_matrix(&mat1);
}
END_TEST

//проверка на невозможность расчета: только для квадратных
//матриц можно рассчитать обратную матрицу
START_TEST(s21_inverse_matrix_4) {
  int err = 0;
  matrix_t mat1;
  matrix_t calc;
  s21_create_matrix(2, 4, &mat1);
  mat1.matrix[0][0] = 1;
  mat1.matrix[0][1] = 3;
  mat1.matrix[0][2] = 451;
  mat1.matrix[0][3] = 2;

  mat1.matrix[1][0] = 2;
  mat1.matrix[1][1] = 3;
  mat1.matrix[1][2] = 3;
  mat1.matrix[1][3] = 1;

  err = s21_inverse_matrix(&mat1, &calc);
  ck_assert_int_eq(2, err);
  if (err == 0) s21_remove_matrix(&calc);
  s21_remove_matrix(&mat1);
}
END_TEST

Suite *suite_s21_matrix(void) {
  Suite *suite;
  TCase *all_case;

  suite = suite_create("s21_matrix");
  all_case = tcase_create("All_case");

  tcase_add_test(all_case, s21_create_matrix_1);
  tcase_add_test(all_case, s21_create_matrix_2);
  tcase_add_test(all_case, s21_create_matrix_3);
  tcase_add_test(all_case, s21_create_matrix_4);
  tcase_add_test(all_case, s21_create_matrix_5);

  tcase_add_test(all_case, s21_remove_matrix_1);
  tcase_add_test(all_case, s21_remove_matrix_2);

  tcase_add_test(all_case, s21_eq_matrix_1);
  tcase_add_test(all_case, s21_eq_matrix_2);
  tcase_add_test(all_case, s21_eq_matrix_3);
  tcase_add_test(all_case, s21_eq_matrix_4);

  tcase_add_test(all_case, s21_sum_matrix_1);
  tcase_add_test(all_case, s21_sum_matrix_2);
  tcase_add_test(all_case, s21_sum_matrix_3);

  tcase_add_test(all_case, s21_sub_matrix_1);
  tcase_add_test(all_case, s21_sub_matrix_2);
  tcase_add_test(all_case, s21_sub_matrix_3);

  tcase_add_test(all_case, s21_mult_matrix_1);
  tcase_add_test(all_case, s21_mult_matrix_2);
  tcase_add_test(all_case, s21_mult_matrix_3);
  tcase_add_test(all_case, s21_mult_matrix_4);
  tcase_add_test(all_case, s21_mult_matrix_5);

  tcase_add_test(all_case, s21_mult_number_1);
  tcase_add_test(all_case, s21_mult_number_2);
  tcase_add_test(all_case, s21_mult_number_3);

  tcase_add_test(all_case, s21_transpose_1);
  tcase_add_test(all_case, s21_transpose_2);
  tcase_add_test(all_case, s21_transpose_3);

  tcase_add_test(all_case, s21_determinant_1);
  tcase_add_test(all_case, s21_determinant_2);
  tcase_add_test(all_case, s21_determinant_3);
  tcase_add_test(all_case, s21_determinant_4);

  tcase_add_test(all_case, s21_calc_complements_1);
  tcase_add_test(all_case, s21_calc_complements_2);
  tcase_add_test(all_case, s21_calc_complements_3);
  tcase_add_test(all_case, s21_calc_complements_4);

  tcase_add_test(all_case, s21_inverse_matrix_1);
  tcase_add_test(all_case, s21_inverse_matrix_2);
  tcase_add_test(all_case, s21_inverse_matrix_3);
  tcase_add_test(all_case, s21_inverse_matrix_4);

  suite_add_tcase(suite, all_case);
  return suite;
}

int main(void) {
  int failed_count;
  Suite *suite;
  SRunner *srunner;

  suite = suite_s21_matrix();
  srunner = srunner_create(suite);

  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_NORMAL);
  failed_count = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
