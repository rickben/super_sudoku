#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "Parser.h"
#include "Solver.h"
#include "SPBufferset.h"
#include "MainAux.h"
#include "FilesAux.h"




int main(int argc, char* argv[]) {
    state = Edit;
    trans_file_to_board("C:\\Users\\User\\CLionProjects\\super_sudoku\\dog.txt");
    while(1){
        interpret_command();
        printf("%d" ,last_cmd->command_code);
    }
}
