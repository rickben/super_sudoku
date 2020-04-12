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

int check_gurobi_board_full();
void copy_curr_to_board();
int in_row_gurobi(int row, int num);
int in_col_gurobi(int col, int num);
int in_block_gurobi(int x, int y, int num);
int is_valid_set_gurobi(int x, int y, int num);
int check_num_var();
void create_empty_model(int is_LP);
int remove_log_to_console();
int create_env();
int create_new_model();
int each_cell_value();
int each_row_value();
int each_col_value();
int each_sub_grid_value();
int optimum_state_ilp();
void check_board_unsolvable_for_guess_hint(int is_guess_hint);
void set_guess_board(double thresholdX);
int optimum_state_lp(int is_guess, double thresholdX, int is_guess_hint, int x, int y);
int optimization_complete(int is_LP, int is_guess, double thresholdX, int is_guess_hint, int x, int y);
void error_report();
int optimize_model();
int write_model();
int capture_sol_info();
void free_model();
void free_env();
int set_obj_max();
int solver(int is_LP, int is_guess, double thresholdX, int is_guess_hint, int x, int y);



#endif
