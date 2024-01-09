#ifndef GREP
#define GREP

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// optarg - argument value if option demands argument
// for example if optstring "e:ivclnhsf:o"; and in console inputs "-e fuck"
// then when we at -e option, global optarg = "fuck"
//   optind - first argument that is not an iption

#define STR_BUFFER 8192
#define MY_REG 1024

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
};

void read_flag(int argc, char *argv[], struct flags *flag, char *expr_string);
void flag_error(char ch);
void add_eflag(char *optarg, int *e_count, char *expr_string);
void add_fflag(char *optarg, int *e_count, char *expr_string, struct flags *);

void open_files(int argc, char *argv[], char *expr_string, struct flags flag);
void reg_compile(char *argv[], char *my_reg, FILE *fp, struct flags flag,
                 int files_count, int *match_mas_file, int currfile);
void c_l_flag(int *match_mas_files, char filemas[][100], int currfile,
              struct flags flag);

#endif  // GREP
