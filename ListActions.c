#include "ListActions.h"
#include "Game.h"
#include "MainAux.h"
#include <stdio.h>
#include <stdlib.h>


Node* insert(Node* curr_node, int command_code, int* command_data, cell cell_data) {
    /* 1. allocate new node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL){
        memory_error("malloc");
    }

    /* 2. put in the data  */
    new_node->command_code = command_code;
    new_node->command_data = command_data;
    new_node->cell_data = cell_data;
    new_node->next = NULL;
    new_node->prev = NULL;
    /*3. check if the given prev_node is NULL */
    if (curr_node == NULL) {
        return new_node;
    }

    /* 4. Make next of new node as next of prev_node */
    new_node->next = NULL;

    /* 5. Make the next of prev_node as new_node */
    curr_node->next = new_node;

    /* 6. Make prev_node as previous of new_node */
    new_node->prev = curr_node;

/* 7. Change previous of new_node's next node
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
*/

    return new_node;


}


void clear_list(Node* head){
    if(head == NULL)
        return;

    while (head->prev!=NULL){
        head = head->prev;
        free(head->next);
    }

    free(head);
}


void init_start_list(){
    cell cell_data = {0,0,0,0,NULL};
    start_list = insert(start_list,-2, NULL, cell_data);
    end_list = insert(start_list,2, NULL, cell_data);
    current_move = start_list;
}

