#ifndef HW3_PARSER_H
#define HW3_PARSER_H
#include <string.h>
#include <stdbool.h>

/*
*Parser Summary:
*
 * This module is in charge of parsing the entered input of the user to the console
 * and to use the specified commands or to print a specific error message
 * to the console.
 * It also checks whether each command was used in the correct state of the program
 * and if not - prints a specific error message
 *
* It supports the following functions (the main ones):
 *
 * command_to_code                  - translates the command entered by the user to a number that represents it
 * interpret_command                - receives the input from the user and disassembles it to command and its parameters
 * execute_command                  - according to the number of the command and its parameters - uses the suitable func
 *
 * additionally it supports auxiliary functions to those 3 functions, mainly checking for errors functions
* ***/

extern char *strtok_r(char *, const char *, char **);

int str_equals(char *str1, char *str2);
bool is_digit(char c);
bool is_dot(char c);
bool is_valid_path(char* path);
int my_pow(int a, int b);
int is_integer(char* s);
bool is_double(char* s);
bool is_valid_param(int command_code, char** command_data);
int command_to_code(char* input) ;
void interpret_command();
void execute_command(int command_code, char** command_data);
#endif
