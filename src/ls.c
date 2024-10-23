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
#include <pwd.h>    //Header para obtener información del propietario del archivo
#include <string.h> //Header para funciones de manipulación de cadenas
#include <time.h> // Header para funciones de tiempo

int print_dir(DIR *dir_temp, int show_hidden);
void printBinary(unsigned int num, int bits_to_print);
void print_permissions(struct stat filestat_temp);

int main(int argc, char **argv){
    if (argc < 2){
        printf("Debe ingresar una dirección como argumento\n");
        return EXIT_FAILURE;
    }

    int show_hidden = 0;    //Variable para mostrar archivos ocultos
    if (argc > 2){
        if (strcmp(argv[2], "-h") == 0)
        {
            printf("= Mostrando archivos ocultos\n");
            show_hidden = 1;
        }
    }
    

    DIR* dir_temp;  //Apuntador a directorio
    //struct stat file_temp;  //

    char *location = argv[1]; // Variable en la que se almacenará la cadena de ubicación
    printf("Dirección: %s\n", location);

    dir_temp = opendir(location);
    if(dir_temp == NULL){
        perror("Error al abrir directorio");
        return EXIT_FAILURE;
    }

    print_dir(dir_temp, show_hidden);

    
    return EXIT_SUCCESS;
}


int print_dir(DIR *dir_temp, int show_hidden){

    /* Print Example First Template 
    |PERMISOS  |N|OWNER    ||GROUP|  |SIZE| |DATE|       |NAME|
    -rw-rw-rw-  1 codespace root      35149 Oct 23 05:23 LICENSE
    -rw-rw-rw-  1 codespace root          0 Oct 23 05:23 README.md
    drwxrwxrwx+ 6 codespace codespace  4096 Oct 23 05:32 builddir
    -rw-rw-rw-  1 codespace root        224 Oct 23 05:23 meson.build
    drwxrwxrwx+ 2 codespace root       4096 Oct 23 05:23 src
     */


    struct dirent dir_ent_temp; //struct para almacenar temporalmente la entrada del directorio
    struct stat filestat_temp;  //struct para almacenar temporalmente la información del archivo
    long prev_pos_ent;  //En esta variable se almacenará la ubicación de la entrada anterior
    prev_pos_ent = telldir(dir_temp);   //Se almacena la dirección de la entrada actual

    printf("PERMISOS   N OWNER      GROUP     SIZE  DATE             NAME\n");
    printf("==========|=|==========|=========|=====|================|================================\n");

    while(readdir(dir_temp)!= NULL){  //Se lee cada una de las entradas
        seekdir(dir_temp, prev_pos_ent);    //Reposicionamiento del apuntador basado en la posición anterior
        
        stat(dir_ent_temp.d_name, &filestat_temp); //Se obtiene la información del archivo
        dir_ent_temp = *readdir(dir_temp);  //Lectura de entrada
        if (show_hidden == 0 && dir_ent_temp.d_name[0] == '.'){
            prev_pos_ent = telldir(dir_temp);   //Se obtiene la dirección actual
            continue;
        }
        print_permissions(filestat_temp);
        printf(" %ld ", filestat_temp.st_nlink); // Número de enlaces


        struct passwd *pw = getpwuid(filestat_temp.st_uid);
        if (pw) {
            printf("%-9.9s", pw->pw_name); // Propietario con longitud ajustada a 8 caracteres
        } else {
            printf("unknown");
        }

        struct passwd *gr = getpwuid(filestat_temp.st_gid); // Grupo
        if (gr) {
            printf("\t%-9.9s", gr->pw_name); // Grupo con longitud ajustada a 8 caracteres
        } else {
            printf("\tunknown  ");
        }

        printf(" %ld", filestat_temp.st_size); // Tamaño del archivo
        
        printf("\t%-16.16s", ctime(&filestat_temp.st_mtime));
        
        printf(" %s\n", dir_ent_temp.d_name); // Impresión del nombre del archivo
        prev_pos_ent = telldir(dir_temp);   //Se obtiene la dirección actual
    }

    closedir(dir_temp); // Cerrar el apuntador a directorio

    return 0;
}

void printBinary(unsigned int num, int bits_to_print) {
    for (int i = bits_to_print - 1; i >= 0; i--) {
        if (i % 4 == 3 && i != bits_to_print - 1)
            printf(" ");
        printf("%d", (num >> i) & 1);
    }
}

void print_permissions(struct stat filestat_temp){
    printf((S_ISDIR(filestat_temp.st_mode))  ? "d" : "-");
    printf((filestat_temp.st_mode & S_IRUSR) ? "r" : "-");
    printf((filestat_temp.st_mode & S_IWUSR) ? "w" : "-");
    printf((filestat_temp.st_mode & S_IXUSR) ? "x" : "-");
    printf((filestat_temp.st_mode & S_IRGRP) ? "r" : "-");
    printf((filestat_temp.st_mode & S_IWGRP) ? "w" : "-");
    printf((filestat_temp.st_mode & S_IXGRP) ? "x" : "-");
    printf((filestat_temp.st_mode & S_IROTH) ? "r" : "-");
    printf((filestat_temp.st_mode & S_IWOTH) ? "w" : "-");
    printf((filestat_temp.st_mode & S_IXOTH) ? "x" : "-");
}