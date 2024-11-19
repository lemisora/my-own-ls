/*
* Headers que proveen acceso a las funciones prototipadas
* Las funciones aquí descritas son las utilidades que usa mosh para interactuar con los archivos y directorios del sistema de archivos
* mosh-utils
*/

#ifndef MOSH_UTILS_H
#define MOSH_UTILS_H

//Tamaño determinado para los buffers
#define BUF_LENGTH 1024

//Tamaño determinado para las rutas
#define PATH_MAX_LENGTH 1024

//Función para crear archivos vacíos
int my_touch(int argc, char **args);

//Función para escribir texto a un archivo, se llama en la shell con el comando 'write'
int my_cat_append(int argc, char **args);

//Función para eliminar archivos, tiene dentro una versión recursiva para eliminar un directorio que contenga archivos
int my_rm(int argc, char **args);

//Función para leer e imprimir el texto de un archivo a la salida estándar
int my_cat(int argc, char **args);

//Función para mover o renombrar archivos y directorios
int my_mv(int argc, char **args);

//Función para crear directorios
int my_mkdir(int argc, char **args);

//Función para listar los archivos y directorios contenidos dentro del directorio actual o de la ruta especificada
int my_ls(int argc, char **args);

//Función para eliminar directorios vacíos
int my_rmdir(int argc, char **args);

#endif
