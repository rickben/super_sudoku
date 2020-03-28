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
    return c>='0'&&c<='9';
}
bool is_dot(char c){
    return c==46;
}

bool is_valid_path(char* path){
    int i;
    for(i=0;i<(int) strlen(path);i++){
        if(path[i]=='|'||path[i]=='<'||path[i]=='>'||path[i]=='"'||path[i]=='?'||path[i]==':'||path[i]=='\\'){
            return false;
        }
    }
    return true;
}

int my_pow(int a, int b){
    int i;
    int ret = 1;
    for (i=0;i<b;i++){
        ret = ret*a;
    }
    return ret;
}

/*gets a string, and returns the number the string represents.
 * if the string does not represent a number, returns -1*/
int is_integer(char* s){
    int i;
    int coordinate = 0;
    for (i = 0; i<(int) strlen(s) ; i++){
        if (is_digit(s[i]) == false)
            return -1;
        else{
            coordinate+=(s[i]-'0')*my_pow(10, strlen(s) - i -1);
        }
    }
    return coordinate;
}

bool is_double(char* s){
    int i;
    int dot_counter = 0;
    int digit_counter = 0;
    for (i = 0; i < (int)strlen(s); i++){
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

bool is_valid_param(int command_code, char** command_data){
    if(command_code==5){
        if(strlen(command_data[3])>0){
            printf("To many parameters given\n");
            return false;
        }
    }
    if(command_code==8||command_code==12||command_code==13){
        if(strlen(command_data[2])>0){
            printf("To many parameters given\n");
            return false;
        }
    }
    if (command_code==1||command_code==2||command_code==3||command_code==7||command_code==11){
        if(strlen(command_data[1])>0){
            printf("To many parameters given\n");
            return false;
        }
    }
    if (command_code==4||command_code==6||command_code==9||command_code==10||command_code==14||command_code==15||command_code==16||command_code==17){
        if(strlen(command_data[0])>0){
            printf("To many parameters given\n");
            return false;
        }
    }
    return true;
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

void interpret_command(){
    int input_len = 256;
    char* input = malloc(input_len* sizeof(char));
    char *token;
    char *rest;
    int command_code = 0;
    int j = 0;
    char **command_data = malloc(sizeof(char*) * 4);
    for (; j < 4; ++j) {
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
        } else{
            return;}
        /*this way the parser ignores empty commands*/
        token = strtok_r(rest, " \t\r", &rest);
        while (token!=NULL&& j<4){
            command_data[j]=token;
            token = strtok_r(rest, " \t\r", &rest);
            j++;
        }
        j=0;
    }
    execute_command(command_code, command_data);
}

void execute_command(int command_code, char** command_data) {
    int x=0,y=0,z=0;
    double d;
    char* stop_string;
    if(!is_valid_param(command_code, command_data))
        return;
    switch(command_code)
    {
        case 1:
            if(command_data[0][0]=='\0'){
                printf("No path given\n");
                break;
            }
            if(!is_valid_path(command_data[0])){
                printf("The parameter isn't legal (invalid path)\n");
                break;
            }
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
            if(command_data[0][0]=='\0'){
                printf("No coordinates given\n");
                break;
            }
            /* translate strings of numbers to integers */
            x = is_integer(command_data[0]);
            y = is_integer(command_data[1]);
            z = is_integer(command_data[2]);
            if(x == -1 || y == -1 || z == -1){
                printf("The parameter isn't legal (not int)\n");
                break;
            }
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
            if(is_integer(command_data[0])  == -1|| is_integer(command_data[1]) == -1){
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
            if(command_data[0][0]=='\0'){
                printf("No coordinates given\n");
                break;
            }
            if(is_integer(command_data[0]) == -1 || is_integer(command_data[1]) == -1){
                printf("The parameter isn't legal (not int)\n");
                break;
            }
            x = (command_data[0][0] - '0');
            y = (command_data[1][0] - '0');
            hint(x,y);
            break;
        case 13:
            if(command_data[0][0]=='\0'){
                printf("No coordinates given\n");
                break;
            }
            if(is_integer(command_data[0]) == -1 || is_integer(command_data[1]) == -1){
                printf("The parameter isn't legal (not int)\n");
                break;
            }
            x = (command_data[0][0] - '0');
            y = (command_data[1][0] - '0');
            guess_hint(x,y);
            break;
        case 14:
            printf("The number of solutions for the current board is %ld\n",num_solutions());
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