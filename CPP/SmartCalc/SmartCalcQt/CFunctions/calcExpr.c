#include <string.h>

#include "../CHeader.h"

int calcInputExprAndX(const char *sendExpr, long double X,
                      long double *calculation) {
  int ret = 1;
  if (isXinExpr(sendExpr)) {  //если есть Х в выражении
    char replacedExpr[300] = {};
    if (replaceXinPlotExpr(sendExpr, replacedExpr,
                           X)) {  //если смогли заменить все Х на число в XValue
      ret = calcExpr(replacedExpr,
                     calculation);  //если смогли рассчитать выражение
    }
  } else {  //если просто выражение то рассчитать
    ret = calcExpr(sendExpr, calculation);
  }
  return ret;
}

int calcExpr(const char *parExpr, long double *result) {
  int current = 0, topNumber = 0, ret = 1;  // 1 - good, 0 - bad
  long double numbers[100] = {0};
  char *changedExpr = (char *)parExpr;
  char parcedToRPNExpr[256] = {'\0'};

  change_expr(changedExpr);  // sin -> s, atan -> a ...
  if (checkExpres(changedExpr, changedExpr) &&
      parsing_to_RPN(changedExpr, parcedToRPNExpr))
    ret = 1;
  else
    ret = 0;
  char c = 0;
  while (ret == 1 && parcedToRPNExpr[current] != '\0') {
    c = parcedToRPNExpr[current];
    if (is_operand(c)) {
      if (stringToDouble(parcedToRPNExpr, &current, &numbers[topNumber])) {
        topNumber += 1;
        //после выхода из функции stringToDouble
      } else
        ret = 0;
    } else if (c == ' ') {
      current += 1;
      continue;
    } else {
      if (is_oneOperandFunction(c)) {  //вычисление функции с одним числом
        ret = calcOneOperandFunction(numbers, topNumber, c);
      } else {
        ret = calcTwoOperandFunction(numbers, &topNumber, c);
      }
    }
    current += 1;
  }
  if (ret) *result = numbers[0];
  return ret;
}

int isXinExpr(const char *parExpr) {
  int ret = 0, i = 0;
  while (parExpr[i] != '\0' && ret == 0) {
    if (parExpr[i] == 'X') ret = 1;
    i++;
  }
  return ret;
}

//функции требующие 1 операнд
char oneOperandFunctions[9] = {'s', 'c', 't', 'i', 'o', 'a', 'q', 'n', 'g'};

int is_oneOperandFunction(char c) {
  int ret = 0;
  for (int i = 0; i < 9 && ret == 0; i++) {
    if (c == oneOperandFunctions[i]) ret = 1;
  }
  return ret;
}

int calcOneOperandFunction(long double numbers[], int topNumber, char c) {
  int ret = 1;
  if (topNumber > 0) {
    long double result = 0;
    long double operand = numbers[topNumber - 1];
    switch (c) {
      case 's':
        result = sinl(operand);
        break;
      case 'c':
        result = cosl(operand);
        break;
      case 't':
        result = tanl(operand);
        break;
      case 'i':
        if (operand >= -1.0 && operand <= 1.0) {
          result = asinl(operand);
        } else
          ret = 0;
        break;
      case 'o':
        if (operand >= -1.0 && operand <= 1.0) {
          result = acosl(operand);
        } else
          ret = 0;
        break;
      case 'a':
        result = atanl(operand);
        break;
      case 'q':
        if (operand >= 0.0) {
          result = sqrtl(operand);
        } else
          ret = 0;
        break;
      case 'n':
        if (operand > 0.0) {
          result = logl(operand);
        } else
          ret = 0;
        break;
      case 'g':
        if (operand > 0.0) {
          result = log10l(operand);
        } else
          ret = 0;
        break;
      default:
        ret = 0;
        break;
    };
    if (ret) numbers[topNumber - 1] = result;
  } else
    ret = 0;
  return ret;
}

int calcTwoOperandFunction(long double numbers[], int *topNumber, char c) {
  int ret = 1;

  if (*topNumber > 1) {
    long double result = 0;
    long double operand1 = numbers[*topNumber - 2],
                operand2 = numbers[*topNumber - 1];

    switch (c) {
      case '+':
        result = operand1 + operand2;
        break;
      case '-':
        result = operand1 - operand2;
        break;
      case '*':
        result = operand1 * operand2;
        break;
      case '/':
        if (operand2 != 0.0) {
          result = operand1 / operand2;
        } else {
          ret = 0;
        }
        break;
      case '^':
        result = pow(operand1, operand2);
        break;
      case '%':
        if (operand2 != 0.0) {
          result = fmod(operand1, operand2);
        } else {
          ret = 0;
        }
        break;
      default:
        ret = 0;
        break;
    }
    if (ret) {
      numbers[*topNumber - 2] = result;
      (*topNumber)--;  // уменьшить количество чисел на 1, так как два числа
                       // пересчитались в одно
    }
  } else {
    ret = 0;
  }
  return ret;
}

//начинает идти по строке с start до конца числа,
int stringToDouble(const char *parExpr, int *start, long double *number) {
  int ret =
      1;  // 0 - неправильное число, 1 - правильное и будет запись в number
  int finish = *start, countDots = 0;
  while (parExpr[finish] != '\0'){
    if(isdigit(parExpr[finish]) || parExpr[finish] == '.') {
      if (parExpr[finish] == '.') countDots += 1;
      finish += 1;
      if (countDots > 1) {
        ret = 0;
        break;
      }
    }else break;
  }
  if (ret == 1) {
    char *begin = (char *)parExpr + *start;
    char *end;
    long double temp = strtold(begin, &end);
    int delta = end-begin;
    *number = temp;  //записать число
    if(delta != 0)
      *start = *start + (end - begin)-1;  //записать позицию последней цифры в числе
  }
  return ret;
}

int calcPlotExprWithX(const char *expr, long double x, long double *result) {
  int ret = 1;
  char changedExpr[300] = {0};
  long double temp = 0;
  ret = replaceXinPlotExpr(expr, changedExpr, x);
  if (ret) {
    ret = calcExpr(changedExpr, &temp);
  }
  if (ret) *result = temp;
  return ret;
}

int replaceXinPlotExpr(const char *expr, char *outputExpr, long double x) {
  char temp[256] = {0};
  char xToString[256];
  sprintf(xToString, "%.7Lf", x);  // convert Lf to char array
  int outputExprSize = 0, xStringSize = strlen(xToString);
  int i = 0, j = 0, ret = 1;

  while (expr[i] != '\0' && ret) {
    if (expr[i] == 'X' || expr[i] == 'x') {
      if ((outputExprSize + xStringSize) < 256) {
        strcat(temp, xToString);
        j += xStringSize;
      } else {  // overflow in expr size -> break
        ret = 0;
        break;
      }
    } else {
      temp[j] = expr[i];
      j++;
    }
    i++;
  }
  if (ret) {
    strncpy(outputExpr, temp, 255);
    outputExpr[255] = '\0';
  }
  return ret;
}
