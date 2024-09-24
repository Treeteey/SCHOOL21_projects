#ifndef WAVE_ALGORITHM_H
#define WAVE_ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
} element_queue;

typedef struct {
  int first;
  int end;
  int capacity;
  element_queue* arr_queue;
} struct_queue;

// реализация очереди
void initialization_queue(struct_queue* queue, int capacity);
void free_queue(struct_queue* queue);
void add_queue_element(struct_queue* queue, element_queue el);
element_queue get_queue_element(struct_queue* queue);
int empty_queue(struct_queue* queue);

// реализация волнового поиска
int permission_to_move(element_queue new_element, element_queue current_element,
                       int x, int y, int** right_wall, int** down_wall,
                       int** visited_position, int ROWS, int COLS);
void pathfinding_algorithm(element_queue** path_saving,
                           element_queue* path_result2, int* len_path,
                           element_queue start_coordinates,
                           element_queue finish_coordinates);
int wave_algorithm(int** right_wall, int** down_wall,
                   element_queue* path_result2, int* len_path,
                   element_queue start_coordinates,
                   element_queue finish_coordinates, int ROWS, int COLS);
// void SolveMaze(int** side, int** bottom, int** hor_values, int** vert_values,
// int maze_row, int maze_col, int b_row, int b_col, int e_row, int e_col);

int SolveMaze(int** side, int** bottom, element_queue** coords, int* steps,
              int maze_row, int maze_col, int b_row, int b_col, int e_row,
              int e_col);

#endif  // WAVE_ALGORITHM_H
