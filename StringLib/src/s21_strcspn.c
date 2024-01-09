#include "s21_string.h"

size_t s21_strcspn(
    const char *str1,
    const char *str2)  // Вычисляет длину начального сегмента str1, который
                       // полностью состоит из символов, не входящих в str2
{
  s21_size_t lenght1 = s21_strlen(str1);
  s21_size_t lenght2 = s21_strlen(str2);
  int sovp = 0;
  s21_size_t itogLenght = 0;

  for (s21_size_t i = 0; i < lenght1; i++) {
    for (s21_size_t j = 0; j < lenght2; j++) {
      if (str1[i] == str2[j]) {
        sovp++;
      }
    }
    itogLenght++;
    if (sovp > 0) {
      itogLenght--;
    }
  }
  return itogLenght;
}
