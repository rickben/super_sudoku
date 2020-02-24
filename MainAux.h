#ifndef HW3_MAINAUX_H
#define HW3_MAINAUX_H
/*EMPTY is used for empty cells in the board
 * */
#define EMPTY 0
#include <stdbool.h>
#include "Game.h"

int* calc_block_size(int len);
void separator_row(int height, int width);

#endif
