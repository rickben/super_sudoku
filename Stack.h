#ifndef HW3_STACK_H
#define HW3_STACK_H

struct rec_stack{
    int top;
    struct rec_stack *next_stack;
}*stack;

int i;

void push_ele(int j);

int pop_ele();

void display_ele();

#endif
