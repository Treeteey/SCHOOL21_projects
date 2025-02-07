#include "s21_string.h"

void *s21_trim(
    const char *src,
    const char
        *trim_chars)  // Возвращает новую строку, в которой удаляются все
                      // начальные и конечные вхождения набора заданных символов
                      // (trim_chars) из данной строки (src). В случае
                      // какой-либо ошибки следует вернуть значение NULL
{
  char *new_str = 0;

  if (trim_chars == s21_NULL) {
    s21_size_t lenSrc = s21_strlen(src) + 1;
    new_str = (char *)calloc(lenSrc, sizeof(char));
    for (s21_size_t i = 0; i < lenSrc; i++) {
      new_str[i] = src[i];
    }
  } else if (src) {
    int start = 0;  // индекс, в дальнейшем без символов в начале
    int end = s21_strlen(src) - 1;  // индекс без символов в конце

    while (src[start] != '\0' && s21_strchr(trim_chars, src[start]) != s21_NULL)
      start++;

    while (end >= start && s21_strchr(trim_chars, src[end]) != s21_NULL) end--;

    int length = end - start + 1;  // длина новой строки

    new_str = (char *)calloc((length + 1), sizeof(char));

    int j = 0;
    while (start <= end) {
      new_str[j] = src[start];
      start++;
      j++;
    }
    new_str[j] = '\0';
  }
  return new_str;
}
