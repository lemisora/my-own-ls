#include <string.h>
#include <stdio.h>
#define BUF_LENGTH 200

int main(){
    char buffer[BUF_LENGTH];
    while(1){
        printf("$");
        if(fgets(buffer, BUF_LENGTH, stdin) != NULL){
            buffer [strcspn(buffer, "\n")] = '\0';


            char *args[BUF_LENGTH/2+1];
            char *token = strtok(buffer, " ");
            int argc = 0;
            while(token != NULL && argc < BUF_LENGTH/2){
                args[argc++] = token;
                token = strtok(NULL, " ");
            }
            args[argc] = NULL;
            printf("Valor de argc = %i\tArgumento ingresado en 0: \"%s\"\n", argc, args[0]);
        }
    }
}
