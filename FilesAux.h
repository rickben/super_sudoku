#ifndef HW3_FILESAUX_H
#define HW3_FILESAUX_H

void free_mem_board();
int solve_mode_to_file(char* file_name);
int edit_mode_to_file(char* file_name);
int trans_board_to_file(char* file_name);
/*
 * Returns 1 if manged to save the board in a file,
 * Otherwise, returns 0.
 * */
int create_board_from_file(int len,int width, int height);
void create_temporary_board_from_file(int len, int width, int height);
void copy_from_temporary_to_curr_board();
void free_temporary_board();
int scan_size_from_file(FILE* in_file);
int scan_rows_from_file(FILE* in_file);
int trans_file_to_board(char* file_name);


#endif
