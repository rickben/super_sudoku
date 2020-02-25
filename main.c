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
    state = Solve;
    trans_file_to_board("C:\\Users\\Ricky Benkovich\\CLionProjects\\super_sudoku\\dog.txt");
    trans_board_to_file("C:\\Users\\Ricky Benkovich\\CLionProjects\\super_sudoku\\ricky.txt");
    printf("%d",curr_board->board[0][0].is_fixed);
}
