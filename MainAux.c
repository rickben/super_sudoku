#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "MainAux.h"
#include "FilesAux.h"
#include <math.h>
#include <stdlib.h>


void update_list_pos_vals(int i, int j, int num){
    int k, flag = 0, cnt = 0;
    int* new_list_poss;
    for (k = 0; k < curr_board->board[i][j].list_poss_values_len; ++k) {
        if (curr_board->board[i][j].list_poss_values[k] == num){
            curr_board->board[i][j].list_poss_values[k] = 0;
            flag = 1;
            break;
        }
    }
    if (flag){
        new_list_poss = malloc((curr_board->board[i][j].list_poss_values_len-1)*sizeof(int));
        for (k = 0; k < curr_board->board[i][j].list_poss_values_len; ++k) {
            if (curr_board->board[i][j].list_poss_values[k] == 0) {
                continue;
            } else {
                new_list_poss[cnt] = curr_board->board[i][j].list_poss_values[k];
                cnt ++;
            }
        }
        curr_board->board[i][j].list_poss_values_len --;
        curr_board->board[i][j].list_poss_values = new_list_poss;
    }
}

void init_temp_board(){
    int i;
    temp_board= (struct cell **) calloc(curr_board->len, sizeof(struct cell *));
    for (i = 0; i < curr_board->len; ++i) {
        temp_board[i] = (struct cell *) calloc(curr_board->len, sizeof(struct cell));
    }
}

void free_temp_board(){
    int i;
    for (i = 0; i < curr_board->len; ++i) {
        free(temp_board[i]);
    }
    free(temp_board);
}

void copy_curr_to_temp_board() {
    int i, j;
    for (i = 0; i < curr_board->len; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            temp_board[i][j].value = curr_board->board[i][j].value;
        }
    }
}

void copy_temp_board_to_curr(){
    int i, j;
    for (i = 0; i < curr_board->len; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            curr_board->board[i][j].value = temp_board[i][j].value;
        }
    }
}

void restart_to_init(){
    state = Init;
    free_mem_board();
}

int check_erroneous_board(){
    int i,j;
    for (i = 0; i < curr_board->len ; ++i)
        for (j = 0; j < curr_board->len ; ++j)
            if(curr_board->board[i][j].is_erroneous)
                return 1;

    return 0;
}

void print_start_program(){
    printf("Welcome to Sudoku puzzle game!\n");
}

int check_num_of_empty_cells(){
    int res = 0, i, j;
    for (i = 0; i < curr_board->len; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            if (curr_board->board[i][j].value == 0){
                res ++;
            }
        }
    }
    return res;
}

int set_random_val(int row, int col){
    int  v, val, num_pos = 0, cnt = 0;
    int* pos_val;
    pos_val = (int*) malloc(curr_board->len*sizeof(int));
    for (v = 0; v < curr_board->len; ++ v) {
        if (is_valid_set(row,col,v+1,curr_board)){
            pos_val[v] = 1;
            num_pos ++;
        } else {
            pos_val[v] = 0;
        }
    }
    if (num_pos == 0){
        return 0;
    }
    val = rand() % num_pos;
    for (v = 0; v < curr_board->len; ++ v) {
        if (pos_val[v] == 1){
            if (cnt == val){
                curr_board->board[row][col].value = val;
                curr_board->board[row][col].is_fixed = 0;
                break;
            }
            cnt++;
        }
    }
    return 1;
}

void find_random_empty_cell(int* row, int* col, int num_empty){
    int ** all_empty_cells;
    int i, j, cnt = 0;
    all_empty_cells = (int**)malloc(num_empty*sizeof(int*));
    for (i = 0; i < num_empty; ++i) {
        all_empty_cells[i] = (int*)malloc(2*sizeof(int));
    }
    for (i = 0; i < curr_board->len; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            if (curr_board->board[i][j].value == 0){
                all_empty_cells[cnt][0] = i;
                all_empty_cells[cnt][1] = j;
                cnt ++;
            }
        }
    }
    cnt = rand() % num_empty;
    *row = all_empty_cells[cnt][0];
    *col = all_empty_cells[cnt][1];
}


/*
 * col->row->value
 * */
int fill_board_random(int x){
    int col, row, num;
    num = check_num_of_empty_cells();
    if (num < x){
        printf("There are less then %d empty cells, generate can't finish",x);
        return -1;
    }
    while (x>0){
        find_random_empty_cell(&row,&col,num);
        /* Find all possible values in this position*/
        if (set_random_val(row,col) == 0){
            return 0;
        }
        --x;
    }
    return 1;
}

void clear_cells_random(int y){
    int col, row;
    y = (curr_board->len * curr_board->len) - y;
    while (y>0){
        col = rand()%curr_board->len;
        row = rand()%curr_board->len;
        if (curr_board->board[row][col].value != 0) {
            curr_board->board[row][col].value = 0;
            curr_board->board[row][col].is_fixed = 0;
            --y;
        }
    }
}




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




void separator_row() {
    int i,j;
    for (i = 0; i < curr_board->len ; ++i) {
        printf("----");
    }
    for(j=0; j<curr_board->block_width; j++) {
        printf("-");
    }
    printf("-\n");
    /*
    printf("-");
    for(; i<curr_board->block_height; i++){
        printf("--");
        for(; j<curr_board->block_width-1; j++){
            printf("----");
        }
        printf("---");
        j=0;
    }
    printf("\n");*/
}

void update_erroneous_cells(){

}



void cell_row(struct cell* arr) {
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
        if((arr[j].is_fixed && state == Solve) || (arr[j].is_erroneous && (((curr_board->mark_errors) && (state == Solve)) || (state == Edit)))){
            if(arr[j].is_fixed && state == Solve){
                printf(".");
            } else {
                printf("*");
            }
        } else {
            printf(" ");
        }
    }
    printf("|\n");

    /*
    for (j = 0; j < curr_board->len; j++) {
        if (j % curr_board->block_width == 0) {
            printf("|");
        }
        if(arr[j].value==0){
            printf("   ");
        } else {
            printf(" %2d", arr[j].value);
        }
        if(curr_board->board[num_row][j].is_fixed && state == Solve){
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
*/
}


void board_print() {
    int k = 0, i, j;
    separator_row(curr_board->block_height, curr_board->block_width);
    for (i = 0; i < curr_board->block_width; i++) {
        for (j = 0; j < curr_board->block_height; j++) {
            cell_row(curr_board->board[k]);
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

void create_board_size_9() {
    int i, j;
    curr_board = (struct curr_board *) calloc(9, sizeof(struct cell));
    curr_board->len = 9;
    curr_board->block_height = 3;
    curr_board->block_width = 3;
    curr_board->mark_errors = 1;
    curr_board->board = (struct cell **) calloc(9, sizeof(struct cell *));
    for (i = 0; i < 9; ++i) {
        curr_board->board[i] = (struct cell *) calloc(9, sizeof(struct cell));
    }
    for (i = 0; i < 9; ++i) {
        for (j = 0; i < 9; ++i) {
            curr_board->board[i][j].value = 0;
        }
    }
}
