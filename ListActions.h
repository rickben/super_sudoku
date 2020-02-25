//
// Created by User on 25/02/2020.
//

#ifndef HW3_LISTACTIONS_H
#define HW3_LISTACTIONS_H
typedef struct Node {
    int command_code;
    int* command_data;
    int board_data;
    struct Node* next; // Pointer to next node in DLL
    struct Node* prev; // Pointer to previous node in DLL
}Node;

void insert(Node* curr_node, int command_code, int* command_data, int board_data);
Node* get_head(Node* curr_node);
#endif //HW3_LISTACTIONS_H
