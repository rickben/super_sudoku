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




enum state{Init, Edit, Solve, Terminate};
enum state state;
Node* undo_head;
Node* redo_head;

void insert_to_undo_lst(int command_code, int* command_data, cell cell_data);
void insert_to_redo_lst(int command_code, int* command_data, cell cell_data);
void my_exit();
void mark_errors(int x);
void print_board();
void undo();
void redo(Node* current_cmd);
void reset();
void board_set(int x, int y, int z);
void hint(int x, int y);
void guess_hint(int x, int y);
long num_solutions();
void autofill();
int validate_board();
void create_board(int len);
void set_values_board();
#endif