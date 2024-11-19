#include "utilities.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int my_mv(int argc, char **args) {
  if (argc != 3) {
    printf("Error: debe incluir la ruta de origen y la ruta destino\n");
    return EXIT_FAILURE;
  }

  const char *origin_path = args[1]; //Aquí se almacena la ruta de origen
  const char *dest_path = args[2];  //Aquí se almacena la ruta destino

  //Se hace el cambio de nombre
  if (rename(origin_path, dest_path) == 0) {
    printf("'%s' se ha renombrado a '%s' de forma exitosa\n", origin_path, dest_path);
  } else {
    perror("Ocurrió un error al renombrar");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
