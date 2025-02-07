#include "myFuncs.h"

int check_flags(int *argc_, char **argv_, struct flags *flag, char *mas_[3]) {
  int keepOutput = 0, isFile = 0, isB = 0;
  FILE *fp = NULL;
  for (int i = 1; i < *argc_; i++) {
    int len = strlen(argv_[i]);  // find lenght of argument
    if (argv_[i][0] == '-' && isFile == 0 &&
        keepOutput == 0) {  // if argv starts with '-' and there wasnt filename
      if (argv_[i][1] != '-') {
        for (int n = 1; n < len; n++)  // check all options after '-'
          switch_option(argv_, i, n, &keepOutput, flag, &isB);
      } else {                 // if argv starts with '--'
        int existingArgv = 0;  // flag if option is existing
        for (int j = 0; j < 3; j++) {
          if (strcmp(argv_[i], mas_[j]) == 0) {
            existingArgv = 1;
            switch (j) {
              case 0:
                flag->b = 1;
                break;
              case 1:
                flag->n = 1;
                break;
              case 2:
                flag->s = 1;
                break;
            }
          }
          if (strlen(argv_[i]) == 2) existingArgv = 1;
        }
        if (existingArgv == 0) {
          printf("cat: illegal option -- -\n");
          printf("usage: cat [-benstuv] [file ...]");
          keepOutput = 1;
        }
      }
    } else {
      if (keepOutput == 0) {
        isFile = 1;
        if (fp = fopen(argv_[i], "rb")) {
          cat(*flag, fp);
          fclose(fp);
        } else {
          fprintf(stderr, "cat: %s: No such file or directory\n", argv_[i]);
        }
      }
    }
  }
  return keepOutput;
};

void switch_option(char *argv_[], int i, int n, int *keepOutput,
                   struct flags *flag, int *isB) {
  switch (argv_[i][n]) {
    case 'b':
      flag->b = 1;
      *isB = 1;
      flag->n = 0;
      break;
    case 'e':
      flag->e = 1;
      flag->v = 1;
      break;
    case 'E':
      flag->e = 1;
      flag->v = 0;
      break;
    case 'n':
      if (*isB)
        flag->n = 0;
      else
        flag->n = 1;
      break;
    case 's':
      flag->s = 1;
      break;
    case 't':
      flag->t = 1;
      flag->v = 1;
      break;
    case 'T':
      flag->t = 1;
      flag->v = 0;
      break;
    case 'v':
      flag->v = 1;
      break;
    default:
      printf("cat: illegal option -- %c\n", argv_[i][n]);
      printf("usage: cat [-benstuv] [file ...]");
      *keepOutput = 1;
  }
};

void cat(struct flags flag, FILE *fp) {
  int cursym /*cur symbol*/, prevsym = '\n' /*prev symbol*/,
                             temp = 0 /*consequtive new lines - \n's*/,
                             count = 1 /*number of line*/,
                             first = 1 /*if cur char is the first in file*/;
  while ((cursym = fgetc(fp)) != EOF) {
    if (flag.s) {
      if (cursym == '\n' && first)
        temp = temp + 2;
      else if (cursym == '\n')
        temp = temp + 1;
      if (cursym != '\n') temp = 0;
    }
    if (cursym == '\n' && (!flag.s || temp < 3)) {
      if (flag.n && prevsym == '\n') printf("%6d\t", count++);
      if (flag.e) printf("$");
      printf("%c", cursym);
    }
    if (cursym != '\n') {
      if ((prevsym == '\n' || first == 1) && (flag.n || flag.b))
        printf("%6d\t", count++);
      if (flag.v && cursym < 32 && cursym != 9 && cursym != 10)
        printf("^%c", cursym + 64);
      // else if (flag.v && cursym > 127 && cursym < 160)
      //   printf("M-^%c", cursym - 64);
      else if (flag.v && cursym == 127)
        printf("^%c", cursym - 64);
      else if (flag.t && cursym == '\t')
        printf("^I");
      else
        printf("%c", cursym);
    }
    prevsym = cursym;
    first = 0;  // after first cycle the rest symbols are not first chars
  }
}