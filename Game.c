#include "Game.h"
#include <stdlib.h>
#include "Solver.h"
#include "MainAux.h"


void board_print() {
    int i, j;
    for (i = 0; i < BOARD_LEN; i++) {
        if(i%BLOCK_LEN==0){
            separator_row();
        }
        for (j = 0; j < BOARD_LEN; j++) {
            if(j%BLOCK_LEN==0){
                if(j==0){
                    printf("|");}
                else{
                    printf(" |");
                }
            }
            if(board.board_game[i][j]==EMPTY){
                printf("   ");
            }
            else if(is_fixed(i,j)){
                printf(" .%d",board.board_game[i][j]);
            }
            else if(!is_fixed(i,j)){
                printf("  %d",board.board_game[i][j]);
            }

        }
        printf(" |\n");
    }
    separator_row();
}



int board_set(int i, int j, int value) {
    if(is_fixed(i,j)){
        printf("Error: cell is fixed\n");
    }
    else
    {
        if(!is_valid_set(i, j, value, board.board_game)){
            printf("Error: value is invalid\n");
        }
        else{
            board.board_game[i][j] = value;
            return 1;
        }
    }
    return 0;
}


void board_validate() {
    int num1,num2;
    for (num1=0; num1<BOARD_LEN; num1++)
        for (num2=0; num2<BOARD_LEN; num2++)
            solution.board_game[num1][num2] = board.board_game[num1][num2];
    if(determ_backtrack()){
        printf("Validation passed: board is solvable\n");
    }
    else{
        printf("Validation failed: board is unsolvable\n");
    }
}


void board_hint(int x ,int y){
    printf("Hint: set cell to %d\n", solution.board_game[x][y]);
}
/*
 * We need to find the value to the position <i,j>
 * by backtracking!!!
 * */
int board_create() {
    int i,j;
    int valid=1;
    board.is_game_over=0;
    board.is_exit=0;
    board.board_game = (int**)malloc(BOARD_LEN * sizeof(int *));
    if(board.board_game){
        for(i = 0; i < BOARD_LEN; ++i){
            board.board_game[ i ] = (int *) malloc(BOARD_LEN * sizeof(int));
            if(!board.board_game){
                valid=0;
            }
        }
        if(valid){
            for(i = 0; i < BOARD_LEN; ++i){
                for (j=0; j< BOARD_LEN; ++j){
                    board.board_game[i][j]=EMPTY;
                }
            }
        }
    }
    else{
        printf("Error: malloc has failed\n");
        board.is_exit=1;
        return 0;
    }
    return 1;
}

int solution_create(){
    int i,j;
    int valid=1;
    solution.board_game = (int**)malloc(BOARD_LEN * sizeof(int *));
    if(solution.board_game){
        for(i = 0; i < BOARD_LEN; ++i){
            solution.board_game[ i ] = (int *) malloc(BOARD_LEN * sizeof(int));
            if(!solution.board_game){
                valid=0;
            }
        }
        if(valid){
            for(i = 0; i < BOARD_LEN; ++i){
                for (j=0; j< BOARD_LEN; ++j){
                    solution.board_game[i][j]=board.board_game[i][j];
                }
            }
        }
    }
    else{
        printf("Error: malloc has failed\n");
        board.is_exit=1;
        return 0;
    }
    return 1;
}

int fixed_create() {
    int i,j;
    int valid=1;
    board_fixed.board_game = (int**)malloc(BOARD_LEN * sizeof(int *));
    if(board_fixed.board_game){
        for(i = 0; i < BOARD_LEN; ++i){
            board_fixed.board_game[ i ] = (int *) malloc(BOARD_LEN * sizeof(int));
            if(!board_fixed.board_game){
                valid=0;
            }
        }
        if(valid){
            for(i = 0; i < BOARD_LEN; ++i){
                for (j=0; j< BOARD_LEN; ++j){
                    board_fixed.board_game[i][j]=EMPTY;
                }
            }
        }
    }
    else{
        printf("Error: malloc has failed\n");
        board.is_exit=1;
        return 0;
    }
    return 1;
}

void board_update() {
    int i, j;
    for (i = 0; i < BOARD_LEN; ++i) {
        for (j = 0; j < BOARD_LEN; ++j) {
            board.board_game[i][j] = board_fixed.board_game[i][j];
        }
    }
}

void board_destroy() {
    int i;
    for(i = 0; i < BOARD_LEN; ++i) {
        free(board.board_game[i]);
        free(solution.board_game[i]);
        free(board_fixed.board_game[i]);
    }
    free(board.board_game);
    free(solution.board_game);
    free(board_fixed.board_game);
}


void start_over() {
    int H;
    board_destroy();
    H= get_hint_size();
    game_restart(H);
}


int board_restart(int H) {
    int t = 81-H;
    if(!board_create()){
        return 0;
    }
    random_backtrack();
    if(!fixed_create()){
        free(board.board_game);
        return 0;
    }

    while(t > 0){
        int y_rand = rand()%BOARD_LEN;
        int x_rand = rand()%BOARD_LEN;
        if(board_fixed.board_game[x_rand][y_rand]==EMPTY){
            board_fixed.board_game[x_rand][y_rand]=board.board_game[x_rand][y_rand];
            t--;
        }
    }
    board_update();
    if(!solution_create()){
        free(board.board_game);
        free(board_fixed.board_game);
        return 0;
    }
    determ_backtrack(solution.board_game);
    return 1;
}

void board_exit() {
    board.is_exit=1;
    print_exit_game();
}



int game_restart(int H) {
    if(!board_restart(H)){
        return 0;
    }
    fgetc(stdin);
    board_print();
    return 1;
}

void check_if_board_solved() {
    int row1;
    int col1;
    if(find_empty_cell(&row1,&col1,board.board_game)==false){
        board_solved();
    }
}
