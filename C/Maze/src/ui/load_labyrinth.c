#include "ui.h"

// load labyrinth options
const char* load_labyrinth_options[] = {"Input filename", "Return to main menu",
                                        "Solve labyrinth"};

/**
 * @brief LoadLabyrinth - loads labyrinth from file
 *
 * @param width - width of the window
 * @param height - height of the window
 *
 * @return enum Status - OK if everything went well, ERROR if there was an error
 * 						and FINISH if user pressed ESC
 */
enum Status LoadLabyrinth(int width, int height) {
  erase();
  struct Labyrinth labyrinth = {NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 1, 1};
  int current_state = (enum LoadLabyrinthEnum)INPUT_FILENAME;
  enum Status load_lab_status = OK;
  int size_load_labyrinth_options =
      sizeof(load_labyrinth_options) / sizeof(load_labyrinth_options[0]);
  int key = 0;
  char* filename = NULL;
  filename = malloc(1024 * sizeof(char));
  for (int i = 0; i < 1024; i++) {
    filename[i] = '\0';
  }
  int filename_len = 0;

  while (load_lab_status == OK) {
    DrawBox(width, height);
    DrawMenuOptions(load_labyrinth_options, size_load_labyrinth_options,
                    &current_state, 2, 2, 2);
    key = getch();
    // ClearLabFromWindow(width, height, MENU_WIDTH);
    switch (key) {
      case KEY_UP:
        (current_state > 0) ? current_state-- : 0;
        break;
      case KEY_DOWN:
        (current_state < size_load_labyrinth_options - 1) ? current_state++ : 0;
        break;
      case '\n':  // enter key
        CaseEnterAtLoadLabSubmenu(&labyrinth, current_state, &load_lab_status,
                                  width, height, &filename, &filename_len);
        if (load_lab_status == ERROR) {
          mvaddstr(height / 2, width / 2, "Wrong filename or terminal size");
          mvaddstr(height / 2 + 1, width / 2,
                   "Press any key if you wanna do it again");
          getch();
          ClearLabFromWindow(width, height, MENU_WIDTH);
          // napms(3000);
          load_lab_status = OK;
        }
        break;
      case 27:  // escape key
        load_lab_status = (enum Status)FINISH;
        break;
    }
    refresh();
  }
  if (filename != NULL) {
    free(filename);
  }
  ClearLabyrinth(&labyrinth);
  return load_lab_status;
}

/**
 * @brief CaseEnterAtLoadLabSubmenu - handles the events of the load labyrinth
 * submenu
 *
 * @param labyrinth - pointer to struct Labyrinth
 * @param current_state - current state of the submenu
 * @param load_lab_status - pointer to enum Status (load_lab_status is changed
 * inside the function)
 * @param width - width of the window
 * @param height - height of the window
 * @param filename - pointer to string of filename
 * @param filename_len - length of filename string
 *
 * @return void
 */
void CaseEnterAtLoadLabSubmenu(struct Labyrinth* labyrinth, int current_state,
                               enum Status* load_lab_status, int width,
                               int height, char** filename, int* filename_len) {
  switch (current_state) {
    case INPUT_FILENAME:
      EditLine(3, 2, *filename, filename_len, 0, 1);

      if (*filename_len != 0) {
        ClearLabyrinth(labyrinth);
        ClearLabFromWindow(width, height, MENU_WIDTH);
        *load_lab_status = LoadLabyrinthByFilename(
            labyrinth, width, height, filename, LAB_HEIGHT_POS, LAB_WIDTH_POS);
      }
      refresh();
      break;
    case RETURN:
      *load_lab_status = FINISH;
      break;
    case SOLVE_LABYRINTH:
      int menu_row = 8, menu_col = 4;  // задается вручную пока что
      SolveLabyrinthSubmenu(labyrinth, LAB_HEIGHT_POS, LAB_WIDTH_POS, menu_row,
                            menu_col);
      break;
  }
}

/**
 * @brief LoadLabyrinthByFilename - loads labyrinth from file and prints it on
 * window
 *
 * @param labyrinth - pointer to struct Labyrinth
 * @param width - width of the window
 * @param height - height of the window
 * @param filename - pointer to string of filename
 * @param filename_len - length of filename string
 * @param move_rows - number of rows to move from top of window
 * @param move_columns - number of columns to move from left of window
 *
 * @return enum Status - OK if all is good, ERROR if error, FINISH if wanna exit
 *
 * The function loads labyrinth from file and prints it on window,
 * scaling it if possible to maximum visible size. If file or scaling is
 * impossible, it returns ERROR, otherwise OK.
 */
enum Status LoadLabyrinthByFilename(struct Labyrinth* labyrinth, int width,
                                    int height, char** filename, int move_rows,
                                    int move_columns) {
  enum Status status = OK;
  FILE* file = NULL;
  status = WOpenFile(&file, filename);
  if (status == OK) {
    status = ReadFile(&file, &((*labyrinth).matrix_side_wall),
                      &((*labyrinth).matrix_bottom_wall), &((*labyrinth).rows),
                      &((*labyrinth).columns));
  }

  int scale_rows = 0, scale_columns = 0;
  if (status == OK) {
    status = CalculateScale(labyrinth, width, height, move_rows, move_columns,
                            &scale_rows, &scale_columns);
  }

  if (status == OK) {
    DrawEmptyLabyrinth(&(*labyrinth).labyrinth, (*labyrinth).rows,
                       (*labyrinth).columns);

    DrawElementsToLabyrinth(&(*labyrinth).labyrinth,
                            &(*labyrinth).matrix_side_wall,
                            &(*labyrinth).matrix_bottom_wall, (*labyrinth).rows,
                            (*labyrinth).columns);

    ImproveLabyrinthWalls(labyrinth);

    ScaleLabyrinth(labyrinth, scale_rows, scale_columns);
  }
  if (file != NULL) {
    fclose(file);
  }

  if (status == OK && width > (*labyrinth).current_columns + 30 &&
      height > (*labyrinth).current_rows + 2) {
    WPrintLabyrinth(&(*labyrinth).new_labyrinth, (*labyrinth).current_rows,
                    (*labyrinth).current_columns, move_rows, move_columns);
    refresh();
  } else {
    status = ERROR;
  }

  return status;
}

/**
 * @brief CalculateScale - calculates the scale of the labyrinth to maximum
 * visible size
 *
 * @param labyrinth - pointer to struct Labyrinth
 * @param width - width of the window
 * @param height - height of the window
 * @param move_rows - number of rows to move from top of window
 * @param move_columns - number of columns to move from left of window
 * @param scale_rows - pointer to int, where the scale of the rows is written
 * @param scale_columns - pointer to int, where the scale of the columns is
 * written
 *
 * @return enum Status - OK if all is good, ERROR if error, FINISH if wanna exit
 *
 * The function calculates the scale of the labyrinth to maximum visible size,
 * taking into account that the symbol in width is 3 times than in height.
 */

// -------  ЗДЕСЬ СООТНОШЕНИЕ СТОРОН НА МАКСИМУМ ----------
enum Status CalculateScale(struct Labyrinth* labyrinth, int width, int height,
                           int move_rows, int move_columns, int* scale_rows,
                           int* scale_columns) {
  enum Status status = OK;

  int height_avail = height - move_rows;
  int width_avail = width - move_columns;
  // найдем во сколько можно увеличить лабиринт чтобы
  // он максимально занимал доступное пространство
  height_avail -= (*labyrinth).rows * 2 + 1;  // first iteration
  if (height_avail) *scale_rows = 1;
  width_avail -= (*labyrinth).columns * 2 + 1;  // first iteration
  if (width_avail) *scale_columns = 1;

  while (height_avail > 0 || width_avail > 0) {
    height_avail -= (*labyrinth).rows;
    *scale_rows += (height_avail > 0) ? 1 : 0;
    width_avail -= (*labyrinth).columns;
    *scale_columns += (width_avail > 0) ? 1 : 0;
  }

  if (*scale_rows < 1 || *scale_columns < 1) {
    status = ERROR;
  }
  return status;
}

// --------- ЗДЕСЬ СООТНОШЕНИЕ СТОРОН 1 : 3 ----------
/*
enum Status CalculateScale(struct Labyrinth *labyrinth, int width, int
height, 					int move_rows, int move_columns,
int* scale_rows, int* scale_columns){ 	enum Status status = OK;

        int height_avail = height - move_rows;
        int width_avail = width - move_columns;
        // найдем во сколько можно увеличить лабиринт чтобы
        // он максимально занимал доступное пространство
        height_avail -= (*labyrinth).rows*2+1; //first iteration
        if(height_avail) *scale_rows = 1;
        width_avail -= (*labyrinth).columns*2+1; // first iteration
        if(width_avail) *scale_columns = 1;

        while(height_avail > 0 || width_avail > 0){
                height_avail -= (*labyrinth).rows;
                *scale_rows += (height_avail>0) ? 1 : 0;
                width_avail -= (*labyrinth).columns;
                *scale_columns += (width_avail>0) ? 1 : 0;
        }
        // соотношение между масштабами должно быть 1:3
        // так как символы в ширину уже в 3 раза чем в высоту
        if(*scale_rows > 1 && *scale_columns > 3) {
                int new_scale_column = 3;
                int new_scale_row = 1;
                while(new_scale_column < *scale_columns && new_scale_row <
*scale_rows){ 			if(new_scale_column+3 < *scale_columns &&
new_scale_row+1 <
*scale_rows){ 				new_scale_column += 3;
new_scale_row += 1; 			}else{ 				break;
                        }
                }
                *scale_rows = new_scale_row;
                *scale_columns = new_scale_column;
        }

        if(*scale_rows < 1 || *scale_columns < 3) {
                status = ERROR;
        }
        return status;
}

*/
