#ifndef MOSH_UTILS_H
#define MOSH_UTILS_H

#define BUF_LENGTH 1024
#define PATH_MAX_LENGTH 1024

#include <stdio.h>

int my_touch(int argc, char **args);
int my_cat_append(int argc, char **args);
int my_rm(int argc, char **args);
int my_cat(int argc, char **args);
int my_mv(int argc, char **args);
int my_mkdir(int argc, char **args);
int my_ls(int argc, char **args);
int my_rmdir(int argc, char **args);

//Funciones para mosh_history.c
//Función principal para manejar el historial de mosh
int history_handling();

//Función para añadir entradas al mosh_history
int add_to_mosh_history(const char **);

//Función para controlar la navegación del historial con las teclas arriba-abajo
void handle_mosh_history_nav(int key, char *buffer, int *pos);

//Función para habilitar 'raw_mode' y manejar directamente las teclas
void enable_raw_mode();

//Función para deshabilitar el 'raw_mode'
void disable_raw_mode();

#endif
