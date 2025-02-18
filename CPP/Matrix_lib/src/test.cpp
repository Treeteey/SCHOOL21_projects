// #include <gtest/gtest.h>
#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

TEST(tests_matrix, equal_mats){
  S21Matrix mat1(1,2);
  mat1(0,0) = 2.00000000001;
  mat1(0,1) = 3;
  S21Matrix mat2(1,2);
  mat2(0,0) = 2;
  mat2(0,1) = 2.999999999999;
  EXPECT_EQ(1, mat1.EqMatrix(mat2));
}

TEST(tests_matrix, not_equal_mats){
  S21Matrix mat1(1,2);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  S21Matrix mat2(2,1);
  mat2(0,0) = 2;
  mat2(1,0) = 3;
  EXPECT_EQ(0, mat1.EqMatrix(mat2));
}

TEST(tests_matrix, sum_mats_1){
  S21Matrix mat1(2,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  S21Matrix mat2(2,3);
  mat2(0,0) = -2;
  mat2(0,1) = -3;
  mat2(0,2) = -23;
  mat2(1,0) = 6;
  mat2(1,1) = 7;
  mat2(1,2) = 11;
  S21Matrix result(2,3);
  result(0,0) = 0;
  result(0,1) = 0;
  result(0,2) = -28;
  result(1,0) = 8;
  result(1,1) = 8;
  result(1,2) = 19;
  mat1.SumMatrix(mat2);  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, sum_mats_2){
  S21Matrix mat1(1,1);
  mat1(0,0) = 2;
  S21Matrix mat2(1,1);
  mat2(0,0) = -1;
  S21Matrix result(1,1);
  result(0,0) = 1;
  mat1.SumMatrix(mat2);  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, sum_wrong_mats){
  S21Matrix mat1(1,2);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  S21Matrix mat2(2,1);
  mat2(0,0) = -1;
  mat2(1,0) = 5;
  S21Matrix result(1,2);
  result(0,0) = 2;
  result(0,1) = 3;
  EXPECT_THROW(mat1.SumMatrix(mat2), std::invalid_argument);
}

TEST(tests_matrix, sub_mats_1){
  S21Matrix mat1(2,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  S21Matrix mat2(2,3);
  mat2(0,0) = -2;
  mat2(0,1) = -3;
  mat2(0,2) = -23;
  mat2(1,0) = 6;
  mat2(1,1) = 7;
  mat2(1,2) = 11;
  S21Matrix result(2,3);
  result(0,0) = 4;
  result(0,1) = 6;
  result(0,2) = 18;
  result(1,0) = -4;
  result(1,1) = -6;
  result(1,2) = -3;
  mat1.SubMatrix(mat2);  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, sub_mats_2){
  S21Matrix mat1(1,1);
  mat1(0,0) = 2;
  S21Matrix mat2(1,1);
  mat2(0,0) = -1;
  S21Matrix result(1,1);
  result(0,0) = 3;
  mat1.SubMatrix(mat2);  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, sub_wrong_mats){
  S21Matrix mat1(1,2);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  S21Matrix mat2(2,1);
  mat2(0,0) = -1;
  mat2(1,0) = 5;
  S21Matrix result(1,2);
  result(0,0) = 2;
  result(0,1) = 3;
  EXPECT_THROW(mat1.SubMatrix(mat2), std::invalid_argument);
  // EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, mul_number_1){
  S21Matrix mat1(2,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  double number = 2;
  S21Matrix result(2,3);
  result(0,0) = 4;
  result(0,1) = 6;
  result(0,2) = -10;
  result(1,0) = 4;
  result(1,1) = 2;
  result(1,2) = 16;
  mat1.MulNumber(number);  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, mul_number_2){
  S21Matrix mat1(1,1);
  mat1(0,0) = 2;
  double number = 2;
  S21Matrix result(1,1);
  result(0,0) = 4;
  mat1.MulNumber(number);
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, mul_matrix_1){
  S21Matrix mat1(2,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  S21Matrix mat2(3,2);
  mat2(0,0) = 2;
  mat2(0,1) = 3;
  mat2(1,0) = -5;
  mat2(1,1) = 2;
  mat2(2,0) = 1;
  mat2(2,1) = 8;
  S21Matrix result(2,2);
  result(0,0) = -16;
  result(0,1) = -28;
  result(1,0) = 7;
  result(1,1) = 72;
  mat1.MulMatrix(mat2);  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, mul_matrix_2){
  S21Matrix mat1(3,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  mat1(2,0) = 5;
  mat1(2,1) = 5;
  mat1(2,2) = 4;
  S21Matrix mat2(3,2);
  mat2(0,0) = 2;
  mat2(0,1) = 3;
  mat2(1,0) = -5;
  mat2(1,1) = 2;
  mat2(2,0) = 1;
  mat2(2,1) = 8;
  S21Matrix result(3,2);
  result(0,0) = -16;
  result(0,1) = -28;
  result(1,0) = 7;
  result(1,1) = 72;
  result(2,0) = -11;
  result(2,1) = 57;
  mat1.MulMatrix(mat2);  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}


TEST(tests_matrix, mul_matrix_3){
  S21Matrix mat1(1,1);
  mat1(0,0) = 2;
  S21Matrix mat2(1,1);
  mat2(0,0) = 5;
  S21Matrix result(1,1);
  result(0,0) = 10;
  mat1.MulMatrix(mat2);  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, mul_wrong_matrix){
  S21Matrix mat1(3,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  mat1(2,0) = 5;
  mat1(2,1) = 5;
  mat1(2,2) = 4;
  S21Matrix mat2(2,3);
  mat2(0,0) = 2;
  mat2(0,1) = 3;
  mat2(0,2) = -5;
  mat2(1,0) = 2;
  mat2(1,1) = 1;
  mat2(1,2) = 8;
  S21Matrix result(3,3);
  result(0,0) = 2;
  result(0,1) = 3;
  result(0,2) = -5;
  result(1,0) = 2;
  result(1,1) = 1;
  result(1,2) = 8;
  result(2,0) = 5;
  result(2,1) = 5;
  result(2,2) = 4;
  EXPECT_THROW(mat1.MulMatrix(mat2), std::invalid_argument);
}

/*
2 3 -5    2 2 5
2 1 8  -> 3 1 5
5 5 4    -5 8 4
*/


TEST(tests_matrix, transpose_1){
  S21Matrix mat1(3,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  mat1(2,0) = 5;
  mat1(2,1) = 5;
  mat1(2,2) = 4;

  S21Matrix result(3,3);
  result(0,0) = 2;
  result(0,1) = 2;
  result(0,2) = 5;
  result(1,0) = 3;
  result(1,1) = 1;
  result(1,2) = 5;
  result(2,0) = -5;
  result(2,1) = 8;
  result(2,2) = 4;
  mat1 = mat1.Transpose();  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, transpose_2){
  S21Matrix mat1(3,1);
  mat1(0,0) = 2;
  mat1(1,0) = 3;
  mat1(2,0) = -5;

  S21Matrix result(1,3);
  result(0,0) = 2;
  result(0,1) = 3;
  result(0,2) = -5;

  mat1 = mat1.Transpose();  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, transpose_3){
  S21Matrix mat1(1,1);
  mat1(0,0) = 2;

  S21Matrix result(1,1);
  result(0,0) = 2;

  mat1 = mat1.Transpose();  
  EXPECT_EQ(1, mat1.EqMatrix(result));
}



TEST(tests_matrix, determinant_1){
  S21Matrix mat1(3,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  mat1(2,0) = 5;
  mat1(2,1) = 5;
  mat1(2,2) = 4;

  double result = -1.0;
  EXPECT_EQ(result, mat1.Determinant());
}

TEST(tests_matrix, determinant_2){
  S21Matrix mat1(2,2);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(1,0) = -5;
  mat1(1,1) = -5;

  double result = 5;
  EXPECT_EQ(result, mat1.Determinant());
}

TEST(tests_matrix, determinant_3){
  S21Matrix mat1(1,1);
  mat1(0,0) = 2.0;

  double result = 2.0;
  EXPECT_EQ(result, mat1.Determinant());
}

TEST(tests_matrix, wrong_determinant){
  S21Matrix mat1(3,2);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(1,0) = -5;
  mat1(1,1) = 2;
  mat1(2,0) = 1;
  mat1(2,1) = 8;

  EXPECT_THROW(mat1.Determinant(), std::invalid_argument);
}




TEST(tests_matrix, calc_complements_1){
  S21Matrix mat1(3,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  mat1(2,0) = 5;
  mat1(2,1) = 5;
  mat1(2,2) = 4;
  S21Matrix result(3,3);
  result(0,0) = -36;
  result(0,1) = 32;
  result(0,2) = 5;
  result(1,0) = -37;
  result(1,1) = 33;
  result(1,2) = 5;
  result(2,0) = 29;
  result(2,1) = -26;
  result(2,2) = -4;
  mat1 = mat1.CalcComplements();
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, calc_complements_2){
  S21Matrix mat1(2,2);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(1,0) = -5;
  mat1(1,1) = -5;
  S21Matrix result(2,2);
  result(0,0) = -5;
  result(0,1) = 5;
  result(1,0) = -3;
  result(1,1) = 2;
  mat1 = mat1.CalcComplements();
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, wrong_calc_complements){
  S21Matrix mat1(3,2);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(1,0) = -5;
  mat1(1,1) = 2;
  mat1(2,0) = 1;
  mat1(2,1) = 8;
  EXPECT_THROW(mat1.CalcComplements(), std::invalid_argument);
}




TEST(tests_matrix, inverse_1){
  S21Matrix mat1(3,3);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(0,2) = -5;
  mat1(1,0) = 2;
  mat1(1,1) = 1;
  mat1(1,2) = 8;
  mat1(2,0) = 5;
  mat1(2,1) = 5;
  mat1(2,2) = 4;
  S21Matrix result(3,3);
  result(0,0) = 36;
  result(0,1) = 37;
  result(0,2) = -29;
  result(1,0) = -32;
  result(1,1) = -33;
  result(1,2) = 26;
  result(2,0) = -5;
  result(2,1) = -5;
  result(2,2) = 4;
  mat1 = mat1.InverseMatrix();
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, inverse_2){
  S21Matrix mat1(2,2);
  mat1(0,0) = 5;
  mat1(0,1) = 3;
  mat1(1,0) = -6;
  mat1(1,1) = -8;
  S21Matrix result(2,2);
  result(0,0) = 4/11.0;
  result(0,1) = 3/22.0;
  result(1,0) = -3/11.0;
  result(1,1) = -5/22.0;
  mat1 = mat1.InverseMatrix();
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, wrong_inverse){
  S21Matrix mat1(3,2);
  mat1(0,0) = 2;
  mat1(0,1) = 3;
  mat1(1,0) = -5;
  mat1(1,1) = 2;
  mat1(2,0) = 1;
  mat1(2,1) = 8;
  EXPECT_THROW(mat1.InverseMatrix(), std::invalid_argument);
}

TEST(tests_matrix, getters){
  S21Matrix mat1(3,2);
  EXPECT_EQ(3, mat1.getterRows_());
  EXPECT_EQ(2, mat1.getterCols_());
}

TEST(tests_matrix, setter_rows_1){
  S21Matrix mat1(2,2);
  mat1(0,0) = 5;
  mat1(0,1) = 3;
  mat1(1,0) = -6;
  mat1(1,1) = -8;
  mat1.setterRows_(4);
  S21Matrix result(4,2);
  result(0,0) = 5;
  result(0,1) = 3;
  result(1,0) = -6;
  result(1,1) = -8;
  result(2,0) = 0;
  result(2,1) = 0;
  result(3,0) = 0;
  result(3,1) = 0;
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, setter_rows_2){
  S21Matrix mat1(2,2);
  mat1(0,0) = 5;
  mat1(0,1) = 3;
  mat1(1,0) = -6;
  mat1(1,1) = -8;
  mat1.setterRows_(1);
  S21Matrix result(1,2);
  result(0,0) = 5;
  result(0,1) = 3;
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, setter_cols_1){
  S21Matrix mat1(2,2);
  mat1(0,0) = 5;
  mat1(0,1) = 3;
  mat1(1,0) = -6;
  mat1(1,1) = -8;
  mat1.setterCols_(4);
  S21Matrix result(2,4);
  result(0,0) = 5;
  result(0,1) = 3;
  result(0,2) = 0;
  result(0,3) = 0;
  result(1,0) = -6;
  result(1,1) = -8;
  result(1,2) = 0;
  result(1,3) = 0;
  EXPECT_EQ(1, mat1.EqMatrix(result));
}

TEST(tests_matrix, setter_cols_2){
  S21Matrix mat1(2,2);
  mat1(0,0) = 5;
  mat1(0,1) = 3;
  mat1(1,0) = -6;
  mat1(1,1) = -8;
  mat1.setterCols_(1);
  S21Matrix result(2,1);
  result(0,0) = 5;
  result(1,0) = -6;
  EXPECT_EQ(1, mat1.EqMatrix(result));
}


TEST(tests_matrix, wrong_setter_cols){
  S21Matrix mat1(2,2);
  mat1(0,0) = 5;
  mat1(0,1) = 3;
  mat1(1,0) = -6;
  mat1(1,1) = -8;
  EXPECT_THROW(mat1.setterCols_(0), std::invalid_argument);
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  
}