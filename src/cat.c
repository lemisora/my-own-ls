#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int my_cat(int argc, char** args){
    if(argc < 2){
        printf("Error: debe ingresar el nombre del archivo a leer\nUso: cat [nombre_archivo]\n");
        return EXIT_FAILURE;
    }

    const char* file_name = args[1];

    int fd = open(file_name, O_RDONLY);
    if(fd == -1){
        perror("Error al abrir el archivo para lectura");
        return EXIT_FAILURE;
    }

    char buffer[BUF_LENGTH];
    ssize_t bytes_read;

    while((bytes_read = read(fd, buffer, BUF_LENGTH)) > 0){
        if(write(STDOUT_FILENO, buffer, bytes_read) != bytes_read){
            perror("Error al mostrar el contenido en salida estándar");
            close(fd);
            return EXIT_FAILURE;
        }
    }

    if(bytes_read == -1){
        perror("Error al leer archivo");
    }
    close(fd);
    return EXIT_SUCCESS;
}
