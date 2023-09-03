#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t len = s21_strlen(needle);
  s21_size_t n = 0;  //количество подряд совпадающих символов
  int found = 0;  //флаг если нашли полное совпадение: 1 - когда n = len
  const char *temp = s21_NULL;
  while (*haystack != '\0' && !found) {
    while (*(haystack + n) == needle[n] && n < len) {
      n += 1;
    }
    if (n == (len)) {
      found = 1;
      temp = haystack;
    } else
      n = 0;
    haystack += 1;
  }
  return (char *)temp;
}