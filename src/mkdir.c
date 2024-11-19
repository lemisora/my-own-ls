#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int my_mkdir(int argc, char **args) {
  if (argc < 2) {
    printf("Error: debe ingresar el nombre del directorio a crear\nUso: mkdir "
           "[nombre_directorio]\n");
    return EXIT_FAILURE;
  } else if(argc > 2) {
      printf("Error: exceso de argumentos\n");
      return EXIT_FAILURE;
  }
  const char *new_dir_name = args[1];   //Obtener la ruta de los argumentos
  mode_t permisos = 0755; //Definir los permisos por defecto

  //Crear el directorio con mkdir() de unistd.h
  if (mkdir(new_dir_name, permisos) == -1) {
    perror("Error al crear directorio");
    return EXIT_FAILURE;
  } else {
    printf("Directorio '%s' creado correctamente\n", new_dir_name);
  }
  return EXIT_SUCCESS;
}
