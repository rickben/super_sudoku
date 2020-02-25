//
// Created by User on 25/02/2020.
//

#ifndef HW3_LISTACTIONS_H
#define HW3_LISTACTIONS_H
typedef struct Node {
    char* command;
    struct Node* next; // Pointer to next node in DLL
    struct Node* prev; // Pointer to previous node in DLL
}Node;

void insert(Node* curr_node, char* command);
Node* get_head(Node* curr_node);
#endif //HW3_LISTACTIONS_H
