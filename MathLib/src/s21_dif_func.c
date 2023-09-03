#include "s21_math.h"

long double s21_factorial(int n)  // for exp & asin
{  // высчитывание факторилала
  if (n == 0)
    return 1;
  else
    return n * s21_factorial(n - 1);
}

long double s21_simple_power(double base, int index)  // for exp
{  // возведение в степень
  long double result = 1.0;
  for (int i = 0; i < index; i++) {
    result *= base;
  }
  return result;
}

///////// for asin ↓

long double s21_arcsin_series(long double xtemp)  // степенной ряд
{
  long double angletemp = 0;
  long double arcsin = xtemp;
  long double series = 0;
  if (xtemp < 0.9) {
    for (int i = 1; i < 100; i++) {
      series = (s21_factorial(2 * i) * s21_pow(xtemp, (2 * i + 1))) /
               (s21_pow(4, i) * s21_pow(s21_factorial(i), 2) *
                (2 * i + 1));  // (2i)! * x^(2i+1) / (4^i * (i!)^2 * (2*i + 1))
                               // - член степенного ряда
      arcsin = arcsin + series;
      ;
    }
    angletemp = arcsin;
  } else if (xtemp > 0.999999999)
    angletemp = s21_PI / 2;  // if |x| ~ 1
  else
    angletemp = s21_binaryTreeAngleAsin(xtemp);  // if x > 0.9
  return angletemp;
}

long double s21_binaryTreeAngleAsin(
    double x)  //  расчет угла методом бинарного поиска улучшает решение при x >
               //  0.9
{
  long double angle = 0;
  long double precision = 0.0000000001;
  long double low = 0;
  long double high = s21_PI / 2;
  long double mid, cos;
  int n = 0;
  while ((high - low) > precision && n < 50) {
    mid = (high + low) / 2.0;  // middle of interval
    cos = s21_cos(mid);
    n = n + 1;
    if (s21_fabs(cos - x) <
        precision) {  // if precision is good return our angle
      angle = mid;
    } else if (cos > x) {  // if not precise enough and cos higher than x -
                           // reduce high value to mid
      low = mid;
    } else
      high = mid;  // if not precise enough and cos lower than x - increase low
                   // value to mid
  }
  return angle = s21_PI / 2 - angle;  // PI/2 - a   , and we need only a
}

///////// for asin ↑

///////// for atan ↓

// must put absolute value - if |x| = 0.9...1.1
long double s21_binaryTreeAtan(double x)  // if |x| = 0.9...1.1
{
  long double angle = 0;
  long double precision = 0.000000000000001;
  long double low = 0;
  long double high = s21_PI / 2;
  long double mid, tang;
  int n = 0;
  int bool = 0;
  while ((high - low) > precision && n < 100 && bool != 1) {
    mid = (high + low) / 2;  // middle of interval
    tang = s21_sin(mid) / s21_cos(mid);
    n = n + 1;
    if (s21_fabs(tang - x) <
        precision) {  // if precision is good return our angle
      angle = mid;
      bool = 1;
    } else if (tang > x) {  // if not precise enough and tang higher than x -
                            // reduce high value to mid
      high = mid;
    } else
      low = mid;  // if not precise enough and tang lower than x - increase low
                  // value to mid
  }
  return angle;
}

long double s21_atan_series(double x) {
  long double series = 0;
  long double xtemp = s21_fabs(x);
  for (int n = 1; n < 200; n++) {
    series += s21_pow(-1, n - 1) * s21_pow(xtemp, (2 * n - 1)) / (2 * n - 1);
  }
  return series;
}

///////// for atan ↑

///////// for tan ↓

// x must be between -PI/2 ... PI/2
long double s21_tan_norm_angle(double x) {
  if (x > s21_PI / 2) {
    while (x > s21_PI / 2) x -= s21_PI;
  }
  if (x < -s21_PI / 2) {
    while (x < -s21_PI / 2) x += s21_PI;
  }
  return x;
}

///////// for tan ↑

///////// for sin_cos ↓

int s21_cossign(double x)  //знак косинуса в зависимости от угла
{
  int znak = 1;
  long double xred =
      s21_reduceAngle(x);  //сначала приведем к виду -2PI < x < 2PI
  if (xred > 0)  //если угол в 1 и 4 четвертях то знак "+", если во 2 и 3 то "-"
  {
    if (xred > s21_PI * 0.5 && xred < 1.5 * s21_PI) znak = -1;
    if (xred <= s21_PI * 0.5 && xred >= 1.5 * s21_PI) znak = 1;
  }
  if (xred < 0) {
    if (xred < -s21_PI * 0.5 && xred > -1.5 * s21_PI) znak = -1;
    if (xred >= -s21_PI * 0.5 && xred <= -1.5 * s21_PI) znak = 1;
  }
  return znak;
}

int s21_sinsign(double x)  //знак синуса в зависимости от угла
{
  int znak = 1;
  double xred = s21_reduceAngle(x);  //сначала приведем к виду -2PI < x < 2PI
  if (xred >
      0)  //если знак в 1 и 2 четвертях то знак "+", если в 3 и 4 то знак "-"
  {
    if (xred >= 0 && xred <= s21_PI) znak = 1;
    if (xred > s21_PI && xred < 2 * s21_PI) znak = -1;
  }
  if (xred < 0) {
    if (xred >= -2 * s21_PI && xred <= -s21_PI) znak = 1;
    if (xred > -s21_PI && xred < 0) znak = -1;
  }
  return znak;
}

long double s21_reduceAngle(
    double x)  //если угол больше 2пи или меньше -2PI то нужно привести его к
               //более читабельному виду в диапазоне -2PI < x < 2PI
{
  long double xtemp = x;
  if (x > 0) {
    while (xtemp >= 2 * s21_PI) xtemp = xtemp - 2 * s21_PI;
  }
  if (xtemp < 0) {
    while (xtemp <= -2 * s21_PI) xtemp = xtemp + 2 * s21_PI;
  }
  return xtemp;
}

//формула ряда маклорена cos(x)= (-1)^n * x^(2n)/(2n)! = A * B / Ccos

//в формуле маклорена угол х желательно привести к виду х < pi/2, знак получим
//из функции cossign() this func must get angle x from -2PI to +2PI range!
long double s21_AngleToStand(double x) {
  if (x < 0) x = x * (-1);
  if (x > s21_PI / 2 && x <= s21_PI) x = s21_PI - x;
  if (x > s21_PI && x <= 1.5 * s21_PI) x = x - s21_PI;
  if (x > 1.5 * s21_PI && x <= 2 * s21_PI) x = 2 * s21_PI - x;
  return x;
}

long double s21_cos_series(double x)  //сумма ряда маклорена для косинуса
{
  long double s = 1.00;
  long double xtemp = s21_AngleToStand(s21_reduceAngle(x));
  for (int n = 100; n > 0; n--)  //
  {
    s = s + s21_pow(-1, n) * (long double)s21_pow(xtemp, 2 * n) /
                s21_factorial(2 * n);
  }
  if (s < 0) s = s * (-1);
  return s;
}

// sin(x)= (-1)^n+1 * x^(2n-1)/(2n-1)! = A * B / Csin
long double s21_sin_series(double x)  //сумма ряда маклорена для синуса
{
  long double s = 0;
  long double xtemp = s21_AngleToStand(s21_reduceAngle(x));
  for (int n = 1; n < 50; n++) {
    s = s + s21_pow(-1, n + 1) * (long double)s21_pow(xtemp, (2 * n - 1)) /
                s21_factorial(2 * n - 1);
  }
  return s;
}

///////// for sin_cos ↑