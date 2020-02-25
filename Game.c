#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "ListActions.h"
#include "MainAux.h"






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

}

void redo(Node* current_cmd){
}

void reset(){

}

void board_set(int x, int y, int z){
    int* command_data = malloc(sizeof(int)*3);
    int board_data=0;
    if(state!=Solve && state != Edit){
        printf("set only available in solve or edit mode");
        return;
    }
    /* TODO check is fixed*/
    command_data[0] = x;
    command_data[1] = y;
    command_data[2] = z;
    board_data = curr_board->board[x][y].value;
    curr_board->board[x][y].value = z;
    insert(last_cmd, 5, command_data, board_data);
}

void hint(int x, int y){
}

void guess_hint(int x, int y){
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



