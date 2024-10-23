# Mi Propio LS -l
El objetivo de este programa es recrear el funcionamiento del programa `ls` de UNIX, en especifico al usar `-l` como parametro de args.


## Compilar
Posiblemente la Unica forma de ejecucion sea mediante `Linux` ya que en `Windows` no se tiene ciertas librerias dependientes del programa

~~Como el header `dirent.h` y `stat.h`~~

### Instalar Compilador
Se ha probado que el programa se ejecuta con la version `1.6.0` de `Meson` el cual se puede instalar de la siguiente forma:
```bash
pip install Ninja
pip install Meson
```
### Compilar programa
``` bash
meson setup builddir
meson compile -C builddir
```

## Ejecucion
Si fue compilado el programa con `Meson` se tiene que ejecutar el siguiente codigo
``` bash
./builddir/ls <directorio>
```
En la parte `<directorio>` se tiene que poner un directorio existente en la computadora en la cual se checara los archivos existentes, sus permisos entre otros datos.

La visualizacion de este seria la siguiente
```bash
Dirección: ./
PERMISOS   N OWNER      GROUP     SIZE  DATE             NAME
==========|=|==========|=========|=====|================|================================
---------- 0 root       root      32816 Thu Apr 12 06:51 meson.build
-rw-rw-rw- 1 codespace  root      224   Wed Oct 23 05:23 LICENSE
-rw-rw-rw- 1 codespace  root      35149 Wed Oct 23 05:23 builddir
drwxrwxrwx 5 codespace  root      4096  Wed Oct 23 05:27 src
drwxrwxrwx 2 codespace  root      4096  Wed Oct 23 06:13 README.md
```
### Mostrar elementos ocultos
Ciertos archivos se ocultan del sistema si el nombre del archivo empieza con `.`, por defecto estos archivos no son mostrados, en caso de que se quieran visualizar se necesitara ingregar `-h` despues del direcctorio
```bash
builddir/ls <direcctorio> -h
```
Asi la visualizacion puede ser la siguiente
```bash
= Mostrando archivos ocultos
Dirección: ./
==========|=|==========|=========|=====|================|================================
---------- 0 root       unknown   32816 Thu Apr 12 06:51 meson.build
-rw-rw-rw- 1 codespace  root      224   Wed Oct 23 05:23 LICENSE
-rw-rw-rw- 1 codespace  root      35149 Wed Oct 23 05:23 builddir
drwxrwxrwx 6 codespace  codespace 4096  Wed Oct 23 08:10 .git
drwxrwxrwx 9 codespace  root      4096  Wed Oct 23 05:23 .gitignore
-rw-rw-rw- 1 codespace  codespace 16    Wed Oct 23 05:33 .
drwxrwxrwx 5 codespace  root      4096  Wed Oct 23 05:27 src
drwxrwxrwx 2 codespace  root      4096  Wed Oct 23 06:13 README.md
-rw-rw-rw- 1 codespace  root      961   Wed Oct 23 08:03 ..
```

# Explicaciones del Programa
## Como obtengo los archivos del directorio?
Usando esta parte del codigo, se permite obtener el direcctorio dado y usamos los headers de `dirent.h` para traducir ciertos datos
```c
// Header para uso de Directorios
#include <dirent.h>

// Obtener el direcctorio ROOT
DIR* dir = opendir(char *location);

// Lee si a donde se apunta existe un direcctorio
readdir(dir);

// busca un archivo siguiente a uno base
seekdir(dir_new, dir_old);

// Almacena la direccion actual para se manejada
telldir(dir);

// Obtenemos la informacion de los archivos
struct stat filestat;
struct dirent dir_ent;
stat(dir_ent.d_name, &filestat);
```
## Obtener los bits de permisos
``` c
#include <sys/stat.h>
// Obtener un bool si existe cierto permiso
int read = filestat.st_mode & S_IRUSR;
```
La tabla de permiso se cuentra dentro del header `stat.h` igual hago liga al 
[Codigo del stat.h](https://sites.uclouvain.be/SystInfo/usr/include/bits/stat.h.html)

## Obtener nombres de propietarios
```c
#include <pwd.h>
// Obtener propietario del Archivo
struct passwd *pw = getpwuid(filestat_temp.st_uid);
printf("%s", pw->pw_name);

// Obtener Grupo al que pertenece
struct passwd *gr = getpwuid(filestat_temp.st_gid);
printf("s", gr->pw_name);
```
## Imprimir las fechas de Ultimas Modificaciones
[How to print date and time returned by stat function](https://stackoverflow.com/questions/32438355/how-to-print-date-and-time-returned-by-stat-function)

Si tenemos `filestat` este tendra las ligas a los tiempos de ultima modificacion, creacion y Acceso.
`.st_mtime` `.st_birthtime` `.st_atime`
```c
#include <time.h>
#include <sys/stat.h>
// Imprimir formateado la fecha
ctime(&filestat.st_mtime)
```
## Modificaciones al Print
Para respetar la visualizacion del programa, los prints tienen un limite para saber quien es el `Owner`, `Group` y la fecha de moficacion `Date`, se usa el siente print

_Codigo_
```c
char [16] variable = "1234567890ABCDEF"
printf(%-9.9s, variable)
```
_Consola_
```bash
$ 123456789
```