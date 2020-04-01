#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
#include "Game.h"
#include <stdbool.h>

void update_list_pos_vals(int i, int j, int num);
void init_temp_board();
void free_temp_board();
void copy_curr_to_temp_board();
void restart_to_init();
int check_erroneous_board();
void print_start_program();
int check_num_of_empty_cells();
int set_random_val(int row, int col);
void find_random_empty_cell(int* row, int* col, int num_empty);
int fill_board_random(int x);
void clear_cells_random(int y);
int in_row(int row, int num, struct curr_board* curr_board);
int in_col(int col, int num, struct curr_board* curr_board);
int in_block(int block_x, int block_y , int num, struct curr_board* curr_board);
int is_valid_set(int x, int y, int num, struct curr_board* curr_board);
int check_board_solved();
void separator_row();
void update_erroneous_cells();
void cell_row(struct cell* arr);
void board_print();
bool find_empty_cell(int* row_pos, int* col_pos, cell** matrix );
bool is_valid_board();
void create_board_size_9();

#endif
