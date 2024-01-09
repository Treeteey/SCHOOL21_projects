#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int stop = 1;
  char *pos = s21_NULL;  //   return NULL if no matches
  const char *tempstr = str;  //чтоб не менять исходную строку!

  for (s21_size_t i = 0; i < s21_strlen(str) && stop && str; i++) {
    if (tempstr[i] == c) {
      pos = (void *)tempstr + i;
      stop = 0;
    }
  }
  return pos;
}