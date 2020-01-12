#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Parser.h"
#include "Solver.h"
#include "SPBufferset.h"




int main(int argc, char* argv[]) {
    int is_last_command = 0;
    int flag=1;
    int H;
    int seed = atoi(argv[argc-1]);
    srand(seed);
    H = get_hint_size();
    if(H==-1){
        return 0;
    }

    if(!game_restart(H)){
        return 0;
    }

    while(flag){
        while(!board.is_game_over&&!board.is_exit){
            if(read_user_commands(is_last_command)){
                board_print();
            }
            check_if_board_solved();}
        if(board.is_exit){
            board_destroy();
            flag=0;
        } else if(board.is_game_over){
            is_last_command = 1;
            read_user_commands(is_last_command);
            if(board.is_exit) {
                board_destroy();
                flag=0;
            }
        }
    }
    return (0);
}
