#include "Parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int str_equals(char *str1, char *str2) {
    return strcmp(str1, str2);
}

int check_which_command(char *input) {
    char exit_command[] = "exit";
    char restart_command[] = "restart";
    char validate_command[] = "validate";
    char hint_command[] = "hint";
    char set_command[] = "set";
    char* command = input;
    if(str_equals(command, exit_command)==0){
        return 1;
    }
    else{
        if(str_equals(command, restart_command)==0){
            return 2;
        }
        else{
            if(str_equals(command, validate_command)==0){
                return 3;
            }
            else{
                if(str_equals(command, hint_command)==0){
                    return 4;
                }
                else{
                    if(str_equals(command, set_command)==0){
                        return 5;
                    }
                }
            }
        }
    }
    /* no match found*/
    return 0;
}

int get_command_type(char* token, int is_last_command){
    int command_type = 0;
    command_type = check_which_command(token);
    /*we can't set a value if it is the last command*/
    if((is_last_command==1 && command_type==5)||(is_last_command==1 && command_type==4) ||(is_last_command==1 && command_type==3)){
        return 0;
    }
    return command_type;
}

int execute_long_command(char *rest, int command_type) {
    int flag=0;
    int coo_array [3] = {0,0,-1};
    int i = 0;
    char * token;
    while ((token = strtok_r(rest, " \n\t\r", &rest))&&i<3) {
        if(strlen(token)>1){
            return flag;
        }
        coo_array[i] = *token - 48;
        i++;
    }
    if(coo_array[0]==0 || coo_array[1]==0){
        command_type = 0;
    }
    else if(command_type==5&&coo_array[2]==0){
        command_type=5;
    }
    else if(command_type==5&&coo_array[2]==-1){
        if(is_fixed(coo_array[1]-1,coo_array[0]-1)){
            coo_array[2]=0;
            command_type=5;
        }
        else {
            command_type=0;
        }
    }

    switch (command_type) {
        case 4:
            board_hint(coo_array[1] - 1, coo_array[0] - 1);
            break;
        case 5:
            flag = board_set(coo_array[1] - 1, coo_array[0] - 1, coo_array[2]);
            break;
        default:
            printf("Error: invalid command\n");
    }
    return flag;
}



int execute_command(char *rest, int command_type){
    int flag = 0;
    switch(command_type)
    {
        case 1:
            board_exit();
            break;
        case 2:
            start_over();
            break;
        case 3:
            board_validate(solution.board_game);
            break;
        case 4:
            execute_long_command(rest, 4);
            break;
        case 5:
            flag = execute_long_command(rest, 5);
            break;
        default:
            printf("Error: invalid command\n");
    }
    return flag;
}

int read_user_commands(int is_last_command) {
    int flag = 0;
    int max_length = 1024;
    char input[1024];
    char *token;
    char *rest;
    int command_type = 0;
    int malloc_err = 0;
    if (fgets(input, max_length, stdin) != NULL) {
        if(input[0]=='\n') {
            while((fgets(input, max_length, stdin)) != NULL && input[0]=='\n');
            if(input[0]!='\n');
            else{
                board_exit();
                return flag;
            }
        }
                /*copy input so we won't ruin it*/
                rest = malloc(sizeof(char) * (strlen(input) + 1));
                if (rest == NULL) {
                    malloc_err = 1;
                    printf("Error: malloc has failed\n");
                } else {
                    strcpy(rest, input);
                    if (rest[strlen(input) - 1] == '\n') {
                        rest[strlen(input) - 1] = 0;
                    }
                    /*get command type by id 0-5*/

                    token = strtok_r(rest, " ", &rest);

                    command_type = get_command_type(token, is_last_command);

                    /*executes the command given, needs the res of the string to do that*/
                    flag = execute_command(rest, command_type);
                }
    }
    else{
        board_exit();
        return flag;

    }

    if (malloc_err == 1) {
        board.is_exit=1;
    }

    if (token != NULL){
        free(token);
    }

    return flag;
}
