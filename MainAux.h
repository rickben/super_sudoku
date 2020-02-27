#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
#include "Game.h"

int check_if_number_float(int x);
int check_erroneous_board();
int check_correct_file_format();
void fill_board_random(int x);
void clear_cells_random(int y);
void print_start_program();
void calc_block_size();
void separator_row();
void cell_row(struct cell* arr, int num_row);
void board_print();
void set_values_board();



#endif
