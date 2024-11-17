#include "utilities.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int my_cat_append(int argc, char **args){
    if(argc < 10){
        printf("Error: debe acompañar de ruta del archivo y el símbolo de FIN\n");
        printf("Uso: write [nombre_archivo] [fin]\nEjemplo: write archivo.txt EOF\n");
        for(int i = 0; i < 10; i++){
            printf("args[%i]: %s\n", i+1, args[i]);
        }
        getchar();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
