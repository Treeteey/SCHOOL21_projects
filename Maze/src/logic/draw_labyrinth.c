#include "maze.h"

/*
ввод: адрес лабиринта, кол-во строк, кол-во столбцов
строится пустая коробка с внешними границами
пересечения стенок показаны точками
--------
|       |
| . . . |
|       |
| . . . |
|       |
| . . . |
|       |
L--------
*/
void DrawEmptyLabyrinth(wchar_t ***labyrinth, int rows, int columns) {
  int row_symbols = 2 * rows + 1;
  int column_symbols = 2 * columns + 1;

  *labyrinth = (wchar_t **)malloc(row_symbols * sizeof(wchar_t *));
  for (int i = 0; i < row_symbols; i++) {
    (*labyrinth)[i] = (wchar_t *)malloc(column_symbols * sizeof(wchar_t));
  }

  for (int r_count = 0; r_count < row_symbols; r_count++) {
    if (r_count == 0) {  // for first row
      for (int c_count = 0; c_count < column_symbols; c_count++) {
        if (c_count == 0) {
          (*labyrinth)[r_count][c_count] = L'┌';  // for top left corner
        } else if (c_count == column_symbols - 1) {
          (*labyrinth)[r_count][c_count] = L'┐';  // ┐ for top right corner
        } else
          (*labyrinth)[r_count][c_count] = L'─';
      }
    }
    if (r_count > 0 && r_count < row_symbols - 1 &&
        r_count % 2 == 0) {  // for middle rows
      for (int c_count = 0; c_count < column_symbols; c_count++) {
        if (c_count == 0 || c_count == column_symbols - 1)
          (*labyrinth)[r_count][c_count] = L'|';  // for top left corner`
        else if (c_count % 2 == 1)
          (*labyrinth)[r_count][c_count] = L' ';
        else
          (*labyrinth)[r_count][c_count] = L'.';
      }
    }
    if (r_count > 0 && r_count < row_symbols - 1 &&
        r_count % 2 == 1) {  // for middle rows with cells
      for (int c_count = 0; c_count < column_symbols; c_count++) {
        if (c_count == 0 || c_count == column_symbols - 1)
          (*labyrinth)[r_count][c_count] = L'│';
        else
          (*labyrinth)[r_count][c_count] = L' ';
      }
    }

    if (r_count == row_symbols - 1) {  // for last row
      for (int c_count = 0; c_count < column_symbols; c_count++) {
        if (c_count == 0)
          (*labyrinth)[r_count][c_count] = L'└';  // for bottom left corner
        else if (c_count == column_symbols - 1)
          (*labyrinth)[r_count][c_count] = L'┘';  // for bottom right corner
        else
          (*labyrinth)[r_count][c_count] = L'─';
      }
    }
  }
}

/*
ввод: адрес лабиринта, кол-во строк, кол-во столбцов

выводится весь лабиринт - НО нужно точно задать количество строк и столбцов
*/
void PrintLabyrinth(wchar_t ***labyrinth, int rows, int columns) {
  printf("rows = %d, columns = %d\n", rows, columns);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      wchar_t ch = (*labyrinth)[i][j];
      printf("%lc", ch);
    }
    printf("\n");
  }
}

/*
ввод: адрес лабиринта, адрес на матрицы боковых и нижних стенок,
кол-во строк, кол-во столбцов

добавление стенок сбоку и снизу от ячеек
*/
void DrawElementsToLabyrinth(wchar_t ***labyrinth, int ***matrix_side_wall,
                             int ***matrix_bottom_wall, int rows, int columns) {
  for (int r_count = 0; r_count < rows; r_count++) {
    for (int c_count = 0; c_count < columns; c_count++) {
      if ((*matrix_side_wall)[r_count][c_count] == 1)
        (*labyrinth)[r_count * 2 + 1][c_count * 2 + 2] = L'|';
      if ((*matrix_bottom_wall)[r_count][c_count] == 1)
        (*labyrinth)[r_count * 2 + 2][c_count * 2 + 1] = L'─';
    }
  }
}

/*
масштаб означает сколько копий колонок добавлять к лабиринту
|d|a|g| -> scale = 3  -> |ddd|aaa|ggg|    (7 columns -> 13 columns)
тогда количество колонок увеличивается на (scale-1)*columns
потом строк тоже как то

копируем данные из labyrinth в new_labyrinth и дублируем КОЛОНКИ scale-1 раз
колонки со стенами НЕ ДУБЛИРУЮТСЯ (то есть колонки 0,2,4,...)

МАСШТАБИРОВАНИЕ ПО КОЛОНКАМ только!

  012345678
  ├─┐ .─┐ |

  scale 3

  0123456789abcdefg
  ├───┐   .───┐   |

  0 columns just copy
  1,3,5,... - labyrinth cells need to duplicate
  1 -> 1,2,3
  3 -> 5,6,7
  5 -> 9,10,11
  2,4,6,... - labyrinth walls NO need to duplicate
  2 -> 4v
  4 -> 8
  6 -> 12
 */
void ScaleLabyrinth(struct Labyrinth *labyrinth, int row_scale,
                    int column_scale) {
  if (row_scale <= 0 && column_scale <= 0) {
    return;
  }
  if ((*labyrinth).new_labyrinth != NULL) {
    FreeLabyrinth(&(labyrinth->new_labyrinth), (*labyrinth).current_rows);
  }

  (*labyrinth).row_scale = row_scale;
  (*labyrinth).column_scale = column_scale;

  (*labyrinth).current_rows =
      (*labyrinth).rows * 2 + 1 + (row_scale - 1) * (*labyrinth).rows;
  (*labyrinth).current_columns =
      (*labyrinth).columns * 2 + 1 + (column_scale - 1) * (*labyrinth).columns;

  //создаем новый лабиринт с увеличенным числом колонок
  int new_columns = (*labyrinth).current_columns;
  int new_rows = (*labyrinth).current_rows;
  (*labyrinth).new_labyrinth = (wchar_t **)malloc(new_rows * sizeof(wchar_t *));
  for (int i = 0; i < new_rows; i++) {
    (*labyrinth).new_labyrinth[i] =
        (wchar_t *)malloc(new_columns * sizeof(wchar_t));
  }

  // масштабирование по столбцам
  int old_columns = (*labyrinth).columns * 2;
  int count_columns = new_columns - 1;

  for (; old_columns >= 0; old_columns--) {
    if (old_columns % 2 == 0) {  //столбцы со стенками
      for (int cur_row = 0; cur_row < (*labyrinth).rows * 2 + 1; cur_row++) {
        (*labyrinth).new_labyrinth[cur_row][count_columns] =
            (*labyrinth).labyrinth[cur_row][old_columns];
      }
      --count_columns;
    }
    if (old_columns % 2 == 1) {  //столбцы без стенок
      for (int copy = 0; copy < column_scale;
           copy++) {  // копирование column_scale раз
        for (int cur_row = 0; cur_row < (*labyrinth).rows * 2 + 1; cur_row++) {
          (*labyrinth).new_labyrinth[cur_row][count_columns] =
              (*labyrinth).labyrinth[cur_row][old_columns];
        }
        --count_columns;
      }
    }
  }

  /*  new_labyrinth после масштабирования по столбцам
      -------------
      |aaa|bbb|ccc|
      -------------
      |ddd|eee|fff|
      -------------
  теперь чтобы выполнить масштабирование по строкам
  надо начать с последней строки в new_labyrinth и просто
  переписывать сам new_labyrinth
  -------------   -------------   -------------   -------------
  |aaa|bbb|ccc|   |aaa|bbb|ccc|   |aaa|bbb|ccc|   |aaa|bbb|ccc|
  -------------   -------------                   |aaa|bbb|ccc|
  |ddd|eee|fff|                                   |aaa|bbb|ccc|
                                  -------------   -------------
                  |ddd|eee|fff|   |ddd|eee|fff|   |ddd|eee|fff|
                  |ddd|eee|fff|   |ddd|eee|fff|   |ddd|eee|fff|
                  |ddd|eee|fff|   |ddd|eee|fff|   |ddd|eee|fff|
  -------------   -------------   -------------   -------------
  */
  // масштабирование по строкам

  int old_row = (*labyrinth).rows * 2;
  int count_row = new_rows - 1;

  for (; old_row > 0; old_row--) {
    if (old_row % 2 == 0) {  //строки со стенками
      for (int cur_col = 0; cur_col < new_columns; cur_col++) {
        (*labyrinth).new_labyrinth[count_row][cur_col] =
            (*labyrinth).new_labyrinth[old_row][cur_col];
      }
      --count_row;
    }
    if (old_row % 2 == 1) {  //строки без стенок
      for (int copy = 0; copy < row_scale;
           copy++) {  // копирование row_scale раз
        for (int cur_col = 0; cur_col < new_columns; cur_col++) {
          (*labyrinth).new_labyrinth[count_row][cur_col] =
              (*labyrinth).new_labyrinth[old_row][cur_col];
        }
        --count_row;
      }
    }
  }
}

void FreeLabyrinth(wchar_t ***labyrinth, int rows) {
  if (*labyrinth != NULL) {
    for (int j = 0; j < rows - 1; j++) {
      free((*labyrinth)[j]);
    }
    free(*labyrinth);
    *labyrinth = NULL;
  }
}

/*
add elements to wall crosses (instead of dots)

    |
    |---.---
    |   |

    improved

    |
    ├---┬---
    |   |
________________
надо пройтись по всем узлам стенок, сделать проверки
и заменить на соответствующие элементы:
    ┴ ┬ ├ ┼ ┤
    └ ┐ ─ ┘ ┌

сделаем switch, зададим каждой линии цифру и будем суммировать
слева от точки = 1
сверху от точки = 10
справа от точки = 100
снизу от точки = 1000

-.-   ->  ---    сумма = 1+100 = 101

 |         |
 .   ->    |     сумма равна = 10 + 1000 = 1010
 |         |

 |         |
─.   ->   ─┘     сумма равна = 1 + 10 = 11


 |         |
─.─   ->  ─┴─     сумма равна = 1 + 10 + 100 = 111


 |         |
─.─   ->  ─┼─     сумма равна = 1 + 10 + 100 + 1000 = 1111
 |         |

 |         |
 .─   ->   └─     сумма равна = 10 + 100 = 110

 |         |
 .─   ->   ├─     сумма равна = 10 + 100 + 1000 = 1110
 |         |


 .─   ->   ┌─     сумма равна = 100 + 1000 = 1100
 |         |


─.─   ->  ─┬─     сумма равна = 1 + 100 + 1000 = 1101
 |         |


─.    ->  ─┐     сумма равна = 1 + 1000 = 1001
 |         |

 |         |
─.    ->  ─┤     сумма равна = 1 + 10 + 1000 = 1011
 |         |

─.    ->  ─ ╴     1


 .─   ->   ╶ ─     сумма равна = 100


 |         |
 .    ->   ╵      сумма равна = 10



 .─   ->   ╷     сумма равна = 1000
 |         |




*/
void ImproveLabyrinthWalls(struct Labyrinth *labyrinth) {
  int sum = 0;
  for (int i = 2; i < (*labyrinth).rows * 2 - 1; i += 2) {
    for (int j = 2; j < (*labyrinth).columns * 2 - 1; j += 2) {
      sum += ((*labyrinth).labyrinth[i][j - 1] == L'─') ? 1 : 0;
      sum += ((*labyrinth).labyrinth[i][j + 1] == L'─') ? 100 : 0;
      sum += ((*labyrinth).labyrinth[i - 1][j] == L'|') ? 10 : 0;
      sum += ((*labyrinth).labyrinth[i + 1][j] == L'|') ? 1000 : 0;
      switch (sum) {
        case 1:
          (*labyrinth).labyrinth[i][j] = L'╴';
          break;

        case 10:
          (*labyrinth).labyrinth[i][j] = L'╵';
          break;

        case 11:
          (*labyrinth).labyrinth[i][j] = L'┘';
          break;

        case 100:
          (*labyrinth).labyrinth[i][j] = L'╶';
          break;

        case 101:
          (*labyrinth).labyrinth[i][j] = L'─';
          break;

        case 110:
          (*labyrinth).labyrinth[i][j] = L'└';
          break;

        case 111:
          (*labyrinth).labyrinth[i][j] = L'┴';
          break;

        case 1000:
          (*labyrinth).labyrinth[i][j] = L'╷';
          break;

        case 1001:
          (*labyrinth).labyrinth[i][j] = L'┐';
          break;

        case 1010:
          (*labyrinth).labyrinth[i][j] = L'|';
          break;

        case 1011:
          (*labyrinth).labyrinth[i][j] = L'┤';
          break;

        case 1100:
          (*labyrinth).labyrinth[i][j] = L'┌';
          break;

        case 1101:
          (*labyrinth).labyrinth[i][j] = L'┬';
          break;
        case 1110:
          (*labyrinth).labyrinth[i][j] = L'├';
          break;

        case 1111:
          (*labyrinth).labyrinth[i][j] = L'┼';
          break;

        default:
          break;
      }
      sum = 0;
    }
  }
  ImproveLabyrintPerimeter(labyrinth);
}

/*
    ┌────    ┌─┬──
    | |      | |
    |        |
    |        |
    |─       ├─
    |        |
    |        |

    improved ->

*/

// void ImproveLabyrintPerimeter(struct Labyrinth *labyrinth){
//     for(int i = 2; i < (*labyrinth).rows*2+1; i+=2){
//         if((*labyrinth).labyrinth[1][i] == L'|'){
//             (*labyrinth).labyrinth[0][i] = L'┬';
//         }
//         if((*labyrinth).labyrinth[(*labyrinth).rows*2-1][i] == L'|'){
//             (*labyrinth).labyrinth[(*labyrinth).rows*2][i] = L'┴';
//         }
//     }

//     for(int i = 2; i < (*labyrinth).columns*2+1; i+=2){
//         if((*labyrinth).labyrinth[i][1] == L'─'){
//             (*labyrinth).labyrinth[i][0] = L'├';
//         }
//         if((*labyrinth).labyrinth[i][(*labyrinth).rows*2-1] == L'─'){
//             (*labyrinth).labyrinth[i][(*labyrinth).rows*2] = L'┤';
//         }
//     }
// }

void ImproveLabyrintPerimeter(struct Labyrinth *labyrinth) {
  for (int i = 2; i < (*labyrinth).columns * 2 + 1; i += 2) {
    if ((*labyrinth).labyrinth[1][i] == L'|') {
      (*labyrinth).labyrinth[0][i] = L'┬';
    }
    if ((*labyrinth).labyrinth[(*labyrinth).rows * 2 - 1][i] == L'|') {
      (*labyrinth).labyrinth[(*labyrinth).rows * 2][i] = L'┴';
    }
  }

  for (int i = 2; i < (*labyrinth).rows * 2 + 1; i += 2) {
    if ((*labyrinth).labyrinth[i][1] == L'─') {
      (*labyrinth).labyrinth[i][0] = L'├';
    }
    if ((*labyrinth).labyrinth[i][(*labyrinth).rows * 2 - 1] == L'─') {
      (*labyrinth).labyrinth[i][(*labyrinth).rows * 2] = L'┤';
    }
  }
}

void ClearLabyrinth(struct Labyrinth *labyrinth) {
  if ((*labyrinth).labyrinth != NULL) {
    for (int i = 0; i < (*labyrinth).rows * 2 + 1; i++) {
      free((*labyrinth).labyrinth[i]);
    }
    (*labyrinth).labyrinth = NULL;
  }

  if ((*labyrinth).new_labyrinth != NULL) {
    for (int i = 0; i < (*labyrinth).current_rows; i++) {
      free((*labyrinth).new_labyrinth[i]);
    }
    (*labyrinth).new_labyrinth = NULL;
  }

  if ((*labyrinth).solved_labyrinth != NULL) {
    for (int i = 0; i < (*labyrinth).current_rows; i++) {
      free((*labyrinth).solved_labyrinth[i]);
    }
    (*labyrinth).solved_labyrinth = NULL;
  }

  if ((*labyrinth).matrix_side_wall != NULL) {
    for (int i = 0; i < (*labyrinth).rows; i++) {
      free((*labyrinth).matrix_side_wall[i]);
    }
    (*labyrinth).matrix_side_wall = NULL;
  }

  if ((*labyrinth).matrix_bottom_wall != NULL) {
    for (int i = 0; i < (*labyrinth).rows; i++) {
      free((*labyrinth).matrix_bottom_wall[i]);
    }
    (*labyrinth).matrix_bottom_wall = NULL;
  }

  if ((*labyrinth).solved_labyrinth != NULL) {
    for (int i = 0; i < (*labyrinth).current_rows; i++) {
      free((*labyrinth).solved_labyrinth[i]);
    }
    (*labyrinth).solved_labyrinth = NULL;
  }

  (*labyrinth).rows = 0;
  (*labyrinth).columns = 0;
  (*labyrinth).current_rows = 0;
  (*labyrinth).current_columns = 0;

  (*labyrinth).row_scale = 0;
  (*labyrinth).column_scale = 0;
}