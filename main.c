#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Parser.h"
#include "SPBufferset.h"
#include "MainAux.h"
#include "List.h"
#include "Solver.h"
#include "Stack.h"
#include "FilesAux.h"
#include "Solver.h"

int main() {
    srand(time(0));
    state = Init;
    global_mark_errors = 1;
    print_start_program();
    while (1){
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
    } 
    return 0;
}
