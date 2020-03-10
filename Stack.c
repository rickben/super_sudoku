#include <stdio.h>
#include "Stack.h"
#include <stdlib.h>

/*Inserting the elements using push function*/

void push_ele(struct curr_board j)
{
    struct rec_stack *m;
    m = (struct rec_stack*) malloc(sizeof( struct rec_stack));
    m->top = j;
    m->next_stack = stack; //receives all previous elements stack
    stack = m;
}

/*Removing the elements using pop function*/

void pop_ele()
{
    if (stack == NULL) { //TODO - or to change it
        printf("The stack is Empty.");
    }
    else {
        stack = stack->next_stack;
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