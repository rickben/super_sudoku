#ifndef HW3_STACK_H
#define HW3_STACK_H
#include "ListActions.h"

struct rec_stack{
    struct curr_board top;
    struct rec_stack *next_stack;
}*stack;

void push_ele(struct curr_board next_board);

struct curr_board pop_ele();

void display_ele();

#endif
