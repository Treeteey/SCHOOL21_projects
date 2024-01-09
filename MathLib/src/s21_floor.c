#include "s21_math.h"

long double s21_floor(double x) {
  long double ost = 0;
  long double integer = 0;
  if (x == s21_INF)
    integer = s21_INF;
  else if (x == s21_NINF)
    integer = s21_NINF;
  else if (x == 0)
    integer = 0;
  else if (x > 0) {
    ost = x - (long long)x;
    integer = x - ost;
  } else {
    ost = x - (long long)x;
    if (ost == 0)
      integer = x - ost;
    else
      integer = x - ost - 1;
  }
  return integer;
}
