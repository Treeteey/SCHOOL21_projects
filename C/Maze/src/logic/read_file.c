#include "maze.h"

enum Status OpenFile(FILE** file) {
  enum Status status = OK;
  char* filename = NULL;
  filename = malloc(1024 * sizeof(char));
  status = (filename == NULL) ? ERROR : OK;  // check if memory was allocated

  if (status == OK) {
    printf("Enter filename: ");

    // filename = "lab1.txt"; // DELETE !
    // printf("\nFile: %s\n", filename); // DELETE !
    scanf("%s", filename);  // UNCOMMENT!

    *file = fopen(filename, "r");

    if (*file == NULL) {
      // printf("Error opening file\n");
      status = ERROR;
    }
  }
  if (filename != NULL) {
    free(filename);
  }

  return status;
};

enum Status ReadFile(FILE** file, int*** matrix_side_wall,
                     int*** matrix_bottom_wall, int* rows, int* columns) {
  enum Status status = OK;
  char line[1024];

  // check if there is a first line with rows and columns info
  if (fgets(line, sizeof(line), *file) == NULL) {
    // fprintf(stderr, "Error reading file\n");
    status = ERROR;
  }

  // read rows and columns
  int count = sscanf(line, "%d %d", rows, columns);
  if (status == OK && count == 2 && *rows > 0 && *columns > 0 && *rows <= 50 &&
      *columns <= 50) {
  } else {
    // mvaddstr(0, 0,
    //          "Error: first line with rows and columns contain invalid
    //          data\n");
    status = ERROR;
  }

  // allocate memory for matrix
  if (status == OK) {
    status = AllocateMatrixMemory(matrix_side_wall, matrix_bottom_wall, *rows,
                                  *columns);
  }

  // read file and write data to matrices
  if (status == OK) {
    // read data for matrix_side_wall
    status = WriteDataInMatrix(file, matrix_side_wall, *rows, *columns);
    // skip empty line between matrices
    if (status == OK && fgets(line, sizeof(line), *file) == NULL) {
      // fprintf(stderr, "Error reading line between matrices\n");
      status = ERROR;
    }
    // read data for matrix_bottom_wall
    status = WriteDataInMatrix(file, matrix_bottom_wall, *rows, *columns);
  }  // finished wrtinig to matrices

  return status;
}

enum Status AllocateMatrixMemory(int*** matrix_side_wall,
                                 int*** matrix_bottom_wall, int rows,
                                 int columns) {
  enum Status status = OK;
  // выделяем память для строк матриц
  // Allocate memory for matrix
  *matrix_side_wall = (int**)malloc(rows * sizeof(int*));
  *matrix_bottom_wall = (int**)malloc(rows * sizeof(int*));
  if (*matrix_side_wall == NULL || *matrix_bottom_wall == NULL) {
    // обработка ошибки: не удалось выделить память
    // printf("Error: unable to allocate memory for matrix_side_wall\n");
    if (*matrix_side_wall != NULL) {
      free(matrix_side_wall);
    }
    if (*matrix_bottom_wall != NULL) {
      free(matrix_bottom_wall);
    }
    status = ERROR;
  }
  // Allocate memory for each row
  if (status == OK) {
    for (int i = 0; status == OK && i < rows; i++) {
      (*matrix_side_wall)[i] = (int*)malloc(columns * sizeof(int));
      if ((*matrix_side_wall)[i] == NULL) {
        // обработка ошибки: не удалось выделить память
        // rows-1 потому что еще не успели выделить память для строки rows
        // но выделили для предыдущих rows-1 строк
        // printf("Error: unable to allocate memory for matrix_side_wall[%d]\n",
        //        i);
        FreeMemory(matrix_side_wall, rows - 1);
        FreeMemory(matrix_bottom_wall, rows - 1);
        status = ERROR;
        break;
      }

      (*matrix_bottom_wall)[i] = (int*)malloc(columns * sizeof(int));
      if ((*matrix_bottom_wall)[i] == NULL) {
        // обработка ошибки: не удалось выделить память
        // printf("Error: unable to allocate memory for
        // matrix_bottom_wall[%d]\n",
        //        i);
        FreeMemory(matrix_side_wall,
                   rows);  //тут успели выделить для rows строки
        FreeMemory(matrix_bottom_wall, rows - 1);
        status = ERROR;
        break;
      }
    }
  }
  return status;
};

void FreeMemory(int*** matrix, int rows) {
  if (*matrix != NULL) {
    for (int j = 0; j < rows; j++) {
      free(*matrix[j]);
    }
    free(*matrix);
    *matrix = NULL;
  }
}

enum Status WriteDataInMatrix(FILE** file, int*** matrix, int rows,
                              int columns) {
  enum Status status = OK;
  char line[1024];
  int cur_row = 0;
  for (; status == OK && cur_row < rows; cur_row++) {
    if (fgets(line, sizeof(line), *file) == NULL) {
      // fprintf(stderr, "Error reading first matrix at row %d\n", cur_row);
      status = ERROR;
    } else {
      int cur_col = 0;
      char* token = strtok(line, " ");
      for (; cur_col < columns && token != NULL; cur_col++) {
        int value = atoi(token);
        if (value != 0 && value != 1) {
          // fprintf(stderr,
          //         "Error: first matrix contains invalid data at row %d\n",
          //         cur_row);
          status = ERROR;
          break;
        }
        (*matrix)[cur_row][cur_col] = value;
        token = strtok(NULL, " ");
      }
      if (cur_col != columns) {
        // fprintf(stderr,
        //         "Error: first matrix contains insufficient data at row %d\n",
        //         cur_row);
        status = ERROR;
      }
    }
  }
  if (cur_row != rows) {
    // fprintf(stderr,
    //         "Error: first matrix contains insufficient number of rows\n");
    status = ERROR;
  }
  return status;
}

void PrintMatrix(int*** matrix_side_wall, int*** matrix_bottom_wall, int rows,
                 int columns) {
  printf("rows: %d, columns: %d\n", rows, columns);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%d ", (*matrix_side_wall)[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%d ", (*matrix_bottom_wall)[i][j]);
    }
    printf("\n");
  }
}