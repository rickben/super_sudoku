#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "MainAux.h"
#include "FilesAux.h"
#include <math.h>
#include <stdlib.h>

void restart_to_init(){
    state = Init;
    free_mem_board();
}

void print_start_program(){
    printf("Welcome to Sudoku puzzle game!\n");
}


int check_erroneous_board(){
    int i,j;
    for (i = 0; i < curr_board->len ; ++i)
        for (j = 0; j < curr_board->len ; ++j)
            if(curr_board->board[i][j].is_erroneous)
                return 1;

    return 0;
}

/*
 * col->row->value
 * */
void fill_board_random(int x){
    int col,row,val;
while (x>0){
    col = rand()%curr_board->len;
    row = rand()%curr_board->len;
    val = rand()%curr_board->len;
    curr_board->board[row][col].value = val;
    /*
    //curr_board->board[row][col].is_fixed = 1;??*/
    --x;
}
}

void clear_cells_random(int y){
    int col, row;
    while (y>0){
        col = rand()%curr_board->len;
        row = rand()%curr_board->len;
        curr_board->board[row][col].value = 0;
        curr_board->board[row][col].is_fixed = 0;
        --y;
    }
}

/*
int check_if_number_float(int x){

 }*/


/*
 * Return false if there's a cell in the same row
 * with the same value, otherwise, returns true
 * */
int in_row(int row, int num, struct curr_board* curr_board) {
    int j;
    for (j = 0; j < curr_board->len; ++j) {
        if (curr_board->board[row][j].value == num) {
            if(num!=0) {
                return 1;
            }
            else{
                return 0;
            }
        }
    }
    return 0;
}

/*
 * Return false if there's a cell in the same column
 * with the same value, otherwise, returns true
 * */
int in_col(int col, int num, struct curr_board* curr_board) {
    int j;
    for (j = 0; j < curr_board->len; ++j) {
        if (curr_board->board[j][col].value == num) {
            if (num != 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

/*
 * Return false if there's a cell in the same block
 * with the same value, otherwise, returns true
 * */
int in_block(int x, int y, int num,  struct curr_board* curr_board) {
    int i, j;
    for (i = 0; i < curr_board->block_height; ++i) {
        for (j = 0; j < curr_board->block_width; ++j) {
            if (curr_board->board[i+x][j+y].value == num) {
                if(num!=0) {
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
    }
    return 0;
}


int is_valid_set(int x, int y, int num , struct curr_board* curr_board) {
    int block_x = (x / (curr_board->block_height))*(curr_board->block_height);
    int block_y = (y / (curr_board->block_width))*(curr_board->block_width);
    return (!in_row(x,num,curr_board) && !in_col(y,num,curr_board) &&
            !in_block(block_x,block_y,num,curr_board));
}




int check_board_solved(){
    int x,y,temp,found_valid;
    new_board.board = curr_board->board;
    new_board.len = curr_board->len;
    new_board.block_width = curr_board->block_width;
    new_board.block_height = curr_board->block_height;
    if(!check_board_full(new_board.board)){
        return 0;
    }
    else {
        for (x = 0; x < curr_board->len; ++x) {
            for (y = 0; y < curr_board->len; ++y) {
                temp = new_board.board[x][y].value;
                new_board.board[x][y].value = 0;
                found_valid = is_valid_set(x, y, temp, &new_board);
                new_board.board[x][y].value = temp;
                if (!found_valid) {
                    return 0;
                }
            }
        }
        return 1;
    }
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

void update_erroneous_cells(){

}



void cell_row(struct cell* arr, int num_row) {
    int j;
    if(state == Edit || (state == Solve && curr_board->mark_errors)){
        update_erroneous_cells();
    }
    for (j = 0; j < curr_board->len; j++) {
        if (j % curr_board->block_width == 0) {
            printf("|");
        }
        if(arr[j].value==0){
            printf("   ");
        } else {
            printf(" %2d", arr[j].value);
        }
        if(curr_board->board[num_row][j].is_fixed){
            printf(".");
        }
        if((curr_board->board[num_row][j].is_erroneous) && (curr_board->mark_errors) && (state == Solve)){
            printf("*");
        }
        if((curr_board->board[num_row][j].is_erroneous) && (state == Edit)){
            printf("*");
        }
        else{
            printf(" ");
        }

    }
    printf("|\n");

}


void board_print() {
    int k = 0, i, j;
    separator_row(curr_board->block_height, curr_board->block_width);
    for (i = 0; i < curr_board->block_width; i++) {
        for (j = 0; j < curr_board->block_height; j++) {
            cell_row(curr_board->board[k],k);
            k++;
        }
        separator_row(curr_board->block_height, curr_board->block_width);
    }
}

bool find_empty_cell(int* row_pos, int* col_pos, cell** matrix ) {
    {
        int i, j;
        for(i=0;i<curr_board->len;i++)
        {
            for(j=0;j<curr_board->len;j++)
            {
                if(matrix[i][j].value == 0)
                {
                    *row_pos = i;
                    *col_pos = j;
                    return true;
                }
            }
        }
        return false;
    }
}

bool is_valid_board(){
    int temp = 0, i, j;
    for (i = 0; i < curr_board->len; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            if(curr_board->board[i][j].value!=0){
                temp = curr_board->board[i][j].value;
                curr_board->board[i][j].value = 0;
                if(!is_valid_set(i,j,temp,curr_board)) {
                    curr_board->board[i][j].value = temp;
                    return false;
                }
                curr_board->board[i][j].value = temp;
            }
        }
    }
    return true;
}

