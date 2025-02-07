#ifndef C_MAZE_H
#define C_MAZE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int **maze;
  int **vert_walls;
  int **hor_walls;
  int rows;
  int cols;
  int y;
  int counter;
  char *filename;
} MatrixInfo_t;

int maze_generation(char *filename, int rows, int columns);
void matrix_init(MatrixInfo_t *info);
bool matrix_error(MatrixInfo_t *info);

void free_matrix(MatrixInfo_t info);
void rows_init(MatrixInfo_t *info);
void multipliers_combination(MatrixInfo_t *info);
void non_connection_multipliers(MatrixInfo_t *info, int *col, int *next_col);
void multipliers_combination_for_last_row(MatrixInfo_t *info);
void copy_num(MatrixInfo_t *info);
void copy_num_check(MatrixInfo_t *info, int *col);
int multipliers_length(MatrixInfo_t *info, int *col);
bool check_next_line(MatrixInfo_t *info, int *col);
void eller_in_binary(MatrixInfo_t *info);
void save_maze(MatrixInfo_t info);

#endif
