#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Solver.h"
#include "ListActions.h"
#include "MainAux.h"
#include "FilesAux.h"
#include "Stack.h"
#include "Solver.h"

/* change for push1*/
void insert_to_undo_lst(int command_code, int* command_data, cell cell_data){
    undo_head = insert(undo_head, command_code, command_data, cell_data);
}
void insert_to_redo_lst(int command_code, int* command_data, cell cell_data){
    redo_head = insert(redo_head, command_code, command_data, cell_data);
}
void my_exit(){
    printf("Exiting...\n");
    if (state == Solve || state == Edit) {
        free_mem_board();
        clear_list(undo_head);
        clear_list(redo_head);
    }
    exit(-1);
}

void save(char* file_name){
    trans_board_to_file(file_name);
}


/*command always available*/
void solve(char* file_name){
    if(trans_file_to_board(file_name, Solve)) {
        print_board();
    }
}


/*command always available*/
void edit(char* file_name){
    if (file_name[0]=='\0'){
        state = Edit;
        create_board_size_9();
        print_board();
    }
    else {
        if(trans_file_to_board(file_name,Edit)){
            print_board();
        }
    }
}


void mark_errors(int x){
    if (x != 0 && x != 1) {
        printf("mark errors only accepts 0 or 1\n");
        return;
    }
    curr_board->mark_errors = x;
}

void print_board(){
    board_print();
}

int undo_action(){
    int* command_data;
    cell cell_data;
    if(undo_head==NULL){
        printf("noting to undo\n");
        return 0;
    }
    if(undo_head->command_code == 5){
        command_data = undo_head->command_data;
        cell_data = undo_head->cell_data;
        curr_board->board[command_data[0]][command_data[1]].value = cell_data.value;
        insert_to_redo_lst(undo_head->command_code, command_data, cell_data);
        undo_head = remove_head(undo_head);
        return 1;
    }
    if(undo_head->command_code == -1){
        command_data = undo_head->command_data;
        cell_data = undo_head->cell_data;
        insert_to_redo_lst(undo_head->command_code, command_data, cell_data);
        undo_head = remove_head(undo_head);
        while (undo_head->command_code != -1){
            command_data = undo_head->command_data;
            cell_data = undo_head->cell_data;
            curr_board->board[command_data[0]][command_data[1]].value = cell_data.value;
            insert_to_redo_lst(undo_head->command_code, command_data, cell_data);
            undo_head = remove_head(undo_head);
        }
        command_data = undo_head->command_data;
        cell_data = undo_head->cell_data;
        insert_to_redo_lst(undo_head->command_code, command_data, cell_data);
        undo_head = remove_head(undo_head);
        return 1;
    }
    return 0;
}
void undo(){
    if(undo_action())
        print_board();
}

int redo_action(){
    int* command_data;

    if(redo_head==NULL){
        printf("noting to redo\n");
        return 0;
    }
    if(redo_head->command_code == 5){
        command_data = redo_head->command_data;
        curr_board->board[command_data[0]][command_data[1]].value = command_data[2];
        redo_head = remove_head(redo_head);
        return 1;
    }
    if(redo_head->command_code == -1){
        redo_head = remove_head(redo_head);
        while (redo_head->command_code != -1){
            command_data = redo_head->command_data;
            curr_board->board[command_data[0]][command_data[1]].value = command_data[2];
            redo_head = remove_head(redo_head);
        }
        redo_head = remove_head(redo_head);
        return 1;
    }
    return 0;
}
void redo() {
    if (redo_action())
        print_board();
}

void reset(){
    int b = 0;
    while(undo_head!=NULL)
        b += undo_action();
    if (b>0)
        print_board();
}

void copy_board_to_cur() {
    int i, j;
    for (i = 0; i < curr_board->len; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            curr_board->board[i][j].value = board[i][j].value;

        }
    }
}

int generate_loop(int x, int y){
    int cnt = 0, num;
    init_temp_board();
    while (cnt < 1000) {
        copy_curr_to_temp_board();
        num = fill_board_random(x);
        if (num == 0) { /* No legal value for one of the X cells */
            copy_temp_board_to_curr(); /* Return to previous board - need to start over*/
            cnt++;
        } else if (num == -1) { /* There are less than x empty cells*/
            free_temp_board();
            return 0; /* Generate had failed*/
        } else { /* No error */
            num = solver(0, 0, 0, 0, 0, 0);
            if (!check_gurobi_board_full() || !num) {
                copy_temp_board_to_curr();
                cnt++;
            } else {
                copy_board_to_cur();
                clear_cells_random(y);
                print_board();
                free_temp_board();
                return 1;
            }
        }
    }
    printf("Generate has failed - After 1000 iterations - the board isn't solvable\n");
    free_temp_board();
    return 0;
}




void generate(int x, int y){
    if (x < 0 || y < 0) {
        printf("Error, all numbers should be positive!\n");
        return;
    } else if (x > curr_board->len *curr_board->len || y > curr_board->len *curr_board->len) {
        printf("Error, a number out of range (0,%d)!\n", curr_board->len *curr_board->len);
        return;
    }else if(check_erroneous_board() || !is_valid_board()){
        printf("The board is erroneous\n");
    } else {
        fill_undo_board();
        if(generate_loop(x,y))
            fill_undo_lst_by_cmp_board(8);
        free_undo_board();

    }
}


void board_set(int x, int y, int z) {
    int *command_data = malloc(sizeof(int) * 3);
    cell cell_data;
    if (x < 1 || y < 1 || z < 0) {
        printf("Error, a number out of range (1,%d)!\n", curr_board->len);
        return;
    } else if (x > curr_board->len  || y > curr_board->len || z > curr_board->len) {
        printf("Error, a number out of range (1,%d)!\n", curr_board->len);
        return;
    } else if (curr_board->board[y-1][x-1].is_fixed && state == Solve) {
        printf("This position is fixed!\n");
        return;
    } else { if(curr_board->board[y-1][x-1].value == z){
	  print_board();
            return;
    } else{
            command_data[0] = y-1;
            command_data[1] = x-1;
            command_data[2] = z;
            cell_data = curr_board->board[y - 1][x - 1];
            if(!is_valid_set(y-1,x-1,z,curr_board)){
                curr_board->board[y-1][x-1].is_erroneous = 1;
            }else{
                curr_board->board[y-1][x-1].is_erroneous = 0;
            }
            curr_board->board[y-1][x-1].value = z;
            insert_to_undo_lst(5, command_data, cell_data);
            clear_list(redo_head);
            print_board();
    }
    }
}

void guess(double x){
   if (check_erroneous_board() || !is_valid_board()){
       printf("The board is erroneous\n");
       return;
   } else {
       if(!solver(1,1,x,0,0,0)){
           printf("The board isn't solvable, guess can't finish\n");
           return;
       }
       copy_board_to_cur();
       print_board();
   }

}


void hint(int x, int y){
    int num;
        if (x < 1 || y < 1) {
            printf("Error, a number out of range (1,%d)!\n", curr_board->len);
            return;
        } else if (x > curr_board->len || y > curr_board->len) {
            printf("Error, a number out of range (1,%d)!\n", curr_board->len);
            return;
        } else if (curr_board->board[y-1][x-1].is_fixed) {
            printf("This position is fixed!\n");
            return;
        } else if (curr_board->board[y-1][x-1].value != 0){
            printf("This position already has a value!\n");
            return;
        } else if(check_erroneous_board() || !is_valid_board()){
            printf("The board is erroneous\n");
        } else{
            num = solver(0,0,0,0,0,0);
            if(!check_gurobi_board_full() || !num){
                printf("This board is unsolvable!\n");
                return;
            } else{
                printf("The value of cell <%d,%d> = %d\n",x,y,board[y-1][x-1].value);
                return;
            }
        }
}

/*
 * !! Remember to check if x and y are numbers, and if they are in the range
 * */
void guess_hint(int x, int y){
        if (x < 1 || y < 1) {
            printf("Error, a number out of range (1,%d)!\n", curr_board->len);
            return;
        } else if (x > curr_board->len || y > curr_board->len) {
            printf("Error, a number out of range (1,%d)!\n", curr_board->len);
            return;
        }else if (curr_board->board[y-1][x-1].is_fixed) {
            printf("This position is fixed!\n");
            return;
        } else if (curr_board->board[y-1][x-1].value != 0){
            printf("This position already has a value!\n");
            return;
        } else if(check_erroneous_board() || !is_valid_board()){
            printf("The board is erroneous\n");
        } else{
            if(!solver(1,0,0,1,y-1,x-1)) { /* prints the scores in solver */
                printf("This board is unsolvable!\n");
                return;
            }
        }
}

/* TODO: When get here - already checked board to be not erroneous*/
int check_validate(){
    int num;
    num = solver(0,0,0,0,0,0);
    if(!check_gurobi_board_full() || !num){
        return 0;
    }
    else{
        return 1;
    }
}

int validate(){
    if (check_erroneous_board() || !is_valid_board()){
        printf("validate not available in erroneous board\n");
        return 0;
    }
    if(!check_validate()){
        printf("Validation failed: board is unsolvable\n");
        return 0;

    } else{
        printf("Validation passed: board is solvable\n");
        return 1;
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
    new_board.mark_errors = new_board.mark_errors;
    new_board.board = (struct cell **) calloc(new_board.len, sizeof(struct cell *));
    for (j = 0; j < new_board.len; ++j) {
        new_board.board[j] = (struct cell *) calloc(new_board.len, sizeof(struct cell));
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

void num_solutions(){
    long count = 0;
    if (check_erroneous_board() || !is_valid_board()){
        printf("num_solutions not available in erroneous board\n");
        return;
    }
    update_new_board_by_curr();
    save_all_curr_cells_fixed(new_board.board);
    push_ele(new_board);
    while (stack != NULL){
        count = update_stack(count);
    }
    printf("The number of solutions for the current board is %ld\n",count);
}

void calculate_list_possible_values(){
    int i,j, len = 0, cell_value, possible_value;
    for (i = 0; i < curr_board->len ; ++i) {
        for (j = 0; j < curr_board->len ; ++j){
            len = 0;
            cell_value = curr_board->board[i][j].value;
            curr_board->board[i][j].list_poss_values = calloc(curr_board->len, sizeof(int));
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
        }
    }
}

void free_list_possible_values(){
    int i,j;
    for (i = 0; i < curr_board->len ; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            free(curr_board->board[i][j].list_poss_values);
            curr_board->board[i][j].list_poss_values_len = 0;
        }
    }
}

void autofill(){
    int i,j;
    int *command_data = malloc(sizeof(int) * 3);
    cell cell_data = {0,0,0,0, NULL};
    if(check_erroneous_board() || !is_valid_board()){
        printf("The board is erroneous\n");
        return;
    }
    calculate_list_possible_values();
    insert_to_undo_lst(-1, command_data, cell_data);
    for (i = 0; i < curr_board->len ; ++i) {
        for (j = 0; j < curr_board->len ; ++j) {
            if (curr_board->board[i][j].list_poss_values_len == 1 && !curr_board->board[i][j].is_fixed){
                command_data[0] = i;
                command_data[1] = j;
                command_data[2] = curr_board->board[i][j].list_poss_values[0];
                cell_data.value = curr_board->board[i][j].value;
                cell_data.is_fixed = curr_board->board[i][j].is_fixed;
                cell_data.is_erroneous = curr_board->board[i][j].is_erroneous;
                if(!is_valid_set(i,j,curr_board->board[i][j].list_poss_values[0], curr_board))
                    curr_board->board[i][j].is_erroneous = 1;
                else
                    curr_board->board[i][j].is_erroneous = 0;
                curr_board->board[i][j].value = curr_board->board[i][j].list_poss_values[0];
                printf("single possible value for <%d,%d> updated: %d\n",i+1,j+1,curr_board->board[i][j].value);
                insert_to_undo_lst(15, command_data, cell_data);
                command_data = malloc(sizeof(int) * 3);
            }
        }
    }
    insert_to_undo_lst(-1, command_data, cell_data);
    free(command_data);
    clear_list(redo_head);
    free_list_possible_values();
    print_board();
}



