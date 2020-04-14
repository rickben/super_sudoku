#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
#include "Game.h"
#include "Solver.h"
#include "Stack.h"
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


void find_random_empty_cell(int* row, int* col, int num_empty);

void first_set_cond_check_param(int x, int y);
void second_set_cond_check_param(int x, int y);

int fill_board_random(int x);
void clear_cells_random(int y);
/**
 * given a board the function in_row() checks if num exists in the given row (a row in board)
 * @return 1 if True
 * @param row
 * @param num
 * @param curr_board
 */
int in_row(int row, int num, struct curr_board* curr_board);
/**
 * given a board the function in_col() checks if num exists in the given col (a column in board)
 * @return 1 if True
 * @param col
 * @param num
 * @param curr_board
 */
int in_col(int col, int num, struct curr_board* curr_board);
/**
 * given a board and a set of coordinates the function in_block() checks if num exists
 * in the block the coordinates belong to
 * @return 1 if True
 * @param block_x
 * @param block_y
 * @param num
 * @param curr_board
 */
int in_block(int block_x, int block_y , int num, struct curr_board* curr_board);
/**
 * given a board and a set of coordinates the function is_valid_set() checks if num exists
 * in the block the coordinates belong to or in the column, or in the row
 * @return 1 if True
 * @param x
 * @param y
 * @param num
 * @param curr_board
 */
int is_valid_set(int x, int y, int num, struct curr_board* curr_board);
/**
 * the function check_board_solved() scans the curr_board to check if it is solved
 */
int check_board_solved();
/**
 * the function separator_row() prints a separator row by the known size of curr_board
 */
void separator_row();
void update_erroneous_cells();
void cell_row(struct cell* arr);
/**
 * the function board_print() prints curr_board according to the given format
 */
void board_print();
/**
 * given a matrix the function fill row_pos, col_pos with the first coordinates (scanning from top left to bottom right)
 * that the matrix contains the cell value of 0
 * @return true iff a zero value cell was found
 * @param row_pos
 * @param col_pos
 * @param matrix
 */
bool find_empty_cell(int* row_pos, int* col_pos, cell** matrix );
/**
 * the function checks if curr_board is valid (not erroneous)
 * @return true iff curr_board is valid
 */
bool is_valid_board();
/**
 * the function checks if new_board is valid (not erroneous)
 * @return true iff new_board is valid
 */
bool is_valid_board_new_board();
/**
 * this function assigns into curr_board an empty board in size 9X9
 */
void create_board_size_9();
/**
 * this function assigns undo_board temporally the values of curr_board
 */
void fill_undo_board();
/**
 * this function frees undo_board
 */
void free_undo_board();
/**
 * this function fills the user linked list moves by comparing the differences between
 * undo_board and the updated curr_board
 * @param command_code
 */
void fill_undo_lst_by_cmp_board(int command_code);
/**
 * inserts new node with the command's number and its data (only successful commands)
 * @param command_code - the number of the command
 * @param command_data - its data - the cell information
 * @param cell_data - the value the cell is changed to
 */
void insert_into_undo_lst(int command_code, int* command_data, cell cell_data);

/**
 * clears from memory all the nodes between end_list (pointer to the end of the linked list)
 * and curr_move (pointer to the last move executed)
 * that way we can add to the end of the list move moves
 */
void clear_redo_gap();
/**
 * copies gurobi's board values (after calling solver())
 * to curr_board's board
 */
void copy_board_to_cur();

/**
 * this function copies into new_board all of curr_board data
 */
void update_new_board_by_curr();
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
