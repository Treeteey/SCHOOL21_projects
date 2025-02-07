#include "ui.h"

int terminal_width = 0;
int terminal_height = 0;

// Menu options
const char* main_menu_options[] = {"Load maze", "Generate maze",
                                   "Load Cave", "Exit"};

/**
 * @brief The main function
 *
 * This function initializes ncurses and locale, than call ProgramWork()
 * function and finally call endwin() to stop ncurses.
 *
 * @return 0 if everything is allright
 */
int main() {
  setlocale(LC_ALL, "");               // Set the locale to the user's default
  setlocale(LC_CTYPE, "en_US.UTF-8");  // Set the locale to UTF-8
  initscr();                           // инициализация ncurses
  cbreak();                            // посимвольный ввод
  noecho();  // отключить вывод на экран
  curs_set(0);  // курсор невидимы (один хрен не работает)
  keypad(stdscr, TRUE);

  ProgramWork();
  echo();
  endwin();
  return 0;
}

/**
 * @brief The main program loop
 *
 * This function does the main work of the program. It contains the main loop of
 * the program. The loop draws the menu on the screen and waits for the user to
 * press a key.
 *
 * This function does not return anything, it only stops when the user wants to
 * close the program.
 */
void ProgramWork() {
  getmaxyx(stdscr, terminal_height, terminal_width);  // Get terminal size
  if (terminal_width < 30 || terminal_height < 12) {
    mvaddstr(1, 1, "Terminal size is too small");
    refresh();
    getch();
    return;
  }
  DrawBox(terminal_width, terminal_height);
  // Set up menu state
  int main_menu_state = (enum MainMenuEnum)LOAD_LABYRINTH;

  enum Status status = OK;
  int size_main_menu_options =
      sizeof(main_menu_options) / sizeof(main_menu_options[0]);

  int key = 0;
  // Start the program loop
  while (status == (enum Status)OK) {
    erase();  // Clear the screen
    refresh();
    DrawBox();
    DrawMenuOptions(main_menu_options, size_main_menu_options, &main_menu_state,
                    2, 2, 2);

    key = getch();
    switch (key) {
      case KEY_UP:
        if (main_menu_state > 0) {
          main_menu_state--;
        }
        break;
      case KEY_DOWN:
        if (main_menu_state < size_main_menu_options - 1) {
          main_menu_state++;
        }
        break;
      case '\n': {  // Enter key
        switch (main_menu_state) {
          case (enum MainMenuEnum)LOAD_LABYRINTH:
            status = LoadLabyrinth(terminal_width, terminal_height);
            if (status == FINISH) status = OK;
            break;
          case (enum MainMenuEnum)GENERATE_LABYRINTH:
            status = GenerateLabyrinth(terminal_width, terminal_height);
            break;
          case (enum MainMenuEnum)EXIT:  // Exit
            status = (enum Status)FINISH;
            break;
        }
        break;  // Add break to prevent fallthrough after the Enter case
      }         // end case '\n'
      case 27:  // Escape key
        status = FINISH;
        break;
    }
    refresh();
  }
}

/**
 * Draws a box of given width and height.
 *
 * This function draws a box with border characters ('-' and '|') on the screen.
 * The box is drawn at the current position of the cursor.
 *
 * \param[in] width width of the box
 * \param[in] height height of the box
 */

void DrawBox() {
  getmaxyx(stdscr, terminal_height, terminal_width);
  for (int i = 0; i < terminal_width; ++i) {
    mvaddch(0, i, '-');
  }
  for (int i = 1; i < terminal_height - 1; ++i) {
    mvaddch(i, 0, '|');
    mvaddch(i, terminal_width - 1, '|');
  }
  for (int i = 0; i < terminal_width; ++i) {
    mvaddch(terminal_height - 1, i, '-');
  }
}

// void DrawBox(int width, int height) {

// 	for (int i = 0; i < width; ++i) {
// 			mvaddch(0, i, '-');
// 	}
// 	for(int i = 1; i < height - 1; ++i) {
// 			mvaddch(i, 0, '|');
// 			mvaddch(i, width - 1, '|');
// 	}
// 	for (int i = 0; i < width; ++i) {
// 			mvaddch(height-1, i, '-');
// 	}
// }

/**
 * Draws menu options at given position and highlights current state.
 *
 * \param[in] options array of menu options
 * \param[in] size size of the options array
 * \param[in,out] state pointer to the current state of menu
 * \param[in] gap gap between menu options
 * \param[in] menu_row row where the menu is drawn
 * \param[in] menu_col column where the menu is drawn
 */
void DrawMenuOptions(const char* options[], int size, int* state, int gap,
                     int menu_row, int menu_col) {
  int y = 0;
  for (int i = 0; i < size; ++i) {
    if (i == *state) {
      mvaddch(menu_row + y, menu_col, '*');
    } else {
      mvaddch(menu_row + y, menu_col, ' ');  // Clear previous selection symbol
    }
    mvaddstr(menu_row + y, menu_col + 2, options[i]);
    y += gap;
  }
}

/**
 * Clears menu options at given position.
 *
 * This function clears the current menu options from the screen.
 * It clears the selection symbol and the text of the menu options.
 *
 * \param[in] options array of menu options
 * \param[in] size size of the options array
 * \param[in] state pointer to the current state of menu
 * \param[in] gap gap between menu options
 * \param[in] menu_row row where the menu is drawn
 * \param[in] menu_col column where the menu is drawn
 */
void ClearMenuOptions(int size, int* state, int gap, int menu_row,
                      int menu_col) {
  int y = 0;
  for (int i = 0; i < size; ++i) {
    if (i == *state) {
      mvaddch(menu_row + y, menu_col, ' ');
    } else {
      mvaddch(menu_row + y, menu_col, ' ');  // Clear previous selection symbol
    }
    for (int j = 0; j < 20 - menu_col; j++) {
      mvaddch(menu_row + y, menu_col + 2 + j, ' ');
    }
    y += gap;
  }
}

/*
<---------------width--------------->
-------------------------------------	|
|              	|      				|	|
|<-menu_width-> | labyrint field	|	| height
|				|					|
| .	.	.	.	.	.	.	.	.	.
|

*/

/**
 * Clears the labyrinth field from the screen.
 *
 * This function clears the area of the screen where the labyrinth is drawn.
 * The area is defined by the given width and height and the position of the
 * menu (menu_width).
 *
 * The function simply prints spaces at the corresponding positions on the
 * screen.
 *
 * \param[in] width width of the screen
 * \param[in] height height of the screen
 * \param[in] menu_width width of the menu
 */
void ClearLabFromWindow(int width, int height, int menu_width) {
  for (int i = 2; i < height - 1; ++i) {
    for (int j = menu_width; j < width; ++j) {
      mvaddch(i, j, ' ');
    }
  }
}

/**
 * Opens a file in read mode.
 *
 * This function tries to open a file with the given name in read mode.
 * If the file cannot be opened, an error status is returned.
 *
 * \param[in,out] file pointer to the file that will be opened
 * \param[in] filename name of the file to be opened
 * \param[in] filename_len length of the filename
 *
 * \return OK if the file was successfully opened, ERROR otherwise
 */
enum Status WOpenFile(FILE** file, char** filename) {
  enum Status status = OK;
  *file = fopen(*filename, "r");

  if (*file == NULL) {
    status = ERROR;
  }

  return status;
};

void WPrintLabyrinth(wchar_t*** labyrinth, int rows, int columns, int move_rows,
                     int move_columns) {
  for (int i = 0; i < rows; i++) {
    // Convert the row of wide characters into a single wchar_t string
    wchar_t row_string[columns + 1];  // +1 for null terminator
    for (int j = 0; j < columns; j++) {
      row_string[j] = (*labyrinth)[i][j];
    }
    row_string[columns] = L'\0';  // Null terminate the string

    // Print the entire row using mvaddwstr
    mvaddwstr(move_rows + i, move_columns, row_string);
  }
}

/*

==18880== 198,352 bytes in 46 blocks are still reachable in loss record 78 of 78
==18880==    at 0x484DA83: calloc (in
/usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==18880==    by 0x4886828: newwin_sp (in
/usr/lib/x86_64-linux-gnu/libncursesw.so.6.3)
==18880==    by 0x488B7CC: newterm_sp (in
/usr/lib/x86_64-linux-gnu/libncursesw.so.6.3)
==18880==    by 0x488C5EC: newterm (in
/usr/lib/x86_64-linux-gnu/libncursesw.so.6.3)
==18880==    by 0x48843AF: initscr (in
/usr/lib/x86_64-linux-gnu/libncursesw.so.6.3)
==18880==    by 0x10BF61: main (in /home/ranil/school21/С/A1_Maze-2/src/ui.out)
==18880==
==18880== LEAK SUMMARY:
==18880==    definitely lost: 0 bytes in 0 blocks
==18880==    indirectly lost: 0 bytes in 0 blocks
==18880==      possibly lost: 201 bytes in 3 blocks
==18880==    still reachable: 636,021 bytes in 450 blocks
==18880==         suppressed: 0 bytes in 0 blocks

// load file exit by escape

==18953== 198,352 bytes in 46 blocks are still reachable in loss record 86 of 86
==18953==    at 0x484DA83: calloc (in
/usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==18953==    by 0x4886828: newwin_sp (in
/usr/lib/x86_64-linux-gnu/libncursesw.so.6.3)
==18953==    by 0x488B7CC: newterm_sp (in
/usr/lib/x86_64-linux-gnu/libncursesw.so.6.3)
==18953==    by 0x488C5EC: newterm (in
/usr/lib/x86_64-linux-gnu/libncursesw.so.6.3)
==18953==    by 0x48843AF: initscr (in
/usr/lib/x86_64-linux-gnu/libncursesw.so.6.3)
==18953==    by 0x10BF61: main (in /home/ranil/school21/С/A1_Maze-2/src/ui.out)
==18953==
==18953== LEAK SUMMARY:
==18953==    definitely lost: 464 bytes in 4 blocks
==18953==    indirectly lost: 20,296 bytes in 58 blocks
==18953==      possibly lost: 201 bytes in 3 blocks
==18953==    still reachable: 636,021 bytes in 450 blocks
==18953==         suppressed: 0 bytes in 0 blocks


*/