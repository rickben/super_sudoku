#include <stdio.h>
#include <stdlib.h>
#include "MainAux.h"
#include <math.h>



int* calc_block_size(int len){
    int root = (int) (sqrt(len));
    int* arr = calloc(2, sizeof(int*));
    while (root > 0){
        if(len % root == 0){
            int n = root;
            int m = (len / root);
            arr[0] = n;
            arr[1] = m;
            return arr;
        }
        root--;
    }
}

void separator_row(int height,int width) {
    int i=0,j=0;
//    printf("%d %d\n", height, width);
    printf("-");
    for(; i<height; i++){
        printf("--");
        for(; j<width-1; j++){
        printf("---");
        }
        printf("---");
        j=0;
    }
    printf("\n");
}


void board_print(int len) {
    int* arr = calc_block_size(len);
    int block_width = arr[0];
    int block_height = arr[1];
    int i, j;
    for (i = 0; i < len; i++) {
        if(i % block_width==0){
            separator_row(block_height, block_width);
        }
        for (j = 0; j < len; j++) {
            if(j%block_height==0){
                if(j==0){
                    printf("|");}
                else{
                    printf(" |");
                }
            }

                printf("   ");



        }
        printf(" |\n");
    }
    separator_row(block_height, block_width);
}

void create_board(int len){
    curr_board->board = calloc(len, sizeof(int*));
    for (int i = 0; i < len; ++i) {
        curr_board->board[i] = calloc(len, sizeof(int*));
    }
}