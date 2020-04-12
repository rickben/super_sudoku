#ifndef HW3_GAME_H
#define HW3_GAME_H
#include <stdio.h>
#include "ListActions.h"

/*
 * curr_board represents the current board game - whether its
 * been loaded in Solve or Edit mode.
 * curr_board->board : is the multi-dimensional array that represents
 * this board game which the player can load, edit, change and save.
 * */

/*
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





enum state{Init, Edit, Solve};
enum state state;

Node* current_move;
Node* end_list;
Node* start_list;

void insert_into_undo_lst(int command_code, int* command_data, cell cell_data);
void clear_redo_gap();
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