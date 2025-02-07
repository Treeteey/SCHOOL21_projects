#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define s21_NULL ((void *)0)

typedef long unsigned s21_size_t;

void *s21_memchr(const void *str, int c, s21_size_t n);  // R
// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);  // A
//Сравнивает первые n байтов str1 и str2.

void *s21_memcpy(void *dest, const void *src, s21_size_t n);  // A
//Копирует n символов из src в dest.

void *s21_memset(void *str, int c, s21_size_t n);  // A
//Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
//указывает аргумент str.

char *s21_strncat(char *dest, const char *src, s21_size_t n);  // A
//Добавляет строку, на которую указывает src, в конец строки, на которую
//указывает dest, длиной до n символов.

char *s21_strchr(const char *str, int c);  // R
//Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
//которую указывает аргумент str.

int s21_strncmp(const char *str1, const char *str2, s21_size_t n);  // A
//Сравнивает не более первых n байтов str1 и str2.

char *s21_strncpy(char *dest, const char *src, s21_size_t n);  // A
//Копирует до n символов из строки, на которую указывает src, в dest.

size_t s21_strcspn(const char *str1, const char *str2);  // A
//Вычисляет длину начального сегмента str1, который полностью состоит из
//символов, не входящих в str2.

char *s21_strerror(int errnum);  // Rob
//Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
//указатель на строку с сообщением об ошибке. Нужно объявить макросы, содержащие
//массивы сообщений об ошибке для операционных систем mac и linux. Описания
//ошибок есть в оригинальной библиотеке. Проверка текущей ОС осуществляется с
//помощью директив.

s21_size_t s21_strlen(const char *str);  // O
//Вычисляет длину строки str, не включая завершающий нулевой символ.

char *s21_strpbrk(const char *s1, const char *s2);  // R
//Находит первый символ в строке str1, который соответствует любому символу,
//указанному в str2.

char *s21_strrchr(const char *str, int c);  // R
//Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
//которую указывает аргумент str.

char *s21_strstr(const char *haystack, const char *needle);  // R
//Находит первое вхождение всей строки needle (не включая завершающий нулевой
//символ), которая появляется в строке haystack.

char *s21_strtok(char *str, const char *delim);  // Rob
//Разбивает строку str на ряд токенов, разделенных delim.

void *s21_to_upper(const char *str);  // A
//Возвращает копию строки (str), преобразованной в верхний регистр. В случае
//какой-либо ошибки следует вернуть значение NULL

void *s21_to_lower(const char *str);  // A
//Возвращает копию строки (str), преобразованной в нижний регистр. В случае
//какой-либо ошибки следует вернуть значение NULL

void *s21_insert(const char *src, const char *str,
                 s21_size_t start_index);  // A
//Возвращает новую строку, в которой указанная строка (str) вставлена в
//указанную позицию (start_index) в данной строке (src). В случае какой-либо
//ошибки следует вернуть значение NULL

void *s21_trim(const char *src, const char *trim_chars);  // A
//Возвращает новую строку, в которой удаляются все начальные и конечные
//вхождения набора заданных символов (trim_chars) из данной строки (src). В
//случае какой-либо ошибки следует вернуть значение NULL

int s21_sprintf(char *str, const char *format, ...);

//структура флагов(для + - и (пробел))
struct flags {
  int plus;
  int space;
  int minus;
  int grid;  //решетка
  int zero;
};

void flag_reading(const char **ch, struct flags *flag);
int width_reading(const char **ch, va_list *factor);
int precision_reading(const char **ch, va_list *factor);
char length_reading(const char **ch);

void reverse_String(char *str, int length);
void type_conversion(long int *d, char length);
void int_to_string(long int number, char *str, struct flags flag, int precision,
                   char int_or_double, char specifier);
void uoxX_type_conversion(unsigned long int *d, char length);
void uoxX_to_string(unsigned long int number, char *str, struct flags flag,
                    int precision, char specifier);

int degree_counter(double *num);
void eE_to_string(double num, char *buffer, int precision, struct flags flag,
                  char specifier);

long double round_to_n_decimals(long double number, int n);
void float_to_string(long double number, char *str, struct flags flag,
                     int precision, char specifier);

void string_to_string(char *enter_str, char *str, int precision);

void string_output_with_specifier(char specifier, va_list *factor,
                                  struct flags flag, int precision, char length,
                                  char *stringWithSpecifier);
void string_output_with_width(char **str, int width, struct flags flag,
                              char *stringWithSpecifier);

int result_sprintf(char *start, char *end);
int share_fun(char c, const char *delim);

#endif