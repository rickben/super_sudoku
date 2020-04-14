#ifndef HW3_SOLVER_H
#define HW3_SOLVER_H
#include "MainAux.h"
#include "Game.h"

/**
 *Solver Summary:
 *
 * This module manges the gurobi solver part of the program - translates the board to
 * variables and constraints suitable for gurobi and then uses its ILP/LP solver to compute
 * an optimum solution, assign values to the program variables to optimize the objective
 * function while satisfying all the constraints - which will give a solution for the board -
 * in ILP it will give an exact solution (if the board is solvable)
 * in LP it will give probabilities for a value to be in a certain cell (if the board is solvable)
 * ***/

/** board is a two dimensional array of cells, its size is the same as curr_board's board
 * and it's being initialized in the same values as curr_board's board.
 * In order to avoid changing the curr_board's board it is defined
 * */
cell      **board;


/**
 * checks if board (of gurobi) has no empty cells
 * @return 1 - if it doesn't have empty cells, 0 otherwise
 */
int check_gurobi_board_full();

/**
 * copies curr_board's board to gurobi's board
 */
void copy_curr_to_board();

/**
 * sets the objective function to be maximum
 * @return 1 if an error occurred, 0 otherwise
 */
int set_obj_max();

/**
 * checks if there is a cell with the value of num in this row
 * @param row - the number of row to check
 * @param num - the value of cell to check
 * @return 1 if there is a cell with the value of num in this row, 0 otherwise
 */
int in_row_gurobi(int row, int num);

/**
 * checks if there is a cell with the value of num in this column
 * @param col - the number of column to check
 * @param num - the value of cell to check
 * @return 1 if there is a cell with the value of num in this column, 0 otherwise
 */
int in_col_gurobi(int col, int num);

/**
 * checks if there is a cell with the value of num in this block
 * @param x - the first row int the block to check
 * @param y - the first column int the block to check
 * @param num - the value of cell to check
 * @return 1 if there is a cell with the value of num in this block, 0 otherwise
 */
int in_block_gurobi(int x, int y, int num);

/**
 * checks if it is valid to set the value of num to the cell <y,x>
 * @param x - the row of the cell
 * @param y - the column of the cell
 * @param num - the value of cell to check
 * @return 1 if it is valid to set value of num to cell <y,x>, 0 otherwise
 */
int is_valid_set_gurobi(int x, int y, int num);

/**
 * counts the number of variables for the optimizer - only empty cells with valid value
 * @return the number of variables
 */
int check_num_var();

/**
 * creates an empty model for the optimizer
 * @param is_LP parameter - 1 if we solve by LP, 0 if we solve by ILP
 */
void create_empty_model(int is_LP);

/**
 * removes the printed messages of gurobi to the console
 * @return 1 if an error occurred, 0 otherwise
 */
int remove_log_to_console();

/**
 * creates an environment for the optimizer
 * @return 1 if an error occurred, 0 otherwise
 */
int create_env();

/**
 * creates a new model for the optimizer
 * @return 1 if an error occurred, 0 otherwise
 */
int create_new_model();

/**
 * sets constraints: for each cell there is only one possible value to set
 * @return 1 if an error occurred, 0 otherwise
 */
int each_cell_value();

/**
 * sets constraints: for each row every value can be set exactly once
 * @return 1 if an error occurred, 0 otherwise
 */
int each_row_value();

/**
 * sets constraints: for each column every value can be set exactly once
 * @return 1 if an error occurred, 0 otherwise
 */
int each_col_value();

/**
 * sets constraints: for each block every value can be set exactly once
 * @return 1 if an error occurred, 0 otherwise
 */
int each_sub_grid_value();

/**
 * if the optimization completed successfully: extracts the solution
 * and sets them to board (gurobi's)
 * @return 1 if an error occurred, 0 otherwise
 */
int optimum_state_ilp();

/**
 * checks and prints message if the board (gurobi's) is unsolvable for guess_hint command
 * @param is_guess_hint - 1 if the command is guess_hint, 0 otherwise
 */
void check_board_unsolvable_for_guess_hint(int is_guess_hint);

/**
 * sets the values with probabilities greater than the threshold to the cells of board
 * @param thresholdX - the threshold to the probabilities
 */
void set_guess_board(double thresholdX);

/**
 * in LP optimizer: if it is guess command - updates the board with values with probabilities
 * greater than the threshold, if it is guess_hint - prints the probabilities of values for the
 * specified cell <y,x>
 * @param is_guess - 1 if it's guess command, 0 otherwise
 * @param thresholdX - the threshold for the probabilities for guess command
 * @param is_guess_hint - 1 if it's guess_hint command, 0 otherwise
 * @param x - the row of the cell for guess_hint command
 * @param y - the column of the cell for guess_hint command
 * @return 1 if an error occurred, 0 otherwise
 */
int optimum_state_lp(int is_guess, double thresholdX, int is_guess_hint, int x, int y);

/**
 * if the optimizer succeeded in reaching optimum - calls for optimum_state_lp or optimum_state_ilp
 * @param is_LP parameter - 1 if we solve by LP, 0 if we solve by ILP
 * @param is_guess - 1 if it's guess command, 0 otherwise
 * @param thresholdX - the threshold for the probabilities for guess command
 * @param is_guess_hint - 1 if it's guess_hint command, 0 otherwise
 * @param x - the row of the cell for guess_hint command
 * @param y - the column of the cell for guess_hint command
 * @return 0 if an error occurred, 1 otherwise
 */
int optimization_complete(int is_LP, int is_guess, double thresholdX, int is_guess_hint, int x, int y);

/**
 * prints error message to the console
 */
void error_report();

/**
 * optimizes the model with the gurobi optimizer
 * @return 1 if an error occurred, 0 otherwise
 */
int optimize_model();

/**
 * writes the model to .lp file
 * @return 1 if an error occurred, 0 otherwise
 */
int write_model();

/**
 * captures the solution information by the gurobi optimizer
 * @return 1 if an error occurred, 0 otherwise
 */
int capture_sol_info();

/**
 * frees the model
 */
void free_model();

/**
 * frees the environment
 */
void free_env();

/**
 * solves the board using gurobi optimizer either via ILP or via LP (for guess of
 * guess_hint commands only)
 * @param is_LP parameter - 1 if we solve by LP, 0 if we solve by ILP
 * @param is_guess - 1 if it's guess command, 0 otherwise
 * @param thresholdX - the threshold for the probabilities for guess command
 * @param is_guess_hint - 1 if it's guess_hint command, 0 otherwise
 * @param x - the row of the cell for guess_hint command
 * @param y - the column of the cell for guess_hint command
 * @return 0 if an error occurred or if the board is unsolvable, otherwise 1
 */
int solver(int is_LP, int is_guess, double thresholdX, int is_guess_hint, int x, int y);


#endif
