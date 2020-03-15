#include <stdio.h>
#include "Stack.h"
#include <stdlib.h>

/*Inserting the elements using push function*/

void push_ele(struct curr_board next_board)
{
    struct rec_stack *m;
    m = (struct rec_stack*) malloc(sizeof( struct rec_stack));
    m->top.board = (struct cell **) calloc(next_board.len, sizeof(struct cell *));
    for (int i = 0; i < next_board.len; ++i) {
        m->top.board[i] = (struct cell *) calloc(next_board.len, sizeof(struct cell));
    }
    for (int j = 0; j < next_board.len; ++j) {
        for (int k = 0; k < next_board.len; ++k)
            m->top.board[j][k].value = next_board.board[j][k].value;
    }
    m->top.len = next_board.len;
    m->top.block_height = next_board.block_height;
    m->top.block_width = next_board.block_width;
    m->top.mark_errors = next_board.mark_errors;
    m->next_stack = stack; //receives all previous elements stack
    stack = m;
}

/*Removing the elements using pop function*/

struct curr_board pop_ele()
{
    if (stack == NULL) { //TODO - or to change it
        printf("The stack is Empty.");
    }
    else {
        struct curr_board board = stack->top;
        stack = stack->next_stack;
        return board;
    }
}
//
//
//void display_ele() {
//    struct rec_stack *pointer = NULL;
//    pointer = stack;
//    printf("[");
//    while(pointer != NULL)
//    {
//        printf("%d\t",pointer->top);
//        pointer = pointer->next_stack;
//    }
//    printf("]");
//}