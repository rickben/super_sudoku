#include "Parser.h"
#include "Game.h"
#include "FilesAux.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int str_equals(char *str1, char *str2) {
    return strcmp(str1, str2);
}


bool is_digit(char c){
    return c>=48&&c<=57;
}
bool is_dot(char c){
    return c==46;
}

bool is_integer(char* s){
    for (int i = 0; i < strlen(s); i++)
        if (is_digit(s[i]) == false)
            return false;
    return true;
}

bool is_double(char* s){
    int dot_counter = 0;
    int digit_counter = 0;
    for (int i = 0; i < strlen(s); i++){
        if (is_digit(s[i]) == false && !is_dot(s[i]))
            return false;
        if(is_dot(s[i]))
            dot_counter++;
        else
            digit_counter++;
    }
    if(dot_counter==0)
        return true;
    if (dot_counter==1&&digit_counter>=1)
        return true;
    return false;
}

int command_to_code(char* input) {
    if (str_equals(input, "solve") == 0)
        return 1;
    else
    if (str_equals(input, "edit") == 0)
        return 2;
    else
    if (str_equals(input, "mark_errors") == 0)
        return 3;
    else
    if (str_equals(input, "print_board") == 0)
        return 4;
    else
    if (str_equals(input, "set") == 0)
        return 5;
    else
    if (str_equals(input, "validate") == 0)
        return 6;
    else
    if (str_equals(input, "guess") == 0)
        return 7;
    else
    if (str_equals(input, "generate") == 0)
        return 8;
    else
    if (str_equals(input, "undo") == 0)
        return 9;
    else
    if (str_equals(input, "redo") == 0)
        return 10;
    else
    if (str_equals(input, "save") == 0)
        return 11;
    else
    if (str_equals(input, "hint") == 0)
        return 12;
    else
    if (str_equals(input, "guess_hint") == 0)
        return 13;
    else
    if (str_equals(input, "num_solutions") == 0)
        return 14;
    else
    if (str_equals(input, "autofill") == 0)
        return 15;
    else
    if (str_equals(input, "reset") == 0)
        return 16;
    else
    if (str_equals(input, "exit") == 0)
        return 17;
    return 0;
}
//TODO change the size of input, because the address is bigger
void interpret_command(){
    int input_len = 256;
    char* input = malloc(input_len* sizeof(char));
    char *token;
    char *rest;
    int command_code = 0;
    int j = 0;
    char **command_data = malloc(sizeof(char*) * 3);
    for (; j < 3; ++j) {
        command_data[j] = malloc(sizeof(char) * input_len);
        command_data[j][0]='\0';
    }
    j=0;
    if(fgets(input, input_len, stdin)!=NULL){

        /* fix input*/
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') input[--len] = '\0';

        /*copy input so we won't ruin it*/
        rest = malloc(sizeof(char) * (strlen(input) + 1));
        strcpy(rest, input);

        token = strtok_r(rest, " \t\r", &rest);

        if(token!=NULL){
            command_code = command_to_code(token);
        }
        token = strtok_r(rest, " \t\r", &rest);
        while (token!=NULL&& j<3){
            command_data[j]=token;
            token = strtok_r(rest, " \t\r", &rest);
            j++;
        }
        j=0;
    }
    execute_command(command_code, command_data);
}

void execute_command(int command_code, char** command_data) {
    int x,y,z;
    double d;
    char* stop_string;
    switch(command_code)
    {
        case 1:
            solve(command_data[0]);
            break;
        case 2:
            edit(command_data[0]);
            break;
        case 3:
            mark_errors((command_data[0][0] - '0'));
            break;
        case 4:
            print_board();
            break;
        case 5:
            if(!is_integer(command_data[0]) || !is_integer(command_data[1]) || !is_integer(command_data[2])){
                printf("The parameter isn't legal (not int)\n");
                break;
            }
            /* translate strings of numbers to integers */
            x = (command_data[0][0] - '0');
            y = (command_data[1][0] - '0');
            z = (command_data[2][0] - '0');
            board_set(x,y,z);
            break;
        case 6:
            validate();
            break;
        case 7:
            if (!is_double(command_data[0])){
                printf("The parameter isn't legal (not double)\n");
                break;
            }
            d = strtod(command_data[0], &stop_string);
            guess(d);
            break;
        case 8:
            if(!is_integer(command_data[0]) || !is_integer(command_data[1])){
                printf("The parameter isn't legal (not int)\n");
                break;
            }
            x = (command_data[0][0] - '0');
            y = (command_data[1][0] - '0');
            generate(x,y);
            break;
        case 9:
            undo();
            break;
        case 10:
            redo();
            break;
        case 11:
            trans_board_to_file(command_data[0]);
            break;
        case 12:
            if(!is_integer(command_data[0]) || !is_integer(command_data[1])){
                printf("The parameter isn't legal (not int)\n");
                break;
            }
            x = (command_data[0][0] - '0');
            y = (command_data[1][0] - '0');
            hint(x,y);
            break;
        case 13:
            if(!is_integer(command_data[0]) || !is_integer(command_data[1])){
                printf("The parameter isn't legal (not int)\n");
                break;
            }
            x = (command_data[0][0] - '0');
            y = (command_data[1][0] - '0');
            guess_hint(x,y);
            break;
        case 14:
            num_solutions();
            break;
        case 15:
            autofill();
            break;
        case 16:
            reset();
            break;
        case 17:
            my_exit();
            break;
        default:
            printf("Error: invalid command\n");
    }
}