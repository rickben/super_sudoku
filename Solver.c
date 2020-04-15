#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "List.h"
#include "gurobi_c.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "Solver.h"
#include "gurobi_c.h"
#define EMPTY 0
#define DIF -1

int DIM;
int height;
int width;
int       flag,flag_guess;
double    num,sum,start;
GRBenv   *env   = NULL;
GRBmodel *model = NULL;
double    sol;
double   *all_poss_scores;
int       var_size, res;
int      *ind_save;
int      *ind;
int	const_size;
double   *val;
double   *obj;
double   *lb;
double   *ub;
char     *vtype;
char     **names;
char      *namestorage;
char     *cursor;
int       optimstatus;
double    objval;
int       i, j, v, ig, jg, count;
int       error = 0;

/* change for push*/


/*
 * Return false if there's a cell in the same row
 * with the same value, otherwise, returns true
 * */
int in_row_gurobi(int row, int num) {
    int j;
    for (j = 0; j < DIM; ++j) {
        if (board[row][j].value == num) {
            return 1;
        }
    }
    return 0;
}

/*
 * Return false if there's a cell in the same column
 * with the same value, otherwise, returns true
 * */
int in_col_gurobi(int col, int num) {
    int j;
    for (j = 0; j < DIM; ++j) {
        if (board[j][col].value == num) {
            return 1;
        }
    }
    return 0;
}

/*
 * Return false if there's a cell in the same block
 * with the same value, otherwise, returns true
 * */
int in_block_gurobi(int x, int y, int num) {
    int i, j;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            if (board[i+x][j+y].value == num) {
                return 1;
            }
        }
    }
    return 0;
}


int is_valid_set_gurobi(int x, int y, int num) {
    int block_x = (x / (height))*(height);
    int block_y = (y / (width))*(width);
    return (!in_row_gurobi(x,num) && !in_col_gurobi(y,num) &&
            !in_block_gurobi(block_x,block_y,num));
}


int check_num_var(){
    int i,j,v;
    int count = 0;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 0; v < DIM; v++) {
                if (board[i][j].value == EMPTY && is_valid_set_gurobi(i,j,v+1)){
                    count++;
                }
            }}}
    return count;
}





void create_empty_model(int is_LP){
    count = 0;
    cursor = namestorage;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 0; v < DIM; v++) {
                if (board[i][j].value == EMPTY && is_valid_set_gurobi(i,j,v+1)){ /* valid_set: v not in row, col, block*/
                    lb[count] = 0;
                    ub[count] = 1;
                    obj[count] = is_LP ? (rand() % DIM + 1) : 0;
                    vtype[count] = is_LP ? GRB_CONTINUOUS : GRB_BINARY;
                    ind_save[i*DIM*DIM+j*DIM+v] = count ;
                    names[count] = cursor;
                    sprintf(names[count], "x[%d,%d,%d]", i, j, v+1);
                    cursor += strlen(names[count]) + 1;
                    count++;
                }
                else{
                    ind_save[i*DIM*DIM+j*DIM+v] = DIF;
                }
            }
        }
    }
}

int create_env(){
    error = GRBloadenv(&env, "sudoku.log");
    return error;
}

int remove_log_to_console(){
    error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
    return error;
}

int create_new_model(){
    error = GRBnewmodel(env, &model, "sudoku", var_size, obj , lb, ub,
                        vtype, names);
    return error;
}


/* Each cell gets a value */
int each_cell_value(){
    const_size = 0;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 0; v < DIM; v++) {
                if(ind_save[i*DIM*DIM+j*DIM+v]!= DIF){
                    ind[const_size] = ind_save[i*DIM*DIM+j*DIM+v];
                    val[const_size] = 1.0;
                    const_size++;
                }
            }
            if (const_size > 0){
                error = GRBaddconstr(model, const_size, ind, val, GRB_EQUAL, 1.0, NULL);
                if (error) return 1;
            }
            const_size = 0;
        }
    }
    return 0;
}

/* Each value must appear once in each row */

int each_row_value(){
    const_size = 0;
    for (v = 0; v < DIM; v++) {
        for (j = 0; j < DIM; j++) {
            for (i = 0; i < DIM; i++) {
                if(ind_save[i*DIM*DIM+j*DIM+v]!= DIF){
                    ind[const_size] = ind_save[i*DIM*DIM+j*DIM+v];
                    val[const_size] = 1.0;
                    const_size++;
                }
            }

            if (const_size > 0){
                error = GRBaddconstr(model, const_size, ind, val, GRB_EQUAL, 1.0, NULL);
                if (error) return 1;
            }
            const_size = 0;
        }
    }
    return 0;
}

/* Each value must appear once in each column */

int each_col_value(){
    const_size = 0;
    for (v = 0; v < DIM; v++) {
        for (i = 0; i < DIM; i++) {
            for (j = 0; j < DIM; j++) {
                if(ind_save[i*DIM*DIM+j*DIM+v] != DIF){
                    ind[const_size] = ind_save[i*DIM*DIM+j*DIM+v];
                    val[const_size] = 1.0;
                    const_size++;
                }
            }
            if (const_size > 0){
                error = GRBaddconstr(model, const_size, ind, val, GRB_EQUAL, 1.0, NULL);
                if (error) return 1;
            }
            const_size = 0;
        }
    }
    return 0;
}

/* Each value must appear once in each sub-grid */

int each_sub_grid_value(){
    for (v = 0; v < DIM; v++) {
        for (ig = 0; ig < width; ig++) {
            for (jg = 0; jg < height; jg++) {
                count = 0;
                for (i = ig*(height); i < (ig+1)*(height); i++) {
                    for (j = jg*(width); j < (jg+1)*(width); j++) {
                        if(ind_save[i*DIM*DIM+j*DIM+v]!= DIF){
                            ind[count] = ind_save[i*DIM*DIM+j*DIM+v];
                            val[count] = 1.0;
                            count++;
                        }
                    }
                }
                if (count > 0){
                    error = GRBaddconstr(model, count, ind, val, GRB_EQUAL, 1.0, NULL);
                    if (error) return 1;
                }
            }
        }
    }
    return 0;
}

int optimum_state_ilp(){
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 0; v < DIM; v++) {
                if (ind_save[i*DIM*DIM+j*DIM+v] != DIF){
                    error = GRBgetdblattrelement(model, "X", ind_save[i*DIM*DIM+j*DIM+v], &sol);
                    if ((int)sol == 1){
                        board[i][j].value = v+1;
                    }
                }
            }}}
    return error;
}

void set_guess_board(double thresholdX){
    count = 0;
    num = 0;
    sum = 0;
    start = 0;
    for (v = 0; v < DIM; ++v) {
        if (all_poss_scores[v] >= thresholdX) {
            sum += all_poss_scores[v];
        }
    }
    num = (((double) rand()) / RAND_MAX) * sum;
    for (v = 0; v < DIM; ++v) {
        if (all_poss_scores[v] >= thresholdX) {
            if ((num >= start && num < (start + all_poss_scores[v])) ) {
                board[i][j].value = v+1;
                break;
            } else if (((start + all_poss_scores[v]) == sum) ){
                board[i][j].value = v+1;
            }
            start += all_poss_scores[v];
        }
    }
}

int print_guess_hint_prob(){
    flag = 0;
    for (v = 0; v < DIM; ++v) {
        if (all_poss_scores[v] > 0){
            printf("value = %d : prob = %f\n",v+1,all_poss_scores[v]);
        }
    }
    return error;
}

void check_board_unsolvable_for_guess_hint(int is_guess_hint){
    if(is_guess_hint && flag == 0){
        printf("Error: This board is unsolvable!\n");
    }
}

void set_guess_prob(){
    all_poss_scores[v] = sol;
}

void set_guess_hint_prob(int x, int y){
    if (i == x && j == y){
        flag = 1;
        all_poss_scores[v] = sol;
    }
}

int optimum_state_lp(int is_guess, double thresholdX, int is_guess_hint, int x, int y){
    flag_guess = 1;
    flag = 0;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            for (v = 0; v < DIM; v++) {
                if (ind_save[i*DIM*DIM+j*DIM+v] != DIF && is_valid_set_gurobi(i,j,v+1)){
                    error = GRBgetdblattrelement(model, "X", ind_save[i*DIM*DIM+j*DIM+v], &sol);
                    if (is_guess){
                        flag_guess = 0;
                        set_guess_prob();
                    }
                    else if (is_guess_hint) {
                        set_guess_hint_prob(x,y);
                    }
                    else
                        return 1;/* ERROR */
                }else{
                    all_poss_scores[v] = -1;
                }
            }
            if (is_guess_hint && flag){
                return print_guess_hint_prob();
            }
            else if (is_guess && board[i][j].value == 0) {
                set_guess_board(thresholdX);
            }
        }}
    check_board_unsolvable_for_guess_hint(is_guess_hint);

    return error;
}

int optimization_complete(int is_LP, int is_guess, double thresholdX, int is_guess_hint, int x, int y){
    if (optimstatus == GRB_OPTIMAL){
        error = is_LP ? optimum_state_lp(is_guess, thresholdX, is_guess_hint, x, y) : optimum_state_ilp();
        return !error;
    }
    return 0;
}


void error_report(){
    if (error) {
        printf("ERROR: %s\n", GRBgeterrormsg(env));
        exit(1);
    }
}

int optimize_model(){
    return GRBoptimize(model);
}

/* Write model to 'sudoku.lp' */

int write_model(){
    return GRBwrite(model, "sudoku.lp");
}

int capture_sol_info(){
    return GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus) || GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
}

void free_model(){
    GRBfreemodel(model);
}

void free_env(){
    GRBfreeenv(env);
}


int set_obj_max(){
    error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
    return error;
}


int check_gurobi_board_full(){
    for (i = 0; i < DIM; ++i) {
        for (j = 0; j < DIM; ++j) {
            if (board[i][j].value == 0){
                return 0;
            }
        }
    }
    return 1;
}

void copy_curr_to_board() {
    int i, j;
    board = (struct cell **) calloc(DIM, sizeof(struct cell *));
    for (i = 0; i < DIM; ++i) {
        board[i] = (struct cell *) calloc(DIM, sizeof(struct cell));
    }
    for (i = 0; i < curr_board->len; ++i) {
        for (j = 0; j < curr_board->len; ++j) {
            board[i][j].value = curr_board->board[i][j].value;
        }
    }
}

void free_gurobi_board(){
    for (i = 0; i < DIM; ++i) {
        free(board[i]);
    }
    free(board);
}
int solver(int is_LP, int is_guess, double thresholdX, int is_guess_hint, int x, int y){
    DIM = curr_board->len;
    width = curr_board->block_width;
    height = curr_board->block_height;
    copy_curr_to_board();

    var_size = check_num_var(board);

    namestorage= (char*)malloc(sizeof(char)*(10*DIM*DIM*DIM));
    if (namestorage == NULL){
        memory_error("malloc");
    }
    val = (double*)malloc(sizeof(double)*DIM);
    if (val == NULL){
        memory_error("malloc");
    }
    ind_save = (int*)malloc(sizeof(int)*(DIM*DIM*DIM));
    if (ind_save == NULL){
        memory_error("malloc");
    }
    ind = (int*)malloc(sizeof(int)*DIM);
    if (ind == NULL){
        memory_error("malloc");
    }
    lb = (double*)malloc(sizeof(double)*var_size);
    if (lb == NULL){
        memory_error("malloc");
    }
    ub = (double*)malloc(sizeof(double)*var_size);
    if (ub == NULL){
        memory_error("malloc");
    }
    obj = (double*)malloc(sizeof(double)*var_size);
    if (obj == NULL){
        memory_error("malloc");
    }
    vtype = (char*)malloc(sizeof(char)*var_size);
    if (vtype == NULL){
        memory_error("malloc");
    }
    names = (char**)malloc(sizeof(char*)*var_size);
    if (names == NULL){
        memory_error("malloc");
    }

    if (is_LP){
        all_poss_scores = (double*)malloc(sizeof(double)*DIM);
        if (all_poss_scores == NULL){
            memory_error("malloc");
        }
    }

    create_empty_model(is_LP);
    if (create_env()) goto QUIT;
    if (remove_log_to_console()) goto QUIT;

    if (create_new_model()) goto QUIT;

    if (each_cell_value()) goto QUIT;
    if (each_row_value()) goto QUIT;
    if (each_col_value()) goto QUIT;
    if (each_sub_grid_value()) goto QUIT;
    if (set_obj_max()) goto QUIT;

    if (optimize_model()) goto QUIT;
    if (write_model()) goto QUIT;
    if (capture_sol_info()) goto QUIT;
    res = optimization_complete(is_LP, is_guess, thresholdX, is_guess_hint, x, y);
    if (!res) goto QUIT;
    if (is_guess && flag_guess)
        return 0;
    return 1;

    QUIT:
    error_report();
    free_model();
    free_env();
    free(lb);
    free(ind);
    free(ind_save);
    free(namestorage);
    free(ub);
    free(obj);
    free(vtype);
    free(names);
    free(val);
    if(is_LP) {
        free(all_poss_scores);
    }
    return 0;
}



