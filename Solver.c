////#include <stdlib.h>
////#include "Solver.h"
//
///*
//  Sudoku example.
//
//  The Sudoku board is a NxN grid, which is further divided into a m*n grids.
//  Each cell in the grid must take a value from 0 to N.
//  No two grid cells in the same row, column, or m*n subgrid may take the
//  same value.
//
//  In the MIP formulation, binary variables x[i,j,v] indicate whether
//  cell <i,j> takes value 'v'.  The constraints are as follows:
//    1. Each cell must take exactly one value (sum_v x[i,j,v] = 1)
//    2. Each value is used exactly once per row (sum_i x[i,j,v] = 1)
//    3. Each value is used exactly once per column (sum_j x[i,j,v] = 1)
//    4. Each value is used exactly once per m*n subgrid (sum_grid x[i,j,v] = 1)
//
//  Input datasets for this example can be found in examples/data/sudoku*.
//*/
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include "gurobi_c.h"
//
//
//
//
///*
// * for curr_board->board, solves  the board
// * */
//int solver_ILP()
//{
//    FILE     *fp    = NULL;
//    int DIM = curr_board->len;
//    GRBenv   *env   = NULL;
//    GRBmodel *model = NULL;
//    int       board[DIM][DIM];
//    char      inputline[100];
//    int       ind[DIM];
//    double    val[DIM];
//    double    lb[DIM*DIM*DIM];
//    double    sol[DIM*DIM*DIM];
//    char      vtype[DIM*DIM*DIM];
//    char     *names[DIM*DIM*DIM];
//    char      namestorage[10*DIM*DIM*DIM];
//    char     *cursor;
//    int       optimstatus;
//    double    objval;
//    int       i, j, v, ig, jg, count;
//    int       error = 0;
//
//
//
//    /* Create environment - log file is mip1.log */
//    error = GRBloadenv(&env, "mip1.log");
//    if (error) {
//        printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
//    if (error) {
//        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    /* Create an empty model named "mip1" */
//    error = GRBnewmodel(env, &model, "mip1", 0, NULL, NULL, NULL, NULL, NULL);
//    if (error) {
//        printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//    /* Create an empty model */
//
//    cursor = namestorage;
//    for (i = 0; i < DIM; i++) {
//        for (j = 0; j < DIM; j++) {
//            for (v = 0; v < DIM; v++) {
//                if (board[i][j] == v)
//                    lb[i*DIM*DIM+j*DIM+v] = 1;
//                else
//                    lb[i*DIM*DIM+j*DIM+v] = 0;
//                vtype[i*DIM*DIM+j*DIM+v] = GRB_BINARY;
//
//                names[i*DIM*DIM+j*DIM+v] = cursor;
//                sprintf(names[i*DIM*DIM+j*DIM+v], "x[%d,%d,%d]", i, j, v+1);
//                cursor += strlen(names[i*DIM*DIM+j*DIM+v]) + 1;
//            }
//        }
//    }
//
//    /* Create environment */
//
//    error = GRBloadenv(&env, "sudoku.log");
//    if (error) goto QUIT;
//
//    /* Create new model */
//
//    error = GRBnewmodel(env, &model, "sudoku", DIM*DIM*DIM, NULL, lb, NULL,
//                        vtype, names);
//    if (error) goto QUIT;
//
//    /* Each cell gets a value */
//
//    for (i = 0; i < DIM; i++) {
//        for (j = 0; j < DIM; j++) {
//            for (v = 0; v < DIM; v++) {
//                ind[v] = i*DIM*DIM + j*DIM + v;
//                val[v] = 1.0;
//            }
//
//            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
//            if (error) goto QUIT;
//        }
//    }
//
//    /* Each value must appear once in each row */
//
//    for (v = 0; v < DIM; v++) {
//        for (j = 0; j < DIM; j++) {
//            for (i = 0; i < DIM; i++) {
//                ind[i] = i*DIM*DIM + j*DIM + v;
//                val[i] = 1.0;
//            }
//
//            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
//            if (error) goto QUIT;
//        }
//    }
//
//    /* Each value must appear once in each column */
//
//    for (v = 0; v < DIM; v++) {
//        for (i = 0; i < DIM; i++) {
//            for (j = 0; j < DIM; j++) {
//                ind[j] = i*DIM*DIM + j*DIM + v;
//                val[j] = 1.0;
//            }
//
//            error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
//            if (error) goto QUIT;
//        }
//    }
//
//    /* Each value must appear once in each subgrid */
//
//    for (v = 0; v < DIM; v++) {
//        for (ig = 0; ig < curr_board->block_height; ig++) {
//            for (jg = 0; jg < curr_board->block_width; jg++) {
//                count = 0;
//                for (i = ig*(curr_board->block_height); i < (ig+1)*(curr_board->block_height); i++) {
//                    for (j = jg*(curr_board->block_height); j < (jg+1)*(curr_board->block_height); j++) {
//                        ind[count] = i*DIM*DIM + j*DIM + v;
//                        val[count] = 1.0;
//                        count++;
//                    }
//                }
//
//                error = GRBaddconstr(model, DIM, ind, val, GRB_EQUAL, 1.0, NULL);
//                if (error) goto QUIT;
//            }
//        }
//    }
//
//    /* Optimize model */
//
//    error = GRBoptimize(model);
//    if (error) goto QUIT;
//
//    /* Write model to 'sudoku.lp' */
//
//    error = GRBwrite(model, "sudoku.lp");
//    if (error) goto QUIT;
//
//    /* Capture solution information */
//
//    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
//    if (error) goto QUIT;
//
//    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
//    if (error) goto QUIT;
//
//    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0,DIM*DIM*DIM, sol);
//    if (error) {
//        printf("ERROR %d GRBgetdblattrarray(): %s\n", error, GRBgeterrormsg(env));
//        return -1;
//    }
//
//    printf("\nOptimization complete\n");
//    if (optimstatus == GRB_OPTIMAL)
//        printf("Optimal objective: %.4e\n", objval);
//    else if (optimstatus == GRB_INF_OR_UNBD)
//        printf("Model is infeasible or unbounded\n");
//    else
//        printf("Optimization was stopped early\n");
//    printf("\n");
//
//    QUIT:
//
//    /* Error reporting */
//
//    if (error) {
//        printf("ERROR: %s\n", GRBgeterrormsg(env));
//        exit(1);
//    }
//
//    fclose(fp);
//
//    /* Free model */
//
//    GRBfreemodel(model);
//
//    /* Free environment */
//
//    GRBfreeenv(env);
//
//    return 0;
//}
//
int solver_LP()
{

}
int solver_ILP(){

}