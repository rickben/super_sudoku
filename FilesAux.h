#ifndef HW3_FILESAUX_H
#define HW3_FILESAUX_H
#include "Game.h"


/**
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

/**
 * frees all memories allocated to the curr_board
 */
void free_mem_board();

/**
 * saves the curr_board's board to a specified file in Solve format
 * @param file_name string - the specified file path
 * @return 0 if errors occurred during the save, 1 otherwise
 */
int solve_mode_to_file(char* file_name);

/**
 * saves the curr_board's board to a specified file in Edit format
 * @param file_name string - the specified file path
 * @return 0 if errors occurred during the save, 1 otherwise
 */
int edit_mode_to_file(char* file_name);

/**
 * saves the curr_board's board to a specified file
 * @param file_name string - the specified file path
 * @return 0 if errors occurred during the save, 1 otherwise
 */
int trans_board_to_file(char* file_name);

/**
 * allocates memory for curr_board (after scan of sizes)
 * @param len (N) - the length of the curr_board's board
 * @param width - the width of the curr_board's board's block
 * @param height - the height of the curr_board's board's block
 */
void create_board_from_file(int len,int width, int height);

/**
 * allocates memory for temporary_board (after scan of sizes)
 * @param len (N) - the length of the temporary_board's board
 * @param width - the width of the temporary_board's board's block
 * @param height - the height of the temporary_board's board's block
 */
void create_temporary_board_from_file(int len, int width, int height);

/**
 * copies values of cells from temporary board to curr_board
 */
void copy_from_temporary_to_curr_board();

/**
 * frees all memories allocated to the temporary_board
 */
void free_temporary_board();

/**
 * scans board's sizes from file (m n)
 * @param in_file string - path of the specified file
 * @return 0 if errors occurred while scanning, 1 otherwise
 */
int scan_size_from_file(FILE* in_file);

/**
 * scans board's values of cells in each row
 * @param in_file - path of the specified file
 * @param State - the state of the program to be (either Solve or Edit)
 * @return 0 if errors occurred while scanning, 1 otherwise
 */
int scan_rows_from_file(FILE *in_file, enum state State);

/**
 * checks if there is a fixed cell with a value of num in the row
 * @param row - the number of row to check
 * @param num - the value of fixed cell to check
 * @return 1 if there is a fixed cell with the value of num in row, 0 otherwise
 */
int in_row_fixed(int row, int num);

/**
 * checks if there is a fixed cell with a value of num in the column
 * @param col - the number of column to check
 * @param num - the value of fixed cell to check
 * @return 1 if there is a fixed cell with the value of num in column, 0 otherwise
 */
int in_col_fixed(int col, int num);

/**
 * checks if there is a fixed cell with a value of num in the block
 * @param x - the first row in block to check
 * @param y - the first column in block to check
 * @param num - the value of fixed cell to check
 * @return 1 if there is a fixed cell with the value of num in block, 0 otherwise
 */
int in_block_fixed(int x, int y, int num);

/**
 * checks if it is valid to set the cell <j,i> with the value of num
 * @param i - number of row
 * @param j - number of column
 * @param num - the value of fixed cell to check
 * @return 1 if it is valid, 0 otherwise
 */
int is_valid_fixed_set(int i, int j, int num);

/**
 * check if there are erroneous fixed cell in temporary_board
 * @return 0 if there are (it's an error), 1 otherwise
 */
int check_erroneous_fixed_cells_temp();

/**
 * loads the board from the specified file to curr_board's board
 * @param file_name string - the specified file path
 * @param State - the state of the program to be (either Edit or Solve)
 * @return
 */
int trans_file_to_board(char* file_name, enum state State);

#endif
