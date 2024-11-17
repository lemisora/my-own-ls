#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int my_rmdir(int argc, char **args) {
  if (argc < 2) {
    printf("Error: debe ingresar el nombre del directorio a eliminar\nUso: "
           "rmdir [nombre_directorio]\n");
    return EXIT_FAILURE;
  }
  const char *dir_name = args[1];

  if (rmdir(dir_name) == 0) {
    printf("Se ha eliminado '%s' de forma exitosa\n", dir_name);
  } else {
    perror("No se pudo eliminar");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
