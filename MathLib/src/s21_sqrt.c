#include "s21_math.h"

long double s21_sqrt(double x) {
  long double low = 0.0;
  long double high = x;
  long double mid = 0.0;

  if (x < 0 || x != x)
    low = s21_NAN;
  else if (x < 1)
    low = 1.0 / s21_sqrt(1.0 / x);  // Вычисление от обратного
  {
    while (high - low > 0.000001)  // Условие остановки: достаточная близость
    {
      mid = (low + high) / 2.0;  // Среднее арифметическое
      if (mid * mid > x)  // Перемножение для выявление схожести в вводом
        high = mid;  // Присваивание при большем результате
      else
        low = mid;  // Присваивание при меньшем результате
    }
  }
  return low;
}