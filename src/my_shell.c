#include "utilities.h"
#include <locale.h>
#include <pwd.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define KW_NUM 11

const char *user;
char hostname[BUF_LENGTH];

char *keywords[KW_NUM] = {"exit", "help",  "touch", "write", "rm",   "cat",
                          "mv",   "mkdir", "ls",    "rmdir", "clear"};

void printPrompt(const char *usr, char *hostname) {
  char dir_actual[PATH_MAX_LENGTH];
  if (getcwd(dir_actual, sizeof(dir_actual)) != NULL) {
    printf("\033[1m\033[34m[%s@\033[32m%s\033[0m\033[1m:%s]$ \033[0m", user,
           hostname, dir_actual);
  } else {
    printf("\033[1m\033[34m[%s@\033[32m%s\033[0m\033[1m]$ \033[0m", user,
           hostname);
  }
}

void printInitMsg() {
  printf("Bienvenido a My Own Shell (Development)!\nPara más información "
         "acerca de los comandos disponibles ingrese el comando: 'help'\n");
}

void printExitMsg() { printf("Saliendo de mosh-dev\n"); }

void clear_screen() { printf("\033[2J\033[H"); }

int shellKeyword(char *command) {
  for (int i = 0; i < KW_NUM; i++)
    if (strcmp(keywords[i], command) == 0)
      return i;
  return -1;
}

void showHelp() {
  printf("Los comandos disponibles en esta shell son los siguientes:\n");
  printf("touch - Crear un archivo vacío\n\tUso: touch [nombre_archivo]\n");
  printf("write - Escribir a un archivo\n\tUso: write [nombre_archivo] "
         "PARAMETRO_FIN\n");
  printf(
      "rm - Eliminar un archivo\n\tUso: rm [nombre_archivo]\nrm -r - Eliminar "
      "directorio con todos sus archivos\n\tUso: rm -r [nombre_directorio]\n");
  printf("cat - Leer el contenido de un archivo e imprimirlo en salida "
         "estándar (en la terminal)\n\tUso: cat [nombre_archivo]\n"
         "cat [nombre_archivo] POSICION - Para leer un archivo e imprimirlo "
         "desde una posición especificada\n"
         "\tEjemplo: cat archivo.txt 2\n");
  printf("ls - Listar los archivos y directorios del directorio en el que se "
         "encuentre o de la dirección proporcionada\n");
  printf("mv - Mover un archivo o un directorio de un lugar a otro o para "
         "cambiarlo de "
         "nombre\n\tUso: mv [ruta_origen] [ruta_destino]\n");
  printf("mkdir - Crear un directorio vacío\n\tUso: mkdir "
         "[nombre_nuevo_directorio]\n");
  printf("rmdir - Eliminar un directorio vacío\n\tUso: rmdir "
         "[nombre_directorio]\n");
  printf("help - Imprimir esta ayuda\n");
  printf("clear - Limpiar el contenido de la pantalla\n");
  printf("exit - Para salir de esta shell\n");
}

int main() {
  int argc;
  if (setlocale(LC_ALL, "") == NULL)
    perror("Error al configurar localización de idioma");

  uid_t uid = getuid();
  struct passwd *pw = getpwuid(uid);

  if (pw == NULL) {
    perror("Error al iniciar shell, no se encuentra usuario");
    return EXIT_FAILURE;
  }

  user = pw->pw_name;
  if (gethostname(hostname, sizeof(hostname)) == -1) {
    perror("Error al iniciar shell, no se encuentra hostname");
    return EXIT_FAILURE;
  }

  char buffer[BUF_LENGTH];
  printInitMsg();

  while (1) {
    printPrompt(user, hostname);
    if (fgets(buffer, BUF_LENGTH, stdin) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      char *args[BUF_LENGTH / 2 + 1];
      char *token = strtok(buffer, " ");
      argc = 0;
      while (token != NULL && argc < BUF_LENGTH) {
        args[argc++] = token;
        token = strtok(NULL, " ");
      }
      args[argc] = NULL;

      int cmd_mapper = shellKeyword(args[0]);
      switch (cmd_mapper) {
      case 0:
        printExitMsg();
        exit(EXIT_SUCCESS);
        break;
      case 1:
        showHelp();
        break;
      case 2:
        my_touch(argc, args);
        break;
      case 3:
        my_cat_append(argc, args);
        break;
      case 4:
        my_rm(argc, args);
        break;
      case 5:
        my_cat(argc, args);
        break;
      case 6:
        my_mv(argc, args);
        break;
      case 7:
        my_mkdir(argc, args);
        break;
      case 8:
        my_ls(argc, args);
        break;
      case 9:
        my_rmdir(argc, args);
        break;
      case 10:
        clear_screen();
        break;
      default:
        printf("\033[1m\033[31mError:\033[0m Comando '%s' no reconocido\n",
               buffer);
        break;
      }
    }
  }
}
