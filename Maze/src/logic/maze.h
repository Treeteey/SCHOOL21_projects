#ifndef SRC_LOGIC_MAZE_H
#define SRC_LOGIC_MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Status { OK = 0, ERROR = 1, FINISH = 2 };

struct Labyrinth {
  wchar_t** new_labyrinth;  // изменяется при изменении масштаба
  wchar_t** labyrinth;  //создается при загрузке, постоянный
  // записывается решение лабиринта
  wchar_t** solved_labyrinth;

  int** matrix_side_wall;
  int** matrix_bottom_wall;

  int rows;
  int columns;
  // current rows and columns also depend on scale! need to realize that feature
  int current_rows;     // when drawing labirinth number of rows changes to
                        // (rows*2+1)
  int current_columns;  // same with columns

  int row_scale;
  int column_scale;
};

// │      |             |      |

// READ FILE
// enum Status OpenFile(char* filename, FILE* file); // wont work
enum Status OpenFile(FILE** file);
enum Status ReadFile(FILE** file, int*** matrix_side_wall,
                     int*** matrix_bottom_wall, int* rows, int* columns);
enum Status AllocateMatrixMemory(int*** matrix_side_wall,
                                 int*** matrix_bottom_wall, int rows,
                                 int columns);
void FreeMemory(int*** matrix, int rows);
enum Status WriteDataInMatrix(FILE** file, int*** matrix, int rows,
                              int columns);

void PrintMatrix(int*** matrix_side_wall, int*** matrix_bottom_wall, int rows,
                 int columns);

// DRAW LABYRINTH
void DrawEmptyLabyrinth(wchar_t*** labyrinth, int rows, int columns);
void DrawElementsToLabyrinth(wchar_t*** labyrinth, int*** matrix_side_wall,
                             int*** matrix_bottom_wall, int rows, int columns);
void PrintLabyrinth(wchar_t*** labyrinth, int rows, int columns);

void ScaleLabyrinth(struct Labyrinth* labyrinth, int row_scale,
                    int column_scale);

void FreeLabyrinth(wchar_t*** labyrinth, int rows);

void ImproveLabyrinthWalls(struct Labyrinth* labyrinth);
void ImproveLabyrintPerimeter(struct Labyrinth* labyrinth);

void ClearLabyrinth(struct Labyrinth* labyrinth);

#endif  // SRC_LOGIC_MAZE_H