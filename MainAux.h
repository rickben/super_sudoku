#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
#include "Game.h"
#include <stdbool.h>

/**
 *MainAux Summary:
 *
 *This module supports all auxiliary functions of the game.
 *
 *It supports the following functions:
 *
 * functions that mange the allocation of memory, functions that check
 * the state of the board and its cells, and functions that update the board
 * ***/

/**
 * prints error message
 * @param func string - the function that created the error
 */
void memory_error(char* func);

/**
 * initializes temp_board for generate command
 */
void init_temp_board();

/**
 * frees all memories allocated for temp_board
 */
void free_temp_board();

/**
 * copies curr_board's cells values into temp_board's cells
 */
void copy_curr_to_temp_board();
/**
 * copies temp_board's cells values into curr_board's cells
 */
void copy_temp_board_to_curr();

/**
 * restart the game to state Init by freeing all memories allocated,
 * and changing the state
 */
void restart_to_init();

/**
 * checks whether the board is erroneous
 * @return 1 if the board is erroneous, 0 otherwise
 */
int check_erroneous_board();

/**
 * prints message for the start of the game
 */
void print_start_program();

/**
 * counts the number of empty cells
 * @return number of empty cells
 */
int check_num_of_empty_cells();

/**
 * randomly chooses a value for the cell <col,row> from
 * a list of valid values
 * @param row - row of cell
 * @param col - column of cell
 * @return 1 if the set was successful, 0 otherwise
 */
int set_random_val(int row, int col);

/**
 *
 * @param row
 * @param col
 * @param num_empty
 */
void find_random_empty_cell(int* row, int* col, int num_empty);

void first_set_cond_check_param(int x, int y);
void second_set_cond_check_param(int x, int y);

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
bool is_valid_board_new_board();
void create_board_size_9();
void fill_undo_board();
void free_undo_board();
void fill_undo_lst_by_cmp_board(int command_code);
#endif
