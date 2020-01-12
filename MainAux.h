#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
/*EMPTY is used for empty cells in the board
 * */
#define EMPTY 0
#include <stdbool.h>
#include "Game.h"

/*BOARD_LEN is used for the size of the board
 * BLOCK_LEN is used for the size of a block
 * */
const int BOARD_LEN;
const int BLOCK_LEN;

/*
 * print the message for exiting the game
 * */
void print_exit_game();
/*
 * function called by print_sudoko_board()
 * */
void separator_row();
/*
 * Looks for an empty cell in the board,
 * if there is one - updates the  pointers :row_pos
 * and col_pos to the position of the first one from the left top-down.
 * otherwise it updates the  pointers :row_pos and col_pos to the
 * position of <BOARDLEN,BOARDLEN> - the end of the board
 * */
bool find_empty_cell(int* row_pos, int* col_pos, int** matrix);
/*
 * Returns boolean for a cell in the location <x,y> whether it is fixed
 * */
bool is_fixed(int x, int y);

/* * Returns boolean for a cell in the location <row,col> whether
 * there's a number in this row that has the same value
 * */
bool in_row(int row, int num, int** matrix);

/* * Returns boolean for a cell in the location <row,col> whether
 * there's a number in this column that has the same value
 * */
bool in_col(int col, int num, int** matrix);

/* * Returns boolean for a cell in the location <row,col> whether
 * there's a number in this block that has the same value
 * */
bool in_block(int block_start, int col_start, int num, int** matrix);

/*
 * Returns boolean for a cell in the location <x,y> whether it is valid
 * Goes over x row and y column and the block which <x,y> is in,
 * and checks if cell_value already exists
 * */
bool is_valid_set(int x, int y, int num, int** matrix);

/*
 * Returns the number of non empty variables
 * in the given array
 * */
int number_of_non_empty_vars(int *array);

/*
 * returns the index of the column of the previous cell in
 * the backtracking algorithm
 * */
int prev_y(int y);

/*
 * returns the index of the row of the previous cell in
 * the backtracking algorithm
 * */
int prev_x(int x, int y);

/*
 * Gets from the user the number of cells be filled
 * int he board, if the number is not from 0 to 80
 * then returns -1, otherwise if the input is not a number
 * then prints error and exits the game and returns -1, otherwise
 * returns the input
 * */
int get_hint_size();

/*
 * Sets the flag is_game_over of board to 1 so
 * from now on the only possible commands are exit
 * and restart
 * */
void board_solved();
#endif
