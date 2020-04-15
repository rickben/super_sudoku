#ifndef HW3_LISTACTIONS_H
#define HW3_LISTACTIONS_H
#include <stdbool.h>
#include "List.h"
#include "MainAux.h"
/**
 *ListActions Summary:
 *
 *This module supports all List auxiliary functions of the game.
 *
 *It supports the following functions:
 *
 * functions that process and manage the user's moves linked list
 * functions that allocate memory and process undo_board
 * in order to manage correctly the user's moves linked list
 * ***/

/**
 * fill the undo_board as curr_board before the current command
 * will change it (only for : guess,generate);
 */
void fill_undo_board();

/**
 * free all memories allocated for undo_board
 */
void free_undo_board();

/**
 *
 * fill the undo_board as curr_board after the current command
 * changed it (only for successful : guess,generate)
 * @param command_code - the commands code number
 */
void fill_undo_lst_by_cmp_board(int command_code);
/**
 * inserts new node with the command's number and its data (only successful commands)
 * @param command_code - the number of the command
 * @param command_data - its data - the cell information
 * @param cell_data - the value the cell is changed to
 */
void insert_into_undo_lst(int command_code, int* command_data, cell cell_data);

/**
 * clears from memory all the nodes between end_list (pointer to the end of the linked list)
 * and curr_move (pointer to the last move executed)
 * that way we can add to the end of the list move moves
 */
void clear_redo_gap();
#endif
