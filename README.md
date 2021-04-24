# Multiplicacion-de-Matrices-x-BloquescOpenMP
Implementacion del algoritmo 1D del algoritmo de multiplicacion por bloques utlizando OpenMP

##Compilar Secuencial
gcc -o secuencial -Wall secuencial.c matrix.c

##Compilar OpenMp
gcc -o openmp -fopenmp -Wall openmp.c matrix.c

##Ejecutar Script
./script.sh

###Nota
 En esta prueba se crean archivos de con solo 2 datos en los archivos. Para hacer la prueba real cambiar el valor del
 "c" en el for del script a 100
 Tambien falta la ejecucion con 2048, 4096 y 8192 pero se pueden agregar al script aunque es conveniente ejecutarlas menos de 
 100 veces ya que tardan mucho tiempo en ejecutarse.
