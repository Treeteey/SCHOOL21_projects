#include "s21_decimal.h"

void decimal_zeroing(s21_decimal *dst) {  //обнуляет переменную типа децимал
  for (int i = 0; i < 4; i++) {
    dst->bits[i] =
        0;  // Обнуляем все элементы массива перед записью нового значения
  }
}

// // int to decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else {
    decimal_zeroing(dst);
    int symbol = 0;  //знак +/-
    if (src < 0) {   //отрицательное число
      symbol = 1;
      src = -src;
    }
    setBit(dst, 127, symbol);

    dst->bits[0] = src;
  }
  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else {
    //функция отсекающая дробную часть(приводит степень к 0)
    s21_truncate(src, &src);
    if (src.bits[1] == 0 && src.bits[2] == 0) {
      *dst = src.bits[0];  //запишется положительное значение
      int symbol = getBit(src, 127);  //знак +/-
      if (symbol == 1) {
        *dst = -*dst;
      }
    } else {  //значение, хранимое в дециал больше |2147483647| - max int
      res = 1;
    }
  }
  return res;
}

int countDecimalPlaces(
    float num) {  //подсчет числа значащих знаков после запятой(первые 7
                  //значимых/до конца если значимых меньше 7)
  // Используем функцию modf() из библиотеки math.h для получения дробной части
  // числа
  double intPart;
  double fractionalPart = modf(num, &intPart);

  // Инициализируем счетчик знаков после запятой
  int count = 0;

  // Умножаем дробную часть на 10 до тех пор, пока она не станет равной 0
  //первые 0 являются незначими, пока не найдем первый не 0, все последующие
  //значения значимые
  int flag_zero = 1;  //флаг проверяющий равенство 0
  while (fabs(fractionalPart) > 0 && flag_zero == 1) {
    fractionalPart *= 10;
    fractionalPart = modf(fractionalPart, &intPart);
    if (intPart != 0) flag_zero = 0;
    count++;
  }  //как выйдем из этого цикла следующие зачения будут значимыми либо уже
     //дошли до конца введенного значения
  int count_significant_figure =
      1;  //при выходе из прошлого цикла одна значимая цифра былв учтена
  while (fabs(fractionalPart) > 0 && count_significant_figure < 7) {
    fractionalPart *= 10;
    fractionalPart = modf(fractionalPart, &intPart);
    count++;
    count_significant_figure++;
  }

  return count;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else {
    double temp = 0;
    int exp = getExp(src);
    for (int i = 0; i < 96; i++) {
      if ((src.bits[i / 32] & (1 << i % 32)) !=
          0) {  //определяет какой бит находится на позиции i
        temp += pow(2, i);
      }
    }
    for (int i = 0; i < exp; i++) temp /= 10.0;
    *dst = (float)temp;
    if (getBit(src, 127) == 1) {
      *dst = -*dst;
    }
  }
  return res;
}

// float to decimal-
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else if (fabs(src) > 0 && fabs(src) < 1e-28) {
    res = 1;
    decimal_zeroing(dst);
  } else {
    double wholePart = 0;
    double decimalPart = modf(
        src, &wholePart);  //получаю целую и дробную части(знаки сохраняются)

    int symbol = src < 0 ? 1 : 0;  //запоминаю знак
    s21_decimal decimalWholePart = {.bits = {0, 0, 0, 0}};
    // Преобразуем целую часть числа
    int intWholePart = (int)wholePart;
    s21_from_int_to_decimal(intWholePart, &decimalWholePart);
    setBit(&decimalWholePart, 127, symbol);

    int countDecimal = countDecimalPlaces(src);  //число знаков после запятой
    for (int i = 0; i < countDecimal; i++) {
      decimalPart *= 10.0;
    }
    decimalPart =
        roundf(decimalPart);  //округляется к ближайшему(для тех значений где
                              //после точки больше 7 знаков)
    int trueDecimalPart = (int)decimalPart;  //дробная часть в виде целого числа

    s21_decimal decimalDecimalPart = {.bits = {0, 0, 0, 0}};
    s21_from_int_to_decimal(trueDecimalPart, &decimalDecimalPart);
    setBit(&decimalDecimalPart, 127, symbol);
    increaseExpByN(&decimalDecimalPart,
                   countDecimal);  //приписываю нужную степень, т.к. в мантису
                                   //записал значение умноженное на 10 в 6

    decimal_zeroing(dst);
    s21_add(decimalWholePart, decimalDecimalPart, dst);
  }
  return res;
}