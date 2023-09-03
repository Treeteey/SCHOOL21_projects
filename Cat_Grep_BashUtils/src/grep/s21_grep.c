#include "s21_grep.h"

int main(int argc, char *argv[]) {
  struct flags flag = {0};
  char expr_string[MY_REG] = {0};

  if (argc > 1) {
    read_flag(argc, argv, &flag, expr_string);
    if (flag.e == 0 && flag.f == 0) {
      if (*argv[optind] == 0) argv[optind] = ".";
      strcat(expr_string, argv[optind]);
      optind += 1;
    }
    open_files(argc, argv, expr_string, flag);
  }
  return 0;
}

void read_flag(int argc, char *argv[], struct flags *flag, char *expr_string) {
  int ch = 0;
  int e_count = 0;  // number of expressions
  char *optstring = "e:ivclnhsf:o";
  while ((ch = getopt_long(argc, argv, optstring, NULL, NULL)) != -1) {
    switch (ch) {
      case 'e':
        flag->e = 1;
        add_eflag(optarg, &e_count, expr_string);
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;  // on Mac l and c work together
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'f':
        flag->f = 1;
        add_fflag(optarg, &e_count, expr_string, flag);
        break;
      case '?':
        exit(1);
      default:
        if (!flag->s) {
          flag_error(ch);
          exit(1);
        }
        break;
    }
  }
}

void flag_error(char ch) {
  printf("grep: invalid option -- %c\n", ch);
  printf(
      "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
      "[-C[num]]\n");
  printf("[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");
  printf(
      "[--context[=num]] [--directories=action] [--label] "
      "[--line-buffered]\n");
  printf("[--null] [pattern] [file ...]");
}

void add_eflag(char *optarg, int *e_count, char *expr_string) {
  if (*e_count != 0) {
    strcat(expr_string, "|");
  }
  if (*optarg == 0) {
    optarg = ".";
    // flag->empty_line++;
  }
  strcat(expr_string, optarg);
  *e_count += 1;
}

void add_fflag(char *optarg, int *e_count, char *expr_string,
               struct flags *flag) {
  FILE *fp_f = NULL;
  char line[STR_BUFFER] = {0};

  if ((fp_f = fopen(optarg, "r")) == NULL) {
    if (!flag->s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", optarg);
    }
    return;
  } else {
    while (fgets(line, STR_BUFFER, fp_f) != NULL) {
      if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = 0;  // '\n' is deleted and replaced with '\0'
      if (*e_count > 0) strcat(expr_string, "|");
      if (*line == '\0') {
        strcat(expr_string, ".");
      } else {
        strcat(expr_string, line);
      }
    }
    fclose(fp_f);
  }
}

void open_files(int argc, char *argv[], char *expr_string, struct flags flag) {
  FILE *fp;
  int files_count = argc - optind;
  int match_mas_file[files_count];
  for (int i = 0; i < files_count; i++) match_mas_file[i] = 0;
  char filemas[files_count][100];  //гребаный С флаг
  int currfile = 0;
  for (; optind < argc; optind++) {
    if ((fp = fopen(argv[optind], "r")) == NULL) {
      if (flag.s == 0) {
        fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
      }
    } else {
      int len = strlen(argv[optind]);
      strncpy(filemas[currfile], argv[optind], len);
      filemas[currfile][len] = '\0';

      currfile = currfile + 1;
      reg_compile(argv, expr_string, fp, flag, files_count, match_mas_file,
                  currfile);
      fclose(fp);
    }
  }
  if (flag.c || flag.l) {
    c_l_flag(match_mas_file, filemas, currfile, flag);
  }
}

void reg_compile(char **argv, char *my_reg, FILE *fp, struct flags flag,
                 int files_count, int *match_mas_file, int currfile) {
  regex_t myre;
  regmatch_t pmatch[10];
  size_t nmatch = 1;
  int err;
  char str[STR_BUFFER];
  int lines_count = 0;
  int i_option = 0;
  int match_line_count = 0;
  if (flag.i != 0) i_option = REG_ICASE;
  err = regcomp(&myre, my_reg, REG_EXTENDED | i_option);
  while (fgets(str, STR_BUFFER, fp) != NULL) {
    lines_count = lines_count + 1;  // if can read line
    err = regexec(&myre, str, nmatch, pmatch, 0);
    if (err == 0 && flag.v == 0) match_line_count = match_line_count + 1;
    if (flag.v && err != 0) match_line_count = match_line_count + 1;
    if ((flag.c == 0 && flag.l == 0 && err == 0 && flag.v == 0) ||
        (flag.c == 0 && flag.l == 0 && flag.v != 0 && err == REG_NOMATCH)) {
      if (flag.h == 0 && files_count > 1) printf("%s:", argv[optind]);
      if (flag.n != 0)  // if flag n != 0 - need line number
        printf("%d:", lines_count);
      printf("%s", str);
      if (str[strlen(str) - 1] != '\n') {
        printf("\n");
      }
    }
  }
  match_mas_file[currfile - 1] = match_line_count;
  regfree(&myre);
}

void c_l_flag(int *match_mas_files, char filemas[][100], int currfile,
              struct flags flag) {
  for (int i = 0; i < currfile; i++) {
    if (flag.c) {
      if (flag.l && currfile == 1) {
        if (match_mas_files[i] == 0) printf("0\n");
        if (match_mas_files[i] != 0) {
          printf("1\n");
          printf("%s\n", filemas[i]);  // that the way on mac
        }
      }
      if (flag.l && currfile > 1) {
        if (match_mas_files[i] == 0) {
          if (flag.h == 0) printf("%s:", filemas[i]);
          printf("0\n");
        }
        if (match_mas_files[i] != 0) {
          if (flag.h == 0) printf("%s:", filemas[i]);  // fucking mac
          printf("1\n");
          printf("%s\n", filemas[i]);  // that the way on mac
        }
      }
      if (currfile == 1 && !flag.l) printf("%d\n", match_mas_files[i]);
      if (currfile > 1 && !flag.l) {
        if (flag.h == 0) printf("%s:", filemas[i]);
        printf("%d\n", match_mas_files[i]);
      }
    }
    if (flag.l && !flag.c) {
      if (match_mas_files[i] != 0) {
        printf("%s\n", filemas[i]);
      }
    }
  }
}