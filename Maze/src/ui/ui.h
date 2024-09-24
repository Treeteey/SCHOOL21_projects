#ifndef SRS_UI_H
#define SRS_UI_H

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../generate_maze/generate_maze.h"
#include "../logic/maze.h"
#include "../solve_maze/wave_algorithm.h"

#define _GNU_SOURCE
#ifdef _WIN32
// #include <ncurses.h>
#include <ncursesw/ncurses.h>
#else
// #include <ncursesw/ncurses.h>
#include <curses.h>
#endif

#define MENU_WIDTH 30  //ширина меню слева от лабиринта
#define LAB_HEIGHT_POS 2  // строка начала лабиринта (левый верхний угол)
#define LAB_WIDTH_POS 30  // столбец начала лабиринта (левый верхний угол)

enum MainMenuEnum { LOAD_LABYRINTH, GENERATE_LABYRINTH, LOAD_CAVE, EXIT };

extern const char* main_menu_options[4];
extern const char* load_labyrinth_options[3];
extern const char* solve_labyrinth_options[6];
// generate labyrinth options
extern const char* gen_labyrinth_options[6];

enum LoadLabyrinthEnum { INPUT_FILENAME = 0, RETURN = 1, SOLVE_LABYRINTH = 2 };

struct Solver {
  char begin_row[4], begin_column[4];
  char end_row[4], end_column[4];
  int b_row_len, b_col_len, e_row_len, e_col_len;
};

struct Generator {
  char row_str[10], column_str[10];
  char filename[100];
  int row_len, column_len, filename_len;
};

void InitiateSolver(struct Solver* solver);
void InitiateGenerator(struct Generator* generator);

void ProgramWork();
void DrawBox();
void DrawMenuOptions(const char* options[], int size, int* state, int gap,
                     int menu_row, int menu_col);
void ClearMenuOptions(int size, int* state, int gap, int menu_row,
                      int menu_col);
void WPrintLabyrinth(wchar_t*** labyrinth, int rows, int columns, int move_rows,
                     int move_columns);
void ClearLabFromWindow(int width, int height, int menu_width);

// --------- LOAD LABRYRINTH MENU

enum Status LoadLabyrinth(int width, int height);

void CaseEnterAtLoadLabSubmenu(struct Labyrinth* labyrinth, int current_state,
                               enum Status* load_lab_status, int width,
                               int height, char** filename, int* filename_len);
enum Status LoadLabyrinthByFilename(struct Labyrinth* labyrinth, int width,
                                    int height, char** filename, int move_rows,
                                    int move_columns);

enum Status WOpenFile(FILE** file, char** filename);

enum Status CalculateScale(struct Labyrinth* labyrinth, int width, int height,
                           int move_rows, int move_columns, int* scale_rows,
                           int* scale_columns);

// --------- SOLVE LABRYRINTH MENU

void SolveLabyrinthSubmenu(struct Labyrinth* labyrinth, int lab_height_pos,
                           int lab_width_pos, int menu_row, int menu_col);

void EditLine(int menu_row, int menu_col, char* line, int* len, int line_type,
              int shift);

enum Status SolveLabyrinth(struct Labyrinth* labyrinth, int b_row, int b_col,
                           int e_row, int e_col);

void CaseEnterAtSolveLabSumbenu(struct Labyrinth* labyrinth,
                                struct Solver* solver,
                                int solve_labyrinth_state, int size,
                                int menu_row, int menu_col, int lab_height_pos,
                                int lab_width_pos, int* stop);

// void DrawSolution(struct Labyrinth *labyrinth, int** solv_lab_hor,
// 				  int** solv_lab_vert);
void DrawSolution(struct Labyrinth* labyrinth, element_queue* coords,
                  int steps);

void WPrintLabyrinthSolution(wchar_t*** labyrinth, int rows, int columns,
                             int move_rows, int move_columns);

// --------- GENERATE LABRYRINTH MENU

enum Status GenerateLabyrinth(int width, int height);

enum Status CaseEnterAtGenLabSubmenu(struct Labyrinth* labyrinth,
                                     struct Generator* generator, int state,
                                     int width, int height);

enum Status GenerateLabyrinthFile(struct Labyrinth* labyrinth, char** filename,
                                  int rows, int columns, int width, int height);

#endif  // SRS_UI_H