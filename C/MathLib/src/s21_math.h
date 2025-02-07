#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdio.h>
#include <stdlib.h>

#define s21_MAX_10_EXP 308  // Максимальный показатель десятичной степени
#define s21_MIN_10_EXP (-307)  // Минимальный показатель десятичной степени

#define s21_MAX_double 1.7976931348623157e+308  // Максимальное значение
#define s21_MIN_double \
  2.2250738585072014e-308  // Минимальное нормализованное положительное значение
#define s21_E 2.71828182845904
#define s21_PI 3.14159265358979323846  // 116

#define s21_INF 1.0 / 0.0
#define s21_NINF -1.0 / 0.0
#define s21_NAN 0.0 / 0.0
#define s21_N_NAN -0.0 / 0.0

// 1 вычисляет абсолютное значение целого числа
int s21_abs(int x);

// 2 вычисляет арккосинус
long double s21_acos(double x);

// 3 вычисляет арксинус
long double s21_asin(double x);

// 4 вычисляет арктангенс
long double s21_atan(double x);

// 5 возвращает ближайшее целое число, не меньшее заданного значения
long double s21_ceil(double x);

// 6 вычисляет косинус
long double s21_cos(double x);

// 7 возвращает значение e, возведенное в заданную степень (good)
long double s21_exp(double x);

// 8 вычисляет абсолютное значение числа с плавающей точкой
long double s21_fabs(double x);

// 9 возвращает ближайшее целое число, не превышающее заданное значение
long double s21_floor(double x);

// 10 остаток операции деления с плавающей точкой
long double s21_fmod(double x, double y);

// 11 вычисляет натуральный логарифм
long double s21_log(double x);

// 12 возводит число в заданную степень
long double s21_pow(double base, double exp);

// 13 вычисляет синус
long double s21_sin(double x);

// 14 вычисляет квадратный корень
long double s21_sqrt(double x);

// 15 вычисляет тангенс
long double s21_tan(double x);

// Вспомогательные функции:
int s21_checkArgAsin(double x);  //аргумент не может быть больше 1 и меньше

long double s21_binaryTreeAngleAsin(
    double x);  // if |x| > 0.9 we calculate angle using s21_cos amd binary tree
                // method
long double s21_arcsin_series(long double xtemp);  //степенной ряд

int s21_cossign(double x);  //знак косинуса в зависимости от угла
int s21_sinsign(double x);  //знак синуса в зависимости от угла
long double s21_reduceAngle(
    double x);  //если угол больше 2пи или меньше -2п то нужно привести его к
                //более читабельному виду в диапазоне -2PI < x < 2PI
long double s21_AngleToStand(
    double x);  //приведение угла к виду х < PI/2 - нужно для рядов маклорена
long double s21_cos_series(double x);  //сумма ряда маклорена для косинуса
long double s21_sin_series(double x);  //сумма ряда маклорена для синуса
long double s21_binaryTreeAngleAsin(
    double x);  // расчет угла методом бинарного поиска улучшает решение при x >
                // 0.9

long double s21_binaryTreeAtan(double x);  // if |x| = 0.9...1.1
long double s21_atan_series(double x);     //степенной ряд

long double s21_tan_norm_angle(double x);  // x must be between -PI/2 ... PI/2

long double s21_factorial(int n);                      // n!
long double s21_simple_power(double base, int index);  // вычисление целого

#endif  // SRC_S21_MATH_H_