#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int my_cat_positioned(const char* path, off_t pos){
    int fd = open(path, O_RDONLY);
    if(fd == -1){
        perror("Error al abrir el archivo");
        return EXIT_FAILURE;
    }
    if(lseek(fd, pos, SEEK_SET) == -1){
        perror("Error al colocarse en la posición designada");
        close(fd);
        return EXIT_SUCCESS;
    }
    char buffer[BUF_LENGTH];
    ssize_t bytes_read;

    while((bytes_read = read(fd, buffer, sizeof(buffer))) > 0){
        if(write(STDOUT_FILENO, buffer, bytes_read) == -1){
            perror("Error al escribir en salida estándar (shell)");
            close(fd);
            return EXIT_FAILURE;
        }
    }

    if(bytes_read == -1){
        perror("Error al leer archivo");
        close(fd);
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}

int my_cat(int argc, char** args){
    if(argc == 3){
        const char* file_name = args[1];
        off_t position = atoll(args[2]);
        if(my_cat_positioned(file_name, position) != EXIT_SUCCESS){
            printf("Saliendo de cat\n");
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    } else if(argc < 2) {
        printf("Error: debe ingresar el nombre del archivo a leer\n"
            "Uso: cat [nombre_archivo]\n"
            "O si quiere leer desde una posición específica\n"
            "Uso: cat [nombre_archivo] POSICION\n");
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
