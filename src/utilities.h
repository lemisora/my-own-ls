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

#endif
