#include "s21_string.h"

// position of first symbol c in first n bytes in str string
void *s21_memchr(const void *str, int c, size_t n) {
  int stop = 1;
  void *pos = s21_NULL;
  const char *tempstr = str;  // указатель на постоянный символ - символ не
                              // может меняться но указатель
  // можно менять. инициализировали типом чар чтобы можно было узнать символ
  // через *
  for (s21_size_t i = 0; i < n && stop && str; i++) {
    if (tempstr[i] == c) {
      pos = (void *)(tempstr +
                     i);  // позиция = адрес начала строки tempstr + i позиция
      // найденного символа. т.к. инициализировали const char* tempstr то надо
      // перевести в void printf("(char*) pos = %p\n", (char*)pos - (char*)str);
      //  printf("void* pos = %p\n", pos);
      stop = 0;
    }
  }
  return pos;
}
