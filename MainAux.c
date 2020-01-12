#include <stdio.h>
#include <stdlib.h>
#include "MainAux.h"
const int BOARD_LEN=9;
const int BLOCK_LEN=3;





void print_exit_game() {
    printf("Exiting...\n");
}


void separator_row() {
    printf("----------------------------------\n");
}


int get_hint_size() {
    int H, value;
    printf("Please enter the number of cells to fill [0-80]:\n");
    while ((value=scanf("%d",&H)) != 1 || H < 0 || H > 80) {
        if(feof(stdin)){
            board_exit();
            return -1;
        }
        if (value != 1) {
            printf("Error: not a number\n");
            board_exit();
            return -1;
        } else {
            printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
        }
        fgetc(stdin);
    }
    return 81-H;
}



/*
 * Returns whether a cell in position <x,y>:
 * 0 - means not fixed (FALSE)
 * 1 - means fixed (TRUE)
 * */
bool is_fixed(int x, int y) {
    if(board_fixed.board_game[x][y]!=EMPTY)
        return true;
    else{
        return false;
    }
}


bool find_empty_cell(int* row_pos, int* col_pos, int** matrix ) {
    {
        int i, j;
        for(i=0;i<BOARD_LEN;i++)
        {
            for(j=0;j<BOARD_LEN;j++)
            {
                if(matrix[i][j] == 0)
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
bool in_row(int row, int num, int** matrix) {
    int j;
    for (j = 0; j < BOARD_LEN; ++j) {
        if (matrix[row][j] == num) {
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
bool in_col(int col, int num, int** matrix) {
    int j;
    for (j = 0; j < BOARD_LEN; ++j) {
        if (matrix[j][col] == num) {
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
bool in_block(int x, int y, int num, int** matrix) {
    int i, j;
    for (i = 0; i < BLOCK_LEN; ++i) {
        for (j = 0; j < BLOCK_LEN; ++j) {
            if (matrix[i+x][j+y] == num) {
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
bool is_valid_set(int x, int y, int num, int** matrix) {
    int block_x = (x/3)*3;
    int block_y = (y/3)*3;
    return (!in_row(x,num,matrix) && !in_col(y,num,matrix) &&
            !in_block(block_x,block_y,num,matrix) && matrix[x][y]==EMPTY);
}



int number_of_non_empty_vars(int *array){
    int len = BOARD_LEN;
    int cnt = 0;
    int i = 0;
    for(;i<len;i++){
        if(array[i]!=0){
            cnt++;
        }
    }
    return cnt;
}




int prev_x(int x, int y) {
    if(y==0)
        if(x>0)
            return x-1;
        else
            return 0;
    else
        return x;
}


int prev_y(int y){
    if(y==0)
        return BOARD_LEN-1;
    else
        return y-1;
}

void board_solved() {
    board.is_game_over=1;
    printf("Puzzle solved successfully\n");
}

