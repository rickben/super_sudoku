#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Parser.h"
#include "Solver.h"
#include "SPBufferset.h"
#include "MainAux.h"
#include "FilesAux.h"
#include <stdbool.h>


const int len=9;
const int block_width=3;
const int block_height=3;
int** board_game;

bool find_empty_cell(int* row_pos, int* col_pos, int** matrix ) {
    {
        int i, j;
        for(i=0;i<len;i++)
        {
            for(j=0;j<len;j++)
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
    for (j = 0; j < len; ++j) {
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
    for (j = 0; j < len; ++j) {
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
    for (i = 0; i < block_height; ++i) {
        for (j = 0; j < block_width; ++j) {
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
    int block_x = (x/block_height)*block_height;
    int block_y = (y/block_width)*block_width;
    return (!in_row(x,num,matrix) && !in_col(y,num,matrix) &&
            !in_block(block_x,block_y,num,matrix) && matrix[x][y]==0);
}

bool is_valid_board(int** matrix){
    int temp = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            if(matrix[i][j]!=0){
                temp = matrix[i][j];
                matrix[i][j] = 0;
                if(!is_valid_set(i,j,temp,matrix)) {
                    matrix[i][j] = temp;
                    return false;
                }
                matrix[i][j] = temp;
            }
        }
    }
    return true;
}

long num_solutions_main(){
    int i=1;
    long count = 0;
    int row=0,col=0;
    int temp = 0;

    if(!is_valid_board(board_game))
        return 0;

    if(!find_empty_cell(&row,&col, board_game)){
        return 1;
    }
    for(;i<=len;i++){
        temp = board_game[row][col];
        board_game[row][col] = i;
        count += num_solutions_main();
        board_game[row][col] = temp;
    }
    return count;
}

int main(int argc, char* argv[]) {
    state = Solve;
    trans_file_to_board("C:\\Users\\User\\CLionProjects\\super_sudoku\\dog.txt");
    board_game = calloc(len, sizeof(int*));
    for (int j = 0; j < len; ++j)
        board_game[j] = calloc(len, sizeof(int));
    printf("%ld\n", num_solutions_main());
//    trans_board_to_file("C:\Users\User\CLionProjects\super_sudoku\\ricky.txt");
}
