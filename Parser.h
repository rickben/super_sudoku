#ifndef HW3_PARSER_H
#define HW3_PARSER_H
#include <string.h>
#include <stdbool.h>

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
