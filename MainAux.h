#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
#include "Game.h"
#include "Solver.h"
#include "Stack.h"
#include <stdbool.h>
#include "ListActions.h"

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
 * finds randomly an empty cell from all the empty cells
 * and sets the value of its row and column in the pointers (parameters)
 * @param row - the row of the cell
 * @param col - the column of the cell
 * @param num_empty - number of current empty cells in curr_board's board
 */
void find_random_empty_cell(int* row, int* col, int num_empty);
/**
 * checks which parameter is the first to meet the first condition
 * @param x - the first parameter
 * @param y - the second parameter
 */
void first_set_cond_check_param(int x, int y);
/**
 * checks which parameter is the first to meet the second condition
 * @param x - the first parameter
 * @param y - the second parameter
 */
void second_set_cond_check_param(int x, int y);
/**
 * fill x empty cells randomly chosen in the board with a randomly
 * chosen valid value
 * @param x - number of empty cells
 * @return 1 if the set of those x cells was successful, 0 otherwise
 */
int fill_board_random(int x);

/**
 * choose  NxN-y cells to make empty, so that the board will have only
 * y non-empty cells
 * @param y - the number of non-empty cells to be
 */
void clear_cells_random(int y);

/**
 * check if in curr_board's board in row - there is a cell
 * with the value of num
 * @param row - the row to check
 * @param num - the value of cell to check
 * @param curr_board - the struct curr_board to check on
 * @return 1 if exists a cell with value num in row, 0 otherwise
 */
int in_row(int row, int num, struct curr_board* curr_board);

/**
 * check if in curr_board's board in column - there is a cell
 * with the value of num
 * @param col - the column to check
 * @param num - the value of cell to check
 * @param curr_board - the struct curr_board to check on
 * @return 1 if exists a cell with value num in column, 0 otherwise
 */
int in_col(int col, int num, struct curr_board* curr_board);

/**
 * check if in curr_board's board in block - there is a cell
 * with the value of num
 * @param block_x - the first row in block
 * @param block_y - the first column in block
 * @param num - the value of cell to check
 * @param curr_board - the struct curr_board to check on
 * @return 1 if exists a cell with value num in block, 0 otherwise
 */
int in_block(int block_x, int block_y , int num, struct curr_board* curr_board);

/**
 * check if it is valid to set the value of num to the cell <y,x> (<col,row>)
 * @param x - the row of the cell
 * @param y - the column of the cell
 * @param num - the value to set to the cell
 * @param curr_board - the struct curr_board to check on
 * @return 1 if it is valid to set num to cell <y,x>, 0 otherwise
 */
int is_valid_set(int x, int y, int num, struct curr_board* curr_board);

/**
 * checking if the board is solved successfully
 * by checking if it's full and all cells valid
 * @return 1 if it is solved, 0 otherwise
 */
int check_board_solved();

/**
 * prints separator row line for the board
 */
void separator_row();

/**
 * updates erroneous cells fields
 * .is_erroneous to be 1, and the rest to 0
 */
void update_erroneous_cells();

/**
 * prints a row of cells of the curr_board's board
 * @param arr - array that contains the row's cells
 */
void cell_row(struct cell* arr);

/**
 * prints the curr_board's board in the specified format
 * by calling separator_row() and cell_row();
 */
void board_print();

/**
 * finds the first empty cell (top-down, left-right)
 * in the given matrix, and sets to pointers (parameters)
 * @param row_pos - pointer to row number
 * @param col_pos - pointer to column number
 * @param matrix - two dimensional array of cells
 * @return True if found an empty cell, False otherwise
 */
bool find_empty_cell(int* row_pos, int* col_pos, cell** matrix );

/**
 * checks if the curr_board's board is valid
 * @return True if it is valid, 0 otherwise
 */
bool is_valid_board();
/**
 * copies gurobi's board values (after calling solver())
 * to curr_board's board
 */
void copy_board_to_cur();

/**
 * creates an empty board of size 9x9 (for empty edit command)
 */
void create_board_size_9();


/**
 * checks if the new_board's board is valid (for num_solutions)
 * @return True if it is valid, 0 otherwise
 */
bool is_valid_board_new_board();

/**
 * makes all the non-empty cells in the board to be fixed
 * @param my_board - the board given
 */
void save_all_curr_cells_fixed(cell** my_board);

/**
 * checks whether the board is full - means there are no empty cells
 * @param my_board - the board given
 * @return 1 if the board is full, 0 otherwise
 */
int check_board_full(cell** my_board);

/**
 * this function copies into new_board all of curr_board data
 */
void update_new_board_by_curr();

/**
 * frees all memory allocated for new_board
 */
void free_new_board();

/**
 * this function pops a new_board from the stack
 * pushes into the stack al the valid boards the can be created out of it
 * @return number of solved new_boards that were popped in the current call of the function
 */
int update_stack(int count);

/**
 * for every cell in curr_board, calculates all the legal values the can be set in it,
 * and assigns it in list_possible_values
 * @return 1 iff exists a cell with 1 legal value
 */
int calculate_list_possible_values();
/**
 * for every cell in curr_board, frees list_possible_values
 */
void free_list_possible_values();
#endif
