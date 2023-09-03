#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  const char *start = s21_NULL;  //   return address of str if no matches
  const char *end = str + s21_strlen(str);
  while (*str != '\0') {
    if (*str == c) {
      start = (char *)str;
    }
    str += 1;
  }
  if (c == '\0') start = end;
  return (char *)start;
}