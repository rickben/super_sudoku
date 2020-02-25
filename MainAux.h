#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
#include "Game.h"

void calc_block_size();
void separator_row();
void cell_row(int* arr, int num_row);
void board_print();
void set_values_board();
int is_fixed(int row, int col);
int is_erroneous();


#endif
