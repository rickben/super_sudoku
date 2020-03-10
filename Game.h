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

void solve();
void edit();
void mark_errors(int x);
void print_board();
void undo();
void redo();
void reset();
void board_set(int x, int y, int z);
void hint(int x, int y);
void guess_hint(int x, int y);
int check_board_full(cell** board);
void save_all_curr_cells_fixed(cell** board);
int find_last_unfixed_un_eq_len(int* row, int* col, struct curr_board new_board);
cell** put_1_in_all_unfixed_cells_right(int row, int col, cell** board);
cell** put_1_in_all_unfixed_cells(cell** board);
struct curr_board update_next_sol(struct curr_board new_board);
long num_solutions();
void autofill();
int validate();
void my_exit();
void create_board(int len);
void board_set(int x, int y, int z);
void generate(int x, int y);
void guess(double x);

#endif