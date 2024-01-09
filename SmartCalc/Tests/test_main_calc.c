#include "test.h"

START_TEST(calc_1) {
  char expression[] = "9 ^ (sin(3))";
  long double calculation = 0;
  long double result_check = 1.3635238;
  int error_check = 1;  // can calculate
  int error = calcInputExprAndX(expression, 0, &calculation);
  ck_assert_double_eq_tol(calculation, result_check, 0.01);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(calc_2) {
  char expression[] = "(-((0.0000001*7)+6*(9-2.01)/8.4+(0.32^5)))";
  long double calculation = 0;
  long double result_check = -4.9962133;
  int error_check = 1;
  int error = calcExpr(expression, &calculation);
  ck_assert_double_eq_tol(calculation, result_check, 0.0000001);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(calc_3) {
  char expression[] = "77mod4-((3*(3^6))-700)/24*12-2";  // % заменить на MOD
  long double calculation = 0;
  long double result_check = -744.5;
  int error_check = 1;
  int error = calcExpr(expression, &calculation);
  ck_assert_double_eq_tol(calculation, result_check, 0.000001);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(calc_4) {
  char expression[] = "-tan(2)/acos(-1)";
  long double calculation = 0;
  long double result_check = 0.6955198;
  int error_check = 1;
  int error = calcExpr(expression, &calculation);
  ck_assert_double_eq_tol(calculation, result_check, 0.000001);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(calc_5) {
  char expression[] = "cos(sin(1))";
  long double calculation = 0;
  long double result_check = 0.6663667;
  int error_check = 1;
  int error = calcExpr(expression, &calculation);
  ck_assert_double_eq_tol(calculation, result_check, 0.000001);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(calc_6) {
  char expression[] = "asin(atan(1)) + sqrt(23/ln(123)) - log(100)";
  long double calculation = 0;
  long double result_check = 1.0895537;
  int error_check = 1;
  int error = calcExpr(expression, &calculation);
  ck_assert_double_eq_tol(calculation, result_check, 0.000001);
  ck_assert_int_eq(error, error_check);
}
END_TEST

START_TEST(calc_7) {
  char expression[] = "9 ^ (sin(X+3))";
  long double calculation = 0;
  long double X = -44;
  long double result_check = 1.41698;
  int error_check = 1;  // can calculate
  int error = calcInputExprAndX(expression, X, &calculation);
  ck_assert_double_eq_tol(calculation, result_check, 0.01);
  ck_assert_int_eq(error, error_check);
}
END_TEST

Suite *calc_tests(void) {
  Suite *s = suite_create("\033[45m--- MAIN CALC ---\033[0m");
  TCase *cases = tcase_create("MAIN CALC: ");
  suite_add_tcase(s, cases);
  tcase_add_test(cases, calc_1);
  tcase_add_test(cases, calc_2);
  tcase_add_test(cases, calc_3);
  tcase_add_test(cases, calc_4);
  tcase_add_test(cases, calc_5);
  tcase_add_test(cases, calc_6);
  tcase_add_test(cases, calc_7);

  return s;
}
