#include "myFuncs.h"
/*
-b - number non-blank lines
-e implies -v  - также отображает символы конца строки как $
-n (GNU: --number) нумерует все выходные строки
-s (GNU: --squeeze-blank) сжимает несколько смежных пустых строк
-t предполагает и -v (GNU: -T то же самое, но без применения -v) также
отображает табы как ^I
*/

int main(int argc, char **argv) {
  struct flags flag = {0};
  char *mas[3] = {"--number-nonblank", "--number",
                  "--squeeze-blank"};  // GNU options
  if (check_flags(&argc, argv, &flag, mas)) exit(1);
  return 0;
}