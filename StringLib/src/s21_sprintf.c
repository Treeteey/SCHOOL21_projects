#include "s21_string.h"

void flag_reading(const char **ch, struct flags *flag) {  //считывание флагов
  while (*++(*ch) == '+' || **ch == '-' || **ch == ' ' || **ch == '#' ||
         **ch == '0') {
    if (**ch == '+') {
      flag->plus = 1;
    } else if (**ch == '-') {
      flag->minus = 1;
    } else if (**ch == ' ') {
      flag->space = 1;
    } else if (**ch == '#') {
      flag->grid = 1;
    } else {
      flag->zero = 1;
    }
  }
  (*ch)--;
}

int width_reading(const char **ch, va_list *factor) {  //считывание ширины
  int width = 0;
  if (*++(*ch) == '*') {
    width = va_arg(*factor, int);
  } else {
    (*ch)--;
    int countOfDigits = 0;  // скольки значное число
    while (*++(*ch) >= '0' && *(*ch) <= '9') {
      countOfDigits++;
    }

    if (countOfDigits != 0) {
      for (int i = 0; i < countOfDigits; i++) {
        width += ((int)*--(*ch) - '0') * pow(10, i);
      }
      *ch = *ch + countOfDigits;
    }

    (*ch)--;
  }
  return width;
}

int precision_reading(const char **ch, va_list *factor) {  //считывание точности
  int precision = -1;  // проверочка на введенную точность

  if (*++(*ch) == '.') {
    precision = width_reading(ch, factor);
  } else {
    (*ch)--;
  }
  return precision;
}

char length_reading(const char **ch) {  //считывание длины
  char length = 'n';                    // длина не задана

  if (*++(*ch) == 'h') {
    length = 'h';
  } else if (*(*ch) == 'l') {
    length = 'l';
  } else if (*(*ch) == 'L') {
    length = 'L';
  } else {
    (*ch)--;
  }

  return length;
}

void type_conversion(long int *d,
                     char length) {  //меняет тип целочисленных переменных
  if (length == 'h') {
    *d = (short int)*d;
  } else if (length != 'l') {
    *d = (int)*d;
  }
}

void reverse_String(char *str, int length) {
  int start = 0, end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start++] = str[end];
    str[end--] = temp;
  }
}

void int_to_string(long int number, char *str, struct flags flag, int precision,
                   char int_or_double, char specifier) {
  int indxStr = 0;     //номер символа в числе
  int isNegative = 0;  //проверка на отрицательность
  if (number < 0) {
    isNegative = 1;
    number = -number;
  }
  int countOfDigits = 0;
  //обработка краевого значения 0
  if (number == 0 && (int_or_double == 'd' || precision == -1))
    str[indxStr++] = '0';
  //запись числа в строку(но инвертированно)
  while (number != 0) {
    int digit = number % 10;
    str[(indxStr)++] = digit + '0';
    number /= 10;
    (countOfDigits)++;
  }
  //заполняю 0 для целочисленных спецификаторов d
  if (specifier == 'd') {
    while (countOfDigits++ < precision) str[indxStr++] = '0';
  }
  if (isNegative) {
    str[indxStr++] = '-';
  } else if (flag.plus == 1) {
    str[indxStr++] = '+';
  } else if (flag.space == 1) {
    str[indxStr++] = ' ';
  }

  //обратно инвертирую в правильном порядке
  reverse_String(str, indxStr);
  str[indxStr] = '\0';
}

void uoxX_type_conversion(
    unsigned long int *d,
    char length) {  //меняет тип беззнаковых целочисленных переменных
  if (length == 'h') {
    *d = (unsigned short int)*d;
  } else if (length != 'l') {
    *d = (unsigned int)*d;
  }
}

void uoxX_to_string(unsigned long int number, char *str, struct flags flag,
                    int precision, char specifier) {
  int indxStr = 0;        //номер символа в числе
  int countOfDigits = 0;  //скольки значное число
  //обработка краевого значения 0
  if (number == 0 && precision == -1)
    str[indxStr++] = '0';
  else {
    int x_digit = 10;
    if (specifier == 'p') {
      specifier = 'x';
      flag.grid = 1;
    }
    if (specifier == 'X' || specifier == 'x')
      x_digit = 16;
    else if (specifier == 'o')
      x_digit = 8;
    //запись числа в строку(но инвертированно)
    while (number != 0) {
      unsigned int digit = number % x_digit;
      if (specifier == 'o' || specifier == 'u' || digit < 10) {
        str[indxStr++] = digit + '0';
      } else {  //заходит только для x и X
        str[indxStr++] =
            digit - 10 + specifier -
            ('X' -
             'A');  // Используем буквы A-F(a-f) для представления чисел 10-15
      }
      number /= x_digit;
      countOfDigits++;
    }
    //заполняю 0 для целочисленных спецификаторов(d, o, u, x, X)
    while (countOfDigits++ < precision) str[indxStr++] = '0';
    if (flag.grid == 1) {  //обработка флага #
      if (specifier == 'o') {
        str[indxStr++] = '0';
      } else if (specifier == 'x' || specifier == 'X') {
        str[indxStr++] = specifier;
        str[indxStr++] = '0';
      }
    }

    //обратно инвертирую в правильном порядке
    reverse_String(str, indxStr);
  }
  str[indxStr] = '\0';
}

//если .5 и меньше то округляет к меньшему
long double round_to_n_decimals(long double number,
                                int n) {  //округление до n знаков после запятой
  double scale = pow(10, n);
  return round(number * scale) / scale;
}

void float_to_string(long double number, char *str, struct flags flag,
                     int precision, char specifier) {
  if (precision == -1)  //пользователь не задал точность
    precision = 6;  //по умолчанию 6 знаков после запятой

  number =
      round_to_n_decimals(number, precision);  //округляю до нужного значения
  double wholePart = 0;
  double decimalPart = modf(number, &wholePart);

  // Преобразуем целую часть числа
  long int intWholePart = wholePart;
  int_to_string(intWholePart, str, flag, precision, 'd', specifier);
  int length = s21_strlen(str);
  if (precision > 0 || flag.grid == 1) {
    // Добавляем разделитель десятичной части
    str[length++] = '.';

    for (int i = 0; i < precision; i++) decimalPart *= 10;
    long int intDecimalPart = (long int)round(
        decimalPart);  //дробная часть представляется целочисленной
    int decimalNumber[precision];
    for (int i = 0; i < precision; i++) decimalNumber[i] = 0;

    for (int i = 0; i < precision;
         i++) {  //вношу каждую цифру числа в массив цифр
      decimalNumber[i] = intDecimalPart % 10;
      intDecimalPart /= 10;
    }

    for (int i = 0; i < precision; i++) {
      int lastDigit =
          precision - 1 - i;  //запись с конца, т.к. инвертирована запись
      str[length++] = decimalNumber[lastDigit] + '0';
    }
  }
  str[length] = '\0';
}

void string_to_string(char *enterStr, char *str, int precision) {
  int len = s21_strlen(enterStr);
  int end = len;
  int i = 0;
  if (precision != -1 && precision < len) {
    end = precision;
  }
  for (; i < end; i++) {
    str[i] = enterStr[i];
  }
  str[i] = '\0';
}

int degree_counter(double *num) {
  int count_exponent = 0;
  if (*num >= 1) {
    while (*num >= 10.0) {
      *num /= 10.0;
      count_exponent++;
    }
  } else {
    while (*num < 1) {
      *num *= 10.0;
      count_exponent--;
    }
  }
  return count_exponent;
}

void eE_to_string(double num, char *buffer, int precision, struct flags flag,
                  char specifier) {
  int isNegative = 0;  //проверка на отрицательность
  if (num < 0) {
    isNegative = 1;
    num = -num;
  }
  int count_exponent = degree_counter(&num);
  if (isNegative) {  //знак если нужен
    s21_strncat(buffer, "-", 1);
  } else if (flag.plus == 1) {
    s21_strncat(buffer, "+", 1);
  } else if (flag.space == 1) {
    s21_strncat(buffer, " ", 1);
  }
  char str_demo[100] = "";
  if (precision == -1) {  //запись с нужной точностью
    s21_sprintf(str_demo, "%f%c%+.2d", num, specifier, count_exponent);
  } else {
    s21_sprintf(str_demo, "%.*f%c%+.2d", precision, num, specifier,
                count_exponent);
  }
  s21_strncat(buffer, str_demo, s21_strlen(str_demo));
}

void string_output_with_specifier(char specifier, va_list *factor,
                                  struct flags flag, int precision, char length,
                                  char *stringWithSpecifier) {
  long int d;
  unsigned long int ld;

  if (specifier == 'd') {
    d = va_arg(*factor, long);
    type_conversion(&d, length);
    int_to_string(d, stringWithSpecifier, flag, precision, 'i', specifier);
  } else if (specifier == 'o' || specifier == 'x' || specifier == 'X' ||
             specifier == 'u' || specifier == 'p') {
    ld = va_arg(*factor, unsigned long int);
    uoxX_type_conversion(&ld, length);
    uoxX_to_string(ld, stringWithSpecifier, flag, precision, specifier);
  } else if (specifier == 'f') {
    if (length != 'L')
      float_to_string(va_arg(*factor, double), stringWithSpecifier, flag,
                      precision, specifier);
    else
      float_to_string(va_arg(*factor, long double), stringWithSpecifier, flag,
                      precision, specifier);
  } else if (specifier == 'e' || specifier == 'E') {
    eE_to_string(va_arg(*factor, double), stringWithSpecifier, precision, flag,
                 specifier);
  } else if (specifier == 'c') {
    stringWithSpecifier[0] = va_arg(*factor, int);
    stringWithSpecifier[1] = '\0';
  } else if (specifier == 's') {
    string_to_string(va_arg(*factor, char *), stringWithSpecifier, precision);
  } else if (specifier == '%') {
    stringWithSpecifier[0] = '%';
    stringWithSpecifier[1] = '\0';
  }
}

void string_output_with_width(char **str, int width, struct flags flag,
                              char *stringWithSpecifier) {
  int lenStringWithSpecifier = s21_strlen(stringWithSpecifier);
  if (width > lenStringWithSpecifier) {
    int len_space = width - lenStringWithSpecifier;
    char arrSpace[1000] = "";
    char simbol = ' ';
    if (flag.zero == 1) simbol = '0';
    s21_memset(arrSpace, simbol, len_space);
    if (flag.minus == 1) {
      s21_strncpy(*str, stringWithSpecifier, lenStringWithSpecifier);
      *str += lenStringWithSpecifier;

      s21_memset(arrSpace, ' ', len_space);
      s21_strncpy(*str, arrSpace, len_space);
      *str += len_space;
    } else {
      s21_strncpy(*str, arrSpace, len_space);
      *str += len_space;

      s21_strncpy(*str, stringWithSpecifier, lenStringWithSpecifier);
      *str += lenStringWithSpecifier;
    }
  } else {
    s21_strncpy(*str, stringWithSpecifier, lenStringWithSpecifier);
    *str += lenStringWithSpecifier;
  }
}

int result_sprintf(char *start, char *end) {  // возвращает дисло записей или -1
  int length = 0;
  char *ptr = start;

  while (ptr != end && *ptr != '\0') {
    length++;
    ptr++;
  }

  return length;
}

int s21_sprintf(char *str, const char *format, ...) {
  char *start = str;  //указатель на начало строки
  va_list factor;
  va_start(factor, format);

  for (const char *ch = format; *ch; ch++) {
    if (*ch != '%') {
      *str++ = *ch;
      continue;
    }
    struct flags flag = {0, 0, 0, 0, 0};

    flag_reading(&ch, &flag);                         //флаги
    int width = width_reading(&ch, &factor);          //ширина
    int precision = precision_reading(&ch, &factor);  //точность
    char length = length_reading(&ch);                //длина

    char stringWithSpecifier[1000] = "";
    char specifier = *++ch;
    if (specifier == 'd' || specifier == 'u' || specifier == 'f' ||
        specifier == 's' || specifier == 'c' || specifier == 'X' ||
        specifier == 'x' || specifier == 'o' || specifier == 'p' ||
        specifier == 'e' || specifier == 'E' || specifier == '%') {
      //часть 1 - строка stringWithSpecifier
      string_output_with_specifier(specifier, &factor, flag, precision, length,
                                   stringWithSpecifier);
      //часть 2 - запись в правильном виде
      string_output_with_width(&str, width, flag, stringWithSpecifier);
    }
  }
  *str = '\0';
  va_end(factor);
  int result = result_sprintf(start, str);
  return result;
}
