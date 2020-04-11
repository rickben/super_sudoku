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

Node* get_head(Node* curr_node){
    Node* head;
    /*1. check if the given prev_node is NULL */
    if (curr_node == NULL) {
        /*Error*/
        return NULL;
    }
    head = curr_node;
    while(head->prev != NULL){
        head = head->prev;
    }
    return head;
}

Node* get_tail(Node* curr_node){
    Node* head;
    /*1. check if the given prev_node is NULL */
    if (curr_node == NULL) {
        /*Error*/
        return NULL;
    }
    head = curr_node;
    while(head->prev != NULL){
        head = head->prev;
    }
    return head;
}

Node* remove_head(Node* head){
    Node* second_last;
    if (head == NULL)
        return NULL;

    if (head->prev == NULL) {
        free(head);
        return NULL;
    }

    /* Find the second last node*/
    second_last = head;
    while (second_last->next == NULL)
        second_last = second_last->prev;

    /* Delete last node*/
    free (second_last->next);

    /* Change next of second last*/
    second_last->next = NULL;

    return second_last;
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
int arr_len(int* arr){
    int i=0;
    while(arr[i]!=0 && i < 9)
        i++;
    return i;
}

void init_start_list(){
    cell cell_data = {0,0,0,0,NULL};
    start_list = insert(start_list,-2, NULL, cell_data);
    end_list = insert(start_list,2, NULL, cell_data);
    current_move = start_list;
}

