#include "s21_decimal.h"
/*
Возвращаемое значение - код ошибки:

0 - OK
1 - ошибка вычисления
*/

/*
Округляет указанное Decimal число
до ближайшего целого числа в сторону отрицательной бесконечности.
*/
int s21_floor(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  if (!result) {
    ret = 1;
  } else {
    s21_decimal temp = value;
    temp.bits[3] = 0;
    int exp = getExp(value), sign = getBit(value, 127), stop = 0;
    //подведем к степени 0 = в мантиссе будут целые числа,
    //к степени 1 - сможем решать что делать дальше
    while (exp > 1 && stop == 0 &&
           ret == 0)  // 54352*10^-4 -> 5435*10^-3 ->...-> 54*10^-1 = 5.4 ~ 5,
                      // -5,4 ~ -6
    {
      stop = s21_div_ten(temp, &temp);  // 1- ошибка, 0 - хорошо
      if (stop == 0) exp -= 1;
    }
    ret = floor_based_on_exp(temp, exp, sign, result);
  }
  return ret;
}

/*          floor_based_on_exp
если exp = 1 //значит смогли доделить мантиссу на 10     98*e-1  3е-1
    если можем поделить на 10   98*e-1
        если положительное число просто возвращаем поделенное число   = 9
        если отрицательное число -98*e-1
            если последняя цифра до деления (lastDigit) равна 0 просто делим
(последняя цифра 8 в 98е-1) если не равна то делим и вычитаем 1    -9-1 = -10
    если не можем поделить на 10     3е-1
        если положительное
            то вернуть {0,0,0,0}
        если отрицательное
            {1,0,0,0b1000....0}
если степень >1 //значит больше не можем делить мантиссу на 10
    если положительное
        то вернуть {0,0,0,0}
    если отрицательное
        {1,0,0,0b1000....0}
*/
int floor_based_on_exp(s21_decimal temp, int exp, int sign,
                       s21_decimal *result) {
  int ret = 0;
  int lastDigit = get_smallestrank_digit(
      temp);  //-54359*10-3 = 9  - последнее число мантиссы
  s21_decimal oneDec = {.bits = {1, 0, 0, 0}};
  s21_decimal zeroDec = {.bits = {0, 0, 0, 0}};
  s21_decimal minusOneDec = {
      .bits = {1, 0, 0, 0b10000000000000000000000000000000}};
  if (exp == 1) {
    if (s21_div_ten(temp, &temp) == 0)  //если смогли поделить
    {
      if (sign == 0)  //если плюс
      {
        writeInDecParts(temp, exp - 1, sign, result);
      } else {  //если минус
        if (lastDigit == 0)
          writeInDecParts(temp, exp, sign, result);
        else {
          if (s21_add_simple(temp, oneDec, &temp) ==
              0)  //если смогли прибавить к мантиссе 1
            writeInDecParts(temp, exp - 1, sign, result);
          else
            ret = 1;  //если не смогли то ошибка!
        }
      }
    } else  //если не смогли поделить
    {
      if (sign == 0)
        *result = zeroDec;
      else
        *result = minusOneDec;
    }
  } else if (exp > 1)  //если степень осталась больше 1 и мантиссу больше
                       //нельзя делить
  {
    if (sign == 0)
      *result = zeroDec;
    else
      *result = minusOneDec;
  } else if (exp == 0)  //если изначально степень была равна 0 то просто
                        //вернуть это же число
  {
    *result = temp;
    setBit(result, 127, sign);
  }
  return ret;
}

/*

Округляет Decimal до ближайшего целого числа

*/
int s21_round(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  if (!result) {
    ret = 1;
  } else {
    s21_decimal temp = value;
    int exp = getExp(value), sign = getBit(value, 127);
    int stop = 0;
    while (exp > 1 && stop == 0)  // 54352*10^-4 -> 5435*10^-3 ->...-> 54*10^-1
                                  // = 5.4 ~ 5,     -5,4 ~ -6
    {
      stop = s21_div_ten(temp, &temp);  // 1- ошибка, 0 - хорошо
      if (stop == 0) exp -= 1;
    }
    ret = round_based_on_exp(temp, exp, sign, result);
  }
  return ret;
}
/*          round_based_on_exp
если exp = 1//значит смогли доделить мантиссу на 10     98*e-1  3е-1
    lastDigit
    если можем поделить на 10   98*e-1 -> 10      93е-1 -> 9       -98e-1 -> -10
-93e-1 -> -9

        если положительное число
            если lastdigit>4 возвращаем поделенное число + 1   = 9 + 1 = 10
            если lastdigit<5 возвращаем поделенное число = 9
        если отрицательное число -98*e-1
            если lastdigit>4 возвращаем поделенное -1 =  -9-1 = -10
            если lastdigit<5 возвращаем поделенное число = -9
        или можно заменить на
        если lastdigit>4 возвращаем поделенное число + sign*1   = 9 + 1*1 = 10
OR -9+ -1*1 = -10 если lastdigit<5 возвращаем поделенное число = 9 если не можем
поделить на 10     3е-1 если положительное если lastdigit>4 возвращаем {1,0,0,0}
            если lastdigit<5 возвращаем {0,0,0,0}
        если отрицательное
            если lastdigit>4 возвращаем {1,0,0,0b100..0}
            если lastdigit<5 возвращаем {0,0,0,0}
        или можно заменить на
        если lastdigit>4 возвращаем sign*1
        если lastdigit<5 возвращаем {0,0,0,0}
если exp > 1 ////значит больше не можем делить мантиссу на 10
    возвращаем {0,0,0,0}
*/
int round_based_on_exp(s21_decimal temp, int exp, int sign,
                       s21_decimal *result) {
  int ret = 0;
  s21_decimal oneDec = {.bits = {1, 0, 0, 0}};
  s21_decimal zeroDec = {.bits = {0, 0, 0, 0}};
  s21_decimal minusOneDec = {
      .bits = {1, 0, 0, 0b10000000000000000000000000000000}};
  int lastDigit = 0;  //-54359*10-3 = 9  - последняя цифра мантиссы
  if (exp == 1) {
    lastDigit = get_smallestrank_digit(temp);
    if (s21_div_ten(temp, &temp) == 0)  //если смогли поделить
    {
      if (lastDigit > 4)  //если последнее число было больше 4 то округлить к
                          //большему целому
      {
        if (s21_add_simple(temp, oneDec, &temp) ==
            0)  //если смогли прибавить к целому 1
          writeInDecParts(temp, exp - 1, sign, result);
        else
          ret = 1;  //если нет то ошибка
      } else  //если последнее число было меньше 5 то оставить как есть
        writeInDecParts(temp, exp - 1, sign, result);
    } else  //если не смогли поделить
    {
      if (lastDigit > 4) {
        if (sign == 0)
          *result = oneDec;
        else
          *result = minusOneDec;
      } else
        *result = zeroDec;
    }
  }
  if (exp > 1) *result = zeroDec;
  if (exp == 0) {
    *result = temp;
  }
  return ret;
}

int s21_truncate(s21_decimal value,
                 s21_decimal *result)  //Возвращает целые цифры указанного
                                       // Decimal числа; любые дробные цифры
                                       //отбрасываются, включая конечные нули
{
  int ret = 0;
  if (!result) {
    ret = 1;
  } else {
    s21_decimal temp = value;
    s21_decimal zeroDec = {.bits = {0, 0, 0, 0}};
    int exp = getExp(value), sign = getBit(value, 127);
    int stop = 0;
    while (exp > 0 && stop == 0)  // 54352*10^-4 -> 5435*10^-3 ->...-> 54*10^-1
                                  // = 5.4 ~ 5,     -5,4 ~ -6
    {
      stop = s21_div_ten(temp, &temp);  // 1- ошибка, 0 - хорошо
      if (stop == 0) exp -= 1;
    }
    if (exp > 0)
      *result = zeroDec;
    else {
      writeInDecParts(temp, exp, sign, result);
    }
  }
  return ret;
}

// Возвращает результат умножения указанного Decimal на -1
int s21_negate(s21_decimal value,
               s21_decimal *result)  //хз как ошибку тут получить
{
  int ret = 0;
  if (!result) {
    ret = 1;
  } else {
    s21_decimal temp = value;
    setBit(&temp, 127, 1 - getBit(value, 127));
    *result = temp;
  }
  return ret;
}
