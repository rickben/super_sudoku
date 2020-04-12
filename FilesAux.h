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
 * trans_board_to_file                  - writes to specified file the curr_board's board's: values, n and m
 * create_board_from_file               - allocates memory for the new - board of curr_board
 * create_temporary_board_from_file     - allocates memory for the temporary_board - in case we need to go back to previous board
 * copy_from_temporary_to_curr_board    - copies temporary_board's information to curr_board - no need to go back to previous board
 * free_temporary_board                 - frees all memory allocated for the temporary_board
 * scan_size_from_file                  - scans m and n sizes from file and set to height and weight of board in the specified file
 * scan_rows_from_file                  - scans values of cells of the board in the specified file
 * in_row_fixed                         - check if there is another fixed cell with the same value - in the same row
 * in_col_fixed                         - check if there is another fixed cell with the same value - in the same col
 * in_block_fixed                       - check if there is another fixed cell with the same value - in the same block
 * is_valid_fixed_set                   - check if there is another fixed cell - in the same row, col or block
 * check_erroneous_fixed_cells_temp     - check if there is erroneous fixed cell in temporary_board
 * trans_file_to_board                  - reads from specified file and sets the values to curr_board's board with block size of n and m
 * ***/


void free_mem_board();
int solve_mode_to_file(char* file_name);
int edit_mode_to_file(char* file_name);
int trans_board_to_file(char* file_name);
void create_board_from_file(int len,int width, int height);
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
