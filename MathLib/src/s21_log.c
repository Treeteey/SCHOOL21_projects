#include "s21_math.h"

long double s21_log(
    double x)  // Метод Маклорена ln(x) = 2* (((x-1) / (x+1))^1 / 1 + ((x-1) /
               // (x+1))^3 / 3 + ((x-1) / (x+1))^5 / 5 + ...)
{
  double big_result = 0.0;
  double result = 0.0;
  double currentValue = (x - 1) / (x + 1);
  double valueSquared = currentValue * currentValue;
  // double small_fractional = 0;
  int n = 1;

  long double res = 0;

  if (x > 0 && x < 1) {
    // small_fractional = 1;
    double term = x - 1;
    double numerator = term;
    double denominator = 1;

    for (int n = 1; n <= 1000; n++) {
      result += numerator / denominator;
      numerator *= -term;  // Меняем знак для следующего члена ряда
      denominator++;
    }
  } else if (x < 0)
    res = s21_N_NAN;
  else if (x == 0)
    res = s21_NINF;
  else if (x != x || x == s21_NINF)
    res = s21_NAN;
  else if (x == s21_INF)
    res = s21_INF;
  else if (x > 1) {
    while (currentValue > 1e-15) {
      big_result += currentValue / n;
      currentValue *= valueSquared;
      n += 2;
    }
    res = 2 * big_result;
  }

  return (x > 0 && x < 1) ? result : res;
}
