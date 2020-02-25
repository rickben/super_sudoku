#include "Game.h"
#include "MainAux.h"
#include <stdlib.h>



int open_new_file(){

}
int close_all_files(){

}


void free_mem_board() {
    int i=0;
    for(i=0; i<curr_board->len; i++)
        free(curr_board->board[i]);

    free(curr_board->board);
    free(curr_board);
}

int trans_board_to_file(char* file_name){
    int i, j;
    if(state == Solve) {
        FILE *in_file = fopen(file_name, "w");
        fprintf(in_file, "%d %d\n", curr_board->block_width, curr_board->block_height);
        for (i = 0; i < curr_board->block_height; i++) {
            for (j = 0; j < curr_board->block_width; j++) {
                fprintf(in_file, "%d", curr_board->board[i][j]);
                if (is_fixed(i, j) && curr_board->board[i][j]!=0) {
                    fprintf(in_file, ".");
                }
                fprintf(in_file, " ");
            }
            fprintf(in_file, "\n");
        }
        fclose(in_file);
        free_mem_board();
        return 1;
    }
    if(!validate_board()){
        printf("board isn't valid!\n");
        return 0;
    }
    else {
        if(state == Edit) {
            FILE *in_file = fopen(file_name, "w");
            fprintf(in_file, "%d %d\n", curr_board->block_width, curr_board->block_height);
            for (i = 0; i < curr_board->block_height; i++) {
                for (j = 0; j < curr_board->block_width; j++) {
                    fprintf(in_file, "%d", curr_board->board[i][j]);
                    if(curr_board->board[i][j]!=0) {
                        fprintf(in_file, ". ");
                    }
                    else{
                        fprintf(in_file, " ");
                    }
                }
                fprintf(in_file, "\n");
            }
            fclose(in_file);
            free_mem_board();
        }
    }
}


void create_board_from_file(int len, int width, int height) {
    curr_board = (struct curr_board *) calloc(len, sizeof(int));
    curr_board->block_width = width;
    curr_board->block_height = height;
    curr_board->len = len ;
    curr_board->board = (int **) calloc(len, sizeof(int *));
    for (int i = 0; i < len; ++i) {
        curr_board->board[i] = (int *) calloc(len, sizeof(int));
    }
}

int scan_size_from_file(FILE* in_file){
    int height, width, len;

    if(fscanf(in_file, "%d %d", &width, &height) != 2 )
    {
        printf("oops, error in scanning size\n");
        return 0;
    }
    if( height < 1 || width<1){
        printf("oops, size smaller than 1\n");
    }
    else{
        len = (height)*(width);
        create_board_from_file(len, width, height);
    }
    return 1;
}


int scan_rows_from_file(FILE *in_file) {
    int i,j;
    for(i=0; i<curr_board->block_height; i++)
        for(j=0; j<curr_board->block_width; j++)
            if(fscanf(in_file, "%d", &curr_board->board[i][j]) != 1)
                return 0;
    return 1;
}

int trans_file_to_board(char* file_name){
    FILE* in_file = fopen(file_name, "r");
    if (! in_file )
    {
        printf("oops, file can't be read\n");
        return 0;
    }

    if(! scan_size_from_file(in_file) ){
        return 0;
    }

    if(! scan_rows_from_file(in_file)){
        return 0;
    }

    fclose(in_file);

    return 1;
}


int save_file(){

}



