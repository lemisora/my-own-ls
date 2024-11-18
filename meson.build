#Archivo de configuración de Meson para el proyecto
project('my-own-shell', 'c', version: '1.1')
executable(
  'mosh', # Nombre del ejecutable
  'src/my_shell.c', # Código fuente principal
  # Utilidades de la shell (mosh-utils)
  'src/ls.c',
  'src/mkdir.c',
  'src/rmdir.c',
  'src/touch.c',
  'src/rm.c',
  'src/cat.c',
  'src/cat_append.c',
  'src/mv.c',
  install: true, # Instalar ejecutable en una carpeta determinada
)
