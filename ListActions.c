#include "ListActions.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>


void insert(Node* curr_node, int command_code, int* command_data, cell cell_data) {
    /* 1. allocate new node */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    /* 2. put in the data  */
    new_node->command_code = command_code;
    new_node->command_data = command_data;
    new_node->cell_data = cell_data;
    /*3. check if the given prev_node is NULL */
    if (undo_head == NULL) {
        undo_head = new_node;
        return;
    }

    /* 4. Make next of new node as next of prev_node */
    new_node->next = undo_head->next;

    /* 5. Make the next of prev_node as new_node */
    undo_head->next = new_node;

    /* 6. Make prev_node as previous of new_node */
    new_node->prev = undo_head;

//    /* 7. Change previous of new_node's next node */
//    if (new_node->next != NULL)
//        new_node->next->prev = new_node;

    undo_head = new_node;


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

Node* remove_head(Node* head){
    if (head == NULL)
        return NULL;

    if (head->prev == NULL) {
        free(head);
        return NULL;
    }

    // Find the second last node
    Node* second_last = head;
    while (second_last->next == NULL)
        second_last = second_last->prev;

    // Delete last node
    free (second_last->next);

    // Change next of second last
    second_last->next = NULL;

    return head;
}

