/*
==========================================================================================
 * Nombre: Multiplicacion de Matrices por Bloques
 * Autor: Equipo 8 Sistemas operativos II
 * Version: 1.0.5
 * Descripcion: Algoritmo de multiplicacion de Matrices por bloque utilizando OpenMP
==========================================================================================
 */
#include "matrix.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int N = atoi(argv[1]);
    int hilos = atoi(argv[2]);
    int *A,*B;
    long *C;
    char archivo[20] = "tiempos_";
    strcat(archivo,argv[1]);
    strcat(archivo,"_");
    strcat(archivo,argv[2]);
    strcat(archivo,".txt");
    
    FILE *fp = fopen(archivo,"a"); 
    if(fp == NULL){
        perror("Error al abrir el archivo!");
        exit(0);
    }
    //rellenado de matrices
    A = alloc_matrix(N);
    B = alloc_matrix(N);
    C = alloc_matrixL(N);
    srand(getpid()); //implatacion de semilla para numeros aleatorios
    fill_matrix(A, N, rand()%1001+1000);
    fill_matrix(B, N, rand()%1001+1000);
    fill_matrixC(C, N, 0);
    
    //Entrando a la region paralela con openmp
    //clock_t start = clock();
    // Start measuring time
    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);

    for(int fb = 0; fb < hilos; fb++){
        for(int cb = 0;cb < hilos;cb++){
            #pragma omp parallel num_threads(hilos)
            {
                int id = omp_get_thread_num();
                int nt = omp_get_num_threads();
                int block = (int)N/nt;
                int inicio_i = fb * block;
                int fin_i = inicio_i + block; 
                int inicio_j = cb * block;
                int fin_j = inicio_j + block;
                int inicio_z = id * block;
                int fin_z = inicio_z + block;

                for (int i = inicio_i; i < fin_i; i++)
                {
                    for (int j = inicio_j; j < fin_j; j++)
                    {
                        for (int z = inicio_z; z < fin_z; z++)
                        {
                            #pragma omp atomic
                            C[i*N + j] += A [i*N + z] * B[z*N + j]; 
                        }
                        
                    }
                    
                }
                
            }
        }
    }
    // Stop measuring time and calculate the elapsed time
    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;

    //clock_t fin = clock();
    //double tiempo = (double)(fin - start);
    //printf("Tiempo de CPU: %.20f\n", tiempo/CLOCKS_PER_SEC);
    //printf("Tiempo de Pared: %.20f seconds.\n", elapsed);
    fprintf(fp,"%.20f\n",elapsed);
    fflush(fp);
    fclose(fp);
    return 0;
}
