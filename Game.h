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
struct cell{
    int value;
    int is_fixed;
    int is_erroneous;
    int* list_poss_values;
};
struct curr_board{
    struct cell** board;
    int block_width;
    int block_height;
    int len;
    int mark_errors;
}*curr_board;



enum state{Init, Edit, Solve, Terminate};
enum state state;
Node* last_cmd;

void my_exit();
int validate_board();
void create_board(int len);
void set_values_board();
void board_set(int x, int y, int z);

#endif