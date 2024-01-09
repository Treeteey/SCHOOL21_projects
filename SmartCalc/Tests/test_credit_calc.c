#include "test.h"

START_TEST(CREDIT_ANNUITY_01) {
  long double sum = 3000000;
  int typeTime = 0;  // in years
  int time = 3;      // 3 years
  int type = 0;      // annuity
  long double percent = 12;
  long double *monthPayment = NULL;
  long double over = 0;
  long double total = 0;

  creditCalc(percent, sum, typeTime, time, type, &monthPayment, &over, &total);
  ck_assert_double_eq_tol(monthPayment[0], 99642.93, 1e-1);
  ck_assert_double_eq_tol(total, 3587145.48, 1e-1);
  ck_assert_double_eq_tol(over, 587145.48, 1e-1);
  if (monthPayment != NULL) {
    free(monthPayment);
  }
}
END_TEST

START_TEST(CREDIT_DIFFERENTIATED_02) {
  long double sum = 5500400;
  int typeTime = 1;  // in MONTH
  int time = 75;     // 75 month
  int type = 1;      // differ
  long double percent = 14.2;
  long double *monthPayment = NULL;
  long double over = 0;
  long double total = 0;

  creditCalc(percent, sum, typeTime, time, type, &monthPayment, &over, &total);
  ck_assert_msg(fabsl(monthPayment[0] - 138426.73) < 1,
                "Assertion failed: monthPayment[0] == %.2Lf, expected == "
                "138426.73, tolerance == 0.1",
                monthPayment[0]);
  ck_assert_msg(fabsl(monthPayment[74] - 74206.51) < 1,
                "Assertion failed: monthPayment[74] == %.2Lf, expected == "
                "74206.51, tolerance == 0.1",
                monthPayment[74]);
  ck_assert_msg(fabsl(total - 7973746.53) < 1,
                "Assertion failed: total == %.2Lf, expected == 7973746.53, "
                "tolerance == 0.1",
                total);
  ck_assert_msg(fabsl(over - 2473346.53) < 1,
                "Assertion failed: over == %.2Lf, expected == 2473346.53, "
                "tolerance == 0.1",
                over);
  if (monthPayment != NULL) {
    free(monthPayment);
  }
}
END_TEST

Suite *credit_tests(void) {
  Suite *s = suite_create("\033[45m--- CREDIT tests ---\033[0m");
  TCase *tc1_1 = tcase_create("credit_tests: ");

  suite_add_tcase(s, tc1_1);

  tcase_add_test(tc1_1, CREDIT_ANNUITY_01);
  tcase_add_test(tc1_1, CREDIT_DIFFERENTIATED_02);

  return s;
}