#include "s21_math.h"

long double s21_tan(double x) {
  long double xnorm = s21_tan_norm_angle(x);
  long double sign = (xnorm >= 0) ? 1 : -1;
  long double xabsnorm = s21_fabs(xnorm);
  long double tang = sign * (s21_sin(xabsnorm) / s21_cos(xabsnorm));
  return tang;
}