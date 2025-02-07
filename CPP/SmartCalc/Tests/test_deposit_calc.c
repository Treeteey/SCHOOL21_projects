#include "test.h"

START_TEST(Deposit_capital_01) {
  long double sum = 22000000;
  int postingPeriod = 2;  // in years
  int timeOfPosting = 3;  // 3 years
  int startDay = 5, startMonth = 1, startYear = 2023;

  long double interest = 15;  //процентная ставка
  long double taxInput = 16;  //ключевая ставка банка
  int capitalization = 1;  //капитализация процентов включена
  int payoutPeriod = 1;  //выплаты ежедневно|капитализия процентов
  long double total = 0;
  long double gainedInterest = 0;
  long double taxSum = 0;

  depositCalc(startDay, startMonth, startYear, sum, postingPeriod,
              timeOfPosting, interest, payoutPeriod, &total, &gainedInterest,
              &taxSum, capitalization, taxInput);
  ck_assert_double_eq_tol(gainedInterest, 12499681.67, 1);
  ck_assert_double_eq_tol(total, 34499681.67, 1);
  ck_assert(fabsl(taxSum - 1541758.62) < 1);
}
END_TEST

START_TEST(Deposit_norm_02) {
  int startDay = 5, startMonth = 1, startYear = 2023;
  long double sum = 22000000;
  int postingPeriod = 0;        // in days
  int timeOfPosting = 50;       // 50 days
  long double interest = 12.2;  //процентная ставка
  long double taxInput = 15;
  int capitalization = 0;  //капитализация процентов выключена
  int payoutPeriod = 3;  //выплаты ежемесячно
  long double total = 0;
  long double gainedInterest = 0;
  long double taxSum = 0;

  depositCalc(startDay, startMonth, startYear, sum, postingPeriod,
              timeOfPosting, interest, payoutPeriod, &total, &gainedInterest,
              &taxSum, capitalization, taxInput);
  ck_assert_double_eq_tol(gainedInterest, 367671.23, 1);
  ck_assert_double_eq_tol(total, 22367671.23, 1);
  ck_assert_double_eq_tol(taxSum, 28297.26, 1);
}
END_TEST

START_TEST(Deposit_norm_03) {
  int startDay = 17, startMonth = 11, startYear = 2023;
  long double sum = 5000000;
  int postingPeriod = 1;      // in month
  int timeOfPosting = 15;     // 15 month
  long double interest = 15;  //процентная ставка
  long double taxInput = 13;
  int capitalization = 0;  //капитализация процентов выключена
  int payoutPeriod = 2;  //выплаты every week
  long double total = 0;
  long double gainedInterest = 0;
  long double taxSum = 0;

  depositCalc(startDay, startMonth, startYear, sum, postingPeriod,
              timeOfPosting, interest, payoutPeriod, &total, &gainedInterest,
              &taxSum, capitalization, taxInput);
  ck_assert_double_eq_tol(gainedInterest, 934931.51, 1);
  ck_assert_double_eq_tol(total, 5934931.51, 1);
  ck_assert_double_eq_tol(taxSum, 84001.37, 1);
}
END_TEST

Suite *deposit_tests(void) {
  Suite *s = suite_create("\033[45m--- Deposit tests ---\033[0m");
  TCase *cases = tcase_create("Deposit tests: ");

  suite_add_tcase(s, cases);

  tcase_add_test(cases, Deposit_capital_01);
  tcase_add_test(cases, Deposit_norm_02);
  tcase_add_test(cases, Deposit_norm_03);

  return s;
}