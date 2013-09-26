Tarea5_Grupo2
Integrantes:
-César Ávila Sánchez
-Fabricio Quirós Corella

Se envian los sgts archivos:
-Readme.txt : descripción de lo enviado
-Steps.txt : pasos realizados durante la tarea
-repmp3.c : código fuente para pipeline de mp3
-reproductor.c : código fuente para pipeline de ogg
-Makefile : makefile para compilar el programa de reproducción de mp3

Para la compilación usando el makefile:
++ El makefile compila solo para repmp3 ++
++ Es importante recordar cambiar la dirección del sistema de archivos en el makefile ++
++ Si se desea compilar para ogg cambiar repmp3 por reproductor ++
++ Si se desea compilar para la PC ++
make x86
++ Si se desea compilar para la BeagleBoard ++
make BB-xM
++ Si se desea compilar para ambas ++
make all

Para correr el programa:
./repmp3 file.mp3
./reproductor file.ogg
