#include "Game.h"
#include "ListActions.h"
#include "MainAux.h"

enum state{Init, Edit, Solve, Terminate};
enum state state;
Node* last_cmd;

void my_exit(){
    state =  Terminate;
    printf("Exiting...\n");
    ///TODO release memory
}

void undo(){

}

void redo(Node* current_cmd){
}

void reset(){

}

void set(int x, int y, int z){
    curr_board->board[x][y] = z;
    insert(last_cmd, "set");/*change char*/
    last_cmd = last_cmd->next;

}

void hint(int x, int y){
}

void guess_hint(int x, int y){
}

void validate(){
    int is_valid = 1;
    if(is_valid){
        printf("Validation passed: board is solvable\n");
    }
    else{

        printf("Validation failed: board is unsolvable\n");
    }
}

void num_solutions(){
}

void autofill(){
}


