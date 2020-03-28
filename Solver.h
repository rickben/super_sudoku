#ifndef HW3_SOLVER_H
#define HW3_SOLVER_H
#include "MainAux.h"
#include "Game.h"
cell      **board;

int check_gurobi_board_full();
void copy_curr_board_to_board();
int in_row_gurobi(int row, int num);
int in_col_gurobi(int col, int num);
void copy_curr_board_to_gurobi_board();
int in_block_gurobi(int x, int y, int num);
int is_valid_set_gurobi(int x, int y, int num);
int check_num_var();
void create_empty_model(int is_LP);
int create_env();
int create_new_model();
int each_cell_value();
int each_row_value();
int each_col_value();
int each_sub_grid_value();
int optimum_state_ilp();
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
