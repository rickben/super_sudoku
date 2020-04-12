#ifndef HW3_FILESAUX_H
#define HW3_FILESAUX_H
#include "Game.h"


/*
 *FilesAux Summary:
 *
 *This module supports saving and loading puzzles from files.
 *Files can be loaded in either the Edit mode ("edit" command) for updates, or the Solve mode ("solve" command) for solving them
 *
 *It supports the following functions:
 *
 * free_mem_board                       - frees all memory allocated for the curr_board
 * solve_mode_to_file                   - in Solve state, save the curr_board's board to the specified file
 * edit_mode_to_file                    - in Edit state, save the curr_board's board to the specified file
 * trans_board_to_file                  - sets a move on game board
 * create_board_from_file               - checks if a move is valid
 * copy_from_temporary_to_curr_board    - uses ILP to print hint for the value in the specified position
 * free_temporary_board                 - randomly sets values for X empty cells, solves by ILP, and randomly leaves Y cells
 * scan_size_from_file                  - uses LP to set legal values to board cells with probabilities higher than X
 * scan_rows_from_file                  - uses LP to print probabilities for the values in the specified position
 * in_row_fixed                         - uses exhaustive backtracking to print the number of solutions for the board
 * in_col_fixed                         - fills all empty cells with only one legal value
 * in_block_fixed                       - prints the current board
 * is_valid_fixed_set                   - undo the last successful move on the board
 * check_erroneous_fixed_cells_temp     - redo the last successful move on the board
 * trans_file_to_board                  - resets the board to its first situation
 * ***/


void free_mem_board();
int solve_mode_to_file(char* file_name);
int edit_mode_to_file(char* file_name);
int trans_board_to_file(char* file_name);
/*
 * Returns 1 if manged to save the board in a file,
 * Otherwise, returns 0.
 * */
int create_board_from_file(int len,int width, int height);
void create_temporary_board_from_file(int len, int width, int height);
void copy_from_temporary_to_curr_board();
void free_temporary_board();
int scan_size_from_file(FILE* in_file);
int scan_rows_from_file(FILE *in_file, enum state State);
int in_row_fixed(int row, int num);
int in_col_fixed(int col, int num);
int in_block_fixed(int x, int y, int num);
int is_valid_fixed_set(int i, int j, int num);
int check_erroneous_fixed_cells_temp();
int trans_file_to_board(char* file_name, enum state State);

#endif
