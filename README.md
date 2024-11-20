# Mi Propio Shell
El objetivo de este programa es recrear una consola de comandos que permita la creacion, modificacion, eliminacion y re-ubicacion de archivos y directorios
## Instalacion
Este programa se compila bajo `C` y `Meson`, por lo que sera necesario descargarlos
**Recomendamos no utilizar la version de meson dada por apt, ya que esta no se encontrara actualizada**

***Version de Meson Recomendada:*** `1.5.0`

```bash
sudo apt-get install build-essential
sudo apt-get install python3-pip
pip install Ninja Meson
```
### Compilar programa
``` bash
meson setup out
meson compile -C out
```

### Ejecutar Programa
Simplemente es necesario abrir el ejecutable del programa `mosh`
```bash
$ out/mosh # El directorio inicial sera en el cual este posicionado
$ out/mosh [directorio a usar] # El directorio inicial sera el dado en args
```
Dentro del programa, se vera un shell parecido a de UNIX
```bash
[user@hardware:/dir]$
```
Aqui puedes ejecutar los siguientes comandos

- `ls`
  - Muestra una lista de archivos y directorio de un directorio
- `mkdir`
  - Crea un nuevo directorio
- `cat`
  - Muestra el contenido de un archivo en formato de texto
- `rm`
  - Elimina un archivo
- `rmdir`
  - Elimina un directorio
- `touch`
  - Crea un archivo de texto en blanco
- `mv`
  - Mueve o renombra archivos o directorios
- `clear`
  -Limpia la terminal


# Referencias
La tabla de permiso se cuentra dentro del header `stat.h` igual hago liga al
[Codigo del stat.h](https://sites.uclouvain.be/SystInfo/usr/include/bits/stat.h.html)

## Imprimir las fechas de Ultimas Modificaciones
[How to print date and time returned by stat function](https://stackoverflow.com/questions/32438355/how-to-print-date-and-time-returned-by-stat-function)


En el cual cada vez que el valor de numeros sobrepase su unidad, se ira cambiando el valor de `unit_index` el cual es una lista con los nombres de los valores que pueden existir
```c
const char *units[] = {"B ", "KB", "MB", "GB", "TB"};
```
En caso de que se sobrepase el valor en terabytes de `1024TB` se imprimira `Exceeds` como forma de proteccion al acceso de lista

## Utilidades del nuevo proyecto
- [x] Mini prompt (debe permitir)
  - [x] Crear archivo (similar a ```touch```)
  - [x] Escribir archivo (similar a ```cat >>``` o ```echo```)
    - [x] Si ya está creado debe escribirse toda la cadena hasta llegar hasta la palabra "FIN"
  - [x] Borrar archivo
  - [x] Mostrar archivo (similar a ```cat```)
    - [x] Especificando la posición desde la que imprimir usando un comando tipo:
    - ```bash
        mostrarArchivo [ruta]/nombreArchivo posición
      ```
    - [x] Si no se especifica posición simplemente se imprime el Archivo
  - [x] renombrarArchivo (similar a ```mv```)
  - [x] crearDirectorio (similar a ```mkdir```)
  - [x] mostrarDirectorio (similar a ```ls```)
  - [x] borrarDirectorio (similar a ```rmdir```)
  - [x] renombrarDirectorio (similar a ```mv```)
  - [x] salir

## Extras
### ls
Ciertos archivos se ocultan del sistema si el nombre del archivo empieza con `.`, por defecto estos archivos no son mostrados, en caso de que se quieran visualizar se necesitara ingregar `-h` despues del direcctorio
```bash
builddir/ls <direcctorio> -h
```
Asi la visualizacion puede ser la siguiente
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
