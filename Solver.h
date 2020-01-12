#ifndef HW3_SOLVER_H
#define HW3_SOLVER_H
#include "MainAux.h"
#include "Game.h"

/*
 *Initializes the pointer to the array of
 * valid numbers to set the board with
 * */
void init_pos_numbers(int x, int y, int *pos_numbers);



/*
 *Solves the board
 * using deterministic backtracking
 * For solving puzzle
 * @param board - the current board game
 * */
bool determ_backtrack();

/*
 * Returns a pointer to array s.t.
 * index of pos_numbers: arr[0]
 * value of pos_numbers: arr[1]
 * */
int* get_random_val_valid(int *pos_numbers);

/*
 *Solves the board
 * using random backtracking
 * For generating puzzle
 * @param board - the current board game
 * */
bool random_backtrack();


#endif
