#include <stdio.h>
#include "Stack.h"
#include "MainAux.h"
#include <stdlib.h>

/*Inserting the elements using push function*/

void push_ele(struct curr_board next_board)
{   int i,j,k;
    struct rec_stack *m;
    /* allocate memory for stack */
    m = (struct rec_stack*) malloc(sizeof( struct rec_stack));
    if (m == NULL) {
        memory_error("malloc");
    }
    /* allocate memory for top board */
    m->top.board = (struct cell **) calloc(next_board.len, sizeof(struct cell *));
    if (m->top.board == NULL) {
        memory_error("calloc");
    }
    for (i = 0; i < next_board.len; ++i) {
        m->top.board[i] = (struct cell *) calloc(next_board.len, sizeof(struct cell));
        if (m->top.board[i] == NULL) {
            memory_error("calloc");
        }
    }
    for (j = 0; j < next_board.len; ++j) {
        for (k = 0; k < next_board.len; ++k)
            m->top.board[j][k].value = next_board.board[j][k].value;
    }
    m->top.len = next_board.len;
    m->top.block_height = next_board.block_height;
    m->top.block_width = next_board.block_width;
    m->next_stack = stack; /*receives all previous elements stack*/
    stack = m;
}

/*Removing the elements using pop function*/

struct curr_board pop_ele()
{   struct curr_board* board;
    if (stack == NULL) {
        printf("The stack is Empty.");
         board = (struct curr_board*)NULL;
        return *board;
    }
    else {
        struct curr_board board = stack->top;
        stack = stack->next_stack;
        return board;
    }
}
