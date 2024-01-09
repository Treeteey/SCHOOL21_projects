#include "s21_math.h"

long double s21_exp(double x) {  // e^x = 1 + x^1/1! + x^2/2! + x^3/3! + ...
  double y = x;
  long double result = 0;

  if (x != x)
    result = s21_NAN;
  else if (x == 0)
    result = 1;
  else if (x > 709.78271289)
    result = s21_INF;
  else if (x < -745.133219)
    result = 0;
  else {
    if (x < 0) x = x * (-1);

    int integerValue = (int)x;
    double fractionValue = x - integerValue;
    long double integerExp = 1.0;

    if (integerValue != 0) {
      integerExp = s21_simple_power(s21_E, integerValue);
    }
    long double fractionExp = 1.0;
    if (fractionValue != 0.0)  // Для существующей дроби
    {
      long double sum = 0.0;
      int n = 0;
      long double value = 1.0;

      while (value > 1e-15)  // 0.000000000000001
      {
        sum += value;
        n++;
        value = s21_simple_power(fractionValue, n) / s21_factorial(n);
      }
      fractionExp = sum;
    }
    result = integerExp * fractionExp;  // Перемножение целой и дробной части
    result = y < 0 ? 1 / result : result;
  }
  return result;  // Для расчета отрицательного значения степени
}