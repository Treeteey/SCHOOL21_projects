#include "s21_string.h"

char *s21_strtok(char *src, const char *delim) {
  int stop = 0;  // флаг для выхода из цикла
  int breakFirstWhile = 0;
  static char *backup_str;  //сохраняем место на котором остановились в прошлый
                            //вызов функции
  if (!src) src = backup_str;
  if (!src)  // если backup = \0  => достигли конца исходной строки  -> выходим
             // из функции
    stop = 1;
  while (!stop && !breakFirstWhile) {  // перемещаем указатаель src на начало
                                       // следующего токена
    if (share_fun(*src, delim)) {  // если текущий символ разделитель ->
                                   // перескакиваем на следующий символ
      src++;
      continue;
    }
    if (*src == '\0')  //конец строки
      stop = 1;
    breakFirstWhile = 1;
  }
  char *ret = src;  //сохраняем начало нового токена
  while (!stop) {  //ищем конец токена или конец строки и заменяем на \0
    if (*src ==
        '\0') {  // достигли конца строки, и следующее выполнение вернет NULL
      backup_str = src;
      stop = 2;
    }
    if (share_fun(*src,
                  delim)) {  //ищем конец токена и заменяем разделитель на \0
      *src = '\0';
      backup_str = src + 1;  //следующий вызов будет после поставленного нами \0
      stop = 2;
    }
    src++;
  }
  if (stop == 1) ret = s21_NULL;
  return ret;
}

int share_fun(char c,
              const char *delim) {  // 1 если символ относится к делителю
  int flag = 0;
  while (*delim != '\0' && flag == 0) {
    if (c == *delim) flag = 1;
    delim++;
  }
  return flag;
}