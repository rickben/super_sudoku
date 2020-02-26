#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "ListActions.h"
#include "MainAux.h"







void insert_to_undo_lst(int command_code, int* command_data, cell cell_data){
    insert(undo_head, command_code, command_data, cell_data);
}
void insert_to_redo_lst(int command_code, int* command_data, cell cell_data){
    insert(redo_head, command_code, command_data, cell_data);
}

void my_exit(){
    state =  Terminate;
    printf("Exiting...\n");
    ///TODO release memory
}

void mark_errors(int x){
    if (state != Solve){
        printf("mark errors only available in solve mode");
        return;
    }
    if (x!=0&&x!=1) {
        printf("mark errors only accepts 0 or 1");
        return;
    }
    curr_board->mark_errors = x;
}

void print_board(){
    if(state!=Solve && state != Edit){
        printf("print board only available in solve or edit mode");
        return;
    }
    board_print();
}

void undo(){
    int* command_data = undo_head->command_data;
    cell cell_data = undo_head->cell_data;
    if(state!=Solve && state != Edit){
        printf("undo only available in solve or edit mode");
        return;
    }
    if(undo_head->command_code == 5){
        curr_board->board[command_data[0]][command_data[1]].value = cell_data.value;
    }
    insert_to_redo_lst(undo_head->command_code, command_data, cell_data);
    undo_head = remove_head(undo_head);
}

void redo(Node* current_cmd){
    if(state!=Solve && state != Edit){
        printf("undo only available in solve or edit mode");
        return;
    }

}

void reset(){

}

void board_set(int x, int y, int z){
    int* command_data = malloc(sizeof(int)*3);
    cell board_data;
    if(state!=Solve && state != Edit){
        printf("set only available in solve or edit mode");
        return;
    }
    /* TODO check is fixed*/
    command_data[0] = x;
    command_data[1] = y;
    command_data[2] = z;
    board_data.value = curr_board->board[x][y].value;
    curr_board->board[x][y].value = z;
    insert_to_undo_lst(5, command_data, board_data);
    redo_head = remove_head(redo_head);
}

void hint(int x, int y){
    int is_erroneous = 0;
    if(state!=Solve){
        printf("hint only available in solve mode");
        return;
    }
    if(is_erroneous){
        printf("Error");
        return;
    }
    printf("%d", curr_board->board[x][y].value);
}

void guess_hint(int x, int y){
    int is_erroneous = 0;
    if(state!=Solve){
        printf("hint only available in solve mode");
        return;
    }
    if(is_erroneous){
        printf("Error");
        return;
    }
    printf("%d", curr_board->board[x][y].value);
}

void validate(){
    if(state!=Solve && state != Edit){
        printf("validate only available in solve or edit mode");
        return;
    }
    int is_valid = 1;
    if(is_valid){
        printf("Validation passed: board is solvable\n");
    }
    else{

        printf("Validation failed: board is unsolvable\n");
    }
}

void num_solutions(){
    if(state!=Solve && state != Edit){
        printf("num_solutions only available in solve or edit mode");
        return;
    }
}

void autofill(){
}

int validate_board(){
    ///TODO
    return 1;
}

void create_board(int len) {
    curr_board = (struct curr_board *) calloc(len, sizeof(struct cell));
    curr_board->len = len;
    curr_board->mark_errors = 0;
    calc_block_size(len);
    curr_board->board = (struct cell **) calloc(len, sizeof(struct cell *));
    for (int i = 0; i < len; ++i) {
        curr_board->board[i] = (struct cell *) calloc(len, sizeof(struct cell));
    }
}



void set_values_board() {
    for (int i = 0; i < curr_board->len; ++i) {
        for (int j = 0; j < curr_board->len; ++j) {
            curr_board->board[i][j].value = 1;
            ///TODO change the values to match the len
        }
    }
}



