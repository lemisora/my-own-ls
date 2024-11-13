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

void showHelp(){// Función para mostrar ayuda adicional al usuario
    printf("Ayuda\n");

}

int shellKeyword(char* command){
    for (int i = 0; i < KW_NUM; i++){
        if(strcmp(keywords[i], command) == 0){
            return i;
        }
    }
    return -1;
}

int main(){
    char buffer[BUF_LENGTH];
    //int cmd_mapper;
    printInitMsg();
    while (1) {
        printPrompt();
        if(fgets(buffer, BUF_LENGTH, stdin)!= NULL){
            buffer[strcspn(buffer, "\n")] = '\0';
            int cmd_mapper = shellKeyword(buffer);
            switch(cmd_mapper){
                case 0: printf("Saliendo de mosh-dev\n"); exit(EXIT_SUCCESS); break;
                case 1: showHelp(); break;
                default: printf("Error: Comando '%s' no reconocido\n", buffer); break;
            }
        }
    }
    return EXIT_SUCCESS;
}
