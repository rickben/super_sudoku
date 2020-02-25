#ifndef HW3_FILESAUX_H
#define HW3_FILESAUX_H

int open_new_file();
int close_all_files();
int trans_board_to_file();
int trans_file_to_board(char* file_name);
/*
 * Returns 1 if manged to save the board in a file,
 * Otherwise, returns 0.
 * */
int save_file();
int create_board_from_file(int len,int width, int height);
int scan_size_from_file(FILE* in_file);
int scan_rows_from_file(FILE* in_file);
void free_mem_board();


#endif
