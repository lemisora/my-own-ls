#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int my_rm_r(){
    return EXIT_SUCCESS;
}

int my_rm(int argc, char **args){
    if(argc < 2){
        printf("Error: debe ingresar el nombre o ruta del archivo a borrar\nUso: rm [ruta_archivo]\n");
        return EXIT_FAILURE;
    }

    const char* file_path = args[1];

    if(unlink(file_path) == 0){
        printf("Se ha borrado el archivo '%s' de forma exitosa\n", file_path);
    } else {
        perror("Error al eliminar el archivo");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
