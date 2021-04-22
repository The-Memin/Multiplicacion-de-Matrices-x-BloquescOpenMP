/*
==========================================================================================
 * Nombre: Multiplicacion de Matrices por Bloques
 * Autor: Equipo 8 Sistemas operativos II
 * Version: 1.0.0
 * Descripcion: Algoritmo de multiplicacion de Matrices por bloque utilizando OpenMP
==========================================================================================
 */
#include "matrix.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(int argc, char *argv[])
{
    int N;
    int hilos;
    N = atoi(argv[1]);
    hilos = atoi(argv[2]);
    int a[N][N];
    int b[N][N];
    int c[N][N];

    //Inicializacion de matrices
    srand(getpid()); //implatacion de semilla para numeros aleatorios
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
           // a[i][j] = rand() % 1001 + 1000;
           // b[i][j] = rand() % 1001 + 1000;
            a[i][j] = 2;
            b[i][j] = 1;
            c[i][j] = 0;
        }    
    }
    
    //Entrando a la region paralela con openmp

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
                            c[i][j] += a[i][z] * b[z][j]; 
                        }
                        
                    }
                    
                }
                
            }
        }
    }

    //impresion de matrices
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("[%d]",a[i][j]);
            
        } 
        printf("\t");
        for (int j = 0; j < N; j++)
        {
            printf("[%d]",b[i][j]);
        }
        printf("\t");
        for (int j = 0; j < N; j++)
        {
            printf("[%d]",c[i][j]);
        } 
        printf("\n");  
    }


    return 0;
}
