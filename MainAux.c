#include <stdio.h>
#include <stdbool.h>
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
/*
 * Return false if there's a cell in the same row
 * with the same value, otherwise, returns true
 * */
bool in_row(int row, int num, cell** matrix) {
    int j;
    for (j = 0; j < curr_board->len; ++j) {
        if (matrix[row][j].value == num) {
            if(num!=0) {
                return true;
            }
            else{
                return false;
            }
        }
    }
    return false;
}

/*
 * Return false if there's a cell in the same column
 * with the same value, otherwise, returns true
 * */
bool in_col(int col, int num, cell** matrix) {
    int j;
    for (j = 0; j < curr_board->len; ++j) {
        if (matrix[j][col].value == num) {
            if (num != 0) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

/*
 * Return false if there's a cell in the same block
 * with the same value, otherwise, returns true
 * */
bool in_block(int x, int y, int num, cell** matrix) {
    int i, j;
    for (i = 0; i < curr_board->block_height; ++i) {
        for (j = 0; j < curr_board->block_width; ++j) {
            if (matrix[i+x][j+y].value == num) {
                if(num!=0) {
                    return true;
                }
                else{
                    return false;
                }
            }
        }
    }
    return false;
}


/*
 * Returns whether a cell in position <x,y>:
 * means not valid (FALSE)
 * means valid (TRUE)
 * */
bool is_valid_set(int x, int y, int num, cell** matrix) {
    int block_x = (x/curr_board->block_height)*curr_board->block_height;
    int block_y = (y/curr_board->block_width)*curr_board->block_width;
    return (!in_row(x,num,matrix) && !in_col(y,num,matrix) &&
            !in_block(block_x,block_y,num,matrix) && matrix[x][y].value==0);
}

bool is_valid_board(cell** matrix){
    int temp = 0;
    for (int i = 0; i < curr_board->len; ++i) {
        for (int j = 0; j < curr_board->len; ++j) {
            if(matrix[i][j].value!=0){
                temp = matrix[i][j].value;
                matrix[i][j].value = 0;
                if(!is_valid_set(i,j,temp,matrix)) {
                    matrix[i][j].value = temp;
                    return false;
                }
                matrix[i][j].value = temp;
            }
        }
    }
    return true;
}

