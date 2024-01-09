#include "s21_math.h"

long double s21_pow(double base, double exp) {
  double result = 1.0;
  if (exp == 0.0)
    result = 1.0;
  else {
    double positiveExp = exp < 0 ? s21_fabs(exp) : exp;  // Положительная часть
    double fractionExp = positiveExp - (int)positiveExp;
    double integerExp = (int)positiveExp;

    while (integerExp > 0.0) {  // Работа с целой частью
      result *= base;
      integerExp--;
    }

    if (fractionExp > 0.0)
    // Работа с дробной частью с помощью экспоненты и логарифма
    // a^b = e^(b * ln(a))
    {
      result *= s21_exp(fractionExp * s21_log(base));
    }
  }

  return exp < 0 ? 1 / result
                 : result;  // Для расчета отрицательного значения степени
}