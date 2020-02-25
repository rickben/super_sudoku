#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "MainAux.h"



void my_exit(){
    state =  Terminate;
    printf("Exiting...\n");
    ///TODO release memory
}

int validate_board(){
    ///TODO
    return 1;
}

void create_board(int len) {
    curr_board = (struct curr_board *) calloc(len, sizeof(int));
    curr_board->len = len;
    curr_board->mark_errors = 0;
    calc_block_size(len);
    curr_board->board = (int **) calloc(len, sizeof(int *));
    for (int i = 0; i < len; ++i) {
        curr_board->board[i] = (int *) calloc(len, sizeof(int));
    }
}



void set_values_board() {
    for (int i = 0; i < curr_board->len; ++i) {
        for (int j = 0; j < curr_board->len; ++j) {
            curr_board->board[i][j] = 1;
            ///TODO change the values to match the len
        }
    }
}



