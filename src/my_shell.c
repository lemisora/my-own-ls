#include "utilities.h"
#include <locale.h> //Header para poder mostrar los mensajes de perror() en el idioma del sistema
#include <pwd.h>    //Header para acceder a propiedades del usuario actual para el prompt
#include <stdbool.h>    //Header que provee a C la capacidad de usar booleanos
#include <stdio.h>      //Funciones de entrada/salida
#include <stdlib.h>     //Otorga la función exit() y los macros para salida exitosa y salida con error
#include <string.h>     //Otorga funciones para manejo de cadenas
#include <unistd.h>     //Otorga funciones para imprimir información útil en el prompt

#define KW_NUM 11   //Número de palabras reservadas (comandos) que interpreta la shell

const char *user;   //Aquí se almacena el nombre del usuario actual
char hostname[BUF_LENGTH];  //Aquí se almacena el hostname del usuario actual

//Arreglo de comandos disponibles
char *keywords[KW_NUM] = {"exit", "help",  "touch", "write", "rm",   "cat",
                          "mv",   "mkdir", "ls",    "rmdir", "clear"};

//Imprimir el prompt
void printPrompt(const char *usr, char *hostname) {
  char dir_actual[PATH_MAX_LENGTH]; //Obtener la ruta actual

  //Se imprime el prompt en color verde
  if (getcwd(dir_actual, sizeof(dir_actual)) != NULL) {
    printf("\033[1m\033[32m[%s@%s\033[0m\033[1m:%s]$ \033[0m", user,
           hostname, dir_actual);
  } else {
    printf("\033[1m\033[32m[%s@%s\033[0m\033[1m]$ \033[0m", user,
           hostname);
  }
}

//Imprimir mensaje inicial
void printInitMsg() {
  printf("Bienvenido a My Own Shell (Development)!\nPara más información "
         "acerca de los comandos disponibles ingrese el comando: 'help'\n");
}

//Imprimir mensaje de salida
void printExitMsg() { printf("Saliendo de mosh-dev\n"); }

//Función para limpiar la pantalla
void clear_screen() { printf("\033[2J\033[H"); }

//Función para mapear comandos
int shellKeyword(char *command) {
    for (int i = 0; i < KW_NUM; i++)
        if (strcmp(keywords[i], command) == 0)
            return i;
    return -1;
}

//Función para mostrar más información sobre los comandos disponibles en mosh
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

int main(void) {
  int argc; //Variable para contar los argumentos de cada una de las utilidades
  if (setlocale(LC_ALL, "") == NULL)    //Se configura el idioma para mostrar mensajes de error del sistema con perror()
    perror("Error al configurar localización de idioma");

  //Obtener UID del usuario
  uid_t uid = getuid();
  struct passwd *pw = getpwuid(uid);

  if (pw == NULL) {
    perror("Error al iniciar shell, no se encuentra usuario");
    return EXIT_FAILURE;
  }

  //Obtener el nombre del usuario y el hostname
  user = pw->pw_name;
  if (gethostname(hostname, sizeof(hostname)) == -1) {
    perror("Error al iniciar shell, no se encuentra hostname");
    return EXIT_FAILURE;
  }

  //Se reserva memoria para el buffer de caracteres
  char buffer[BUF_LENGTH];
  printInitMsg(); //Mensaje inicial

  while (1) {
    printPrompt(user, hostname);    //Se imprime el prompt

    //Interpretación de comandos ingresados
    if (fgets(buffer, BUF_LENGTH, stdin) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0'; //Reformateo de la cadena para hacerla válida

      if(strlen(buffer) == 0) continue; //Pasar al siguiente ciclo de reconocimiento de comando si se ingresa un ENTER

      //Tokenización de argumentos
      char *args[BUF_LENGTH / 2 + 1];
      char *token = strtok(buffer, " ");
      argc = 0; //Reinicialización del contador de argumentos
      while (token != NULL && argc < BUF_LENGTH) {
        args[argc++] = token;
        token = strtok(NULL, " ");
      }
      args[argc] = NULL;

      //Mapeo de comandos
      int cmd_mapper = shellKeyword(args[0]);

      //Verificación de validez de comando y ejecución de la tarea que le corresponde
      switch (cmd_mapper) {
      case 0:   //Salir de a shell
        printExitMsg();
        exit(EXIT_SUCCESS);
        break;
      case 1:   //Imprimir ayuda
        showHelp();
        break;
      case 2:   //Comando touch
        my_touch(argc, args);
        break;
      case 3:   //Comando write
        my_cat_append(argc, args);
        break;
      case 4:   //Comando rm
        my_rm(argc, args);
        break;
      case 5:   //Comando cat
        my_cat(argc, args);
        break;
      case 6:   //Comando mv
        my_mv(argc, args);
        break;
      case 7:   //Comando mkdir
        my_mkdir(argc, args);
        break;
      case 8:   //Comando ls
        my_ls(argc, args);
        break;
      case 9:   //Comando rmdir
        my_rmdir(argc, args);
        break;
      case 10:  //Comando clear
        clear_screen();
        break;
      default:  //Comando desconocido
        printf("\033[1m\033[31mError:\033[0m Comando '%s' no reconocido\n", //Se imprime un error resaltado en rojo
               buffer);
        break;
      }
    }
  }
}
