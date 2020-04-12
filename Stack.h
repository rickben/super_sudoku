#ifndef HW3_STACK_H
#define HW3_STACK_H
#include "ListActions.h"

/**
*Stack Summary:
*
 * This module is in charge of the stack that replaces the recursion in the
 * exhaustive backtracking algorithm for num_solutions
 * The stack saves curr_boards (the board are in the size of curr_board's board)
* It supports the following functions:
 *
 * push_ele               - pushes the given board to the stack, and its now at the top
 * pop_ele                - pops the given board to the stack, and returns it
**/


/** The rec_stack struct represents the stack that replaces the recursion in
 * the exhaustive backtracking algorithm:
 * top : the board (struct curr_board) in the top of the stack
 * rec_stack : a pointer to the next board (struct curr_board) in the stack
 * */
struct rec_stack{
    struct curr_board top;
    struct rec_stack *next_stack;
}*stack;

/**
 * pushes a new element to stack
 * @param curr_board - the current board in the
 * exhaustive backtracking algorithm
 */
void push_ele(struct curr_board next_board);

/**
 * pushes a new element to stack
 * @return curr_board - the top board in the stack
 */
struct curr_board pop_ele();


#endif
