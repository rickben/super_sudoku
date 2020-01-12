#ifndef HW3_GAME_H
#define HW3_GAME_H
#include <stdio.h>

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
struct list{
    int** board_game;
    int is_game_over;
    int is_exit;
} board,solution,board_fixed;


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

/*
 * Prints the current sudoku board
 * */
void board_print();


/*
 * Creates a new board game : initializes fixed_board.board_game
 * int the size of BOARD_LEN X BOARD_LEN
 *  Return 0 if a malloc error happened
 * */
int fixed_create();

/*
 * Sets the value to the board
 * as the user commanded
 * if it was a successful set then
 * return 1, else return 0
 * */
int board_set();

/*
 *Checks if the curr ent board is solvable
 * using valid_determ_backtrack()
 * */
void board_validate();

/*
 *Receive a possible value for the cell <x,y>
 * using the stored puzzle solution
 * @param x , y - row number , column number
 * */
void board_hint(int x, int y);

/*
 * Creates a new board game : initializes board.board_game
 * int the size of BOARD_LEN X BOARD_LEN
 *  * Return 0 if a malloc error happened

 * */
int board_create();

/*
 * Free all memory resources associated with a game
 * */
void board_destroy();

/*
 * Uses suitable functions to initialize and
 * restart the game
 * */
int board_restart(int H);

/*
 * If board exit returns 1, the game should
 * terminate after the print
 * */
void board_exit();

/*
 * Creates a new board game : initializes solution.board_game
 * and then sets the same values of the board.board_game
 * int the size of BOARD_LEN X BOARD_LEN
 * Return 0 if a malloc error happened
 * */
int solution_create();

/*
 * Restarts the game by calling the suitable
 * functions
 * */
int game_restart(int H);


/*
 * checks if there is no empty cells, if there is no
 * calls board_solved
 * */
void check_if_board_solved();

/*
 *restarts the game by calling the
 * suitable functions
 * */
void start_over();

#endif
