#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int my_mkdir(int argc, char **args) {
  const char *new_dir_name = args[1];
  if (argc < 2) {
    printf("Error: debe ingresar el nombre del directorio a crear\nUso: mkdir "
           "[nombre_directorio]\n");
    return EXIT_FAILURE;
  }
  mode_t permisos = 0755;

  if (mkdir(new_dir_name, permisos) == -1) {
    perror("Error al crear directorio");
    return EXIT_FAILURE;
  } else {
    printf("Directorio '%s' creado correctamente\n", new_dir_name);
  }
  return EXIT_SUCCESS;
}
