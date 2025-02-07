#include "generate_maze.h"

int maze_generation(char *filename, int rows, int columns) {
  srand(time(NULL));
  MatrixInfo_t info = {0};
  info.filename = filename;
  info.rows = rows;
  info.cols = columns;
  matrix_init(&info);

  if (matrix_error(&info) == false) {
    for (; info.y < info.rows; info.y++) {
      rows_init(&info);
      multipliers_combination(&info);
      copy_num(&info);
      eller_in_binary(&info);
      if (info.y == info.rows - 1) {
        multipliers_combination_for_last_row(&info);
      }
    }
    save_maze(info);
    free_matrix(info);
  }
  return 0;
}

void matrix_init(MatrixInfo_t *info) {
  info->rows = info->rows;
  info->cols = info->cols;

  info->maze = (int **)calloc(info->rows, sizeof(int *));
  info->vert_walls = (int **)calloc(info->rows, sizeof(int *));
  info->hor_walls = (int **)calloc(info->rows, sizeof(int *));
  for (int i = 0; i < info->rows; i++) {
    info->maze[i] = (int *)calloc(info->cols, sizeof(int));
    info->vert_walls[i] = (int *)calloc(info->cols, sizeof(int));
    info->hor_walls[i] = (int *)calloc(info->cols, sizeof(int));
  }
}

bool matrix_error(MatrixInfo_t *info) {
  bool res = false;
  if (info->maze == NULL || info->maze[0] == NULL) {
    res = true;
  }
  return res;
}

void free_matrix(MatrixInfo_t info) {
  for (int i = 0; i < info.rows; i++) {
    free(info.maze[i]);
    free(info.vert_walls[i]);
    free(info.hor_walls[i]);
  }
  free(info.maze);
  free(info.vert_walls);
  free(info.hor_walls);
}

void rows_init(MatrixInfo_t *info) {
  for (int j = 0; j < info->cols; j++) {
    if (info->maze[info->y][j] == 0) {
      info->maze[info->y][j] = info->counter + 1;
      info->counter++;
    }
  }
}

void multipliers_combination(MatrixInfo_t *info) {
  for (int i = 0; i < info->cols - 1; i++) {
    int next = i + 1;
    if (info->maze[info->y][i] == info->maze[info->y][i + 1]) {
      info->vert_walls[info->y][i] = 1;
    }
    if (rand() % 2 == 0) {
      non_connection_multipliers(info, &i, &next);
    } else {
      info->vert_walls[info->y][i] = 1;
    }
    if (i < info->cols - 2 &&
        info->maze[info->y][i + 1] == info->maze[info->y][i + 2]) {
      info->vert_walls[info->y][i + 1] = 1;
    }
  }
}

void multipliers_combination_for_last_row(MatrixInfo_t *info) {
  for (int i = 0; i < info->cols - 1; i++) {
    int next = i + 1;
    if (info->maze[info->y][i] != info->maze[info->y][i + 1] &&
        info->vert_walls[info->y][i] == 1) {
      info->vert_walls[info->y][i] = 0;
    }
    non_connection_multipliers(info, &i, &next);
  }
}

void non_connection_multipliers(MatrixInfo_t *info, int *col, int *next_col) {
  int old_val = info->maze[info->y][*next_col];
  int new_val = info->maze[info->y][*col];
  for (int i = 0; i < info->cols; i++) {
    if (info->maze[info->y][i] == old_val) {
      info->maze[info->y][i] = new_val;
    }
  }
}

void copy_num(MatrixInfo_t *info) {
  for (int i = 0; i < info->cols; i++) {
    int copy = 0;
    int check = multipliers_length(info, &i);
    if (i < info->cols && check_next_line(info, &i) == false &&
        info->y < info->rows - 1 && check > 1) {
      for (int j = 0; j < check; j++) {
        if (rand() % 2 == 0) {
          copy = rand() % (check);
          info->maze[info->y + 1][i + copy] = info->maze[info->y][i + copy];
        }
      }
    } else if (i < info->cols && check_next_line(info, &i) == false &&
               info->y < info->rows - 1 && check == 1) {
      info->maze[info->y + 1][i] = info->maze[info->y][i];
    }
  }
}

int multipliers_length(MatrixInfo_t *info, int *col) {
  int length = 1;
  for (int i = *col; i < info->cols - 1; i++) {
    if (info->maze[info->y][*col] == info->maze[info->y][i + 1]) {
      length++;
    }
  }
  return length;
}
bool check_next_line(MatrixInfo_t *info, int *col) {
  for (int i = 0; i < info->cols; i++) {
    if (info->y < info->rows - 1 &&
        info->maze[info->y + 1][i] == info->maze[info->y][*col]) {
      return true;
    }
  }
  return false;
}

void eller_in_binary(MatrixInfo_t *info) {
  for (int i = 0; i < info->cols; i++) {
    if (i == info->cols - 1) {
      info->vert_walls[info->y][i] = 1;
    }

    if (info->y < info->rows - 1 &&
        info->maze[info->y + 1][i] == info->maze[info->y][i] &&
        info->maze[info->y + 1][i] != 0) {
      info->hor_walls[info->y][i] = 0;
    } else {
      info->hor_walls[info->y][i] = 1;
    }
    if (info->y < info->rows - 1 && i < info->cols - 1 &&
        info->maze[info->y + 1][i] == info->maze[info->y + 1][i + 1] &&
        info->maze[info->y + 1][i] != 0) {
      info->vert_walls[info->y + 1][i] = 1;
    }
  }
}
void save_maze(MatrixInfo_t info) {
  FILE *file = fopen(info.filename, "w");
  if (file != NULL) {
    fprintf(file, "%d %d\n", info.rows, info.cols);
    for (int i = 0; i < info.rows; i++) {
      for (int j = 0; j < info.cols; j++) {
        fprintf(file, "%d ", info.vert_walls[i][j]);
      }
      fprintf(file, "\n");
    }
    fprintf(file, "\n");
    for (int i = 0; i < info.rows; i++) {
      for (int j = 0; j < info.cols; j++) {
        fprintf(file, "%d ", info.hor_walls[i][j]);
      }
      fprintf(file, "\n");
    }
    fclose(file);
  }
}