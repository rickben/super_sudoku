#include "Game.h"
#include "MainAux.h"


enum state{Init, Edit, Solve, Terminate};
enum state state;

void my_exit(){
    state =  Terminate;
    printf("Exiting...\n");
    ///TODO release memory
}


