#include "utilities.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int my_cat_append(int argc, char **args) {
  if (argc != 3) {
    printf("Error: debe acompañar de ruta del archivo y el símbolo de FIN\n");
    printf(
        "Uso: write [nombre_archivo] [fin]\nEjemplo: write archivo.txt EOF\n");
    return EXIT_FAILURE;
  }

  const char *file_path = args[1]; // Se almacena la ruta del archivo
  const char *end_condition = args[2]; // Se almacena la cadena de finalización de escritura

  int fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND,
                0644); // Se abre el archivo, si no existe se crea, si existe se
                       // escribe en él, si existe y tiene texto entonces se
                       // concatena el texto ingresado
  if (fd < 0) {
    perror("Error al abrir el archivo");
    return EXIT_FAILURE;
  }

  char buffer[BUF_LENGTH];  //Reserva de memoria para el buffer de caracteres

  while (1) {
    printf("~ ");   //Símbolo que representa el inicio de una línea en el texto

    //Leer lo ingresado por el usuario y guardarlo en el buffer
    if (!fgets(buffer, sizeof(buffer), stdin)) {
      perror("Error al leer entrada");
      close(fd);
      return EXIT_FAILURE;
    }

    //Formateo del buffer para hacer que sea válido
    buffer[strcspn(buffer, "\n")] = '\0';

    //Terminar el ciclo cuando se encuentra la condición de finalización
    if (strcmp(buffer, end_condition) == 0) break;

    //Concatenar salto de línea para imprimirlo correctamente en el archivo
    strcat(buffer, "\n");

    //Se calcula el tamaño de la cadena para guardar dicha cantidad de caracteres en el archivo
    ssize_t string_length = strlen(buffer);

    //Escribir al archivo
    if (write(fd, buffer, string_length) == -1) {
      perror("Error al escribir en el archivo");
      close(fd);
      return EXIT_FAILURE;
    }
  }
  close(fd);    //Se cierra el descriptor de archivo
  printf("Se ha escrito en el archivo '%s'\n", file_path);
  return EXIT_SUCCESS;
}
