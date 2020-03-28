#ifndef HW3_LISTACTIONS_H
#define HW3_LISTACTIONS_H


/* change for push*/

typedef struct cell{
    int value;
    int is_fixed;
    int is_erroneous;
    int list_poss_values_len;
    int* list_poss_values;
}cell;

struct curr_board{
    struct cell** board;
    int block_width;
    int block_height;
    int len;
    int mark_errors;
}*curr_board, new_board, *temporary_board;

typedef struct Node {
    int command_code;
    int* command_data;
    cell cell_data;
    struct Node* next; /* Pointer to next node in DLL */
    struct Node* prev; /* Pointer to previous node in DLL */
}Node;

cell** temp_board;

Node* insert(Node* curr_node, int command_code, int* command_data, cell cell_data);
Node* remove_head(Node* head);
Node* get_head(Node* curr_node);
void clear_list(Node* head);
int arr_len(int* arr);
#endif