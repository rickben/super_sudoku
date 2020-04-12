#ifndef HW3_PARSER_H
#define HW3_PARSER_H
#include <string.h>
#include <stdbool.h>

/**
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
**/

extern char *strtok_r(char *, const char *, char **);

/**
 * compares two strings
 * @param first string
 * @param second string
 * @return 0 if the strings the same, otherwise the strings are different
 * */
int str_equals(char *str1, char *str2);

/**
 * checks if a given char is a digit (0 to 9 only)
 * @param char c
 * @return True (1) if c is a digit, otherwise False (0)
 */
bool is_digit(char c);

/**
 * checks if a given char is a dot
 * @param char c
 * @return True (1) if c is a dot, otherwise False (0)
 */
bool is_dot(char c);

/**
 * checks if a given string is a valid path to a file
 * @param string path
 * @return True (1) if the string is a valid path, otherwise False (0)
 */
bool is_valid_path(char* path);

/**
 * calculates a in the power of b (a ^ b)
 * @param int a
 * @param int b
 * @return a in the power of b (a ^ b)
 */
int my_pow(int a, int b);

/**
 * checks if a given string is an integer
 * @param  string s
 * @return 1 if s is an integer, otherwise 0
 */
int is_integer(char* s);

/**
 * checks if a given string is a double
 * @param  string s
 * @return 1 if s is a double, otherwise 0
 */
bool is_double(char* s);

/**
 * checks if the parameters to the command are valid
 * @param command_code - the number represents the command
 * @param command_data - array of strings which are the parameters
 * @return True (1) if the parameters are valid, False (0) otherwise
 */
bool is_valid_param(int command_code, char** command_data);

/**
 * checks if the input string is one of the optional commands
 * @param string input
 * @return the command_code, its the number that represents the command
 */
int command_to_code(char* input) ;

/**
 * gets the input from the user and disassembles it to command and
 * parameters
 */
void interpret_command();
/**
 *  according to the command_code(# of command) and command_data(parameters)-
 *  activate the command with the given parameters or prints an error
 * @param command_code
 * @param command_data
 */
void execute_command(int command_code, char** command_data);

#endif
