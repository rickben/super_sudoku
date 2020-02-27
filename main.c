#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Parser.h"
#include "SPBufferset.h"
#include "MainAux.h"




int main(int argc, char* argv[]) {
    int flag = 1;
    state = Init;
    print_start_program();
    while (flag){
        interpret_command();
    }
}
