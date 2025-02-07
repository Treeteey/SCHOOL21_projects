#include "s21_math.h"

long double s21_sin(double x)  //команда для вызова функции синуса
{
  long double sin_sign = s21_sinsign(x);
  long double base = s21_sin_series(x);
  return sin_sign * base;
};