#ifndef MYFUNCS
#define MYFUNCS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

struct flags {
  int e;
  int b;
  int n;
  int t;
  int s;
  int v;
};

int check_flags(int *argc_, char **argv_, struct flags *flag, char *mas_[3]);
void switch_option(char *argv_[], int i, int n, int *keepOutput,
                   struct flags *flag, int *isB);
void cat(struct flags flag, FILE *fp);

#endif