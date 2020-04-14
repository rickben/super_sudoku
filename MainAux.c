#include <stdio.h>
#include <stdbool.h>
#include "MainAux.h"
#include "FilesAux.h"
#include <stdlib.h>

void memory_error(char* func){
    printf("ERROR: memory leak in function %s\n",func);
    my_exit();
}


void init_temp_board(){
    int i;
    temp_board= (struct cell **) calloc(curr_board->len, sizeof(struct cell *));
    if (temp_board == NULL){
        memory_error("calloc");
    }
    for (i = 0; i < curr_board->len; ++i) {
        temp_board[i] = (struct cell *) calloc(curr_board->len, sizeof(struct cell));
        if (temp_board[i] == NULL){
            memory_error("calloc");
        }
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
    free_mem_board();
    clear_list(end_list);
    end_list = NULL;
    start_list = NULL;
    state = Init;
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
    /* allocate memory for array of possible values in the
     * size of curr_board's length for this cell <col,row> */
    pos_val = (int*) malloc(curr_board->len*sizeof(int));
    if (pos_val == NULL){
        memory_error("malloc");
    }
    /* for every value that can be in the board -
     * check if it's valid - and set flag to 1 in pos_val */
    for (v = 0; v < curr_board->len; ++ v) {
        if (is_valid_set(row,col,v+1,curr_board)){
            pos_val[v] = 1;
            num_pos ++;
        } else {
            /* if not valid - set flag to 0*/
            pos_val[v] = 0;
        }
    }
    if (num_pos == 0){ /* there are no possible values for this cell */
        free(pos_val);
        return 0;
    }
    val = rand() % num_pos; /* randomly pick an index between 0 to num_pos-1*/
    for (v = 0; v < curr_board->len; ++ v) {
        if (pos_val[v] == 1){ /* if the flag is 1*/
            if (cnt == val){ /* cnt is the index of the 1's in the pos_val array */
                curr_board->board[row][col].value = v+1;
                curr_board->board[row][col].is_fixed = 0;
                break;
            }
            cnt++;
        }
    }
    free(pos_val);
    return 1;
}


void first_set_cond_check_param(int x, int y){
    if (x < 1) {
        printf("Error: the first parameter is out of range (1,%d)!\n", curr_board->len);
        return;
    } else if (y < 1) {
        printf("Error: the second parameter is out of range (1,%d)!\n", curr_board->len);
        return;
    } else {
        printf("Error: the third parameter is out of range (1,%d)!\n", curr_board->len);
        return;
    }
}

void second_set_cond_check_param(int x, int y){
    if (x > curr_board->len) {
        printf("Error: the first parameter is out of range (1,%d)!\n", curr_board->len);
        return;
    } else if (y > curr_board->len) {
        printf("Error: the second parameter is out of range (1,%d)!\n", curr_board->len);
        return;
    } else {
        printf("Error: the third parameter is out of range (1,%d)!\n", curr_board->len);
        return;
    }
}



void find_random_empty_cell(int* row, int* col, int num_empty){
    int ** all_empty_cells;
    int i, j, cnt = 0; /* cnt iterates from 0 to the number of empty cells */
    /* allocate memory for array in the size of number of empty cells */
    all_empty_cells = (int**)malloc(num_empty*sizeof(int*));
    if (all_empty_cells == NULL){
        memory_error("malloc");
    }
    for (i = 0; i < num_empty; ++i) {
        all_empty_cells[i] = (int*)malloc(2*sizeof(int));
        if (all_empty_cells[i] == NULL){
            memory_error("malloc");
        }
    }
    /* each entry in the array contains 2 values:
     * first - i - the row of the empty cell
     * second - j - the col of the empty cell*/
    for (i = 0; i < curr_board->len; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            if (curr_board->board[i][j].value == 0){ /* if the cell is empty */
                all_empty_cells[cnt][0] = i;
                all_empty_cells[cnt][1] = j;
                cnt ++;
            }
        }
    }
    /*
     * randomly chooses index from 0 to number of empty cells:
     * it means randomly choose an empty cell
     * */
    cnt = rand() % num_empty;
    *row = all_empty_cells[cnt][0];
    *col = all_empty_cells[cnt][1];

    /* free all memory allocated */
    for (i = 0; i < num_empty; ++i) {
        free(all_empty_cells[i]);
    }
    free(all_empty_cells);
}

/*
 * col->row->value
 * */
int fill_board_random(int x){
    int col, row, num;
    num = check_num_of_empty_cells();
    if (num < x){
        printf("Error: There are less then %d empty cells, generate can't finish\n",x);
        return -1;
    }
    while (x>0){
        num = check_num_of_empty_cells();
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
    for(j=0; j<curr_board->block_height; j++) {
        printf("-");
    }
    printf("-\n");
}

void update_erroneous_cells(){
    int i,j,num;
    for (i = 0; i < curr_board->len ; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            if (!curr_board->board[i][j].is_fixed){
                num = curr_board->board[i][j].value;
                curr_board->board[i][j].value = 0;
                if (!is_valid_set(i,j,num,curr_board)){
                    curr_board->board[i][j].value = num;
                    curr_board->board[i][j].is_erroneous = 1;
                }else{
                    curr_board->board[i][j].value = num;
                    curr_board->board[i][j].is_erroneous = 0;
                }
            } else{
                curr_board->board[i][j].is_erroneous = 0;
            }
        }
    }
}



void cell_row(struct cell* arr) {
    int j;
    if(state == Edit || (state == Solve && global_mark_errors)){
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
        if((arr[j].is_fixed && state == Solve) || (arr[j].is_erroneous && (((global_mark_errors) && (state == Solve)) || (state == Edit)))){
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
}


void board_print() {
    int k = 0, i, j;
    separator_row();
    for (i = 0; i < curr_board->block_width; i++) {
        for (j = 0; j < curr_board->block_height; j++) {
            cell_row(curr_board->board[k]);
            k++;
        }
        separator_row();
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

bool is_valid_board_new_board(){
    int temp = 0, i, j;
    for (i = 0; i < new_board.len; ++i) {
        for (j = 0; j < new_board.len; ++j) {
            if(new_board.board[i][j].value!=0){
                temp = new_board.board[i][j].value;
                new_board.board[i][j].value = 0;
                if(!is_valid_set(i,j,temp,&new_board)) {
                    new_board.board[i][j].value = temp;
                    return false;
                }
                new_board.board[i][j].value = temp;
            }
        }
    }
    return true;
}

void create_board_size_9() {
    int i, j;
    if(state!=Init){
        free_mem_board();
        clear_list(end_list);
        end_list = NULL;
        start_list = NULL;
    }
    curr_board = (struct curr_board *) calloc(9, sizeof(struct cell));
    if (curr_board == NULL) {
        memory_error("calloc");
    }
    curr_board->len = 9;
    curr_board->block_height = 3;
    curr_board->block_width = 3;
    curr_board->board = (struct cell **) calloc(9, sizeof(struct cell *));
    if (curr_board->board == NULL) {
        memory_error("calloc");
    }
    for (i = 0; i < 9; ++i) {
        curr_board->board[i] = (struct cell *) calloc(9, sizeof(struct cell));
        if (curr_board->board[i] == NULL) {
            memory_error("calloc");
        }
    }
    for (i = 0; i < 9; ++i) {
        for (j = 0; i < 9; ++i) {
            curr_board->board[i][j].value = 0;
        }
    }
}

void copy_board_to_cur() {
    int i, j;
    for (i = 0; i < curr_board->len; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            curr_board->board[i][j].value = board[i][j].value;

        }
    }
}

void save_all_curr_cells_fixed(cell** my_board){
    int i,j;
    for (i = 0; i < curr_board->len ; ++i)
        for (j = 0; j < curr_board->len ; ++j)
            if(my_board[i][j].value != 0)
                my_board[i][j].is_fixed = 1;
            else{
                my_board[i][j].is_fixed = 0;
            }
}

int check_board_full(cell** my_board){
    int i,j;
    for (i = 0; i < curr_board->len ; ++i)
        for (j = 0; j < curr_board->len ; ++j)
            if(my_board[i][j].value == 0)
                return 0;

    return 1;
}

void update_new_board_by_curr(){
    int j,k;
    new_board.len = curr_board->len;
    new_board.block_width = curr_board->block_width;
    new_board.block_height = curr_board->block_height;
    new_board.board = (struct cell **) calloc(new_board.len, sizeof(struct cell *));
    if (new_board.board == NULL){
        memory_error("calloc");
    }
    for (j = 0; j < new_board.len; ++j) {
        new_board.board[j] = (struct cell *) calloc(new_board.len, sizeof(struct cell));
        if (new_board.board[j] == NULL){
            memory_error("calloc");
        }
    }
    for (j = 0; j < new_board.len; ++j) {
        for (k = 0; k < new_board.len; ++k)
            new_board.board[j][k] = curr_board->board[j][k];
    }
}


int update_stack(int count){
    int row = 0, col = 0, i;
    new_board = pop_ele();
    if (find_empty_cell(&row,&col, new_board.board)){
        for(i = 1;i <= new_board.len ;i++){
            new_board.board[row][col].value = i;
            if(is_valid_board_new_board()){
                push_ele(new_board);
            }
        }
    }
    else {
        if (is_valid_board(&new_board)){
            count++;
        }
    }
    return count;
}

int calculate_list_possible_values(){
    int i,j, len = 0, cell_value, possible_value, is_filled=0;
    for (i = 0; i < curr_board->len ; ++i) {
        for (j = 0; j < curr_board->len ; ++j){
            len = 0;
            cell_value = curr_board->board[i][j].value;
            if (cell_value != 0) {
                curr_board->board[i][j].list_poss_values_len = -1; /* don't calculate the poss_values for non-empty cell */
                continue;
            }
            curr_board->board[i][j].list_poss_values = calloc(curr_board->len, sizeof(int));
            if (curr_board->board[i][j].list_poss_values == NULL){
                memory_error("calloc");
            }
            for ( possible_value = 1; possible_value <= curr_board->len; ++possible_value) {
                if(possible_value!=cell_value){
                    curr_board->board[i][j].value=possible_value;
                    if( is_valid_board()){
                        curr_board->board[i][j].list_poss_values[len] = possible_value;
                        len++;
                    }
                }
            }
            curr_board->board[i][j].list_poss_values_len = len;
            curr_board->board[i][j].value = cell_value;
            if(len==1)
                is_filled=1;
        }
    }
    return is_filled;
}

void free_list_possible_values(){
    int i,j;
    for (i = 0; i < curr_board->len ; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            if (curr_board->board[i][j].list_poss_values_len != -1) {
                free(curr_board->board[i][j].list_poss_values);
                curr_board->board[i][j].list_poss_values_len = 0;
            }
        }
    }
}