#include "s21_math.h"

long double s21_asin(double x) {
  long double result;
  if (x != x || x < -1 || x > 1)
    result = s21_NAN;
  else {
    long double angle = 0;
    long double xtemp = (x > 0) ? x : x * (-1.0);  // absolute value
    long double sign = (x < 0) ? -1.00 : 1.00;
    angle = s21_arcsin_series(xtemp);
    result = sign * angle;
  }
  return result;
}