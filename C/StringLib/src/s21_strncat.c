#include "s21_string.h"

char *s21_strncat(
    char *dest, const char *src,
    size_t n)  // Добавляет строку, на которую указывает src, в конец строки, на
               // которую указывает dest, длиной до n символов
{
  unsigned int lenghtDest = 0;
  unsigned int lengthSrc = 0;
  while (dest[lenghtDest] != '\0') {
    lenghtDest++;
  }
  while (src[lengthSrc] != '\0' && lengthSrc < n) {
    dest[lenghtDest + lengthSrc] = src[lengthSrc];
    lengthSrc++;
  }
  dest[lenghtDest + lengthSrc] = '\0';
  return dest;
}
