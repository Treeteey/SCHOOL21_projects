#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src,
                 size_t n)  // Копирует n символов из src в dest
{
  unsigned char *dest_1 = (unsigned char *)dest;
  unsigned char *src_1 = (unsigned char *)src;
  while (n > 0) {
    *dest_1++ = *src_1++;
    n--;
  }
  return dest;
}