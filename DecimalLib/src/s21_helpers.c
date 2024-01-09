#include "s21_decimal.h"

// int convertBinaryStringToInt(char *binaryString) {
//   int decimalNumber = strtol(binaryString, NULL, 2);
//   return decimalNumber;
// }

// //перевод десятичного целого в двоичный и вывод в строку
// void int_to_binary_string(int n) {
//   unsigned int mask =
//       1 << (sizeof(int) * 8 - 1);  // Определяем маску для первого бита
//   for (int i = 0; i < (int)sizeof(int) * 8; i++) {
//     // Применяем побитовую операцию И (&) между значением и маской
//     int bit = (n & mask) ? 1 : 0;
//     printf("%d", bit);  // Выводим бит
//     mask >>= 1;  // Сдвигаем маску на один бит вправо
//   }
// }

// // //вывести децимал в двоичном виде
// void printDec(s21_decimal num) {
//   for (int i = 3; i >= 0; i--) {
//     int_to_binary_string(num.bits[i]);
//     printf(" ");
//   }
//   printf("\n");
// }

// //вывести децимал в десятичном виде
// void printDecInt(s21_decimal num) {
//   printf("sign = %d, exp = %d, ", getBit(num, 127), getExp(num));
//   for (int i = 2; i >= 0; i--) {
//     printf("%u ", num.bits[i]);
//   }
//   printf("\n");
// }

// void printDecSmallestExp(s21_decimal num) {
//   s21_decimal temp = num;
//   int exp = getExp(temp);
//   while (s21_div_ten(temp, &temp) == 0 && exp > 1) exp -= 1;
//   printf("good looking: ");
//   printDecInt(temp);
// }

//узнать бит в позицию n
int getBit(s21_decimal num, int n) {
  int nBits = n / 32;      // find bits[nBits]
  int posAtBits = n % 32;  // find bit in bits[nbits]
  unsigned int mask =
      1 << posAtBits;  // Определяем маску и смещаем на определяему позицию
  int bitATn = (num.bits[nBits] & mask) ? 1 : 0;
  return bitATn;
}

//установить бит value в позицию n
void setBit(
    s21_decimal *num, int n,
    int value)  //полагается что value 0 или 1, 0 < n < 128, num существует!
{
  int nBits = n / 32;      // find bits[nBits]
  int posAtBits = n % 32;  // find bit in bits[nbits]
  unsigned int mask = 1 << posAtBits;
  if (value) {
    num->bits[nBits] |= mask;  // 001010111 | 000100000  = 001110111
  } else {
    num->bits[nBits] &= ~mask;  // mask=0100, ~mask = 1011; 0101 & 1011 = 0001 -
                                // изменили 3 бит справа на 0
  }
}

int moveLeft(s21_decimal *num)  // move left mantiss by ONE bit:    0001 1011
                                // 0101  -> 0011 0110 1010
{
  int lastBit = getBit(*num, 95);
  //если старший бит (96-ой) в 3 части мантиссы (bits[2]) равен 0 то мы можем
  //сместить все биты влево, иначе будет переполнение:  GOOD 01101 -> 11010; BAD
  // af 10010 -> 00100
  if (!lastBit) {
    int highBit = 0;
    for (int i = 2; i > 0; i--) {
      highBit = getBit(
          *num,
          (i - 1) * 32 + 31);  //сохраним старший бит предыдущей части мантиссы
      num->bits[i] <<= 1;      //сдвигаем влево
      setBit(num, i * 32,
             highBit);  //перепишем младший бит i части старшим битом i-1 части:
                        // 0101 0110 то будет 0100 0110
    }
    num->bits[0] <<= 1;  //тупо сдвигаем низшую часть мантиссы
  }
  return lastBit;  //если 0 то все хорошо, 1 - число не было сдвинуто на бит
}

void moveRightNTimes(
    s21_decimal *num,
    int n)  // move right by n bits:    0001 1011 0101  -> 0000 1101 1010
{
  int firstBit;
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < 2; i++) {
      firstBit = getBit(
          *num, (i + 1) * 32);  //сохраним младший бит следующей части мантиссы
      num->bits[i] >>= 1;       // move right by 1 bit
      setBit(num, i * 32 + 31,
             firstBit);  //перепишем старший бит i части младшим битом i+1
                         //части: 0101 0110 то будет 0101 1110
    }
    num->bits[2] >>= 1;  //тупо сдвигаем высшую часть мантиссы вправо
                         // printDec(*num);
  }
}

//проверка правильно ли записан bits[3] : 0 - ok, 1 - BAD
// int checkExpBits(s21_decimal num) {
//   int valid = 0, bit = 0;
//   unsigned int mask = 1;  // Определяем маску для первого бита: 0001
//   for (int i = 0; i < (int)sizeof(int) * 8 && !valid; i++) {
//     bit = (num.bits[3] & mask) ? 1 : 0;
//     if (((i >= 0 && i < 16) || (i >= 24 && i <= 30)) &&
//         bit)  //если биты 0-15 и 24-30 не равны нулю то вывести ошибку
//     {
//       // printf("wrong bits[3] NIBBA: at %d\nlook what you entered BIH\n",
//       i);
//       // int_to_binary_string(num.bits[3]);
//       valid = 1;
//     }
//     mask <<= 1;  //смещаем влево: 0010
//   }
//   return valid;
// }

//вычислить экспоненту
int getExp(s21_decimal num) {
  s21_decimal temp = num;
  setBit(&temp, 127, 0);
  temp.bits[3] >>= 16;
  int exp = temp.bits[3];
  return exp;
}

// +n to exponent
void increaseExpByN(s21_decimal *num, int n) {
  int add = n * (1 << 16);
  num->bits[3] += add;
}

// position of highest bit (0..95) with 1 value
int findMaxBit(s21_decimal num) {
  int max = 0, stop = 0;
  for (int i = 95; i >= 0 && !stop; i--) {
    if (getBit(num, i) == 1) {
      max = i;
      stop = 1;
    }
  }
  return max;
}

//находит значение младшего разряда мантиссы 2132415521 -> 1     124 -> 4
int get_smallestrank_digit(s21_decimal num) {
  s21_decimal temp = num;
  s21_div_ten(temp, &temp);   // 123:10 = 12
  s21_mult_ten(temp, &temp);  // 12*10 = 120
  s21_minus_simple(
      num, temp, &temp);  // 123-120 = 3 - цифра младшего разряда в мантиссе num
  return temp.bits[0];
}

// int checkAddOne(
//     s21_decimal *num)  //проверка сможем ли добавить к мантиссе единицу
// {
//   s21_decimal one = {.bits = {1, 0, 0, 0}}, temp = *num;
//   return s21_add_simple(temp, one, &temp);  // num не изменится
// }

// void addOne(s21_decimal *num)  //добавление к мантиссе единицы
// {
//   s21_decimal one = {.bits = {1, 0, 0, 0}}, temp = *num;
//   int exp = getExp(*num), sign = getBit(*num, 127);
//   s21_add_simple(temp, one, num);  // num изменится
//   increaseExpByN(num, exp);
//   setBit(num, 127, sign);
// }

// void subOne(s21_decimal *num)  //вычитание из мантиссы единицы
// {
//   s21_decimal one = {.bits = {1, 0, 0, 0}}, temp = *num;
//   int exp = getExp(*num), sign = getBit(*num, 127);
//   s21_minus_simple(temp, one, num);
//   increaseExpByN(num, exp);
//   setBit(num, 127, sign);
// }

void writeInDecParts(s21_decimal mantissa, int exp, int sign,
                     s21_decimal *result) {
  if (result)  //если норм с памяться наверно
  {
    s21_decimal res = {{0}};
    res.bits[0] = mantissa.bits[0];
    res.bits[1] = mantissa.bits[1];
    res.bits[2] = mantissa.bits[2];
    increaseExpByN(&res, exp);
    setBit(&res, 127, sign);
    *result = res;
  }
}
