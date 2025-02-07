#include "../s21_math.h"

#include "s21_math_tests.h"

START_TEST(fun_s21_exp) {
  ck_assert_ldouble_nan(s21_exp(s21_NAN));
  ck_assert_ldouble_eq_tol(s21_exp(7.345e-29), exp(7.345e-29), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(0.0), exp(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(28), exp(28), 1e-1);
  ck_assert_ldouble_eq_tol(s21_exp(-5), exp(-5), 1e-6);
  ck_assert_ldouble_eq(s21_exp(s21_MAX_double), exp(s21_MAX_double));
  ck_assert_ldouble_eq(s21_exp(s21_MIN_double), exp(s21_MIN_double));
  ck_assert_ldouble_eq(s21_exp(709.7827129), exp(709.7827129));
  ck_assert_ldouble_eq(s21_exp(-745.13322), exp(-745.13322));
}
END_TEST

START_TEST(fun_s21_log) {
  ck_assert_ldouble_nan(s21_log(s21_NAN));
  ck_assert_ldouble_nan(s21_log(s21_NINF));
  ck_assert_ldouble_nan(s21_log(-1));
  ck_assert_ldouble_nan(s21_log(-987565.9874641213656));
  ck_assert_ldouble_eq(s21_log(0), log(0));
  ck_assert_ldouble_eq_tol(s21_log(0.23455), log(0.23455), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(0.3), log(0.3), 1e-6);
  ck_assert_ldouble_infinite(s21_log(s21_INF));
  ck_assert_ldouble_eq(s21_log(s21_INF), log(s21_INF));
  ck_assert_ldouble_eq(s21_log(1), log(1));
  ck_assert_ldouble_eq_tol(s21_log(1.233), log(1.233), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(987565.9874641213656),
                           log(987565.9874641213656), 1e-6);
}
END_TEST

START_TEST(fun_s21_sqrt) {
  ck_assert_ldouble_nan(s21_sqrt(s21_NAN));
  ck_assert_ldouble_nan(s21_sqrt(-34.12));
  ck_assert_ldouble_eq_tol(s21_sqrt(5), sqrt(5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(1000), sqrt(1000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(987565.9874641213656),
                           sqrt(987565.9874641213656), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(1e-7), sqrt(1e-7), 1e-6);
}
END_TEST

START_TEST(fun_s21_fabs) {
  ck_assert_ldouble_nan(s21_fabs(s21_NAN));
  ck_assert_ldouble_eq(s21_fabs(-1.000005), fabs(-1.000005));
  ck_assert_ldouble_eq_tol(s21_fabs(987565.9874641213656),
                           fabs(987565.9874641213656), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fabs(-987565.9874641213656),
                           fabs(-987565.9874641213656), 1e-6);
  ck_assert_ldouble_eq(s21_fabs(s21_MAX_double), fabs(s21_MAX_double));
  ck_assert_ldouble_eq(s21_fabs(s21_MIN_double), fabs(s21_MIN_double));
  ck_assert_ldouble_eq_tol(s21_fabs(0.0), fabs(0.0), 1e-6);
}
END_TEST

START_TEST(fun_s21_fmod) {
  ck_assert_ldouble_nan(s21_fmod(2, 0.0));
  ck_assert_ldouble_nan(s21_fmod(s21_NAN, 2));
  ck_assert_ldouble_nan(s21_fmod(2, s21_NAN));
  ck_assert_ldouble_nan(s21_fmod(s21_INF, 14));

  ck_assert_ldouble_eq(s21_fmod(0.0, 2), fmod(0.0, 2));
  ck_assert_ldouble_eq(s21_fmod(17, 3), fmod(17, 3));
  ck_assert_ldouble_eq(s21_fmod(-35, 6), fmod(-35, 6));
  ck_assert_ldouble_eq(s21_fmod(75, -8), fmod(75, -8));
  ck_assert_ldouble_eq(s21_fmod(-144, -27), fmod(-144, -27));

  ck_assert_ldouble_eq_tol(s21_fmod(10, 0.000008), fmod(10, 0.000008), 1e-6);
  ck_assert_ldouble_eq_tol(s21_fmod(11, 0.003), fmod(11, 0.003), 1e-6);

  ck_assert_ldouble_eq_tol(s21_fmod(14, s21_INF), fmod(14, s21_INF), 1e-6);
}
END_TEST

START_TEST(fun_s21_seil) {
  ck_assert_ldouble_nan(s21_ceil(s21_NAN));
  ck_assert_ldouble_infinite(s21_ceil(s21_INF));
  ck_assert_ldouble_eq(s21_ceil(s21_INF), ceil(s21_INF));
  ck_assert_ldouble_eq(s21_ceil(s21_NINF), ceil(s21_NINF));
  ck_assert_ldouble_eq(s21_ceil(1), ceil(1));
  ck_assert_ldouble_eq(s21_ceil(-1), ceil(-1));
  ck_assert_ldouble_eq(s21_ceil(-12345), ceil(-12345));
  ck_assert_ldouble_eq(s21_ceil(0.0), ceil(0.0));
  ck_assert_ldouble_eq(s21_ceil(35465.2345675), ceil(35465.2345675));
  ck_assert_ldouble_eq(s21_ceil(-780675.2346), ceil(-780675.2346));
  ck_assert_ldouble_eq(s21_ceil(s21_MIN_double), ceil(s21_MIN_double));
  ck_assert_ldouble_eq(s21_ceil(4732323456789076.5), ceil(4732323456789076.5));
}
END_TEST

START_TEST(fun_s21_floor) {
  ck_assert_ldouble_nan(s21_floor(s21_NAN));
  ck_assert_ldouble_infinite(s21_floor(s21_INF));
  ck_assert_ldouble_eq(s21_floor(s21_INF), floor(s21_INF));
  ck_assert_ldouble_eq(s21_floor(s21_NINF), floor(s21_NINF));
  ck_assert_ldouble_eq(s21_floor(1), floor(1));
  ck_assert_ldouble_eq(s21_floor(-1), floor(-1));
  ck_assert_ldouble_eq(s21_floor(-12345), floor(-12345));
  ck_assert_ldouble_eq(s21_floor(0.0), floor(0.0));
  ck_assert_ldouble_eq(s21_floor(35465.2345675), floor(35465.2345675));
  ck_assert_ldouble_eq(s21_floor(-780675.2346), floor(-780675.2346));
  ck_assert_ldouble_eq(s21_floor(s21_MIN_double), floor(s21_MIN_double));
  ck_assert_ldouble_eq(s21_floor(1e-7), floor(1e-7));
  ck_assert_ldouble_eq(s21_floor(1.79769e+3), floor(1.79769e+3));
  ck_assert_ldouble_eq(s21_floor(4732323456789076.5),
                       floor(4732323456789076.5));
}
END_TEST

START_TEST(fun_s21_abs) {
  ck_assert_int_eq(s21_abs(-1), abs(-1));
  ck_assert_int_eq(s21_abs(987565), abs(987565));
  ck_assert_int_eq(s21_abs(-987565), abs(-987565));
  ck_assert_int_eq(s21_abs(0), abs(0));
  ck_assert_int_eq(s21_abs(056), abs(056));
  ck_assert_int_eq(s21_abs(-0765), abs(-0765));
  ck_assert_int_eq(s21_abs(-000132435465), abs(-000132435465));
}
END_TEST

START_TEST(fun_s21_pow) {
  ck_assert_ldouble_nan(s21_pow(-77, -0.532));
  ck_assert_ldouble_eq(s21_pow(0.0, 3), pow(0.0, 3));
  ck_assert_ldouble_eq(s21_pow(123, 0.0), pow(123, 0.0));
  ck_assert_ldouble_eq(s21_pow(0.0, 0.0), pow(0.0, 0.0));
  ck_assert_ldouble_eq(s21_pow(17, 3), pow(17, 3));
  ck_assert_ldouble_eq_tol(s21_pow(31.456, 0.3), pow(31.456, 0.3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_pow(23, -5.1), pow(23, -5.1), 1e-6);
}
END_TEST

START_TEST(fun_s21_acos) {
  ck_assert_ldouble_nan(s21_acos(s21_NAN));
  ck_assert_ldouble_nan(s21_acos(1.01));
  ck_assert_ldouble_nan(s21_acos(-1.01));
  ck_assert_ldouble_eq(s21_acos(1), acos(1));
  ck_assert_ldouble_eq(s21_acos(0), acos(0));
  ck_assert_ldouble_eq(s21_acos(-1), acos(-1));
  ck_assert_ldouble_eq_tol(s21_acos(0.0000315580447250),
                           acos(0.0000315580447250), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-0.0000312143567211),
                           acos(-0.0000312143567211), 1e-6);
}
END_TEST

START_TEST(fun_s21_asin) {
  ck_assert_ldouble_nan(s21_asin(s21_NAN));
  ck_assert_ldouble_nan(s21_asin(1.01));
  ck_assert_ldouble_nan(s21_asin(-1.01));
  ck_assert_ldouble_eq(s21_asin(1), asin(1));
  ck_assert_ldouble_eq(s21_asin(0), asin(0));
  ck_assert_ldouble_eq(s21_asin(-1), asin(-1));
  ck_assert_ldouble_eq_tol(s21_asin(0.0000315580447250),
                           asin(0.0000315580447250), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-0.0000312143567211),
                           asin(-0.0000312143567211), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0.92435465), asin(0.92435465), 1e-6);
}
END_TEST

START_TEST(fun_s21_atan) {
  ck_assert_ldouble_nan(s21_atan(s21_NAN));
  ck_assert_ldouble_eq(s21_atan(1), atan(1));
  ck_assert_ldouble_eq(s21_atan(0), atan(0));
  ck_assert_ldouble_eq(s21_atan(-1), atan(-1));
  ck_assert_ldouble_eq_tol(s21_atan(0.0000315580447250),
                           atan(0.0000315580447250), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0.0000312143567211),
                           atan(-0.0000312143567211), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0.0000312143567211),
                           atan(-0.0000312143567211), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(1.5707947559985698),
                           atan(1.5707947559985698), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(s21_MAX_double), atan(s21_MAX_double),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(s21_MIN_double), atan(s21_MIN_double),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0.9234546023242), atan(0.9234546023242),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(1.00001345975937), atan(1.00001345975937),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0.9897812523342), atan(-0.9897812523342),
                           1e-6);
}
END_TEST

START_TEST(fun_s21_cos) {
  ck_assert_ldouble_nan(s21_cos(s21_NAN));
  ck_assert_ldouble_eq_tol(s21_cos(1), cos(1), 1e-6);
  ck_assert_ldouble_eq(s21_cos(0), cos(0));
  ck_assert_ldouble_eq_tol(s21_cos(-1), cos(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(0.0000315580447250), cos(0.0000315580447250),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(s21_PI * 1.5), cos(s21_PI * 1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-s21_PI * 1.5), cos(-s21_PI * 1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(3.12), cos(3.12), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(s21_PI), cos(s21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-s21_PI), cos(-s21_PI), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(6.2), cos(6.2), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-9.012), cos(-9.012), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(-0.0000312143567211),
                           cos(-0.0000312143567211), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(987565.9874641213656),
                           cos(987565.9874641213656), 1e-6);
  ck_assert_ldouble_eq_tol(s21_cos(s21_MIN_double), cos(s21_MIN_double), 1e-6);
}
END_TEST

START_TEST(fun_s21_sin) {
  ck_assert_ldouble_nan(s21_sin(s21_NAN));
  ck_assert_ldouble_eq_tol(s21_sin(1), sin(1), 1e-6);
  ck_assert_ldouble_eq(s21_sin(0), sin(0));
  ck_assert_ldouble_eq_tol(s21_sin(-1), sin(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(0.0000315580447250), sin(0.0000315580447250),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(s21_PI * 1.5), sin(s21_PI * 1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-s21_PI * 1.5), sin(-s21_PI * 1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-2.523), sin(-2.523), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(3.8), sin(3.8), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-4.6432), sin(-4.6432), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(-0.0000312143567211),
                           sin(-0.0000312143567211), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(987565.9874641213656),
                           sin(987565.9874641213656), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sin(s21_MIN_double), sin(s21_MIN_double), 1e-6);
}
END_TEST

START_TEST(fun_s21_tan) {
  ck_assert_ldouble_nan(s21_tan(s21_NAN));
  ck_assert_ldouble_eq_tol(s21_tan(1), tan(1), 1e-6);
  ck_assert_ldouble_eq(s21_tan(0), tan(0));
  ck_assert_ldouble_eq_tol(s21_tan(-1), tan(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(9875.9874641213656), tan(9875.9874641213656),
                           1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(1), tan(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(s21_MIN_double), tan(s21_MIN_double), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-0.0000312143567211),
                           tan(-0.0000312143567211), 1e-6);
  ck_assert_ldouble_eq_tol(s21_tan(-1453.34842), tan(-1453.34842), 1e-6);
}
END_TEST

Suite *suite_fun_math(void) {
  Suite *suite;
  TCase *all_tcase;

  suite = suite_create("fun_math");
  all_tcase = tcase_create("All_case");

  tcase_add_test(all_tcase, fun_s21_exp);
  tcase_add_test(all_tcase, fun_s21_log);
  tcase_add_test(all_tcase, fun_s21_sqrt);
  tcase_add_test(all_tcase, fun_s21_fabs);
  tcase_add_test(all_tcase, fun_s21_fmod);
  tcase_add_test(all_tcase, fun_s21_seil);
  tcase_add_test(all_tcase, fun_s21_floor);
  tcase_add_test(all_tcase, fun_s21_abs);
  tcase_add_test(all_tcase, fun_s21_pow);
  tcase_add_test(all_tcase, fun_s21_acos);
  tcase_add_test(all_tcase, fun_s21_asin);
  tcase_add_test(all_tcase, fun_s21_atan);
  tcase_add_test(all_tcase, fun_s21_cos);
  tcase_add_test(all_tcase, fun_s21_sin);
  tcase_add_test(all_tcase, fun_s21_tan);

  suite_add_tcase(suite, all_tcase);

  return suite;
}

int main(void) {
  int failed_count;
  Suite *suite;
  SRunner *srunner;

  suite = suite_fun_math();
  srunner = srunner_create(suite);

  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_NORMAL);
  failed_count = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}