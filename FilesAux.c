
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
        printf("Error: file can't be read\n");
        return 0;
    }
    fprintf(in_file, "%d %d\n", curr_board->block_width, curr_board->block_height);
    for (i = 0; i < curr_board->len; i++) {
        for (j = 0; j < curr_board->len; j++) {
            fprintf(in_file, "%d", curr_board->board[i][j].value);
            if (curr_board->board[i][j].is_fixed!=0 && curr_board->board[i][j].value!=0) {
                fprintf(in_file, ".");
            }
            fprintf(in_file, " ");
        }
        fprintf(in_file, "\n");
    }
    fclose(in_file);
    free_mem_board();
    clear_list(end_list);
    end_list = NULL;
    start_list = NULL;
    state = Init;
    return 1;
}
int edit_mode_to_file(char* file_name) {
    int i,j;
    FILE *in_file = fopen(file_name, "w");
    if (! in_file ){
        printf("Error: file can't be read\n");
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
    clear_list(end_list);
    end_list = NULL;
    start_list = NULL;
    state = Init;
    return 1;
}

int trans_board_to_file(char* file_name){
    if(state == Solve) {
        return solve_mode_to_file(file_name);
    } else if(state == Edit && check_erroneous_board()){
        printf("Error: Erroneous board cannot be saved in Edit mode!\n");
        return 0;
    }
    else if(!check_validate() && state == Edit){
        printf("Error: Board without a solution cannot be saved in Edit mode!\n");
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
    if (curr_board == NULL) {
        memory_error("calloc");
    }
    curr_board->block_width = width;
    curr_board->block_height = height;
    curr_board->len = len ;
    curr_board->board = (struct cell **) calloc(len, sizeof(struct cell *));
    if (curr_board->board == NULL) {
        memory_error("calloc");
    }
    for (i = 0; i < len; ++i) {
        curr_board->board[i] = (struct cell *) calloc(len, sizeof(struct cell));
        if (curr_board->board[i] == NULL) {
            memory_error("calloc");
        }
    }
}
void create_temporary_board_from_file(int len, int width, int height) {
    int i;
    temporary_board = (struct curr_board *) calloc(len, sizeof(struct cell));
    if (temporary_board == NULL) {
        memory_error("calloc");
    }
    temporary_board->block_width = width;
    temporary_board->block_height = height;
    temporary_board->len = len ;
    temporary_board->board = (struct cell **) calloc(len, sizeof(struct cell *));
    if (temporary_board->board == NULL) {
        memory_error("calloc");
    }
    for (i = 0; i < len; ++i) {
        temporary_board->board[i] = (struct cell *) calloc(len, sizeof(struct cell));
        if (temporary_board->board[i] == NULL) {
            memory_error("calloc");
        }
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

    if(fscanf(in_file, "%d %d", &height, &width) != 2 )
    {
        printf("Error: error in scanning size\n");
        return 0;
    }
    if( height < 1 || width<1){
        printf("Error: size smaller than 1\n");
        return 0;
    }
    else{
        len = (height)*(width);
        len = (height)*(width);
        create_temporary_board_from_file(len, width, height);
    }
    return 1;
}

/*
 * TODO need to change - to fgets, to check if the file in the right format
 * */
int scan_rows_from_file(FILE *in_file, enum state State) {
    int i,j;
    int c;
    for(i=0; i<temporary_board->len; i++) {

        for (j = 0; j < temporary_board->len; j++) {

            if (fscanf(in_file, "%d", &temporary_board->board[i][j].value) != 1) {
                return 0;
            } else{
                if (temporary_board->board[i][j].value < 0 ||
                    temporary_board->board[i][j].value > temporary_board->len){
                    printf("Error: a number out of range (1,%d) in file!\n",temporary_board->len);
                }
                if (temporary_board->board[i][j].value != 0) {
                    temporary_board->board[i][j].is_fixed = 0;
                }
            }
            if ((fgetc(in_file))=='.' && State == Solve && temporary_board->board[i][j].value != 0){
                    temporary_board->board[i][j].is_fixed = 1;
            }
        }

    }

    /*return 0 if there is anything else written if the file*/
    while ((c=fgetc(in_file))!=EOF){
        if(c>=33&&c<=126) {
            return 0;
        }
    }
    return 1;

}


/*
 * Return false if there's a cell in the same row
 * with the same value, otherwise, returns true
 * */
int in_row_fixed(int row, int num) {
    int j;
    for (j = 0; j < temporary_board->len; ++j) {
        if (temporary_board->board[row][j].value == num && temporary_board->board[row][j].is_fixed) {
            if(num!=0) {
                return 1;
            }
            else{
                return 0;
            }
        }
    }
    return 0;
}

/*
 * Return false if there's a cell in the same column
 * with the same value, otherwise, returns true
 * */
int in_col_fixed(int col, int num) {
    int j;
    for (j = 0; j < temporary_board->len; ++j) {
        if (temporary_board->board[j][col].value == num && temporary_board->board[j][col].is_fixed) {
            if (num != 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

/*
 * Return false if there's a cell in the same block
 * with the same value, otherwise, returns true
 * */
int in_block_fixed(int x, int y, int num) {
    int i, j;
    for (i = 0; i < temporary_board->block_height; ++i) {
        for (j = 0; j < temporary_board->block_width; ++j) {
            if (temporary_board->board[i+x][j+y].value == num && temporary_board->board[i+x][j+y].is_fixed) {
                if(num!=0) {
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
    }
    return 0;
}


int is_valid_fixed_set(int i, int j, int num){
    int block_x = (i / (temporary_board->block_height))*(temporary_board->block_height);
    int block_y = (j / (temporary_board->block_width))*(temporary_board->block_width);
    return (!in_row_fixed(i,num) && !in_col_fixed(j,num) &&
            !in_block_fixed(block_x,block_y,num));
}

int check_erroneous_fixed_cells_temp(){
    int i,j,num;
    for (i = 0; i < temporary_board->len ; ++i) {
        for (j = 0; j < temporary_board->len; ++j) {
            if (temporary_board->board[i][j].is_fixed){
                num = temporary_board->board[i][j].value;
                temporary_board->board[i][j].value = 0;
                if (!is_valid_fixed_set(i,j,num)){
                    temporary_board->board[i][j].value = num;
                    return 0;
                }else{
                    temporary_board->board[i][j].value = num;
                }
            }
        }
    }
    return 1;
}


int trans_file_to_board(char* file_name, enum state State){
    FILE* in_file = fopen(file_name, "r");
    if (! in_file )
    {
        printf("Error: file can't be read\n");
        return 0;
    }

    if(! scan_size_from_file(in_file) ){
        fclose(in_file);
        return 0;
    }

    if(! scan_rows_from_file(in_file, State)){
        printf("Error: File's board is not in a correct format\n");
        free_temporary_board();
        fclose(in_file);
        return 0;
    }
    if(! check_erroneous_fixed_cells_temp()){
        printf("Error: File's board is not legal - erroneous fixed cells\n");
        free_temporary_board();
        fclose(in_file);
        return 0;
    }
    if(state!=Init){
        free_mem_board();
        clear_list(end_list);
        end_list = NULL;
        start_list = NULL;
    }
    state = State;
    copy_from_temporary_to_curr_board();
    free_temporary_board();
    update_erroneous_cells();
    fclose(in_file);
    init_start_list();
    return 1;
}




