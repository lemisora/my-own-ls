#include "utilities.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>

// Implementación de touch para crear archivos con mosh
int my_touch(int argc, char **args) {
  if (argc < 2) {
    printf("Error: debe de ingresar el nombre del fichero/archivo a "
           "crear\nUso: touch [nombre_fichero]\n");
    return EXIT_FAILURE;
  }

  const char *file_name = args[1];
  int fd = open(file_name, O_WRONLY | O_CREAT, 0644);
  if (fd == -1) {
    perror("Error al crear archivo");
    return EXIT_FAILURE;
  }
  close(fd);
  if (utime(file_name, NULL) == -1) {
    perror("Error al actualizar fecha de modificación");
    return EXIT_FAILURE;
  }
  printf("Se ha creado el archivo '%s'\n", file_name);
  return EXIT_SUCCESS;
}
