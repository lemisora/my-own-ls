#include "utilities.h"
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>

const char history_path[BUF_LENGTH];

int set_history_path(char *path){
    strcpy(path, history_path);
    return EXIT_SUCCESS;
}

int history_handling(){

    return EXIT_SUCCESS;
}

int add_to_mosh_history(const char **comando){
    return EXIT_SUCCESS;
}

void handle_mosh_history_nav(int key, char *buffer, int *pos){

}

void enable_raw_mode(){

}

void disable_raw_mode(){

}
