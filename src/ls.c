/*
    Este programa es una versión simplificada del programa 'ls' de los sistemas
   *nix Se emplearán descriptores de archivos y directorios para realizar la
   correcta representación en pantalla de los archivos disponibles dada una
   dirección como argumento
*/
#include "utilities.h"
#include <dirent.h> //Header para acceder a las entradas de directorio del sistema
#include <fcntl.h>
#include <pwd.h> //Header para obtener información del propietario del archivo
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Header para funciones de manipulación de cadenas
#include <sys/stat.h>
#include <time.h> // Header para funciones de tiempo
#define PATH_MAX 4096

char buffer[BUF_LENGTH];

int print_dir(DIR *dir_temp, int show_all, int detailed, const char *location);
void printBinary(unsigned int num, int bits_to_print);
void print_permissions(struct stat filestat_temp);
void bytes_converted(unsigned int bytes);

int my_ls(int argc, char **args) {
  char *location;
  int detailed = false;
  int show_all = false;
  /*
    - Se imprime la lista del directorio actual en caso de no dar una ruta
    - Se imprime la lista de archivos de la ruta dada
    - Se imprime una lista detallada si se usa el parámetro -l
  */

  if (argc < 2) {
    location = ".\0"; // Variable en la que se almacenará la cadena de la ruta
  } else if (argc == 2) {
      if(strcmp("-l", args[1]) == 0){
          location = ".\0";
          detailed = true;
      } else {
        location = args[1];
      }
  } else if (argc == 3) {
    location = args[1]; // Variable en la que se almacenará la cadena de la ruta
    if (strcmp("-l", args[2]) != 0) {
      printf("Error: opción '%s' no válida para ls\n", args[2]);
      return EXIT_FAILURE;
    } else {
        detailed = true;
    }
  }

  DIR *dir_temp; // Apuntador a directorio
  // struct stat file_temp;  //

  // printf("Dirección: %s\n", location);

  dir_temp = opendir(location);
  if (dir_temp == NULL) {
    perror("Error al abrir directorio");
    return EXIT_FAILURE;
  }

  print_dir(dir_temp, show_all, detailed, location);
  return EXIT_SUCCESS;
}

int print_dir(DIR *dir_temp, int show_all, int detailed, const char *location) {

  struct dirent *dir_ent_temp; // struct para almacenar temporalmente la entrada
                               // del directorio
  struct stat filestat_temp;   // struct para almacenar temporalmente la
                               // información del archivo
  char filepath[PATH_MAX];     // Para almacenar la ruta completa del archivo

  if(detailed){
      printf("PERMISOS   N    DUENO     GRUPO     TAMANO  FECHADEMODIFICACION "
             "INODO       OFFSET              NOMBRE\n");
      printf("==========|====|=========|=========|=======|===================|====="
             "======|===================|================================\n");
  }

  while ((dir_ent_temp = readdir(dir_temp)) !=
         NULL) { // Se obtiene la entrada actual

    if (show_all == 0 && dir_ent_temp->d_name[0] == '.') {
      continue;
    }

    // Concatenamos la ruta del directorio (location) con el nombre del archivo
    snprintf(filepath, sizeof(filepath), "%s/%s", location,
             dir_ent_temp->d_name);
    if (stat(filepath, &filestat_temp) == -1) {
      perror("Error al obtener información del archivo");
      continue;
    }

    // |PERMISOS|
    if (detailed) {
      print_permissions(filestat_temp);
      // |CARPETAS ENLACES|
      printf(" %ld\t", filestat_temp.st_nlink); // Número de enlaces

      // |PROPIETARIO|
      struct passwd *pw = getpwuid(filestat_temp.st_uid);
      if (pw) {
        printf("%-9.9s",
               pw->pw_name); // Propietario con longitud ajustada a 8 caracteres
      } else {
        printf("unknown  ");
      }

      // |GRUPO|
      struct passwd *gr = getpwuid(filestat_temp.st_gid); // Grupo
      if (gr) {
        printf(" %-9.9s",
               gr->pw_name); // Grupo con longitud ajustada a 8 caracteres
      } else {
        printf(" unknown  ");
      }

      // |TAMAÑO|
      bytes_converted(filestat_temp.st_size); // Tamaño del archivo

      // |FECHA|
      printf(" %-19.19s", ctime(&filestat_temp.st_mtime));

      // inodes
      printf(" %-11.11lu", dir_ent_temp->d_ino);
      printf(" %-11.11lu", dir_ent_temp->d_off);
    // |NOMBRE|
        strcpy(buffer, dir_ent_temp -> d_name);
        if(S_ISDIR(filestat_temp.st_mode)){
            strcat(buffer, "/");
            printf("\033[1m\033[34m %-32.32s\n\033[0m", buffer);
        } else {
            printf(" %-32.32s\n",buffer);
        }
    } else {
        strcpy(buffer, dir_ent_temp -> d_name);
        if(S_ISDIR(filestat_temp.st_mode)){
            strcat(buffer, "/");
            printf("\033[1m\033[34m%s \033[0m", buffer);
        }else{
            printf("%s ",buffer);
        }
    }
  }

  closedir(dir_temp); // Cerrar el apuntador a directorio
  printf("\n");
  return 0;
}

void printBinary(unsigned int num, int bits_to_print) {
  for (int i = bits_to_print - 1; i >= 0; i--) {
    if (i % 4 == 3 && i != bits_to_print - 1)
      printf(" ");
    printf("%d", (num >> i) & 1);
  }
}

void print_permissions(struct stat filestat_temp) {
  printf((S_ISDIR(filestat_temp.st_mode)) ? "d" : "-");
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

void bytes_converted(unsigned int bytes) {
  const char *units[] = {"B ", "KB", "MB", "GB", "TB"};
  int unit_index = 0;
  double size = bytes;

  while (size >= 1024 && unit_index < sizeof(units) / sizeof(units[0]) - 1) {
    size /= 1024;
    unit_index++;
  }
  if (unit_index > 4) {
    printf("Exceeds");
  } else {
    printf("%5.0f %s", size, units[unit_index]);
  }
}
