#include "s21_math.h"

long double s21_cos(double x) {
  int cos_sign = s21_cossign(x);
  long double base = s21_cos_series(x);
  long double cos = cos_sign * base;
  return cos;
};