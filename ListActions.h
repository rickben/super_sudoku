#ifndef HW3_LISTACTIONS_H
#define HW3_LISTACTIONS_H

/**
 *ListActions Summary:
 *
 *This module manges the actions lists -  maintains a doubly-linked list of the user's moves,
 * and a pointer marking the current move.
 *
 *It supports the following functions:
 *
 * insert                    - inserts an new node to the doubly-linked list of the user's moves
 * clear_list                - clears all the nodes in the doubly-linked list of the user's moves
 * init_start_list           - initializes the doubly-linked list of the user's moves
 * ***/

/** In this module the curr_board and cell structs are defined:
 *
 * cell represents a single cell in the board. It contains the cells value,
 * a flag (0/1) if it is fixed (is_fixed), a flag (0/1) if it is erroneous (is_erroneous),
 * and for the use of autofill command: list_poss_values_len - the length of the list of possible
 * values for this cell, and list_poss_values - list of possible values for this cell
*/
typedef struct cell{
    int value;
    int is_fixed;
    int is_erroneous;
    int list_poss_values_len;
    int* list_poss_values;
}cell;

/**
 * curr_board - struct that contains board - the N x N current board (two dimensional array of cells)
 * in the game that is either in Solve or Edit mode, the board's block width - block_width
 * (n - num of columns in block), the board's block height - block_height (m - num of rows in block)
 * and the len of the board
 * curr_board: the board for the game
 * new_board: a board for check_board_solved function
 * temporary_board: saves the new board loaded from file, and if its not valid - it will be freed and the
 * previous board will still be
 * undo_board: a board for the use of undo_command, to move to the undone board
 * */
struct curr_board{
    struct cell** board;
    int block_width;
    int block_height;
    int len;
}*curr_board, new_board, *temporary_board, *undo_board;


/**
 * global_mark_errors - is a global variable which at the start of the program is defined
 * to be 1 and can change via the mark_errors command
 * */
int global_mark_errors;


/**
 *  Node is a struct that contains - command_code that represents the type of command,
 *  The possible command_code and there meaning:
 *  set: 5 (only one change of value in cell) , guess,generate,autofill: -1 (multiple cells that can be changed) .
 *  command_data which is an array of numbers that represents the data from this command
 *  in the format:
 *  command[0] - is the row of the cell
 *  command[1] - is the col of the cell
 *  command[2] - is the value of the cell
 *  cell_data - represents the value of the cell
 *  next - is a pointer to the next node in the doubly-linked list
 *  prev - is a pointer to the previous node in the doubly-linked list
 *   - It saves only successful moves of set, guess, generate and autofill
 * */
typedef struct Node {
    int command_code;
    int* command_data;
    cell cell_data;
    struct Node* next; /* Pointer to next node in DLL */
    struct Node* prev; /* Pointer to previous node in DLL */
}Node;

/**
 * temp_board is used for only generate command - to save the board
 * that to insure that if the command is unsuccessful - we can gp back to the
 * board that is saved in temp_board
 * */
cell** temp_board;

Node* insert(Node* curr_node, int command_code, int* command_data, cell cell_data);
void clear_list(Node* head);
void init_start_list();
#endif