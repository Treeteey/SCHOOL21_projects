#include "wave_algorithm.h"

// реализация очереди
void initialization_queue(struct_queue* queue, int capacity) {
  queue->first = 0;
  queue->end = 0;
  queue->capacity = capacity;
  queue->arr_queue = calloc(capacity, sizeof(element_queue));
}

void free_queue(struct_queue* queue) { free(queue->arr_queue); }

void add_queue_element(struct_queue* queue, element_queue el) {
  queue->arr_queue[queue->end++] = el;
}

element_queue get_queue_element(struct_queue* queue) {
  return queue->arr_queue[queue->first++];
}

int empty_queue(struct_queue* queue) { return queue->first == queue->end; }

// реализация волнового поиска
int permission_to_move(element_queue new_element, element_queue current_element,
                       int x, int y, int** right_wall, int** down_wall,
                       int** visited_position, int ROWS, int COLS) {
  int flag = 0;
  if (new_element.x >= 0 && new_element.x < COLS && new_element.y >= 0 &&
      new_element.y < ROWS &&
      visited_position[new_element.y][new_element.x] != 1)
    flag = 1;
  if (right_wall[current_element.y][current_element.x] == 1 && x == 1) flag = 0;
  if (current_element.x > 0 &&
      right_wall[current_element.y][current_element.x - 1] == 1 && x == -1)
    flag = 0;
  if (down_wall[current_element.y][current_element.x] == 1 && y == 1) flag = 0;
  if (current_element.y > 0 &&
      down_wall[current_element.y - 1][current_element.x] == 1 && y == -1)
    flag = 0;
  return flag;
}

void pathfinding_algorithm(element_queue** path_saving,
                           element_queue* path_result2, int* len_path,
                           element_queue start_coordinates,
                           element_queue finish_coordinates) {
  element_queue current_element = finish_coordinates;
  while (current_element.x != start_coordinates.x ||
         current_element.y != start_coordinates.y) {
    path_result2[(*len_path)++] = current_element;
    current_element = path_saving[current_element.y][current_element.x];
  }
  path_result2[(*len_path)++] = current_element;
}

int wave_algorithm(int** right_wall, int** down_wall,
                   element_queue* path_result2, int* len_path,
                   element_queue start_coordinates,
                   element_queue finish_coordinates, int ROWS, int COLS) {
  struct_queue c_queue = {0};
  initialization_queue(&c_queue, ROWS * COLS);
  int** visited_position = calloc(ROWS, sizeof(int*));
  for (int i = 0; i < ROWS; i++) {
    visited_position[i] = calloc(COLS, sizeof(int));
  }
  element_queue** path_saving = calloc(ROWS, sizeof(element_queue*));
  for (int i = 0; i < ROWS; i++) {
    path_saving[i] = calloc(COLS, sizeof(element_queue));
  }

  visited_position[start_coordinates.y][start_coordinates.x] = 1;
  add_queue_element(&c_queue, start_coordinates);

  int flag = 0;
  while (!empty_queue(&c_queue) && !flag) {
    element_queue current_element = get_queue_element(&c_queue);

    if (current_element.x == finish_coordinates.x &&
        current_element.y == finish_coordinates.y) {
      pathfinding_algorithm(path_saving, path_result2, len_path,
                            start_coordinates, finish_coordinates);
      flag = 1;
    }

    int arr_x[4] = {1, -1, 0, 0};
    int arr_y[4] = {0, 0, 1, -1};
    for (int i = 0; i < 4; i++) {
      element_queue new_element = {0};
      new_element.x = current_element.x + arr_x[i];
      new_element.y = current_element.y + arr_y[i];
      if (permission_to_move(new_element, current_element, arr_x[i], arr_y[i],
                             right_wall, down_wall, visited_position, ROWS,
                             COLS)) {
        add_queue_element(&c_queue, new_element);
        visited_position[new_element.y][new_element.x] = 1;
        path_saving[new_element.y][new_element.x] = current_element;
      }
    }
  }

  for (int i = 0; i < ROWS; i++) {
    free(visited_position[i]);
    free(path_saving[i]);
  }

  free(visited_position);
  free(path_saving);
  free_queue(&c_queue);

  return flag;
}

int SolveMaze(int** side, int** bottom, element_queue** coords, int* steps,
              int maze_row, int maze_col, int b_row, int b_col, int e_row,
              int e_col) {
  int ret = 1;  // 1 - OK, 0 - ERROR
  *coords = calloc(maze_row * maze_col, sizeof(element_queue));
  int len_path = 0;

  element_queue start_coordinates = {b_col, b_row};
  element_queue finish_coordinates = {e_col, e_row};

  if (wave_algorithm(side, bottom, *coords, &len_path, start_coordinates,
                     finish_coordinates, maze_row, maze_col)) {
    ret = 1;
    *steps = len_path;
  } else {
    ret = 0;
  }
  return ret;
}