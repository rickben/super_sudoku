#ifndef HW3_PARSER_H
#define HW3_PARSER_H
#include <string.h>
int str_equals(char *str1, char *str2);
int command_to_code(char* input) ;
void interpret_command();
void execute_command(int command_code, char** command_data);
#endif
