#include "ui.h"

// generate labyrinth options
const char* gen_labyrinth_options[] = {"rows", "columns",
                                       // "filename",
                                       "GENERATE", "Return", "Solve"};

/**
 * @brief GenerateLabyrinth - generates a labyrinth of given size,
 * 				prompts user for filename and then saves the
 * labyrinth to file.
 *
 * @param width - width of the window
 * @param height - height of the window
 *
 * @return OK if everything went well, ERROR if there was an error
 * 		   and FINISH if user pressed ESC
 */
enum Status GenerateLabyrinth(int width, int height) {
  erase();
  struct Labyrinth labyrinth = {NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 1, 1};
  struct Generator generator;
  InitiateGenerator(&generator);
  int status = OK;
  int state = 0;

  int key;
  while (status == OK) {
    DrawBox(width, height);
    DrawMenuOptions(gen_labyrinth_options, 6, &state, 1, 2, 2);
    refresh();
    key = getch();

    switch (key) {
      case KEY_UP:
        if (state > 0) {
          state--;
        }
        break;
      case KEY_DOWN:
        if (state < 5) {
          state++;
        }
        break;
      case '\n':
        status = CaseEnterAtGenLabSubmenu(&labyrinth, &generator, state, width,
                                          height);
        if (status == ERROR) {
          mvaddstr(height / 2, width / 2, "Wrong filename or terminal size");
          mvaddstr(height / 2 + 1, width / 2,
                   "Press any key if you wanna do it again");
          getch();
          ClearLabFromWindow(width, height, MENU_WIDTH);
          status = OK;
        }
        break;
      case 27:  // ESC
        status = FINISH;
        break;
        refresh();
    }
  }
  refresh();
  ClearLabyrinth(&labyrinth);
  return OK;
}

/**
 * @brief InitiateGenerator - initializes the struct Generator by setting all
 * 				fields to 0 and setting the first elements of
 * strings to
 * '\0'
 *
 * @param generator - pointer to struct Generator
 */
void InitiateGenerator(struct Generator* generator) {
  generator->row_len = 0;
  generator->column_len = 0;
  generator->filename_len = 0;

  generator->filename[0] = '\0';
  generator->row_str[0] = '\0';
  generator->column_str[0] = '\0';
}

/**
 * @brief CaseEnterAtGenLabSubmenu - handles the events of the generate
 * labyrinth submenu
 *
 * @param labyrinth - pointer to struct Labyrinth
 * @param generator - pointer to struct Generator
 * @param state - current state of the submenu
 * @param width - width of the terminal
 * @param height - height of the terminal
 *
 * @return enum Status - OK if all is good, ERROR if error, FINISH if wanna exit
 */
enum Status CaseEnterAtGenLabSubmenu(struct Labyrinth* labyrinth,
                                     struct Generator* generator, int state,
                                     int width, int height) {
  enum Status ret = OK;
  switch (state) {
    case 0:  // rows string modify
      EditLine(2, 2, generator->row_str, &generator->row_len, 1, 10);
      break;
    case 1:  // columns string modify
      EditLine(3, 2, generator->column_str, &generator->column_len, 1, 10);
      break;
    case 2:  // GENERATE
      ClearLabFromWindow(width, height, MENU_WIDTH);
      int rows = atoi(generator->row_str);
      int columns = atoi(generator->column_str);
      char* filename = malloc(12 * sizeof(char));
      strcpy(filename, "my_maze.txt");
      filename[11] = '\0';
      ret = GenerateLabyrinthFile(labyrinth, &filename, rows, columns, width,
                                  height);
      // add function to generate maze
      if (ret == ERROR) {
        ClearLabFromWindow(width, height, MENU_WIDTH);
        refresh();
        mvaddstr(height / 2, width / 2, "Wrong input data or terminal size");
        mvaddstr(height / 2 + 1, width / 2,
                 "Press any key if you wanna do it again");
        getch();
        ClearLabFromWindow(width, height, MENU_WIDTH);
        refresh();
        ret = OK;
      } else {
        WPrintLabyrinth(&(*labyrinth).new_labyrinth, (*labyrinth).current_rows,
                        (*labyrinth).current_columns, 2, 30);
      }
      free(filename);
      break;
    case 3:  // return
      ret = FINISH;
      break;
    case 4:                            // solve
      int menu_row = 8, menu_col = 4;  // задается вручную пока что
      SolveLabyrinthSubmenu(labyrinth, LAB_HEIGHT_POS, LAB_WIDTH_POS, menu_row,
                            menu_col);
      break;
  };
  return ret;
}

/**
 * @brief GenerateLabyrinthFile - generates a labyrinth and saves it to file
 *
 * @param labyrinth - pointer to struct Labyrinth
 * @param filename - pointer to string of filename
 * @param filename_len - length of filename string
 * @param rows - number of rows in labyrinth
 * @param columns - number of columns in labyrinth
 * @param width - width of the terminal
 * @param height - height of the terminal
 *
 * @return enum Status - OK if all is good, ERROR if error, FINISH if wanna exit
 */
enum Status GenerateLabyrinthFile(struct Labyrinth* labyrinth, char** filename,
                                  int rows, int columns, int width,
                                  int height) {
  maze_generation(*filename, rows, columns);

  return LoadLabyrinthByFilename(labyrinth, width, height, filename,
                                 LAB_HEIGHT_POS, LAB_WIDTH_POS);
}
