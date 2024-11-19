#include "utilities.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

//Función de eliminado recursiva
int my_rm_r(const char *path);

int my_rm(int argc, char **args) {
  if (argc < 2) {
    printf("Error: debe ingresar el nombre o ruta del archivo a borrar\nUso: "
           "rm [ruta_archivo]\n");
    return EXIT_FAILURE;
  } else if(argc > 2){
    printf("Error: exceso de argumentos\n");
    return EXIT_FAILURE;
  }
  int recursive = 0;    //Boolean para decidir si se utiliza la versión recursiva
  const char *file_path;    //Ruta del archivo o directorio

  //Verificar si se necesita la versión recursiva
  if (strcmp(args[1], "-r") == 0) {
    if (argc < 3) {
      fprintf(stderr, "Error: debe ingresar la ruta después de '-r'\n");
      return EXIT_FAILURE;
    }
    recursive = 1;  // Se llamará a la versión recursiva
    file_path = args[2];    //Se obtiene la ruta
  } else {
    file_path = args[1];    //Se obtiene la ruta
  }

  if (recursive) {
    printf("¿Desea eliminar '%s'? [s/n] ", file_path);
    char opc = getchar();   //Se obtiene confirmación
    getchar();  //Obtener caracteres extra que no correspondan
    if (opc != 's') {
      printf("Operación cancelada\n");
      return EXIT_SUCCESS;
    }
  }

  if ((recursive ? my_rm_r(file_path) : unlink(file_path)) != 0) {  //Llamar a la función recursiva o eliminar el archivo
    perror("Error al eliminar");
    return EXIT_FAILURE;
  }
  if(recursive)
      printf("Se ha borrado el directorio '%s' con su contenido de forma exitosa\n", file_path);
  else
      printf("Se ha borrado el archivo '%s' de forma exitosa\n", file_path);
  return EXIT_SUCCESS;
}

//Función recursiva para eliminar directorios y su contenido, archivos y directorios incluidos
int my_rm_r(const char *path) {
  struct stat path_stat;    //Se obtiene información de las entradas del directorio
  if (stat(path, &path_stat) != 0) {
    perror("Error al acceder a la ruta ingresada");
    return EXIT_FAILURE;
  }
  if (S_ISREG(path_stat.st_mode)) { //Si es archivo común
    if (unlink(path) != 0) {
      perror("Error al eliminar");
      return EXIT_FAILURE;
    }
  } else if (S_ISDIR(path_stat.st_mode)) {  //En caso de que sea directorio
    DIR *temp_dir = opendir(path);          //Se abre el directorio para eliminar su contenido, en caso de tener
    if (!temp_dir) {
      perror("Error al abrir directorio");
      return EXIT_FAILURE;
    }
    struct dirent *entry;                   //struct para almacenar las entradas del directorio
    while ((entry = readdir(temp_dir)) != NULL) {   //Eliminar cada una de las entradas hasta que no haya nada
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {    //Ignorar la carpeta actual y la carpeta padre
        continue;
      }
      char full_path[BUF_LENGTH];   //Buffer para la ruta completa

      //Obtener la ruta completa y verificar que sea válida
      if (snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name) >= sizeof(full_path)) {
        fprintf(stderr, "Error: ruta demasiado larga\n");
        closedir(temp_dir); //Cerrar directorio
        return EXIT_FAILURE;
      }

      //Eliminar el directorio accediendo a la función recursiva
      if (my_rm_r(full_path) != 0) {
        closedir(temp_dir);
        perror("Error al eliminar directorio");
        return EXIT_FAILURE;
      }
    }
    closedir(temp_dir);

    //Una vez vacio eliminar el directorio con rmdir()
    if (rmdir(path) != 0) {
      perror("Error al eliminar directorio");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
