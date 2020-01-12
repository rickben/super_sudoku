#include <stdlib.h>
#include "Solver.h"

struct my_tuple {
    int len;
    int* possible_numbers;
};

int* get_random_val_valid(int *pos_numbers) {
    int real_len;
    int *result;
    int *real_arr;
    int i = 0;
    int j = 0;
    int index;
    result = (int *) malloc(2 * sizeof(int));
    if(result!=NULL){
        real_len = number_of_non_empty_vars(pos_numbers);
        real_arr = (int *) calloc(real_len,  sizeof(int));

        if(real_arr!=NULL){
            if (real_len > 1) {
                index = rand() % real_len;
                for (; i < BOARD_LEN; i++) {
                    if (pos_numbers[i] != 0) {
                        real_arr[j] = pos_numbers[i];
                        if(j==index){
                            result[0]=i;
                        }
                        j++;
                    }
                }
                result[1] = real_arr[index];
            }
            else{
                result[1]=real_arr[0];
                for(i=0;i<BOARD_LEN;i++){
                    if(pos_numbers[i]==real_arr[0]){
                        result[0]=i;
                        return result;
                    }
                }
        }
        free(real_arr);
        }
    }
    else{
        printf("Error: malloc has failed\n");
    }
    return result;
}


/*
 * Gets position <x,y< on the board from which to do the backtracking
 * */
bool determ_backtrack() {
    int row1;
    int col1;
    int num;

    if(find_empty_cell(&row1, &col1,solution.board_game) == 0)
        return true;
    for(num=1;num<=BOARD_LEN;num++)
    {

        if(is_valid_set(row1, col1, num, solution.board_game))
        {
            solution.board_game[row1][col1] = num;
            if(determ_backtrack())
                return true;
            solution.board_game[row1][col1]=EMPTY;
        }
    }
    return false;
}

void init_pos_numbers(int x, int y, int *pos_numbers) {
    int i=0;
    for(;i<BOARD_LEN;i++){
        pos_numbers[i]=i+1;
    }
    i=0;
    for(;i<BOARD_LEN;i++){
        if(!is_valid_set(x, y, pos_numbers[i], board.board_game))
            pos_numbers[i]=0;
    }
}

bool random_backtrack() {
    int x,y;
    int len;
    int index = -1;
    int ind=0;
    int* rand_val;
    int* pos_numbers = (int*)calloc(BOARD_LEN , sizeof(int));
    if(find_empty_cell(&x, &y, board.board_game) ==false){
        free(pos_numbers);
        return true;
    }
    init_pos_numbers(x,y,pos_numbers);
    len = number_of_non_empty_vars(pos_numbers);
    if(len==1){
        ind=0;
        for(;ind<BOARD_LEN;ind++){
            if(pos_numbers[ind]!=0){
                board.board_game[x][y] = pos_numbers[ind];
                pos_numbers[ind]=0;
                len=0;
                break;
            }
        }
        if(random_backtrack()){
            free(pos_numbers);
            return true;
        }
    }
    if(len>1){
        while(number_of_non_empty_vars(pos_numbers)>0){
            if(number_of_non_empty_vars(pos_numbers)==1){
                ind=0;
                for(;ind<BOARD_LEN;ind++){
                    if(pos_numbers[ind]!=0){
                        board.board_game[x][y] = pos_numbers[ind];
                        pos_numbers[ind]=0;
                        break;
                    }
                }
                if(random_backtrack()){
                    free(pos_numbers);
                    return true;
                }
            }
            else{
                rand_val=get_random_val_valid(pos_numbers);
                if(is_valid_set(x, y, rand_val[1], board.board_game)){
                    board.board_game[x][y] = rand_val[1];
                    index=rand_val[0];
                    pos_numbers[index]=0;
                    if(random_backtrack()){
                        free(rand_val);
                        free(pos_numbers);
                        return true;
                    }
                    else{
                        free(rand_val);
                    }
                }
                else{
                    pos_numbers[index] = 0;
                }

            }
        }
    }
    if (number_of_non_empty_vars(pos_numbers)==0){
        board.board_game[prev_x(x,y)][prev_y(y)] = EMPTY;
    }
    free(pos_numbers);
    return false;
}
