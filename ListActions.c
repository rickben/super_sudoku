#include "ListActions.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>


void insert(Node* curr_node, int command_code, int* command_data, int board_data) {
    /* 1. allocate new node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    /* 2. put in the data  */
    new_node->command_code = command_code;
    new_node->command_data = command_data;
    new_node->board_data = board_data;
    /*3. check if the given prev_node is NULL */
    if (last_cmd == NULL) {
        last_cmd = new_node;
        return;
    }

    /* 4. Make next of new node as next of prev_node */
    new_node->next = last_cmd->next;

    /* 5. Make the next of prev_node as new_node */
    last_cmd->next = new_node;

    /* 6. Make prev_node as previous of new_node */
    new_node->prev = last_cmd;

//    /* 7. Change previous of new_node's next node */
//    if (new_node->next != NULL)
//        new_node->next->prev = new_node;

    last_cmd = new_node;


}

Node* get_head(Node* curr_node){
    /*1. check if the given prev_node is NULL */
    if (curr_node == NULL) {
        /*Error*/
        return NULL;
    }
    Node* head = curr_node;
    while(head->prev != NULL){
        head = head->prev;
    }
    return head;
}

Node* get_tail(Node* curr_node){
    /*1. check if the given prev_node is NULL */
    if (curr_node == NULL) {
        /*Error*/
        return NULL;
    }
    Node* head = curr_node;
    while(head->prev != NULL){
        head = head->prev;
    }
    return head;
}

