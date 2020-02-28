#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
#include "Game.h"

int check_if_number_float(int x);
int check_board_solved();
void restart_to_init();
void update_erroneous_cells();
int check_erroneous_board();
int in_row(int row, int num);
int in_col(int col, int num);
int in_block(int block_x, int block_y , int num);
int is_valid_set(int x, int y, int num);
int check_correct_file_format();
void fill_board_random(int x);
void clear_cells_random(int y);
void print_start_program();
void calc_block_size();
void separator_row();
void cell_row(struct cell* arr, int num_row);
void board_print();
void set_values_board();
int is_fixed(int row, int col);
int is_erroneous();
bool find_empty_cell(int* row_pos, int* col_pos, cell** matrix );
bool in_row(int row, int num, cell** matrix);
bool in_col(int col, int num, cell** matrix);
bool in_block(int x, int y, int num, cell** matrix);
bool is_valid_set(int x, int y, int num, cell** matrix);
bool is_valid_board(cell** matrix);

#endif
