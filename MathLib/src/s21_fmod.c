#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double ost = 0;
  if (y == 0 || x == s21_INF)
    ost = s21_NAN;
  else if (y == s21_INF)
    ost = x;
  else {
    int integer = x / y;
    ost = x - (integer * y);
  }
  return ost;
}