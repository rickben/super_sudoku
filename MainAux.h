#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
#include "Game.h"

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
