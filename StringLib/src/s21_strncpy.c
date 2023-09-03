#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src,
                  size_t n)  // Копирует до n символов из строки, на которую
                             // указывает src, в dest
{
  int i = 0;
  while (n > 0) {
    dest[i] = src[i];
    n--;
    i++;
  }
  return dest;
}