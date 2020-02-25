#include "ListActions.h"
#include <stdio.h>
#include <stdlib.h>


void insert(Node* curr_node, char* command) {
    /*1. check if the given prev_node is NULL */
    if (curr_node == NULL) {
        /*Error*/
        return;
    }

    /* 2. allocate new node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    /* 3. put in the data  */
    new_node->command = command;

    /* 4. Make next of new node as next of prev_node */
    new_node->next = curr_node->next;

    /* 5. Make the next of prev_node as new_node */
    curr_node->next = new_node;

    /* 6. Make prev_node as previous of new_node */
    new_node->prev = curr_node;

    /* 7. Change previous of new_node's next node */
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
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

