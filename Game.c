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

void undo(){

}

void redo(Node* current_cmd){
}

void reset(){

}

void set(int x, int y, int z){
    curr_board->board[x][y].value = z;
    insert(last_cmd, "set");/*change char*/
    last_cmd = last_cmd->next;

}

void hint(int x, int y){
}

void guess_hint(int x, int y){
}

void validate(){
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



