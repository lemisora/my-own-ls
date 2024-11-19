#include "utilities.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Función para imprimir un archivo con una posición determinada
int my_cat_positioned(const char *path, off_t pos);

int my_cat(int argc, char **args) {
  if (argc == 3) {  //Caso de cat con posición específica de comienzo
    const char *file_name = args[1];    //Obtener el nombre del archivo
    off_t position = atoll(args[2]);    //Obtener la posición
    if (my_cat_positioned(file_name, position) != EXIT_SUCCESS) {   //Llamar la función que usa la posición
      printf("Saliendo de cat\n");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  } else if (argc < 2) {    //Menos argumentos
    printf("Error: debe ingresar el nombre del archivo a leer\n"
           "Uso: cat [nombre_archivo]\n"
           "O si quiere leer desde una posición específica\n"
           "Uso: cat [nombre_archivo] POSICION\n");
    return EXIT_FAILURE;
  } else if(argc > 3){  //Demasiados argumentos
    printf("Error: exceso de argumentos\n");
    return EXIT_FAILURE;
  }

  // Para leer el archivo e imprimirlo completo

  const char *file_name = args[1];  //Obtener el nombre del archivo

  int fd = open(file_name, O_RDONLY);   //Abrir el archivo con permisos de lectura únicamente
  if (fd == -1) {
    perror("Error al abrir el archivo para lectura");
    return EXIT_FAILURE;
  }

  char buffer[BUF_LENGTH];  //Buffer de caracteres
  ssize_t bytes_read;   //Para calcular el número de bytes leídos

  while ((bytes_read = read(fd, buffer, BUF_LENGTH)) > 0) { //Comparar bytes leídos con los escritos
    if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
      perror("Error al mostrar el contenido en salida estándar");
      close(fd);    //Cerrar descriptor de archivo
      return EXIT_FAILURE;
    }
  }

  if (bytes_read == -1) {
    perror("Error al leer archivo");
  }
  close(fd);    //Cerrar descriptor de archivo
  return EXIT_SUCCESS;
}

int my_cat_positioned(const char *path, off_t pos) {
  int fd = open(path, O_RDONLY);    //Abrir archivo con permisos de escritura
  if (fd == -1) {
    perror("Error al abrir el archivo");
    return EXIT_FAILURE;
  }
  if (lseek(fd, pos, SEEK_SET) == -1) { //Mover el apuntador a la posición ordenada
    perror("Error al colocarse en la posición designada");
    close(fd);  //Cerrar descriptor de archivo
    return EXIT_SUCCESS;
  }
  char buffer[BUF_LENGTH];  //Buffer de caracteres
  ssize_t bytes_read;   //Calcular el número de bytes leídos

  while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
    if (write(STDOUT_FILENO, buffer, bytes_read) == -1) {
      perror("Error al escribir en salida estándar (shell)");
      close(fd);    //Cerrar descriptor de archivo
      return EXIT_FAILURE;
    }
  }

  if (bytes_read == -1) {
    perror("Error al leer archivo");
    close(fd);  //Cerrar descriptor de archivo
    return EXIT_FAILURE;
  }

  close(fd);    //Cerrar descriptor de archivo
  return EXIT_SUCCESS;
}
