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
  } else if(argc > 2) {
    printf("Error: exceso de argumentos\n");
    return EXIT_FAILURE;
  }

  const char *file_name = args[1];  //Obtener el nombre del archivo a crear o sobreescribir
  int fd = open(file_name, O_WRONLY | O_CREAT, 0644);   //Abrir archivo con permisos de escritura, y en caso de no existir se crea
  if (fd == -1) {
    perror("Error al crear archivo");
    return EXIT_FAILURE;
  }
  close(fd);    //Cerrar descriptor de archivo

  //Actualizar la 'fecha de modificación'
  if (utime(file_name, NULL) == -1) {
    perror("Error al actualizar fecha de modificación");
    return EXIT_FAILURE;
  }
  printf("Se ha creado el archivo '%s'\n", file_name);
  return EXIT_SUCCESS;
}
