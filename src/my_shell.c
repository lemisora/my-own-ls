#include "utilities.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUF_LENGTH 200
#define KW_NUM 10

char *keywords[KW_NUM] = {"exit", "help", "touch", "echo", "rm","cat","mv","mkdir","ls","rmdir"};

void printPrompt(){
    printf("$ ");
}

void printInitMsg(){
    printf("Bienvenido a My Own Shell (Development)!\n");
}

void printExitMsg(){
    printf("Saliendo de mosh-dev\n");
}

void printArgs(int argc, char** argv){
    printf("Argumentos ingresados: %i -> \"%s\"\n", argc, argv[0]);
}

int shellKeyword(char* command){
    for (int i = 0; i < KW_NUM; i++){
        if(strcmp(keywords[i], command) == 0){
            return i;
        }
    }
    return -1;
}

void showHelp(){
    printf("Los comandos disponibles en esta shell son los siguientes:\n");
    printf("exit\n");
    printf("help\n");
    printf("touch\n\n");
}

int main(){
    int argc;
    char buffer[BUF_LENGTH];
    //int cmd_mapper;
    printInitMsg();
    while (1) {
        printPrompt();
        if(fgets(buffer, BUF_LENGTH, stdin)!= NULL){
            buffer[strcspn(buffer, "\n")] = '\0';

            char *args[BUF_LENGTH/2+1];
            char *token = strtok(buffer, " ");
            argc = 0;
            while(token != NULL && argc < BUF_LENGTH){
                args[argc++] = token;
                token = strtok(NULL, " ");
            }
            args[argc] = NULL;

            int cmd_mapper = shellKeyword(args[0]);
            //printArgs(argc, args);
            switch(cmd_mapper){
                case 0: printExitMsg(); exit(EXIT_SUCCESS); break;
                case 1: showHelp(); break;
                case 8: my_ls(argc, args); break;
                default: printf("Error: Comando '%s' no reconocido\n", buffer); break;
            }
        }
    }
}
