#include "utilities.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// int my_mv(int argc, char **args){
//     if(argc < 3){
//         printf("Error: se debe ingresar el nombre/ruta del archivo o
//         directorio original y del nombre/ruta destino\n"); printf("Uso: mv
//         [ruta_original] [ruta_destino]\n"); return EXIT_FAILURE;
//     }
//     const char* origin = args[1];
//     const char* destination = args[2];

//     int org_fd = open(origin, O_RDONLY);
//     if(org_fd == -1){
//         perror("Error al leer archivo de origen");
//         return EXIT_FAILURE;
//     }

//     int dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if(dest_fd == -1){
//         perror("Error al crear el archivo de destino");
//         return EXIT_FAILURE;
//     }

//     char buffer[BUF_LENGTH];
//     ssize_t bytes_read, bytes_written;
//     while((bytes_read = read(org_fd, buffer, BUF_LENGTH)) > 0){
//         bytes_written = write(dest_fd, buffer, bytes_read);
//         if(bytes_written != bytes_read){
//             perror("Error al escribir archivo de destino");
//             close(org_fd);
//             close(dest_fd);
//             return EXIT_FAILURE;
//         }
//     }

//     if(bytes_read == -1){
//         perror("Error al abrir archivo origen");
//         return EXIT_FAILURE;
//     }

//     close(org_fd);
//     close(dest_fd);

//     if(unlink(origin) == -1){
//         perror("Error al eliminar el archivo de origen");
//         return EXIT_FAILURE;
//     }

//     return EXIT_SUCCESS;
// }

int my_mv(int argc, char **args) {
  if (argc != 3) {
    printf("Error: debe incluir la ruta de origen y la ruta destino\n");
    return EXIT_FAILURE;
  }

  const char *origin_path = args[1];
  const char *dest_path = args[2];

  if (rename(origin_path, dest_path) == 0) {
    printf("'%s' se ha renombrado a '%s' de forma exitosa\n", origin_path,
           dest_path);
  } else {
    perror("Ocurrió un error al renombrar");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
