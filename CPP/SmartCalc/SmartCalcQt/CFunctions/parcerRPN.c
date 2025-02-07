#include "../CHeader.h"

char symArr[17] = {'+', '-', '/', '*', '~', '^', 's', 'i', 'n',
                   'c', 'o', 't', 'a', '%', 'q', 'l', 'g'};

char operAfterPowArr[9] = {'s', 'c', 't', 'i', 'o', 'a', 'q', 'n', 'g'};

int parsing_to_RPN(const char *expr, char *outputExpr) {
  Stack stack = {.data = {0}, .top = -1};
  int i = 0, j = 0, ret = 1;
  char temp = {0}, c = '\0';
  char tempExpr[300] = {0};
  while (ret == 1 && expr[i] != '\0' && j < 299) {
    c = expr[i];
    if (is_operand(c) || c == 'x' || c == 'X') {
      // Число - добавляем в строку вывода
      tempExpr[j++] = c;
    } else if (is_function(c)) {
      //если функция то ставим пробел
      if (tempExpr[j - 1] != ' ') {
        tempExpr[j++] = ' ';
      }
      if (isEmpty(&stack) || (priority(stack.data[stack.top]) < priority(c)))
        push(&stack, c);
      else {
        if(peek(&stack)== '^' && operAfterPow(c)){
          push(&stack, c);
        }else{
          while (!isEmpty(&stack) &&
                 priority(stack.data[stack.top]) >= priority(c)) {
            temp = pop(&stack);
            tempExpr[j++] = temp;
            tempExpr[j++] = ' ';
          }
          push(&stack, c);
        }
      }
    } else if (c == '(')
      push(&stack, c);
    else if (c == ')') {
      while (!isEmpty(&stack) && peek(&stack) != '(') {
        temp = pop(&stack);
        tempExpr[j++] = temp;
        tempExpr[j++] = ' ';
      }
      if (peek(&stack) == '(')
        pop(&stack);
      else {
        ret = 0;
      }
    }
    i++;
  }
  while (!isEmpty(&stack) && ret) {
    if (tempExpr[j - 1] != ' ') tempExpr[j] = ' ';
    temp = pop(&stack);
    if (temp == ')' || temp == '(') {
      ret = 0;
    } else {
      tempExpr[j++] = temp;
      tempExpr[j++] = ' ';
    }
  }
  if (ret) {
    for (int m = 0; m < j; m++) {
      *outputExpr = tempExpr[m];
      outputExpr++;
    }
  }

  return ret;
}

int operAfterPow(char c){
  int ret = 0;
  for(size_t i = 0; i < sizeof(operAfterPowArr) && ret == 0; i++){
    if(c == operAfterPowArr[i]) ret = 1;
  }
  return ret;
}


void printFuncName(char c) {
  switch (c) {
    case 's':
      printf("sin");
      break;
    case 'c':
      printf("cos");
      break;
    case 't':
      printf("tan");
      break;
    case 'i':
      printf("asin");
      break;
    case 'o':
      printf("acos");
      break;
    case 'a':
      printf("atan");
      break;
    case '%':
      printf("mod");
      break;
    case 'q':
      printf("sqrt");
      break;
    case 'n':
      printf("ln");
      break;
    case 'g':
      printf("log");
      break;
    default:
      break;
  }
}

int isEmpty(Stack *stack) { return stack->top == -1; }

int isFull(Stack *stack) { return stack->top == MAX_SIZE - 1; }

void push(Stack *stack, char c) {
  if (!isFull(stack)) {
    stack->top += 1;
    stack->data[stack->top] = c;
  } else
    printf("stack is full\n");
}

//если вернется 0 то стек пустой
char pop(Stack *stack) {
  char c = '0';
  if (!isEmpty(stack)) {
    c = stack->data[stack->top];
    stack->data[stack->top] = '\0';
    --stack->top;
  } else
    printf("Pop: stack is empty\n");
  return c;
}

char peek(Stack *stack) {
  char c = '0';
  if (isEmpty(stack)) {
    c = '\0';
  } else
    c = stack->data[stack->top];
  return c;
}

int is_operand(char symbol) {
  int ret = 0;
  if (isdigit(symbol) || symbol == '.') ret = 1;
  return ret;
}

int is_function(char symbol) {
  int ret = 0;
  for (size_t i = 0; i < sizeof(symArr); i++) {
    if (symbol == symArr[i]) {
      ret = 1;
      break;
    }
  }
  return ret;
}

/*
заменим в исходной строке:
sin = s
cos = c
tan = t
asin = i
acos = o
atan = a
sqrt = q
ln = n
log = g
mod = %
*/

void change_expr(char *expr) {
  while (*expr != '\0') {
    if (strncmp(expr, "sin", 3) == 0) {
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr) = 's';
    } else if (strstr(expr, "cos") == expr) {
      //            strcpy(expr, expr + 2);
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr) = 'c';
    } else if (strstr(expr, "tan") == expr) {
      //            strcpy(expr, expr + 2);
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr) = 't';
    } else if (strstr(expr, "asin") == expr) {
      //            strcpy(expr, expr + 3);
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr) = 'i';
    } else if (strstr(expr, "acos") == expr) {
      //            strcpy(expr, expr + 3);
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr) = 'o';
    } else if (strstr(expr, "atan") == expr) {
      //            strcpy(expr, expr + 3);
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr) = 'a';
    } else if (strstr(expr, "sqrt") == expr) {
      //            strcpy(expr, expr + 3);
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr) = 'q';
    } else if (strstr(expr, "ln") == expr) {
      //            strcpy(expr, expr + 1);
      *(expr++) = ' ';
      *(expr) = 'n';
    } else if (strstr(expr, "log") == expr) {
      //            strcpy(expr, expr + 2);
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr) = 'g';
    } else if (strstr(expr, "mod") == expr) {
      //            strcpy(expr, expr + 2);
      *(expr++) = ' ';
      *(expr++) = ' ';
      *(expr) = '%';
    }
    expr++;
  }
}

int priority(char c) {
  int ret = 0;
  switch (c) {
    case '(':
      ret = 0;
      break;
    case '+':
    case '-':
      ret = 1;
      break;
    case '/':
    case '*':
    case '%':
      ret = 2;
      break;
    case 's':
    case 'c':
    case 't':
    case 'i':
    case 'o':
    case 'a':
    case 'q':
    case 'n':
    case 'g':
    case '^':
      ret = 3;
      break;
    default:
      break;
  }
  return ret;
}

int isExisitngSymbol(char c) {
  int ret = 0, size = sizeof(symArr);
  for (int i = 0; i < size; i++) {
    if (c == symArr[i]) ret = 1;
  }
  if (isdigit(c) || c == '.' || c == ' ' || c == '(' || c == ')') ret = 1;
  return ret;
}

//проверка на правильность введенного выражения
//если неправильно то вывести текст ошибки, если правильно то вывести значение
int checkExpres(const char *inputExpr, char *outputExpr) {
  int ret = 1, i = 0, j = 0;
  char changedExpr[255] = {'\0'};
  while (inputExpr[i] != '\0' && ret == 1) {
    if (!isExisitngSymbol(inputExpr[i])) {
      ret = 0;
    } else {
      if (inputExpr[i] == '-' &&
          (i == 0 || (i > 0 && inputExpr[i - 1] == '('))) {
        changedExpr[j++] = '0';
      }
    }
    changedExpr[j] = inputExpr[i];
    j++;
    i++;
  }
  if (ret == 1) {
    int m = 0;
    while (changedExpr[m] != '\0') {
      *outputExpr++ = changedExpr[m];
      m++;
    }
    *outputExpr = '\0';
  }
  return ret;
}
