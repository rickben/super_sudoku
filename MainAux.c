#include <stdio.h>
#include <string.h>
#include "MainAux.h"
#include <math.h>

void print_start_program(){
    printf("Welcome to Sudoku puzzle game!\nYou may enter either Solve or Edit mode\nby typing the name of the mode:\n");
}

int check_correct_file_format(){
    //TODO
}

int check_erroneous_board(){
    int i,j;
    for (i = 0; i < curr_board->len ; ++i)
        for (j = 0; j < curr_board->len ; ++j)
            if(curr_board->board[i][j].is_erroneous)
                return 1;

    return 0;
}

void fill_board_random(int x){
//TODO
}

void clear_cells_random(int y){
//TODO
}

int check_if_number_float(int x){
    //TODO
}


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
        if(curr_board->board[num_row][j].is_fixed == 1){
            printf(".");
        }
        if(curr_board->board[num_row][j].is_erroneous == 1){
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

