#ifndef HW3_PARSER_H
#define HW3_PARSER_H
#include <string.h>
#include <stdbool.h>

bool is_digit(char c);
bool is_dot(char c);
bool is_integer(char* s);
bool is_double(char* s);
int str_equals(char *str1, char *str2);
int command_to_code(char* input) ;
void interpret_command();
void execute_command(int command_code, char** command_data);
#endif
