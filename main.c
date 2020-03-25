#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Parser.h"
#include "SPBufferset.h"
#include "MainAux.h"
#include "Stack.h"
#include "FilesAux.h"
#include "Solver.h"


int main(int argc, char* argv[]) {
    srand(time(0));
    /*
    int flag = 1;
    int seed = atoi(argv[argc-1]);
    state = Init;
    srand(seed);
    print_start_program();
    while (flag){
        printf("Please enter a command:\n");
        interpret_command();
        if(state == Solve){
            if(check_board_solved()){
                if(check_erroneous_board()){
                    printf("The solution is erroneous!\n");
                }
                else{
                    printf("The puzzle was solved successfully!\n");
                    restart_to_init();
                }
            }
        } else if (state == Edit){
        }
    }*/
}
