#ifndef FUNK
#define FUNK
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// void int_to_binary_string(int n);
// int convertBinaryStringToInt(char *binaryString);
// void printDec(s21_decimal num);
// void printDecInt(s21_decimal num);
// void printDecSmallestExp(s21_decimal num);
int getBit(s21_decimal num, int n);
void setBit(s21_decimal *num, int n, int value);
int moveLeft(s21_decimal *num);  // move left by ONE bit:    0001 1011 0101  ->
                                 // 0011 0110 1010
void moveRightNTimes(
    s21_decimal *num,
    int n);  // move right by n bits:    0001 1011 0101  -> 0000 1101 1010
// int checkExpBits(s21_decimal num);  // check if bits[3] is RIGHT
int getExp(s21_decimal num);  // extract exponent
void increaseExpByN(s21_decimal *num, int n);
int findMaxBit(s21_decimal num);
int get_smallestrank_digit(s21_decimal num);
// void addOne(s21_decimal *num);  //добавление к мантиссе единицы
// void subOne(s21_decimal *num);  //вычитание из мантиссы единицы
// int checkAddOne(
// s21_decimal *num);  //проверка сможем ли добавить к мантиссе единицу
void correct_decimals_add_sub(s21_decimal *num1, s21_decimal *num2);
void writeInDecParts(s21_decimal mantissa, int exp, int sign,
                     s21_decimal *result);  //записать в децимал отдельн
                                            //мантиссу степень знак

void checking_for_small_or_negative_infinity(s21_decimal temp, int *ret,
                                             char a_or_s);
int add_or_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
               char a_or_s);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add_simple(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);
int s21_minus_simple(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result);
int s21_mul(s21_decimal num1, s21_decimal num2, s21_decimal *result);
int s21_mult_simple(s21_decimal num1, s21_decimal num2,
                    s21_decimal *result);  // no common exponent
int s21_mult_ten(s21_decimal num, s21_decimal *result);
int s21_div_simple(s21_decimal num1, s21_decimal num2, s21_decimal *result);
int s21_div_ten(s21_decimal num, s21_decimal *result);
int s21_div(s21_decimal num1, s21_decimal num2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_remove_zeros(s21_decimal *num);  // 3000*10^-3  -> 3*10^0

int s21_is_less_simple(s21_decimal num1, s21_decimal num2);
int s21_is_less_or_equal_simple(s21_decimal num1, s21_decimal num2);
// int s21_is_greater_simple(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal_simple(s21_decimal num1, s21_decimal num2);
int s21_is_equal_simple(s21_decimal num1, s21_decimal num2);
// int s21_is_not_equal_simple(s21_decimal num1, s21_decimal num2);

// compare functions
void true_view(s21_decimal *num1, s21_decimal *num2);
void svap(int flag, s21_decimal *temp1, s21_decimal *temp2, s21_decimal num1,
          s21_decimal num2);
int s21_is_less(s21_decimal num1, s21_decimal num2);
int zero_check(s21_decimal num);
// int s21_is_less_or_equal_with_spec(s21_decimal num1, s21_decimal num2,
//                                    char spec);
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_greater(s21_decimal num1, s21_decimal num2);
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);
int s21_is_equal(s21_decimal num1, s21_decimal num2);
int s21_is_not_equal(s21_decimal num1, s21_decimal num2);

// convertors functions
void decimal_zeroing(s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int countDecimalPlaces(float num);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int floor_based_on_exp(s21_decimal temp, int exp, int sign,
                       s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int round_based_on_exp(s21_decimal temp, int exp, int sign,
                       s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  // FUNK
