#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *start = s21_NULL;
  int stop = 1;
  s21_size_t len2 = s21_strlen(str2);
  while (*str1 != '\0' && stop) {
    for (s21_size_t i = 0; i < len2 && stop; i++) {
      if (*str1 == str2[i]) {
        start = str1;
        stop = 0;
      }
    }
    str1 += 1;
  }
  return (char *)start;  // cast to type char*
}