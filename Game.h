#ifndef HW3_GAME_H
#define HW3_GAME_H
#include <stdio.h>
#include <stdbool.h>
#include "List.h"

/**
 * curr_board represents the current board game - whether its
 * been loaded in Solve or Edit mode.
 * curr_board->board : is the multi-dimensional array that represents
 * this board game which the player can load, edit, change and save.
 * */

/**
 *Game Summary:
 *
 *A curr_board->len X curr_board->len (N X N) puzzle board with only one player.
 *
 *It supports the following functions:
 *
 * save                    - saves current board to specified file
 * solve                   - sets Solve mode and loads the board from specified file
 * edit                    - sets Edit mode and loads the board from specified file / empty 9x9 board
 * board_set               - sets a move on game board
 * validate                - checks if a move is valid
 * hint                    - uses ILP to print hint for the value in the specified position
 * generate                - randomly sets values for X empty cells, solves by ILP, and randomly leaves Y cells
 * guess                   - uses LP to set legal values to board cells with probabilities higher than X
 * guess_hint              - uses LP to print probabilities for the values in the specified position
 * num_solutions           - uses exhaustive backtracking to print the number of solutions for the board
 * autofill                - fills all empty cells with only one legal value
 * print_board             - prints the current board
 * undo                    - undo the last successful move on the board
 * redo                    - redo the last successful move on the board
 * reset                   - resets the board to its first situation
 * mark_errors             - sets the mark_errors field to X (0 or 1)
 * board_exit              - prints and exits the game
 * ***/




/**
 * This enum - state, represents the current state of the game, it's
 * is either in Init, Edit of Solve state
 * */
enum state{Init, Edit, Solve};
enum state state;

/**
 * This Nodes represent:
 * current_move - pointer to current node in the doubly-linked list of moves
 * end_list - the end node in the doubly-linked list of moves
 * start_list - the start node in the doubly-linked list of moves
 * */
Node* current_move;
Node* end_list;
Node* start_list;


/**
 * frees all the memory and exits the program
 */
void my_exit();

/**
 * saves the curr_board's board to the specified file
 * @param file_name - path to the specified file
 */
void save(char* file_name);

/**
 * loads to state Solve the board from to the specified file
 * @param file_name - path to the specified file
 */
void solve(char* file_name);

/**
 * loads to state Edit the board from to the specified file
 * @param file_name - path to the specified file
 */
void edit(char* file_name);

/**
 * sets the parameter global_mark_errors to x
 * @param x - the parameter to set to
 */
void mark_errors(int x);

/**
 * prints the curr_board's board
 */
void print_board();

/**
 * undo's the last action
 * @return 1 if successful, 0 otherwise
 */
int undo_action(bool is_reset);

/**
 * calls undo_action, and prints the board if the command
 * was successful
 */
void undo();

/**
 * redo's the last action
 * @return 1 if successful, 0 otherwise
 */
int redo_action();

/**
 * calls redo_action, and prints the board if the command
 * was successful
 */
void redo();

/**
 * resets the board to its first state
 */
void reset();


/**
 * tries to fill x empty cells with random values,
 * run ILP and then leave y random empty cells,
 * if it fails tries again for 1000 iterations
 * @param x - the number of first cells to fill
 * @param y - the number of last cells to leave empty
 * @return if all the 1000 the tries were unsuccessful - 0, otherwise 1.
 */
int generate_loop(int x, int y);

/**
 * checks whether conditions for the command met, if they
 * do - calls generate_loop, otherwise prints error
 * @param x - the number of first cells to fill
 * @param y - the number of last cells to leave empty
 */
void generate(int x, int y);

/**
 * executes set command
 * @param x - the number of column
 * @param y - the number of row
 * @param z - the value to set
 */
void execute_set_command(int x, int y, int z);

/**
 * sets the cell <x,y> (col,row) in the curr_board's board,
 * with the value of z. calls execute_set_command
 * @param x - the number of column
 * @param y - the number of row
 * @param z - the value to set
 */
void board_set(int x, int y, int z);

/**
 * using LP - fills the curr_board's board with values
 * with probabilities greater than x
 * @param x - the threshold for probabilities
 */
void guess(double x);

/**
 * using ILP get a hint to the value of the cell
 * @param x - the column of the cell
 * @param y - the row of the cell
 */
void hint(int x, int y);

/**
 * using LP prints probabilities of values to be set to the cell
 * @param x - the column of the cell
 * @param y - the row of the cell
 */
void guess_hint(int x, int y);

/**
 * using ILP checks if the board is full after running the solver
 * if not - the board is not valid (can not be saved)
 * @return 1 if the board is valid, 0 otherwise
 */
int check_validate();

/**
 * checks whether the board is valid - means it can be solved
 * @return 1 if the board is valid, 0 otherwise
 */
int validate();

/**
 * using exhaustive backtracking algorithm and a stack, it calculates
 * the number of possible solutions for the curr_board's board
 */
void num_solutions();

/**
 * fills all empty cells with only one possible value with that value
 */
void autofill();

#endif