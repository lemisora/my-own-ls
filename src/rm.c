#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int my_rm_r(const char* path){
    struct stat path_stat;
    if(stat(path, &path_stat) != 0){
        perror("Error al acceder a la ruta ingresada");
        return EXIT_FAILURE;
    }
    if(S_ISREG(path_stat.st_mode)){
        if(unlink(path) != 0){
            perror("Error al eliminar");
            return EXIT_FAILURE;
        }
    }else if(S_ISDIR(path_stat.st_mode)){
        DIR *temp_dir = opendir(path);
        if(!temp_dir){
            perror("Error al abrir directorio");
            return EXIT_FAILURE;
        }
        struct dirent *entry;
        while((entry = readdir(temp_dir)) != NULL){
            if(strcmp(entry -> d_name, ".") == 0 || strcmp(entry -> d_name, "..") == 0){
                continue;
            }
            char full_path[BUF_LENGTH];
            if(snprintf(full_path, sizeof(full_path), "%s/%s", path, entry -> d_name) >= sizeof(full_path)){
                fprintf(stderr, "Error: ruta demasiado larga\n");
                closedir(temp_dir);
                return EXIT_FAILURE;
            }

            if(my_rm_r(full_path) != 0){
                closedir(temp_dir);
                perror("Error al eliminar directorio");
                return EXIT_FAILURE;
            }
        }
        closedir(temp_dir);

        if(rmdir(path) != 0){
            perror("Error al eliminar directorio");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int my_rm(int argc, char **args){
    if(argc < 2){
        printf("Error: debe ingresar el nombre o ruta del archivo a borrar\nUso: rm [ruta_archivo]\n");
        return EXIT_FAILURE;
    }
    int recursive = 0;
    const char* file_path;

    if(strcmp(args[1], "-r") == 0){
        if(argc < 3){
            fprintf(stderr, "Error: debe ingresar la ruta después de '-r'\n");
            return EXIT_FAILURE;
        }
        recursive = 1;
        file_path = args[2];
    }else{
        file_path = args[1];
    }

    if(recursive){
        printf("¿Desea eliminar '%s'? [s/n] ", file_path);
        char opc = getchar();
        getchar();
        if(opc != 's'){
            printf("Operación cancelada\n");
            return EXIT_SUCCESS;
        }
    }

    if((recursive ? my_rm_r(file_path) : unlink(file_path)) != 0){
        fprintf(stderr, "Error al eliminar '%s'\n", file_path);
        return EXIT_FAILURE;
    }
    printf("Se ha borrado el archivo '%s' de forma exitosa\n", file_path);
    return EXIT_SUCCESS;
}
