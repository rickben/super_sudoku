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
    for (i = 0; i < len; ++i) {
        for (j = 0; j < len; ++j) {
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
    int block_x = (x/block_width) * block_height;
    int block_y = (y/block_width) * block_height;
    return (!in_row(x,num,matrix) && !in_col(y,num,matrix) &&
            !in_block(block_x,block_y,num,matrix) && matrix[x][y]==0);
}

int* get_first_empty_cell(int** board){
    int* arr = malloc(2* sizeof(int));
    for(int i=0;i<len;i++)
        for(int j=0;j<len;j++){
            if( board[i][j]==0){
                arr[0] = i;
                arr[1] = j;
                return arr;
            }
        }
    return NULL;
}

bool determ_backtrack(int** board) {
    int row1;
    int col1;
    int num;

    if(find_empty_cell(&row1, &col1,board) == 0)
        return true;
    for(num=1;num<=len;num++)
    {

        if(is_valid_set(row1, col1, num, board))
        {
            board[row1][col1] = num;
            if(determ_backtrack(board))
                return true;
            board[row1][col1]=0;
        }
    }
    return false;
}

int num_solutions_main(int** board){
    int i=0;
    int count = 0;
    int* arr = malloc(2* sizeof(int));
    arr = get_first_empty_cell(board);

    /*allocate new mem and free to determ backtrack*/
    int** board_copy = calloc(len, sizeof(int*));
    for (int j = 0; j < len; ++j) {
        board_copy[j] = calloc(len, sizeof(int));
    }
    for (int j = 0; j < len;j++) {
        for(int k=0;k<len;k++)
            board_copy[j][k] = board[j][k];
    }

    if(!determ_backtrack(board_copy))
        return 0;

    /*allocate new mem and free to determ backtrack*/
    for (int j = 0; j < len; ++j)
        free(board_copy[j]);
    free(board_copy);

    if(arr == NULL){
        return 1;
    }
    for(;i<len;i++){
        board[arr[0]][arr[1]] = i;
        count += num_solutions_main(board);
    }
    return count;
}

int main(int argc, char* argv[]) {
    state = Solve;
    trans_file_to_board("C:\\Users\\User\\CLionProjects\\super_sudoku\\dog.txt");
    int** board = calloc(len, sizeof(int*));
    for (int j = 0; j < len; ++j)
        board[j] = calloc(len, sizeof(int));
    printf("%d", num_solutions_main(board));
//    trans_board_to_file("C:\Users\User\CLionProjects\super_sudoku\\ricky.txt");
}
