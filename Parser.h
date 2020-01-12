#ifndef HW3_PARSER_H
#define HW3_PARSER_H
#include "MainAux.h"

/*
 * Receives the first string in the command
 * and interpret to its kind
 * Call the method corresponding to each command:
 * set : board_set()
 * hint : board_hint()
 * validate : board_validate()
 * restart : board_restart()
 * exit : board_exit()
 * invalid : user_error_print(??)
 * */


extern char *strtok_r(char *, const char *, char **);

/*returns 0 if both strings are identical, negative number if the ASCII value of the first char in
 * str1 is lesser, and positive value otherwise*/
int str_equals(char *str1, char *str2);

/*for each command returns a matching number to identify it:
 * exit = 1
 * restart = 2
 * validate = 3
 * hint = 4
 * set = 5
 * invalid command (less then 4 characters) = -1
 * unknown command = 0*/
int check_which_command(char *input);

/*given the first word of the command, return the command type
 * if this is the last command, doesn't allow set command*/
int get_command_type(char* token, int is_last_command);

/*given a command type 4/5, meaning hint/set, calculates the right coordinates
 * and executes the command
 * if set/hint was given coordinates which are more the one digit
 * returns flag = 0*/
int execute_long_command(char *rest, int command_type);

/*
 * given the command type and the rest of the input, executes the command:
 *
 * */
int execute_command(char *rest, int command_type);

/*
 * Reads the users input, splits it to parts and
 * interpret using other functions
 * */
int read_user_commands(int is_last_command);


#endif
