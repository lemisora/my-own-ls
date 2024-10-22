/*
    Este programa es una versión simplificada del programa 'ls' de los sistemas *nix
    Se emplearán descriptores de archivos y directorios para realizar la correcta representación
    en pantalla de los archivos disponibles dada una dirección como argumento
*/
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv){
    if (argc < 2){
        printf("Debe ingresar una dirección como argumento");
        return EXIT_FAILURE;
    }

    char *location = argv[1]; // Variable en la que se almacenará la cadena de ubicación

    return EXIT_SUCCESS;
}
