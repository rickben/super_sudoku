#include "Parser.h"
#include "Game.h"
#include "FilesAux.h"
#include "MainAux.h"
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

bool is_valid_param(int command_code, char command_data[4][258]){
    if(command_code==5){
        if(strlen(command_data[3])>0){
            printf("Error: To many parameters given\n");
            return false;
        }
    }
    if(command_code==8||command_code==12||command_code==13){
        if(strlen(command_data[2])>0){
            printf("Error: To many parameters given\n");
            return false;
        }
    }
    if (command_code==1||command_code==2||command_code==3||command_code==7||command_code==11){
        if(strlen(command_data[1])>0){
            printf("Error: To many parameters given\n");
            return false;
        }
    }
    if (command_code==4||command_code==6||command_code==9||command_code==10||command_code==14||command_code==15||command_code==16||command_code==17){
        if(strlen(command_data[0])>0){
            printf("Error: To many parameters given\n");
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
    char c;
    int input_len = 257;
    char input[257];
    char *token;
    char* ptr;
    int command_code = 0;
    int j = 0;
    char command_data[4][258];

    for (; j < 4; ++j) {
        command_data[j][0]='\0';
    }
    j=0;
    if(fgets(input, input_len, stdin)!=NULL){
        size_t len = strlen(input);

        /*flush*/
        if((int)len==(input_len-1)){
            printf("Error: command is to long\n");
            while((c = getchar()) != '\n' && c != EOF);
            if (c == EOF){
                my_exit();
            }
            return;
        }

        /* fix input*/
        if (len > 0 && input[len - 1] == '\n') input[--len] = '\0';

        token = strtok_r(input, " \t\r", &ptr);

        if(token!=NULL){
            command_code = command_to_code(token);
        } else{
            return;
        }
        /*this way the parser ignores empty commands*/
        token = strtok_r(NULL, " \t\r", &ptr);
        while (token!=NULL&& j<4){
            strcpy(command_data[j], token);
            token = strtok_r(NULL, " \t\r", &ptr);
            j++;
        }
        j=0;
    }
    else{
        my_exit();
    }
    execute_command(command_code, command_data);
}

void execute_command(int command_code, char command_data[4][258]) {
    int x=0,y=0,z=0;
    double d;
    char* stop_string;
    if(!is_valid_param(command_code, command_data))
        return;
    switch(command_code)
    {
        case 1:
            if(command_data[0][0]=='\0'){
                printf("Error: No path given\n");
                break;
            }
            if(!is_valid_path(command_data[0])){
                printf("Error: The parameter isn't legal (invalid path)\n");
                break;
            }
            solve(command_data[0]);
            break;
        case 2:
            edit(command_data[0]);
            break;
        case 3:
            if (state != Solve){
                printf("Error: Mark errors only available in solve mode\n");
                break;
            }
            if(command_data[0][0]=='\0'){
                printf("Error: No parameter given\n");
                break;
            }
            x = is_integer(command_data[0]);
            if(x == -1){
                printf("Error: The parameter isn't legal\n");
                break;
            }
            mark_errors(x);
            break;
        case 4:
            if(state != Solve && state != Edit) {
                printf("Error: Print board only available in solve or edit mode\n");
                break;
            }
            print_board();
            break;
        case 5:
            if (state != Solve && state != Edit) {
                printf("Error: Set only available in solve or edit mode\n");
                break;
            }
            if(command_data[0][0]=='\0'||command_data[1][0]=='\0'||command_data[2][0]=='\0'){
                printf("Error: Missing coordinates\n");
                break;
            }
            /* translate strings of numbers to integers */
            x = is_integer(command_data[0]);
            y = is_integer(command_data[1]);
            z = is_integer(command_data[2]);
            if(x == -1 || y == -1 || z == -1){
                if (x == -1){
                    printf("Error: The first parameter isn't legal (not a positive number)\n");
                    break;
                } else if (y == -1){
                    printf("Error: The second parameter isn't legal (not a positive number)\n");
                    break;
                } else {
                    printf("Error: The third parameter isn't legal (not a positive number)\n");
                    break;
                }
            }
            board_set(x,y,z);
            break;
        case 6:
            if(state!=Solve && state != Edit){
                printf("Error: validate only available in solve or edit mode\n");
                break;
            }
            validate();
            break;
        case 7:
            if(state != Solve){
                printf("Error: Guess command is only available in Solve mode\n");
                break;
            }
            if(command_data[0][0]=='\0'){
                printf("Error: No parameter given\n");
                break;
            }
            if (!is_double(command_data[0])){
                printf("Error: The parameter isn't legal (not a positive double)\n");
                break;
            }
            d = strtod(command_data[0], &stop_string);
            guess(d);
            break;
        case 8:
            if (state != Edit){
                printf("Error: Generate command is available only in Edit mode!\n");
                break;
            }
            if(command_data[0][0]=='\0'||command_data[1][0]=='\0'){
                printf("Error: No parameters given\n");
                break;
            }
            x = is_integer(command_data[0]);
            y = is_integer(command_data[1]);
            if(x == -1 || y == -1){
                if (x == -1){
                    printf("Error: The first parameter isn't legal (not a positive number)\n");
                    break;
                } else {
                    printf("Error: The second parameter isn't legal (not a positive number)\n");
                    break;
                }
            }
            generate(x,y);
            break;
        case 9:
            if(state != Solve && state != Edit){
                printf("Error: Undo only available in solve or edit mode\n");
                break;
            }
            undo();
            break;
        case 10:
            if (state != Solve && state != Edit) {
                printf("Error: Redo only available in solve or edit mode\n");
                break;
            }
            redo();
            break;
        case 11:
            if (state != Solve && state != Edit){
                printf("Error: Save command is only available in Solve or Edit mode\n");
                break;
            }
            if(command_data[0][0]=='\0'){
                printf("Error: No path given\n");
                break;
            }
            if(!is_valid_path(command_data[0])){
                printf("Error: The parameter isn't legal (invalid path)\n");
                break;
            }
            save(command_data[0]);
            break;
        case 12:
            if(state != Solve) {
                printf("Error: Hint command is only available in Solve mode\n");
                break;
            }
            if(command_data[0][0]=='\0'||command_data[1][0]=='\0'){
                printf("Error: No coordinates given\n");
                break;
            }
            x = is_integer(command_data[0]);
            y = is_integer(command_data[1]);
            if(x == -1 || y == -1){
                if (x == -1){
                    printf("Error: The first parameter isn't legal (not a positive number)\n");
                    break;
                } else {
                    printf("Error: The second parameter isn't legal (not a positive number)\n");
                    break;
                }
            }
            hint(x,y);
            break;
        case 13:
            if(state != Solve) {
                printf("Error: Guess_hint command is only available in Solve mode\n");
                break;
            }
            if(command_data[0][0]=='\0'||command_data[1][0]=='\0'){
                printf("Error: No coordinates given\n");
                break;
            }
            x = is_integer(command_data[0]);
            y = is_integer(command_data[1]);
            if (x == -1 || y == -1){
                if (x == -1){
                    printf("Error: The first parameter isn't legal (not a positive number)\n");
                    break;
                } else {
                    printf("Error: The second parameter isn't legal (not a positive number)\n");
                    break;
                }
            }
            guess_hint(x,y);
            break;
        case 14:
            if (state != Solve && state != Edit){
                printf("Error: Num_solutions command is only available in Solve or Edit mode\n");
                break;
            }
            num_solutions();
            break;
        case 15:
            if (state != Solve){
                printf("Error: Autofill command is only available in Solve mode\n");
                break;
            }
            autofill();
            break;
        case 16:
            if (state != Solve && state != Edit) {
                printf("Error: Reset only available in solve or edit mode\n");
                break;
            }
            reset();
            break;
        case 17:
            my_exit();
            break;
        default:
            printf("Error: invalid command\n");
    }
}