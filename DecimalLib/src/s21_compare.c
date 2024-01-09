#include "s21_decimal.h"

//сравнение только мантисс без знаков и экспоненты
// 1 - num1<num2| 0 - num1 >= num2
int s21_is_less_simple(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if (s21_is_less_or_equal_simple(num1, num2)) {
    ret = 1;
    if (s21_is_equal_simple(num1, num2) == 1) ret = 0;
  }
  return ret;
}

//сравнение только мантисс без знаков и экспоненты
// 1 - num1<=num2| 0 - num1 > num2
int s21_is_less_or_equal_simple(s21_decimal num1, s21_decimal num2) {
  // hasHigherbit - флаг который означает что какой то бит в числе 2 был больше
  // чем в числе 1, но старшие биты одинаковы:
  //  например  1010 1100,
  // 4биты равны,
  // 3биты 0<1 поэтому ставим флаг hasHigherbit
  // 2биты 1>0, могла бы быть ошибка но мы добавили флаг что 3 бит числа 2
  // больше
  int max1 = findMaxBit(num1), max2 = findMaxBit(num2);
  int ret = 1, i = max2, hasHigherBit = 0;
  if (max1 > max2)
    ret = 0;
  else {
    for (i = max2; i >= 0 && ret; i--) {
      if (getBit(num1, i) < getBit(num2, i) && hasHigherBit == 0)
        hasHigherBit = 1;
      else if (getBit(num1, i) > getBit(num2, i) && hasHigherBit == 0)
        ret = 0;
    }
  }
  return ret;
}

// compare only mantissas
// int s21_is_greater_simple(s21_decimal num1, s21_decimal num2) {
//   return 1 - s21_is_less_or_equal_simple(num1, num2);
// }
// compare only mantissas
int s21_is_greater_or_equal_simple(s21_decimal num1, s21_decimal num2) {
  int ret = 1;
  if (s21_is_less_simple(num1, num2) == 1) ret = 0;
  return ret;
}

int s21_is_equal_simple(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if (num1.bits[0] == num2.bits[0] && num1.bits[1] == num2.bits[1] &&
      num1.bits[2] == num2.bits[2])
    ret = 1;
  return ret;
}

// int s21_is_not_equal_simple(s21_decimal num1, s21_decimal num2) {
//   int ret = 1;
//   if (s21_is_equal_simple(num1, num2) == 1) ret = 0;
//   return ret;
// }

//выбирает что будем домножать на 10, а что 10(если надо)
void svap(int flag, s21_decimal *temp1, s21_decimal *temp2, s21_decimal num1,
          s21_decimal num2) {
  if (flag == 1) {
    *temp1 = num2;
    *temp2 = num1;
  } else {
    *temp1 = num1;
    *temp2 = num2;
  }
}

//--------------------------------------
void true_view(s21_decimal *num1,
               s21_decimal *num2) {  //приводит к одной степени
  int exp1 = getExp(*num1);
  int exp2 = getExp(*num2);
  int f = 0, multTimesN = 0;

  if (exp1 > exp2) {
    f = 1;
    multTimesN = exp1 - exp2;
  } else {
    f = 2;
    multTimesN = exp2 - exp1;
  }

  if (multTimesN != 0) {
    s21_decimal temp1, temp2;  // temp1 доможаем на 10, temp2 делим на 10
    svap(f, &temp1, &temp2, *num1, *num2);
    int start_exp1 = getExp(temp1),
        start_exp2 = getExp(temp2);  //вычисяет начальное значение степени
    int symbol1 = getBit(temp1, 127), symbol2 = getBit(temp2, 127);  //знаки +/-
    int divTimesN = multTimesN, flag = 0;

    int enter_mult = 0;
    for (int i = 0; i < multTimesN && flag == 0; i++) {  //умножаю на 10 x раз
      flag = s21_mult_ten(temp1, &temp1);
      if (flag == 0) {
        enter_mult = 1;
        divTimesN--;
      }
    }
    //необходимо записать измененное значение
    if (enter_mult == 1) {
      increaseExpByN(&temp1, start_exp1 + multTimesN - divTimesN);
      setBit(&temp1, 127, symbol1);
    }
    // 2 предыдущие приписывают символ +/- и нужную степень

    int enter_div = 0;
    for (int i = 0; i < divTimesN; i++) {  //делю на 10 N-x раз
      s21_div_ten(temp2, &temp2);
      enter_div = 1;
    }
    if (enter_div == 1) {
      increaseExpByN(&temp2, start_exp2 + divTimesN);
      setBit(&temp2, 127, symbol2);
    }
    svap(f, num1, num2, temp1, temp2);
  }
}

// 1 - num1<num2| 0 - num1 >= num2
int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if (s21_is_less_or_equal(num1, num2) == 1 && s21_is_equal(num1, num2) == 0)
    ret = 1;
  return ret;
}

// 1 если равен 0
int zero_check(s21_decimal num) {
  int ret = 1;
  for (size_t i = 0; i < 3; i++) {
    if (num.bits[i] != 0) ret = 0;
  }
  return ret;
}

// 1 - num1<=num2| 0 - num1 > num2 при одинаковом знаке
int s21_is_less_or_equal_simple_with_spec(s21_decimal num1, s21_decimal num2,
                                          char symbol) {
  int ret = 1;
  int max1 = findMaxBit(num1), max2 = findMaxBit(num2), coutRavno = 0;
  if (max1 > max2)
    ret = 0;
  else if (max1 == max2) {
    int flag = 1;
    for (int i = max2; i >= 0 && flag == 1; i--) {
      if (getBit(num1, i) < getBit(num2, i)) {
        ret = 1;
        flag = 0;
      } else if (getBit(num1, i) == getBit(num2, i)) {
        coutRavno++;
      } else {  // getBit(num1, i) > getBit(num2,i)
        ret = 0;
        flag = 0;
      }
    }
  }
  if (symbol == '-') ret = 1 - ret;
  if (coutRavno == max2 + 1) ret = 1;
  return ret;
}

// 1 - num1<=num2| 0 - num1 > num2
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  int ret = 1;
  int znakNum1 = getBit(num1, 127), znakNum2 = getBit(num2, 127);
  if (zero_check(num1) && zero_check(num2)) {
    ret = 1;
  } else if (znakNum1 == 1 && znakNum2 == 0) {  //первый - второй +
    ret = 1;
  } else if (znakNum1 == 0 && znakNum2 == 1) {  //первый + второй -
    ret = 0;
  } else {                    //либа оба +, либо оба -
    true_view(&num1, &num2);  //привожу к одинаковой степени
    if (znakNum1 == 0) {  //оба +
      ret = s21_is_less_or_equal_simple_with_spec(num1, num2, '+');
    } else {  //оба -
      ret = s21_is_less_or_equal_simple_with_spec(num1, num2, '-');
    }
  }
  return ret;
}

// num1 > num2
int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int ret = s21_is_less(num2, num1);
  return ret;
}

// num1 >= num2
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  int ret = s21_is_less_or_equal(num2, num1);
  return ret;
}

// num1 == num2
int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int ret = 0;
  if (zero_check(num1) && zero_check(num2))  //проверка на +0 и -0
    ret = 1;
  else {
    true_view(&num1, &num2);  //привожу к одинаковой степени
    if (num1.bits[0] == num2.bits[0] && num1.bits[1] == num2.bits[1] &&
        num1.bits[2] == num2.bits[2] && getBit(num1, 127) == getBit(num2, 127))
      ret = 1;
  }
  return ret;
}

// num1 != num2
int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  int ret = 1 - s21_is_equal(num1, num2);
  return ret;
}
