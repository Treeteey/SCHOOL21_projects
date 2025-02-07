#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2,
               size_t n)  // Сравнивает первые n байтов str1 и str2.
{
  unsigned char *str_1 = (unsigned char *)str1;
  unsigned char *str_2 = (unsigned char *)str2;
  int cmp = 0;
  while (n > 0 && !cmp) {
    if (*str_1 != *str_2) {
      cmp = *str_1 - *str_2;
    }
    n--;
    str_1++;
    str_2++;
  }
  return cmp;
}