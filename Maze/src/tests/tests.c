#include "tests.h"

#include "../solve_maze/wave_algorithm.h"

START_TEST(test1) {
  MatrixInfo_t info = {0};
  info.rows = 5;
  info.cols = 5;
  matrix_init(&info);
  for (int i = 1; i < info.rows; i++)
    for (int j = 1; j < info.cols; j++) ck_assert_int_eq(0, info.maze[i][j]);
  free_matrix(info);
}
END_TEST

START_TEST(test2) {
  MatrixInfo_t info = {0};
  ck_assert_int_eq(1, matrix_error(&info));
}
END_TEST

START_TEST(test3) {
  MatrixInfo_t info = {0};
  info.rows = 10;
  info.cols = 10;
  matrix_init(&info);
  rows_init(&info);
  for (int i = 1; i < info.rows; i++) {
    ck_assert_int_eq(i, info.maze[info.y][i - 1]);
  }
  free_matrix(info);
}
END_TEST

START_TEST(test4) {
  MatrixInfo_t info = {0};
  maze_generation("", 10, 10);
  ck_assert_ptr_null(info.filename);
}

END_TEST

START_TEST(test5) {
  MatrixInfo_t info = {0};
  maze_generation("test_maze.txt", 10, 10);
  ck_assert_ptr_null(info.filename);
}

END_TEST

START_TEST(wave_1) {
  int ROWS = 4;
  int COLS = 4;

  int **right_wall = calloc(ROWS, sizeof(int *));
  int **down_wall = calloc(ROWS, sizeof(int *));

  for (int i = 0; i < ROWS; i++) {
    right_wall[i] = calloc(COLS, sizeof(int));
    down_wall[i] = calloc(COLS, sizeof(int));
  }

  int right_wall2[4][4] = {
      {0, 0, 0, 1}, {0, 1, 1, 1}, {1, 1, 0, 1}, {0, 0, 0, 1}};

  int down_wall2[4][4] = {
      {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 1}};

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      right_wall[i][j] = right_wall2[i][j];
      down_wall[i][j] = down_wall2[i][j];
    }
  }

  int b_row = 0;
  int b_col = 0;

  int e_row = 3;
  int e_col = 3;

  element_queue *coords = NULL;
  element_queue coords_for_test[7] = {{3, 3}, {3, 2}, {3, 1}, {3, 0},
                                      {2, 0}, {1, 0}, {0, 0}};
  int steps = 0;

  SolveMaze(right_wall, down_wall, &coords, &steps, ROWS, COLS, b_row, b_col,
            e_row, e_col);
  for (int i = 0; i < steps; i++) {
    ck_assert_int_eq(coords[i].x, coords_for_test[i].x);
    ck_assert_int_eq(coords[i].y, coords_for_test[i].y);
  }
  ck_assert_int_eq(steps, 7);

  if (coords != NULL) free(coords);

  for (int i = 0; i < ROWS; i++) {
    free(right_wall[i]);
    free(down_wall[i]);
  }
  free(right_wall);
  free(down_wall);
}
END_TEST

Suite *s21_maze(void) {
  Suite *s = suite_create("s21_suite_maze");
  TCase *tc = tcase_create("s21_tcase_maze");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, wave_1);

  suite_add_tcase(s, tc);

  return s;
}

int main(void) {
  int failed = 0;
  Suite *result = s21_maze();

  SRunner *runner = srunner_create(result);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  failed += srunner_ntests_failed(runner);
  srunner_free(runner);

  return failed != 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
