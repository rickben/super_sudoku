#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Solver.h"
#include "ListActions.h"
#include "MainAux.h"
#include "FilesAux.h"


void insert_to_undo_lst(int command_code, int* command_data, cell cell_data){
    undo_head = insert(undo_head, command_code, command_data, cell_data);
}
void insert_to_redo_lst(int command_code, int* command_data, cell cell_data){
    redo_head = insert(redo_head, command_code, command_data, cell_data);
}
void my_exit(){
    printf("Exiting...\n");
    free_mem_board();
    exit(-1);
}

/*command always available*/
void solve(char* file_name){
    ///TODO do i need to release memory from before or do i reach here clean?
    //command always available
    state = Solve;
    trans_file_to_board(file_name);
}


/*command always available*/
void edit(char* file_name){
    state = Edit;
    if (file_name[0]=='\0'){
        create_board(9);
    }
    else {
        trans_file_to_board(file_name);
    }
}


void mark_errors(int x){
    if (state != Solve){
        printf("mark errors only available in solve mode\n");
        return;
    }
    if (x != 0 && x != 1) {
        printf("mark errors only accepts 0 or 1\n");
        return;
    }
    curr_board->mark_errors = x;
}

void print_board(){
    if(state != Solve && state != Edit){
        printf("print board only available in solve or edit mode\n");
        return;
    }
    board_print();
}

void undo(){
    if(state!=Solve && state != Edit){
        printf("undo only available in solve or edit mode\n");
        return;
    }
    if(undo_head==NULL){
        printf("noting to undo\n");
        return;
    }
    int* command_data;
    cell cell_data;
    if(undo_head->command_code == 5){
        command_data = undo_head->command_data;
        cell_data = undo_head->cell_data;
        curr_board->board[command_data[0]][command_data[1]].value = cell_data.value;
        insert_to_redo_lst(undo_head->command_code, command_data, cell_data);
        undo_head = remove_head(undo_head);
        return;
    }
    if(undo_head->command_code == 15 || undo_head->command_code == -1){
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
        return;
    }
}

void redo() {
    if (state != Solve && state != Edit) {
        printf("undo only available in solve or edit mode\n");
        return;
    }
    if(redo_head==NULL){
        printf("noting to redo\n");
        return;
    }
    int* command_data;
    cell cell_data;
    if(redo_head->command_code == 5){
        command_data = redo_head->command_data;
        cell_data = redo_head->cell_data;
        curr_board->board[command_data[0]][command_data[1]].value = cell_data.value;
        redo_head = remove_head(redo_head);
    }
    if(redo_head->command_code == 15 || redo_head->command_code == -1){
        while (redo_head->command_code != -1){
            command_data = redo_head->command_data;
            cell_data = redo_head->cell_data;
            curr_board->board[command_data[0]][command_data[1]].value = cell_data.value;
            redo_head = remove_head(redo_head);
        }
        redo_head = remove_head(redo_head);
        return;
    }
}

void reset(){
    if (state != Solve && state != Edit) {
        printf("reset only available in solve or edit mode\n");
        return;
    }
    while(undo_head!=NULL)
        undo();
}


void generate(int x, int y){
    if (state == Edit){
        if (x < 0 || y < 0) {
            printf("Error, a number out of range (0,%d)!\n", curr_board->len);
            return;
        } else if (x > curr_board->len || y > curr_board->len) {
            printf("Error, a number out of range (0,%d)!\n", curr_board->len);
            return;
        }
        else{
            fill_board_random(x);
            solver_ILP();
            clear_cells_random(y);

        }} else{
        printf("This command is available only in Edit mode!\n");
        return;
    }
}


void board_set(int x, int y, int z) {
    int *command_data = malloc(sizeof(int) * 3);
    cell cell_data;
    if (state != Solve && state != Edit) {
        printf("set only available in solve or edit mode\n");
        return;
    }
    if (x < 1 || y < 1 || z < 0) {
        printf("Error, a number out of range (1,%d)!\n", curr_board->len);
        return;
    } else if (x > curr_board->len || y > curr_board->len || z > curr_board->len) {
        printf("Error, a number out of range (1,%d)!\n", curr_board->len);
        return;
    } else if (curr_board->board[y][x].is_fixed) {
        printf("This position is fixed!\n");
        return;
    } else {
        command_data[0] = x-1;
        command_data[1] = y-1;
        command_data[2] = z;
        cell_data = curr_board->board[y - 1][x - 1];
        if(!is_valid_set(y-1,x-1,z)){
            curr_board->board[y-1][x-1].is_erroneous = 1;
        }
        curr_board->board[y-1][x-1].value = z;
        insert_to_undo_lst(5, command_data, cell_data);
        clear_list(redo_head);
    }
}


void guess(double x){
    if(state != Solve){
        printf("This command is only available in Solve mode\n");
        return;
    } else {
        if (check_erroneous_board()){
            printf("The board is erroneous\n");
            return;
        } else{
            solver_LP();
            //TODO complete
        }
    }
}


void hint(int x, int y){
    if(state != Solve){
        printf("This command is only available in Solve mode\n");
        return;
    } else {
        if (x < 1 || y < 1) {
            printf("Error, a number out of range (1,%d)!\n", curr_board->len);
            return;
        } else if (x > curr_board->len || y > curr_board->len) {
            printf("Error, a number out of range (1,%d)!\n", curr_board->len);
            return;
        }else if(check_erroneous_board()){
            printf("The board is erroneous\n");
        }else if (curr_board->board[y][x].is_fixed) {
            printf("This position is fixed!\n");
            return;
        } else if (curr_board->board[y][x].value != 0){
            printf("This position already has a value!\n");
            return;
        } else{
            if(solver_ILP() == 0){ //unsolvable TODO - needs to run on a copy of the bord so it wont be filled?
                printf("This board is unsolvable!\n");
                return;
            } else{
                //TODO return the value of board[y][x] from the ILP solver
            }
        }
    }
}

/*
 * !! Remember to check if x and y are numbers, and if they are in the range
 * */
void guess_hint(int x, int y){
    if(state != Solve){
        printf("This command is only available in Solve mode\n");
        return;
    } else {
        if (x < 1 || y < 1) {
            printf("Error, a number out of range (1,%d)!\n", curr_board->len);
            return;
        } else if (x > curr_board->len || y > curr_board->len) {
            printf("Error, a number out of range (1,%d)!\n", curr_board->len);
            return;
        }else if(check_erroneous_board()){
            printf("The board is erroneous\n");
        }else if (curr_board->board[y][x].is_fixed) {
            printf("This position is fixed!\n");
            return;
        } else if (curr_board->board[y][x].value != 0){
            printf("This position already has a value!\n");
            return;
        } else{
            if(solver_LP() == 0){ //unsolvable TODO - needs to run on a copy of the bord so it wont be filled?
                printf("This board is unsolvable!\n");
                return;
            } else{
                //TODO print all the legal values for board[y][x] from the LP solver that >0 (bigger than)
            }
        }
    }
}

int validate(){
    if(state!=Solve && state != Edit){
        printf("validate only available in solve or edit mode\n");
        return 0;
    }
    int is_valid = 1;
    if(is_valid){
        printf("Validation passed: board is solvable\n");
        return 1;
    }
    else{

        printf("Validation failed: board is unsolvable\n");
        return 0;
    }
}

long num_solutions(){
    if(state!=Solve && state != Edit){
        printf("num_solutions only available in solve or edit mode\n");
        return -1;
    }
    int i=1;
    long count = 0;
    int row=0,col=0;
    int temp = 0;

    if(!is_valid_board())
        return 0;

    if(!find_empty_cell(&row,&col, curr_board->board)){
        return 1;
    }
    for(;i<=curr_board->len;i++){
        temp = curr_board->board[row][col].value;
        curr_board->board[row][col].value = i;
        count += num_solutions();
        curr_board->board[row][col].value = temp;
    }
    return count;
}

void autofill(){
    int i,j;
    if (state == Solve) {
        if(check_erroneous_board()){
            printf("The board is erroneous\n");
            return;
        }
        int *command_data = malloc(sizeof(int) * 3);
        cell cell_data = {0,0,0,0, NULL};
        for (i = 0; i < curr_board->len ; ++i) {
            for (j = 0; j < curr_board->len ; ++j) {
                if (curr_board->board[i][j].list_poss_values_len==1){
                    command_data[0] = i;
                    command_data[1] = j;
                    command_data[2] = curr_board->board[i][j].value;
                    cell_data = curr_board->board[i][j];
                    curr_board->board[i][j].value = curr_board->board[i][j].list_poss_values[0];
                    printf("single possible value for <%d,%d> updated: %d\n",i,j,curr_board->board[i][j].value);
                    undo_head = insert(undo_head, 15, command_data, cell_data);
                }
            }
        }
        undo_head = insert(undo_head, -1, command_data, cell_data);
        clear_list(redo_head);
    } else {
        printf("This command is only available in Solve or Edit mode\n");
        return;
    }
}



void create_board(int len) {
    curr_board = (struct curr_board *) calloc(len, sizeof(struct cell));
    curr_board->len = len;
    curr_board->mark_errors = 1;
    calc_block_size(len);
    curr_board->board = (struct cell **) calloc(len, sizeof(struct cell *));
    for (int i = 0; i < len; ++i) {
        curr_board->board[i] = (struct cell *) calloc(len, sizeof(struct cell));
    }
}
