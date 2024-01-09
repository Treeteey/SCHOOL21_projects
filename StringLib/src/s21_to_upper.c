#include "s21_string.h"

void *s21_to_upper(
    const char *str)  // Возвращает копию строки (str), преобразованной в
                      // верхний регистр. В случае какой-либо ошибки следует
                      // вернуть значение NULL
{
  char *result = s21_NULL;
  if (str) {
    s21_size_t length = s21_strlen(str);
    result = (char *)calloc((length + 1), sizeof(char));
    s21_size_t i = 0;
    while (i <= length) {
      if (str[i] >= 97 && str[i] <= 122) {
        result[i] = str[i] - 32;
      } else {
        result[i] = str[i];
      }
      i++;
    }
  }
  return result;
}
