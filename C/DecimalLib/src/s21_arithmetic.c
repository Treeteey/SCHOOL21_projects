#include "s21_decimal.h"

//степень у децимала не должна быть больще 28, если она больше и для ее
//уменьшения мы не может делить мантиссу на 10 то число очень маленькое вернуть
//ошибку = 1
// int convert_to_proper_decimal(s21_decimal num, s21_decimal *result) {
//   s21_decimal temp = num;
//   int res = 0, exp = getExp(temp);
//   while (exp > 28 && s21_div_ten(temp, &temp) == 0) {
//     exp -= 1;
//   }
//   if (exp > 28)
//     res = 1;
//   else {
//     increaseExpByN(&temp, (exp - getExp(num)));
//     setBit(&temp, 127, getBit(num, 127));  //запишем знак
//     *result = temp;
//   }
//   return res;
// }

//подготовит decimal для суммирования
void correct_decimals_add_sub(s21_decimal *num1, s21_decimal *num2) {
  //для суммирования и вычитания надо подогнать степени так чтобы сумма мантисс
  //не переполнялась
  s21_decimal temp1 = *num1, temp2 = *num2;
  int exp1 = getExp(temp1), exp2 = getExp(temp2);
  int sign1 = getBit(*num1, 127), sign2 = getBit(*num2, 127);

  /*
  выровним степени умножением мантисс на 10 и прибавлением к степени 1
  */
  while (exp1 > exp2 && s21_mult_ten(temp2, &temp2) ==
                            0)  //умножаем мантиссу 2 числа пока степени не
                                //сравнятся или мантисса не достигнет максимума
  {
    exp2 += 1;
  }
  while (exp1 < exp2 &&
         s21_mult_ten(temp1, &temp1) ==
             0)  //умножаем мантиссу 1 числа пока степени не сравнятся
  {
    exp1 += 1;
  }

  //если не смогли выровнять степени за предыдущие циклы то
  //теперь делим числа с большей степенью и уменьшаем степень
  while (exp1 >= 0 && exp1 > exp2 && s21_div_ten(temp1, &temp1) == 0) {
    exp1 -= 1;
  }
  while (exp2 >= 0 && exp1 < exp2 && s21_div_ten(temp2, &temp2) == 0) {
    exp2 -= 1;
  }
  /*
  если все равно не смогли выровнять степени значит мантисса какого то из чисел
  не вместится в мантиссу другого числа: 1231...........342  0.0001 и меньшее
  число тупо убрать а вернуть только большее
  */
  *num1 = temp1;
  *num2 = temp2;
  num1->bits[3] = 0;
  num2->bits[3] = 0;
  increaseExpByN(num1, exp1);  //запишем степени
  increaseExpByN(num2, exp2);
  setBit(num1, 127, sign1);
  setBit(num2, 127, sign2);
}

void checking_for_small_or_negative_infinity(s21_decimal temp, int *ret,
                                             char a_or_s) {
  s21_decimal psmall = {.bits = {1, 0, 0, 0b00000000000111000000000000000000}};
  s21_decimal msmall = {.bits = {1, 0, 0, 0b10000000000111000000000000000000}};
  if (a_or_s == 's' && zero_check(temp)) {
    *ret = 0;
  } else if (getBit(temp, 127) == 1 && s21_is_greater(temp, msmall) == 1) {
    *ret = 2;
  } else if (getBit(temp, 127) == 0 && s21_is_less(temp, psmall) == 1) {
    *ret = 2;
  }
}

int add_or_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
               char a_or_s) {
  int ret = 0;
  s21_decimal temp = {{0}};
  if (!result) {
    ret = 1;
  } else if (zero_check(value_1) == 1 &&
             zero_check(value_2) == 1) {  //если оба 0
    *result = temp;
  } else {
    s21_decimal temp1 = value_1, temp2 = value_2;
    int sign1 = getBit(temp1, 127), sign2 = getBit(temp2, 127);  //знак децимала

    correct_decimals_add_sub(&temp1, &temp2);  //подогнать степени чисел

    int exp1 = getExp(temp1), exp2 = getExp(temp2);

    if ((sign1 + sign2) % 2 == 1)  //если знак одного из чисел отрицательный то
                                   //вычесть
    {
      if (a_or_s == 's' && s21_is_equal_simple(value_1, value_2)) {
        decimal_zeroing(result);
      } else {
        s21_minus_simple(temp1, temp2, &temp);
        s21_decimal comp1 = temp1, comp2 = temp2;
        setBit(&comp1, 127, 0);
        setBit(&comp2, 127, 0);
        if (sign1 == 1) {
          //если знак первого числа отрицательный и оно больше
          //второго то сумма таких чисел будет с отрицательным знаком
          if (s21_is_greater_or_equal(comp1, comp2) == 1) setBit(&temp, 127, 1);
        } else {
          //если знак второго числа отрицательный и его модуль больше
          //модуля первого то сумма таких чисел будет отрицательной
          if (s21_is_less_or_equal(comp1, comp2) == 1) setBit(&temp, 127, 1);
        }
        increaseExpByN(&temp, exp1);
      }
    } else {
      while (s21_add_simple(temp1, temp2, &temp) == 1 && exp1 > 0 && exp2 > 0) {
        s21_div_ten(temp1, &temp1);
        exp1 -= 1;
        a_or_s == 'a' ? s21_div_ten(temp1, &temp1) : s21_div_ten(temp2, &temp2);
        exp2 -= 1;
      }
      if (s21_add_simple(temp1, temp2, &temp) == 1) ret = 1;
      increaseExpByN(&temp, exp1);
      setBit(&temp, 127, sign1);
    }
    checking_for_small_or_negative_infinity(temp, &ret, a_or_s);
    if (!ret) *result = temp;
  }
  return ret;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  if (!result) {
    ret = 1;
  } else {
    ret = add_or_sub(value_1, value_2, result, 'a');
  }
  return ret;
}

//сложение без учета знаков, степеней, но есть проверка на переполнение
//(возвращает 1)
int s21_add_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result) {
  int i = 0, max = 0, maxVal2 = 0, ret = 0;
  s21_decimal temp = {{0}};
  // find max bit
  max = findMaxBit(value_1);
  maxVal2 = findMaxBit(value_2);
  max = (max > maxVal2) ? max : maxVal2;

  int sum = 0, mem = 0, s1 = 0, s2 = 0;
  for (i = 0; i < max + 2 && !ret; i++) {
    s1 = getBit(value_1, i);
    s2 = getBit(value_2, i);
    sum = s1 + s2 + mem;
    if (i == 95 && sum > 1)
      ret = 1;
    else {
      if (sum == 0) {
        setBit(&temp, i, 0);
        mem = 0;
      } else if (sum == 1) {
        setBit(&temp, i, 1);
        mem = 0;
      } else if (sum == 2) {
        setBit(&temp, i, 0);
        mem = 1;
      } else if (sum == 3) {
        setBit(&temp, i, 1);
        mem = 1;
      }
    }
  }
  /*
      при переполнении нужно ли увеличить степень?
  */
  if (!ret) *result = temp;
  return ret;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int ret = 0;
  if (!result) {
    ret = 1;
  } else {
    s21_decimal temp1 = value_1, temp2 = value_2, temp = {{0}};
    setBit(&temp2, 127, 1 - getBit(temp2, 127));
    int ret = add_or_sub(temp1, temp2, &temp, 's');
    if (!ret) *result = temp;
  }
  return ret;
}

//вычитание мантисс без учета знаков, степеней!
int s21_minus_simple(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int ret = 0, next = 0, maxBitWithOne = 0, s = 0;
  s21_decimal temp = {{0}}, t1 = {{0}}, t2 = {{0}};
  if (s21_is_less_simple(value_1, value_2) == 1) {
    t1 = value_2;
    t2 = value_1;
  } else {
    t1 = value_1;
    t2 = value_2;
  }

  maxBitWithOne = findMaxBit(t1);
  for (int i = 0; i < maxBitWithOne + 1; i++) {
    s = getBit(t1, i) - getBit(t2, i) - next;
    if (s < 0) {
      next = 1;
      setBit(&temp, i, s + 2);
    } else {
      setBit(&temp, i, s);
      next = 0;
    }
  }
  *result = temp;
  return ret;
}

int s21_mul(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  int ret = 0;
  if (!result)
    ret = 1;
  else {
    int exp1 = getExp(num1), exp2 = getExp(num2);
    int sign = getBit(num1, 127) + getBit(num2, 127);  //знак децимала

    int maxbit1 = findMaxBit(num1), maxbit2 = findMaxBit(num2);
    int sumMaxBits = maxbit1 + maxbit2 +
                     1;  //если суммарная позиция старших битов матисс больше 95
                         //то не получится просто перемножить мантиссы, надо их
                         //сократить поделив на 10: 110111*1010 -> 000101*0001
    s21_decimal temp = {{0}};
    s21_decimal temp1 = num1, temp2 = num2;

    while (sumMaxBits > 95 &&
           !ret)  //нужно уменьшить мантиссы на столько чтобы можно было
                  //спокойно их переменожить без переполнения
    {
      if (maxbit1 > maxbit2 && exp1) {
        s21_div_ten(temp1, &temp1);
        exp1 -= 1;
      } else if (maxbit1 < maxbit2 && exp2) {
        s21_div_ten(temp2, &temp2);
        exp2 -= 1;
      } else {
        if (s21_div_ten(temp1, &temp1) == 0 && exp1)
          exp1 -= 1;
        else if (s21_div_ten(temp2, &temp2) == 0 && exp2)
          exp2 -= 1;
        else
          ret = 1;  //не смогли сократить мантиссы
      }
      if ((findMaxBit(temp1) + findMaxBit(temp2)) == sumMaxBits)
        ret = 1;  //не смогли изменить мантиссы все жопа тогда
      sumMaxBits = findMaxBit(temp1) + findMaxBit(temp2) + 1;
    }
    if (ret == 0) {
      s21_mult_simple(temp1, temp2, &temp);  //запишем произведение мантисс
      increaseExpByN(&temp, exp1 + exp2);  //запишем суммарную степень
      if (sign % 2 == 1) setBit(&temp, 127, 1);  //запишем знак
    }
    if (ret == 0) *result = temp;
  }
  return ret;
}

//умножение только мантисс (без учета знаков и степени)
/*
    11011
     1001
    =====
    11011
   00000
  00000
 11011
 ========
 11110011

*/
int s21_mult_simple(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  int max = findMaxBit(num2), ret = 0;
  s21_decimal sum = {{0}};
  s21_decimal temp1 = {{0}};
  for (int i = 0; i < max + 1 && !ret; i++) {
    temp1 = num1;
    if (getBit(num2, i) == 1) {
      for (int j = 0; j < i && !ret; j++)
        ret = moveLeft(
            &temp1);  // ret = 1 будет переполнение при сдвиге влево 1011 ->
                      // 0110 ret = 0  cмогли сдвинуть на бит влево
      if (!ret)
        ret = s21_add_simple(temp1, sum,
                             &sum);  // ret = 0 смогли сложить без переполнения
    }
  }
  if (!ret) *result = sum;
  return ret;
}

// multiply mantissa by 10
/*
    11011
     1010 (10)
    =====
    00000
   11011
  00000
 11011
 ========
100001110

*/
int s21_mult_ten(s21_decimal num, s21_decimal *result) {
  int ret = 0;
  s21_decimal ten = {.bits = {10, 0, 0, 0}};
  s21_decimal sum = {{0}};
  s21_decimal temp = {{0}};
  for (int i = 0; i < 4 && !ret; i++)  // max pos of 1 in ten(1010) = 3, 3+1 = 4
  {
    temp = num;
    if (getBit(ten, i) == 1) {
      for (int j = 0; j < i && !ret; j++)
        ret = moveLeft(&temp);  // ret = 0  cмогли сдвинуть на бит влево
      if (!ret)
        ret = s21_add_simple(temp, sum,
                             &sum);  // ret = 0 смогли сложить без переполнения
    }
  }
  if (!ret) *result = sum;
  return ret;
}

/*
простое деление мантисс, если num1<num2 вывод = 0

 1011011|1010
-1010    0001001
    1011
   -1010
       1

 11101000010|101
-101         00101110011
  1001
  -101
   1000
   -101
     110
    -101
       1001
       -101
        1000
        -101
          11
101110011 + 11
*/
int s21_div_simple(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  int ret = 0;
  s21_decimal div = {{0}};                    //результат
  s21_decimal temp = {.bits = {0, 0, 0, 0}};  //временный децимал
  s21_decimal mid = num1;  //промежуточный децимал
  int max1 = findMaxBit(num1), maxBitPos = 0;
  int zero = s21_is_equal_simple(num2, div);
  if (s21_is_greater_or_equal_simple(num1, num2) &&
      zero == 0)  //проверяем если делимое больше или равно делителя, делитель
                  //не равен 0
  {
    for (int i = max1; i >= 0; i--) {  //проходим со старшего бита в делимом
      temp = mid;  //записываем временную мантиссу, которая на каждом
      moveRightNTimes(&temp, i);  //смещаем пока temp не станет >= num2
      if (s21_is_greater_or_equal_simple(temp, num2))  //когда temp >= num2
      {
        s21_minus_simple(temp, num2, &temp);  //записываем в temp остаток
        maxBitPos = findMaxBit(temp);  //находим старший бит остатка равный 1
        for (int j = 0; j <= maxBitPos;
             j++)  //теперь должны переписать этот остаток в промежуточный
                   //децимал начиная с i позиции
          setBit(&mid, j + i, getBit(temp, j));
        for (int j = i + maxBitPos + 1; j <= max1;
             j++)  //а все старшие не 0 биты заменить на 0
          setBit(&mid, j, 0);
        setBit(&div, i, 1);  //запишем в результат в позицию i ответ 1
      } else
        setBit(&div, i, 0);  //если временный децимал оказался меньше num2 то в
                             //ответ пишем 0 и дальше продолжаем смещение
    }
  } else
    ret = 2;               // small number
  if (zero == 1) ret = 1;  // infinity
  if (ret == 0) *result = div;
  return ret;
}

int s21_div(s21_decimal num1, s21_decimal num2, s21_decimal *result) {
  int ret = 0;
  if (zero_check(num2) == 1 || !result)  //добавил result = NULL
    ret = 3;                             //деление на 0
  else if (zero_check(num1) == 1) {      // 0 делить на x равно 0
    decimal_zeroing(result);
  } else {
    int whileStop = 0;
    int exp1 = getExp(num1), exp2 = getExp(num2);
    int sign = getBit(num1, 127) + getBit(num2, 127);  //знак децимала
    s21_decimal temp = {.bits = {0, 0, 0, 0}};
    s21_decimal temp1 = num1, temp2 = num2;
    /*
        need to make mantissa num1 as big as possible or at least bigger than
       num2 for better accuracy then divide_simple and calculate delta =
       exp1-exp2, if delta less than 0 then multiply division by 10 and delta +=
       1 if cant multiply until delta == 0 than we got number bigger than 2^32
    */
    while (s21_mult_ten(temp1, &temp1) ==
           0)  // increase mantissa of temp1 as possible
      exp1 += 1;
    while (s21_is_less_simple(temp1, temp2) == 1 /*1 = true*/ &&
           whileStop == 0)  // make mantissas of temp1 >= temp2
    {
      if (s21_div_ten(temp2, &temp2) == 0)
        exp2 -= 1;
      else
        whileStop = 1;
    }
    // here we must have mantissa of temp1 > temp2
    s21_div_simple(temp1, temp2, &temp);  // just divide prepared mantissas
    int delta = exp1 - exp2;  //результирующя степень после деления

    // cant have a*10^3, so make 10a*10^2 and so on until 10^0,
    // or until cant multiply by 10
    while (delta < 0 && ret == 0)  //степень должна быть больше либо равна 0
    {
      if (s21_mult_ten(temp, &temp) == 0)
        delta += 1;
      else
        ret = 1;  // bigger than 2^32 of +inf
    }
    if (delta >= 0 && ret == 0) {
      while (delta > 29 && ret == 0)  //если степень больше 29 надо делить
                                      //мантиссу на 10 до степени 28
      {
        if (s21_div_ten(temp, &temp) == 0)
          delta -= 1;
        else
          ret = 2;  // smaller than 1*10^-28
      }
      if (delta <= 28 && ret == 0 && result) {
        writeInDecParts(temp, delta, sign, result);
        s21_remove_zeros(result);
      }
    }
  }
  return ret;
}

int s21_div_ten(s21_decimal num, s21_decimal *result) {
  int ret = 1;
  s21_decimal ten = {.bits = {10, 0, 0, 0}};
  s21_decimal temp = {.bits = {0, 0, 0, 0}};
  if (!s21_div_simple(num, ten, &temp)) {
    *result = temp;
    ret = 0;
  }
  return ret;
}

void s21_remove_zeros(s21_decimal *num)  // 3000*10^-3  -> 3*10^0
{
  s21_decimal temp = *num, mid = {{0}};
  int lastDigit = get_smallestrank_digit(temp), stop = 0, exp = getExp(temp),
      memexp = 0;
  int sign = getBit(*num, 127);
  memexp = exp;
  while (stop == 0 && exp > 0) {
    /*
    123/10 = 12
    12*10 = 120
    123 != 120 - значит нельзя сократить мантиссу

    1230/10 = 123
    123*10 = 1230
    1230 == 1230 значит можно сократить мантиссу
    */
    mid = temp;
    lastDigit = get_smallestrank_digit(temp);
    if (s21_div_ten(temp, &temp) == 1)
      stop = 1;
    else {
      s21_mult_ten(temp, &temp);
      if (s21_is_equal_simple(temp, mid) == 0) {
        stop = 1;
        temp.bits[0] += lastDigit;
      } else {
        s21_div_ten(temp, &temp);
        exp -= 1;
      }
    }
  }
  int delta = memexp - exp;
  if (delta) {
    for (int i = 0; i < (memexp - exp); i++) {
      s21_div_ten(*num, num);
    }
    num->bits[3] = 0;
    setBit(num, 127, sign);
    increaseExpByN(num, exp);
    // printf("delta = %d\n", delta);
  }
}