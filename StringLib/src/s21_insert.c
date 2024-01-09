#include "s21_string.h"

void *s21_insert(
    const char *src, const char *str,
    size_t start_index)  // Возвращает новую строку, в которой указанная строка
                         // (str) вставлена в указанную позицию (start_index) в
                         // данной строке (src). В случае какой-либо ошибки
                         // следует вернуть значение NULL
{
  char *buff = s21_NULL;
  if (src && str && start_index <= s21_strlen(src)) {
    int srcLength = s21_strlen(src);
    int strLength = s21_strlen(str);
    int newLength = srcLength + strLength;
    buff = (char *)calloc((newLength + 1), sizeof(char));

    s21_strncpy(
        buff, src,
        start_index);  // Копируем src в новую строку до момента start_index

    s21_strncpy(
        buff + start_index, str,
        strLength);  // Копируем str в новую строку после предыдущих действий

    s21_strncpy(buff + start_index + strLength, src + start_index,
                srcLength - start_index);  // Копируем оставшуюся часть строки

    buff[newLength] = '\0';
  } else
    buff = s21_NULL;
  return buff;
}
