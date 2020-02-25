#include <stdio.h>
#include "MainAux.h"
#include <math.h>



void calc_block_size(){
    int root = (int) (sqrt(curr_board->len));
    while (root > 0){
        if(curr_board->len % root == 0){
            curr_board->block_height = root;
            curr_board->block_height = (curr_board->len / root);
            curr_board->block_height = (curr_board->len / root);
        }
        root--;
    }
}

void separator_row() {
    int i=0,j=0;
    printf("-");
    for(; i<curr_board->block_height; i++){
        printf("--");
        for(; j<curr_board->block_width-1; j++){
        printf("----");
        }
        printf("---");
        j=0;
    }
    printf("\n");
}

int is_fixed(int row, int col) {
    return 0;
}

int is_erroneous() {
    return 0;
}

void cell_row(struct cell* arr, int num_row) {
    for (int j = 0; j < curr_board->len; j++) {
        if (j % curr_board->block_width == 0) {
            printf("|");
        }
        if(arr[j].value==0){
            printf("   ");
        } else {
            printf(" %2d", arr[j].value);
        }
        if(is_fixed(num_row,j)==1){
            printf(".");
        }
        else if(is_erroneous()==1){
            printf("*");
        } else{
            printf(" ");
        }

    }
    printf("|\n");

}


void board_print() {
        int k=0;
        separator_row(curr_board->block_height, curr_board->block_width);
        for (int i = 0; i < curr_board->block_width; i++) {
            for (int j = 0; j < curr_board->block_height; j++) {
                cell_row(curr_board->board[k],k);
                k++;
            }
            separator_row(curr_board->block_height, curr_board->block_width);
        }
}

