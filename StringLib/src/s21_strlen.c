#include "s21_string.h"

size_t s21_strlen(const char *str)  // Вычисляет длину строки str, не включая
                                    // завершающий нулевой символ //O
{
  s21_size_t lenght = 0;
  if (str) {
    for (int i = 0; str[i] != '\0'; i++) {
      lenght++;
    }
  }
  return lenght;
}