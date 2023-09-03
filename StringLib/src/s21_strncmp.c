#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2,
                size_t n)  // Сравнивает не более первых n байтов str1 и str2
{
  int cmp = 1;
  if (n == 0 || str1 == s21_NULL || str2 == s21_NULL) cmp = 0;
  if (cmp != 0) {
    while ((*str1 == *str2) && (n > 1) && *str1 && *str2) {
      str1++;
      str2++;
      n--;
    }
    cmp = *str1 - *str2;
  }
  return cmp;
}