#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "ListActions.h"
#include "gurobi_c.h"


#define EMPTY 0
int       flag;
double    num,sum,start;
GRBenv   *env   = NULL;
GRBmodel *model = NULL;
double    sol;
/*double   *all_pos_sol;*/
double   *all_poss_scores;
int       var_size, res;
int       *ind_save;
int       *ind;
int	      const_size;
double    *val;
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



/*
 * Return false if there's a cell in the same row
 * with the same value, otherwise, returns true
 * */
int in_row_gurobi(int row, int num) {
    for (j = 0; j < gurobi_board->len; ++j) {
        if (gurobi_board->board[row][j].value == num) {
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
    for (j = 0; j < gurobi_board->len; ++j) {
        if (gurobi_board->board[j][col].value == num) {
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
    for (i = 0; i < gurobi_board->block_height; ++i) {
        for (j = 0; j < gurobi_board->block_width; ++j) {
            if (gurobi_board->board[i+x][j+y].value == num) {
                return 1;
            }
        }
    }
    return 0;
}


int is_valid_set_gurobi(int x, int y, int num) {
    int block_x = (x / (gurobi_board->block_height))*(gurobi_board->block_height);
    int block_y = (y / (gurobi_board->block_width))*(gurobi_board->block_width);
    return (!in_row_gurobi(x,num) && !in_col_gurobi(y,num) &&
            !in_block_gurobi(block_x,block_y,num));
}


int check_num_var(){
    int count = 0;
    for (i = 0; i < gurobi_board->len; i++) {
        for (j = 0; j < gurobi_board->len; j++) {
            for (v = 0; v < gurobi_board->len; v++) {
                if (gurobi_board->board[i][j].value == EMPTY && is_valid_set_gurobi(i,j,v+1)){
                    count++;
                }
            }}}
    return count;
}





void create_empty_model(int is_LP){
    count = 0;
    cursor = namestorage;
    for (i = 0; i < gurobi_board->len; i++) {
        for (j = 0; j < gurobi_board->len; j++) {
            for (v = 0; v < gurobi_board->len; v++) {
                if (gurobi_board->board[i][j].value == EMPTY && is_valid_set_gurobi(i,j,v+1)){ /* valid_set: v not in row, col, block*/
                    lb[count] = 0;
                    ub[count] = 1;
                    obj[count] = is_LP ? (rand() % DIM + 1) : 0;
                    vtype[count] = is_LP ? GRB_CONTINUOUS : GRB_BINARY;
                    ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v] = count ;
                    names[count] = cursor;
                    sprintf(names[count], "x[%d,%d,%d]", i, j, v+1);
                    cursor += strlen(names[count]) + 1;
                    count++;
                }
                else{
                    ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v] = EMPTY;
                }
            }
        }
    }
}

int create_env(){
    error = GRBloadenv(&env, "sudoku.log");
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
    for (i = 0; i < gurobi_board->len; i++) {
        for (j = 0; j < gurobi_board->len; j++) {
            for (v = 0; v < gurobi_board->len; v++) {
                if(ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v]!= EMPTY){
                    ind[const_size] = ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v];
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
    for (v = 0; v < gurobi_board->len; v++) {
        for (j = 0; j < gurobi_board->len; j++) {
            for (i = 0; i < gurobi_board->len; i++) {
                if(ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v]!= EMPTY){
                    ind[const_size] = ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v];
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
    for (v = 0; v < gurobi_board->len; v++) {
        for (i = 0; i < gurobi_board->len; i++) {
            for (j = 0; j < gurobi_board->len; j++) {
                if(ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v] != EMPTY){
                    ind[const_size] = ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v];
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
/**/
int each_sub_grid_value(){
    for (v = 0; v < (gurobi_board->len); v++) {
        for (ig = 0; ig < gurobi_board->block_width; ig++) {
            for (jg = 0; jg < gurobi_board->block_height; jg++) {
                count = 0;
                for (i = ig*(gurobi_board->block_height); i < (ig+1)*(gurobi_board->block_height); i++) {
                    for (j = jg*(gurobi_board->block_width); j < (jg+1)*(gurobi_board->block_width); j++) {
                        if(ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v]!= EMPTY){
                            ind[count] = ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v];
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
    printf("Optimal objective: %.4e\n", objval);
    for (i = 0; i < gurobi_board->len; i++) {
        for (j = 0; j < gurobi_board->len; j++) {
            for (v = 0; v < gurobi_board->len; v++) {
                if (ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v] != EMPTY){
                    error = GRBgetdblattrelement(model, "X", ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v], &sol);
                    if ((int)sol == 1){
                        printf("x[%d,%d,%d]=%d\n",i,j,v+1,(int)sol);
                        gurobi_board->board[i][j].value = v+1;
                    }
                }
            }}}
    return error;
}

int optimum_state_lp(int is_guess, double thresholdX, int is_guess_hint, int x, int y){
    flag = 0;
    printf("Optimal objective: %.4e\n", objval);
    for (i = 0; i < gurobi_board->len; i++) {
        for (j = 0; j < gurobi_board->len; j++) {
            for (v = 0; v < gurobi_board->len; v++) {
                if (ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v] != EMPTY){
                    error = GRBgetdblattrelement(model, "X", ind_save[i*(gurobi_board->len)*(gurobi_board->len)+j*(gurobi_board->len)+v], &sol);
                    if (is_guess){
                        all_poss_scores[v] = sol;
                    }
                    else if (is_guess_hint) {
                        if (i == y && j == x){ /* x,y=col,row*/
                            flag = 1;
                            all_poss_scores[v] = sol;
                        }
                    }
                    else
                        return 1;/* ERROR */
                }else{
                    all_poss_scores[v] = -1;
                }
            }
            if (is_guess_hint && flag){
                flag = 0;
                for (v = 0; v < gurobi_board->len; ++v) {
                    if (all_poss_scores[v] > 0){
                        printf("value = %d : prob = %f\n",v+1,all_poss_scores[v]);
                    }
                }
                return error;
            }
            else if (is_guess && gurobi_board->board[i][j].value == 0) {
                count = 0;
                num = 0;
                sum = 0;
                start = 0;
                for (v = 0; v < gurobi_board->len; ++v) {
                    if (all_poss_scores[v] >= thresholdX) {
                        sum += all_poss_scores[v];
                    }
                }
                printf("sum :%f\n",sum);
                num = (((double) rand()) / RAND_MAX) * sum;
                for (v = 0; v < gurobi_board->len; ++v) {
                    if (all_poss_scores[v] >= thresholdX) {
                        if (num >= start && num < (start + all_poss_scores[v])) {
                            printf("num =%f, str:%f, end:%f, score:%f\n",num,start,start + all_poss_scores[v],all_poss_scores[v]);
                            gurobi_board->board[i][j].value = v+1;
                            break;
                        } else if ((start + all_poss_scores[v]) == sum){
                            gurobi_board->board[i][j].value = v+1;
                        }
                        start += all_poss_scores[v];
                    }
                }
            }
            /* choose randomly the value for x[i,j] from all_poss_scores */
            /* here */
        }}
    return error;
}

int optimization_complete(int is_LP, int is_guess, double thresholdX, int is_guess_hint, int x, int y){
    printf("\nOptimization complete\n");
    if (optimstatus == GRB_OPTIMAL){
        error = is_LP ? optimum_state_lp(is_guess, thresholdX, is_guess_hint, x, y) : optimum_state_ilp();
        printf("\n");
        return !error;
    }
    else if (optimstatus == GRB_INF_OR_UNBD)
        printf("Model is infeasible or unbounded\n");
    else
        printf("Optimization was stopped early\n");
    printf("\n");
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

void copy_curr_board_to_gurobi_board(){
    gurobi_board =  (struct curr_board *) calloc(curr_board->len, sizeof(struct cell));
    gurobi_board->block_width = curr_board->block_width;
    gurobi_board->block_height = curr_board->block_height;
    gurobi_board->len = curr_board->len ;
    gurobi_board->mark_errors = 1;
    gurobi_board->board = (struct cell **) calloc(curr_board->len, sizeof(struct cell *));
    for (i = 0; i < curr_board->len; ++i) {
        gurobi_board->board[i] = (struct cell *) calloc(curr_board->len, sizeof(struct cell));
    }

}

int check_gurobi_board_full(){
    for (i = 0; i < gurobi_board->len; ++i) {
        for (j = 0; j < gurobi_board->len; ++j) {
            if (gurobi_board->board[i][j].value == 0){
                return 0;
            }
        }
    }
    return 1;
}


int solver(int is_LP, int is_guess, double thresholdX, int is_guess_hint, int x, int y, int is_generate){
    int DIM = curr_board->len;
    copy_curr_board_to_gurobi_board();
    var_size = check_num_var();

    namestorage= (char*)malloc(sizeof(char)*(10*DIM*DIM*DIM));
    val = (double*)malloc(sizeof(double)*DIM);
    ind_save = (int*)malloc(sizeof(int)*(DIM*DIM*DIM));
    ind = (int*)malloc(sizeof(int)*DIM);
    lb = (double*)malloc(sizeof(double)*var_size);
    ub = (double*)malloc(sizeof(double)*var_size);
    obj = (double*)malloc(sizeof(double)*var_size);
    vtype = (char*)malloc(sizeof(char)*var_size);
    names = (char**)malloc(sizeof(char*)*var_size);
    if (is_LP){
        all_poss_scores = (double*)malloc(sizeof(double)*DIM);
    }

    create_empty_model(is_LP);
    if (create_env()) goto QUIT;
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
    if(is_LP && is_guess || is_generate){
        curr_board->board = gurobi_board->board;
    }

    QUIT:
    error_report();
    free_model();
    free_env();
    free(namestorage);
    free(val);
    free(ind_save);
    free(ind);
    free(lb);
    free(ub);
    free(obj);
    free(vtype);
    free(names);
    free(all_poss_scores);
    return res;
}


