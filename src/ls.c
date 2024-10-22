/*
    Este programa es una versión simplificada del programa 'ls' de los sistemas *nix
    Se emplearán descriptores de archivos y directorios para realizar la correcta representación
    en pantalla de los archivos disponibles dada una dirección como argumento
*/
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h> //Header para acceder a las entradas de directorio del sistema

int main(int argc, char **argv){
    if (argc < 2){
        printf("Debe ingresar una dirección como argumento\n");
        return EXIT_FAILURE;
    }

    DIR* dir_temp;  //Apuntador a directorio
    struct dirent dir_ent_temp; //struct para almacenar temporalmente la entrada del directorio
    long prev_pos_ent;  //En esta variable se almacenará la ubicación de la entrada anterior
    //struct stat file_temp;  //

    char *location = argv[1]; // Variable en la que se almacenará la cadena de ubicación
    printf("Dirección: %s\n", location);

    dir_temp = opendir(location);
    if(dir_temp == NULL){
        perror("Error al abrir directorio");
        return EXIT_FAILURE;
    }

    prev_pos_ent = telldir(dir_temp);   //Se almacena la dirección de la entrada actual

    while(readdir(dir_temp)!= NULL){  //Se lee cada una de las entradas
        seekdir(dir_temp, prev_pos_ent);    //Reposicionamiento del apuntador basado en la posición anterior
        dir_ent_temp = *readdir(dir_temp);  //Lectura de entrada
        printf("%s\n", dir_ent_temp.d_name);    //Impresión del nombre de entrada de directorio
        prev_pos_ent = telldir(dir_temp);   //Se obtiene la dirección actual
    }
    closedir(dir_temp); // Cerrar el apuntador a directorio
    return EXIT_SUCCESS;
}
