#include "s21_math.h"

// atan(x) = (-1)^(n-1) * x^(2n-1)/(2n-1)
long double s21_atan(double x) {
  long double absX = s21_fabs(x);
  long double my_atan;
  long double sign = (x >= 0) ? 1 : -1;
  if (absX < 0.9)
    my_atan = sign * s21_atan_series(absX);
  else if (absX >= 0.9 && absX <= 1.1) {
    my_atan = sign * s21_binaryTreeAtan(absX);
  } else
    my_atan = sign * (s21_PI / 2 - s21_atan_series(1 / absX));
  return my_atan;
}
