#include "../solve_maze/wave_algorithm.h"
#include "ui.h"

const char *solve_labyrinth_options[] = {"row begin", "row end", "col begin",
                                         "col end",   "SOLVE",   "Return"};

/**
 * @brief SolveLabyrinthSubmenu - prints the menu of the solve labyrinth submenu
 *
 * @param labyrinth - pointer to struct Labyrinth
 * @param lab_height_pos - row of the beginning of labyrinth in the window
 * @param lab_width_pos - column of the beginning of labyrinth in the window
 * @param menu_row - row of the beginning of the menu in the window
 * @param menu_col - column of the beginning of the menu in the window
 *
 * @return void
 *
 * The function prints the menu of the solve labyrinth submenu and waits for the
 * user to enter the data. The function processes the user's key presses and
 * calls the functions accordingly. The function also prints the result of the
 * solution of the labyrinth.
 *
 */
void SolveLabyrinthSubmenu(struct Labyrinth *labyrinth, int lab_height_pos,
                           int lab_width_pos, int menu_row, int menu_col) {
  struct Solver solver;
  InitiateSolver(&solver);
  int size =
      sizeof(solve_labyrinth_options) / sizeof(solve_labyrinth_options[0]);
  int solve_labyrinth_state = 0;
  int stop = 0;
  while (stop == OK) {
    DrawMenuOptions(solve_labyrinth_options, size, &solve_labyrinth_state, 1,
                    menu_row, menu_col);
    int key = getch();
    switch (key) {  // process key
      case KEY_UP:
        solve_labyrinth_state -= (solve_labyrinth_state > 0) ? 1 : 0;
        break;
      case KEY_DOWN:
        solve_labyrinth_state += (solve_labyrinth_state < size - 1) ? 1 : 0;
        break;
      case '\n':  // preocess Enter key
      {           // Enter key
        CaseEnterAtSolveLabSumbenu(labyrinth, &solver, solve_labyrinth_state,
                                   size, menu_row, menu_col, lab_height_pos,
                                   lab_width_pos, &stop);
      } break;
      case 27:  // escape key
        stop = FINISH;
        ClearMenuOptions(size, &solve_labyrinth_state, 1, menu_row, menu_col);
        refresh();
        break;
    }
  }
}

/**
 * Initializes the Solver structure by setting all of its fields to zero.
 * @param solver The Solver structure to be initialized.
 */
void InitiateSolver(struct Solver *solver) {
  solver->begin_row[0] = '\0';
  solver->begin_column[0] = '\0';
  solver->end_row[0] = '\0';
  solver->end_column[0] = '\0';

  solver->b_row_len = 0;
  solver->b_col_len = 0;
  solver->e_row_len = 0;
  solver->e_col_len = 0;
}

/**
 * @brief Handles the events of the solve labyrinth submenu
 *
 * @param labyrinth - pointer to struct Labyrinth
 * @param solver - pointer to struct Solver
 * @param solve_labyrinth_state - current state of the submenu
 * @param size - size of solve_labyrinth_options array
 * @param menu_row - row of the menu
 * @param menu_col - column of the menu
 * @param lab_height_pos - row position of the labyrinth
 * @param lab_width_pos - column position of the labyrinth
 * @param stop - pointer to enum Status, is changed to FINISH if wanna exit
 */
void CaseEnterAtSolveLabSumbenu(struct Labyrinth *labyrinth,
                                struct Solver *solver,
                                int solve_labyrinth_state, int size,
                                int menu_row, int menu_col, int lab_height_pos,
                                int lab_width_pos, int *stop) {
  switch (solve_labyrinth_state) {
    case 0:  // row begin
      EditLine(menu_row, menu_col, solver->begin_row, &(*solver).b_row_len, 1,
               12);
      break;
    case 1:  // column begin
      EditLine(menu_row + 1, menu_col, solver->end_row, &(*solver).e_row_len, 1,
               12);
      break;
    case 2:  // row end
      EditLine(menu_row + 2, menu_col, solver->begin_column,
               &(*solver).b_col_len, 1, 12);
      break;
    case 3:  // column end
      EditLine(menu_row + 3, menu_col, solver->end_column, &(*solver).e_col_len,
               1, 12);
      break;
    case 4:  // solve
      int b_row = atoi(solver->begin_row), b_col = atoi(solver->begin_column),
          e_row = atoi(solver->end_row), e_col = atoi(solver->end_column);

      enum Status status = OK;
      if (b_row < 0 || b_col < 0 || e_row < 0 || e_col < 0 ||
          b_row > (*labyrinth).rows || b_col > (*labyrinth).columns ||
          e_row > (*labyrinth).rows || e_col > (*labyrinth).columns) {
        status = ERROR;
      }

      if (status == OK && labyrinth->new_labyrinth != NULL) {
        status = SolveLabyrinth(labyrinth, b_row - 1, b_col - 1, e_row - 1,
                                e_col - 1);
      }

      if (status == FINISH) {
        WPrintLabyrinth(&(*labyrinth).solved_labyrinth,
                        (*labyrinth).current_rows, (*labyrinth).current_columns,
                        lab_height_pos, lab_width_pos);
      } else {
        int width, height;
        getmaxyx(stdscr, height, width);
        ClearLabFromWindow(width, height, MENU_WIDTH);
      }
      refresh();
      break;
    case 5:  // return to main menu
      *stop = FINISH;
      ClearMenuOptions(size, &solve_labyrinth_state, 1, menu_row, menu_col);
      break;
  }  // end switch solve_labyrinth_state
}

/*
line_type = 0 - filename
line_type = 1 - number

| menu    >[]   |
menu starts at 2
shift = 8  - between begin of menu and '>' symbol
*/

/**
 * @brief EditLine - allows user to edit a line
 *
 * @param menu_row - row of the menu
 * @param menu_col - column of the menu
 * @param line - string to edit
 * @param len - pointer to length of the string
 * @param line_type - type of the line, 0 - filename, 1 - number
 * @param shift - shift between '>' and start of the line
 *
 * @return void
 */
void EditLine(int menu_row, int menu_col, char *line, int *len, int line_type,
              int shift) {
  int temp_col = menu_col + shift;
  mvaddch(menu_row, temp_col++, '>');
  mvaddstr(menu_row, temp_col++, "[]");
  if (*len != 0) {
    for (int i = 0; i < *len; i++) {
      mvaddch(menu_row, temp_col + i, line[i]);
    }
    temp_col += *len;
    mvaddch(menu_row, temp_col, ']');
  }

  int input = getch();
  while (input != '\n') {
    if (input == '\n' || input == 8 || input == 27 || input == KEY_BACKSPACE ||
        input == 263) {
      // escape key
      if (input == 27) break;
      // backspace
      if ((input == 8 || input == 127 || input == KEY_BACKSPACE ||
           input == 263) &&
          *len > 0) {
        (*len)--;
        line[*len] = '\0';
        mvaddch(menu_row, temp_col--, ' ');
        mvaddch(menu_row, temp_col, ']');
        refresh();
      }
    } else {
      // number
      if (line_type == 1) {
        if (isdigit(input) && *len < 3) {
          mvaddch(menu_row, temp_col++, input);
          mvaddch(menu_row, temp_col, ']');
          line[(*len)++] = input;
          refresh();
        }
      } else {  // filename
        mvaddch(menu_row, temp_col++, input);
        mvaddch(menu_row, temp_col, ']');
        line[(*len)++] = input;
        refresh();
      }
      line[*len] = '\0';
    }
    input = getch();
  }  // end while input != '\n'
  mvaddch(menu_row, menu_col + shift, ' ');
}

/**
 * @brief SolveLabyrinth - solves the labyrinth and prints the solution
 *
 * @param labyrinth - pointer to struct Labyrinth
 * @param b_row - row of the begin point
 * @param b_col - column of the begin point
 * @param e_row - row of the end point
 * @param e_col - column of the end point
 *
 * @return enum Status - OK if all is good, ERROR if error, FINISH if wanna exit
 *
 * The function solves the labyrinth and prints the solution.
 * If the labyrinth is not loaded, it returns ERROR, otherwise OK.
 */

enum Status SolveLabyrinth(struct Labyrinth *labyrinth, int b_row, int b_col,
                           int e_row, int e_col) {
  int rows = (*labyrinth).rows;
  int columns = (*labyrinth).columns;
  enum Status status = OK;

  element_queue *coords = NULL;
  int steps = 0;
  if ((b_row >= 0 && b_col >= 0 && e_row >= 0 && e_col >= 0) &&
      (b_row < rows && b_col < columns && e_row < rows && e_col < columns)) {
    SolveMaze((*labyrinth).matrix_side_wall, (*labyrinth).matrix_bottom_wall,
              &coords, &steps, rows, columns, b_row, b_col, e_row, e_col);

    DrawSolution(labyrinth, coords, steps);

    if (coords != NULL) free(coords);
    status = FINISH;
  } else {
    status = ERROR;
  }
  return status;
}

// enum Status SolveLabyrinth(struct Labyrinth *labyrinth, int b_row, int b_col,
//                            int e_row, int e_col) {
//   int rows = (*labyrinth).rows;
//   int columns = (*labyrinth).columns;

//   element_queue *coords = NULL;
//   int steps = 0;

//   SolveMaze((*labyrinth).matrix_side_wall, (*labyrinth).matrix_bottom_wall,
//             &coords, &steps, rows, columns, b_row, b_col, e_row, e_col);

//   DrawSolution(labyrinth, coords, steps);

//   if (coords != NULL) free(coords);
//   return FINISH;
// }

/*
если масштаб равен 3 то линия должна в 3/2 = 1 линии отрисовываться
отсчет линий с нуля начинается
        |   |   |   ->   | o |   |   |
                                         | o |   |   |

если масштаб равен 4 то линия должна в 4/2 = 2 линии отрисовываться
        |    |    |   ->   |  o |    |    |
                                           |  o |    |    |
*/

/**
 * @brief DrawSolution - draws the solution of the labyrinth
 *
 * @param labyrinth - pointer to struct Labyrinth
 * @param solv_lab_hor - matrix of horizontal lines of the solution
 * @param solv_lab_vert - matrix of vertical lines of the solution
 *
 * The function draws the solution of the labyrinth by drawing
 * horizontal and vertical lines in the places where the solution
 * of the labyrinth passes.
 *
 * The function first allocates memory for the scaled solved labyrinth,
 * then it draws the solution.
 */

void DrawSolution(struct Labyrinth *labyrinth, element_queue *coords,
                  int steps) {
  // allocate memory for whar_t **scaled_solved_labyrinth first that is the
  // variable in struct Labyrinth
  (*labyrinth).solved_labyrinth =
      (wchar_t **)malloc((*labyrinth).current_rows * sizeof(wchar_t *));
  for (int i = 0; i < (*labyrinth).current_rows; i++) {
    (*labyrinth).solved_labyrinth[i] =
        (wchar_t *)malloc((*labyrinth).current_columns * sizeof(wchar_t));
  }
  for (int i = 0; i < (*labyrinth).current_rows; i++) {
    for (int j = 0; j < (*labyrinth).current_columns; j++) {
      (*labyrinth).solved_labyrinth[i][j] = (*labyrinth).new_labyrinth[i][j];
    }
  }

  int current_row = (*labyrinth).row_scale / 2 + 1 +
                    coords[steps - 1].y * ((*labyrinth).row_scale + 1);
  int current_col = (*labyrinth).column_scale / 2 + 1 +
                    coords[steps - 1].x * ((*labyrinth).column_scale + 1);
  int delta_x = 0;  // горизонтальная
  int delta_y = 0;  // вертикальная

  for (int i = steps - 1; i > 0; i--) {
    delta_x = coords[i - 1].x - coords[i].x;
    delta_y = coords[i - 1].y - coords[i].y;
    if (delta_x == 0) {
      // vertical line
      for (int j = 0; j < (*labyrinth).row_scale + 1; j++) {
        (*labyrinth).solved_labyrinth[current_row][current_col] = L'▮';  // L'|'
        current_row += delta_y;
      }
    } else {
      // horizontal line
      for (int j = 0; j < (*labyrinth).column_scale + 1; j++) {
        (*labyrinth).solved_labyrinth[current_row][current_col] = L'▬';  // L'-'
        current_col += delta_x;
      }
    }
  }  // end for loop
}  // DrawSolution function