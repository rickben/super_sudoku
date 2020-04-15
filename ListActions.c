#include "ListActions.h"
#include <stdlib.h>

void fill_undo_board(){
    int i,j;
    undo_board = (struct curr_board *) calloc(curr_board->len, sizeof(struct cell));
    if (undo_board == NULL) {
        memory_error("calloc");
    }
    undo_board->board = (struct cell **) calloc(curr_board->len, sizeof(struct cell *));
    if (undo_board->board == NULL) {
        memory_error("calloc");
    }
    for (i = 0; i < curr_board->len; ++i) {
        undo_board->board[i] = (struct cell *) calloc(curr_board->len, sizeof(struct cell));
        if (undo_board->board[i] == NULL) {
            memory_error("calloc");
        }
    }
    undo_board->len = curr_board->len;
    undo_board->block_width = curr_board->block_width;
    undo_board->block_height = curr_board->block_height;
    for (i = 0; i < undo_board->len; i++) {
        for (j = 0; j < undo_board->len; j++) {
            undo_board->board[i][j].value = curr_board->board[i][j].value;
        }
    }
}

void free_undo_board(){
    int i;
    for (i = 0; i < undo_board->len; ++i) {
        free(undo_board->board[i]);
    }
    free(undo_board->board);
    free(undo_board);
}

void fill_undo_lst_by_cmp_board(int command_code){
    int i,j, is_filled = 0;
    int command_data[3];
    cell cell_data = {0,0,0,0, NULL};
    clear_redo_gap();
    for(i=0;i<undo_board->len;i++){
        for(j=0;j<undo_board->len;j++){
            if(undo_board->board[i][j].value!=curr_board->board[i][j].value){
                is_filled++;
                if (is_filled==1)
                    insert_into_undo_lst(-1, command_data, cell_data);
                cell_data.value = undo_board->board[i][j].value;
                cell_data.is_fixed = undo_board->board[i][j].is_fixed;
                cell_data.is_erroneous = undo_board->board[i][j].is_erroneous;
                command_data[0] = i;
                command_data[1] = j;
                command_data[2] = curr_board->board[i][j].value;
                insert_into_undo_lst(command_code, command_data, cell_data);
            }
        }
    }
    if(is_filled>0)
        insert_into_undo_lst(-1, command_data, cell_data);
}
void insert_into_undo_lst(int command_code, int* command_data, cell cell_data){
    Node* temp = end_list->prev;
    temp = insert(temp, command_code, command_data, cell_data);
    temp->next = end_list;
    end_list->prev = temp;
    current_move = end_list->prev;
}
void clear_redo_gap(){
    while(end_list->prev!=current_move){
        end_list = end_list->prev;
        free(end_list->next);
    }
}