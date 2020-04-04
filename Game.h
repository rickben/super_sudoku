#ifndef HW3_GAME_H
#define HW3_GAME_H
#include <stdio.h>
#include "ListActions.h"


/*
 * is_game_over is a flag that
 * represents if the board is solved,
 * board_game is the multi-dimensional array that
 * represents this board_game
 * board : the board_game which the player gets and changes
 * fixed_board : the board_game after the clean of leaving only
 * the number of cells, received by the user.
 * solution: the board_game after getting the same values as
 * fixed_board and then determ_backtrack() for future hints
 * */

/*
 *Game Summary:
 *
 *A BOARDLEN X BOARDLEN (rows X columns) puzzle board with only one player.
 *
 *It supports the following functions:
 *
 *board_create            - creates a new game board
 *board_destroy           - free all memory of game
 *board_set               - sets a move on game board
 *board_valid             - checks if a move is valid
 *board_print             - prints the current board
 *board_restart           - restarts the game
 * board_exit             - prints and exits the game
 * */




enum state{Init, Edit, Solve};
enum state state;
Node* undo_head;
Node* redo_head;

void insert_to_undo_lst(int command_code, int* command_data, cell cell_data);
void insert_to_redo_lst(int command_code, int* command_data, cell cell_data);
void my_exit();
void save(char* file_name);
void solve(char* file_name);
void edit(char* file_name);
void mark_errors(int x);
void print_board();
int undo_action();
void undo();
int redo_action();
void redo();
void reset();
void copy_board_to_cur();
int generate_loop(int x, int y);
void generate(int x, int y);
void board_set(int x, int y, int z);
void guess(double x);
void hint(int x, int y);
void guess_hint(int x, int y);
int check_validate();
int validate();
void save_all_curr_cells_fixed(cell** my_board);
int check_board_full(cell** my_board);
void num_solutions();
void autofill();

#endif