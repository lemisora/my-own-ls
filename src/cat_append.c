#include "utilities.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int my_cat_append(int argc, char **args){
    if(argc != 3){
        printf("Error: debe acompañar de ruta del archivo y el símbolo de FIN\n");
        printf("Uso: write [nombre_archivo] [fin]\nEjemplo: write archivo.txt EOF\n");
        return EXIT_FAILURE;
    }

    const char* file_path = args[1];
    const char* end_condition = args[2];

    int fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd < 0){
        perror("Error al abrir el archivo");
        return EXIT_FAILURE;
    }

    char buffer[BUF_LENGTH];
    while(1){
        fflush(stdin);
        printf("~ ");
        if(!fgets(buffer, sizeof(buffer), stdin)){
            perror("Error al leer entrada");
            close(fd);
            return EXIT_FAILURE;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        if(strcmp(buffer, end_condition) == 0){
            break;
        }
        strcat(buffer, "\n");

        ssize_t string_length = strlen(buffer);

        if(write(fd, buffer, string_length) == -1){
            perror("Error al escribir en el archivo");
            close(fd);
            return EXIT_FAILURE;
        }
    }
    close(fd);
    printf("Se ha escrito en el archivo '%s'\n", file_path);
    return EXIT_SUCCESS;
}
