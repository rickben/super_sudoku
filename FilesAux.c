#include "Game.h"
#include "MainAux.h"
#include <stdlib.h>



void free_mem_board() {
    int i;
    for(i=0; i<curr_board->len; i++) {
        free(curr_board->board[i]);
    }
    free(curr_board->board);
    free(curr_board);
}

int solve_mode_to_file(char* file_name){
    int i,j;
    FILE *in_file = fopen(file_name, "w");
    if (! in_file ){
        printf("oops, file can't be read\n");
        return 0;
    }
    fprintf(in_file, "%d %d\n", curr_board->block_width, curr_board->block_height);
    for (i = 0; i < curr_board->len; i++) {
        for (j = 0; j < curr_board->len; j++) {
            fprintf(in_file, "%d", curr_board->board[i][j].value);
            if (curr_board->board[i][j].is_fixed!=0 && curr_board->board[i][j].value!=0) {
                fprintf(in_file, ".");
            }
            else if (curr_board->board[i][j].is_erroneous!=0 && curr_board->board[i][j].value!=0) {
                fprintf(in_file, "*");
            }
            fprintf(in_file, " ");
        }
        fprintf(in_file, "\n");
    }
    fclose(in_file);
    free_mem_board();
    state = Init;
    return 1;
}
int edit_mode_to_file(char* file_name) {
    int i,j;
    FILE *in_file = fopen(file_name, "w");
    if (! in_file ){
        printf("oops, file can't be read\n");
        return 0;
    }
        fprintf(in_file, "%d %d\n", curr_board->block_width, curr_board->block_height);
    for (i = 0; i < curr_board->len; i++) {
        for (j = 0; j < curr_board->len; j++) {
            fprintf(in_file, "%d", curr_board->board[i][j].value);
            if (curr_board->board[i][j].value != 0) {
                fprintf(in_file, ". ");
            } else {
                fprintf(in_file, " ");
            }
        }
        fprintf(in_file, "\n");
    }
    fclose(in_file);
    free_mem_board();
    state = Init;
    return 1;
}

int trans_board_to_file(char* file_name){
    if(state == Solve) {
        return solve_mode_to_file(file_name);
    } else if(state == Edit && check_erroneous_board()){
        printf("Erroneous board cannot be saved!\n");
        return 0;
    }
    else if(!validate() && state == Edit){
        printf("Invalid board cannot be saved!\n");
        return 0;
    }
    else {
        if(state == Edit) {
            return edit_mode_to_file(file_name);
        }
    }
    return 0;
}


void create_board_from_file(int len, int width, int height) {
    int i;
    curr_board = (struct curr_board *) calloc(len, sizeof(struct cell));
    curr_board->block_width = width;
    curr_board->block_height = height;
    curr_board->len = len ;
    curr_board->mark_errors = 1;
    curr_board->board = (struct cell **) calloc(len, sizeof(struct cell *));
    for (i = 0; i < len; ++i) {
        curr_board->board[i] = (struct cell *) calloc(len, sizeof(struct cell));
    }
}
void create_temporary_board_from_file(int len, int width, int height) {
    int i;
    temporary_board = (struct curr_board *) calloc(len, sizeof(struct cell));
    temporary_board->block_width = width;
    temporary_board->block_height = height;
    temporary_board->len = len ;
    temporary_board->mark_errors = 1;
    temporary_board->board = (struct cell **) calloc(len, sizeof(struct cell *));
    for (i = 0; i < len; ++i) {
        temporary_board->board[i] = (struct cell *) calloc(len, sizeof(struct cell));
    }
}

void copy_from_temporary_to_curr_board(){
    int i,j;
    create_board_from_file(temporary_board->len, temporary_board->block_width, temporary_board->block_height);
    for (i=0;i<temporary_board->len;i++){
        for (j=0;j<temporary_board->len;j++){
            curr_board->board[i][j].is_fixed = temporary_board->board[i][j].is_fixed;
            curr_board->board[i][j].value = temporary_board->board[i][j].value;
            curr_board->board[i][j].is_erroneous = temporary_board->board[i][j].is_erroneous;
            curr_board->board[i][j].list_poss_values = temporary_board->board[i][j].list_poss_values;
            curr_board->board[i][j].list_poss_values_len = temporary_board->board[i][j].list_poss_values_len;
        }
    }
}

void free_temporary_board(){
    int i;
    for (i = 0; i < temporary_board->len; ++i)
        free(temporary_board->board[i]);
    free(temporary_board);
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
        return 0;
    }
    else{
        len = (height)*(width);
        create_temporary_board_from_file(len, width, height);
    }
    return 1;
}

/*
 * TODO need to change - to fgets, to check if the file in the right format
 * */
int scan_rows_from_file(FILE *in_file) {
    int i,j;
    char c;
    for(i=0; i<temporary_board->len; i++) {

        for (j = 0; j < temporary_board->len; j++) {

            if (fscanf(in_file, "%d", &temporary_board->board[i][j].value) != 1) {
                return 0;
            } else{
                if (temporary_board->board[i][j].value != 0) {
                    temporary_board->board[i][j].is_fixed = 0;
                }
            }
            if (fscanf(in_file,"%c",&c)) {
                if (c == '.' && state == Solve) {
                    temporary_board->board[i][j].is_fixed = 1;
                } else if (c == '*') {
                    temporary_board->board[i][j].is_erroneous = 1;
                }
            }
        }

    }
    /*return 0 if there is anything else written if the file*/
    if (fscanf(in_file,"%c",&c))
        if(c>=33&&c<=126) {
            printf("this is c:%c",c);
            return 0;
        }
    return 1;

}

int trans_file_to_board(char* file_name, enum state State){
    FILE* in_file = fopen(file_name, "r");
    if (! in_file )
    {
        printf("oops, file can't be read\n");
        return 0;
    }
    state = State;
    if(! scan_size_from_file(in_file) ){
        printf("File not in correct format\n");
        return 0;
    }

    if(! scan_rows_from_file(in_file)){
        printf("File not in correct format\n");
        return 0;
    }

    copy_from_temporary_to_curr_board();
    free_temporary_board();

    fclose(in_file);

    return 1;
}




